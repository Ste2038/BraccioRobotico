#include "MQTTmanager.h"
//#include "Config.h"

WiFiClient espClient;
PubSubClient client(espClient);

void mqtt_callback(char* topic, byte* message, unsigned int length);

/* PUBLIC */

void wifi_init(char* mqtt_server) {
  WiFi.mode(WIFI_STA);  // explicitly set mode, esp defaults to STA+AP
  // it is a good practice to make sure your code sets wifi mode how you want it.

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  //wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result

  /* ADD ADDITIONAL PARAMETERS */
  WiFiManagerParameter custom_text_box("my_text", "Enter your string here", "default string", 50);
  wm.addParameter(&custom_text_box);

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("TestAP", "password");  // password protected ap

  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  } else {
    //if you get here you have connected to the WiFi

    //Connection to Mqtt server
    client.setServer(mqtt_server, 1883);
    client.setCallback(mqtt_callback);

    ota_init("Admin");

    Serial.println("connected...yeey :)");
  }
}

bool wifi_isConnected() {
  return client.connected();
}

void mqtt_loop(){
  if(!wifi_isConnected()){
    mqtt_reconnect();
    if(!wifi_isConnected()){
      delay(5000);
    }
  }
  client.loop();

  ArduinoOTA.handle();
}

//Function used to reconnect with mqtt broker after connection is lost.
void mqtt_reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      mqtt_subscribeAll();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
    }
  }
}

void mqtt_subscribe(char* topic){
  client.subscribe(topic);
}

void mqtt_subscribeAll(){
  /*if(num_stepper >= 1)
    mqtt_subscribe("Braccio/Motori/Stepper1/set");
  if(num_stepper >= 2)
    mqtt_subscribe("Braccio/Motori/Stepper2/set");
  if(num_stepper >= 3)
    mqtt_subscribe("Braccio/Motori/Stepper3/set");

  if(num_servo >= 1)
    mqtt_subscribe("Braccio/Motori/Servo1/set");
  if(num_servo >= 2)
    mqtt_subscribe("Braccio/Motori/Servo2/set");
  if(num_servo >= 3)
    mqtt_subscribe("Braccio/Motori/Servo3/set");
  if(num_servo >= 4)
    mqtt_subscribe("Braccio/Motori/Servo4/set");
  if(num_servo >= 5)
    mqtt_subscribe("Braccio/Motori/Servo5/set");
  if(num_servo >= 6)
    mqtt_subscribe("Braccio/Motori/Servo6/set");*/
}

void mqtt_publish(char* topic, char* payload){
  client.publish(topic, payload);
}

void mqtt_publish(char* topic, int payload){
  char tmpChars[8];
  dtostrf(payload, 1, 0, tmpChars);

  client.publish(topic, tmpChars);
}

void ota_init(char* psw){
  ArduinoOTA.setPassword(psw);
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
}

/* PRIVATE */

//Function called every time a new payload is published on a subriscribed topic
void mqtt_callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  char* messageTempChar = (char*) malloc(length * sizeof(char));
  int i = 0;
  int numPassi = 0;

  for (i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
    messageTempChar[i] = (char)message[i];
  }
  messageTempChar[i] = '\0';
  Serial.println();

  numPassi = messageTemp.toInt();
  Serial.println(numPassi);

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  /*if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      //digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      //digitalWrite(ledPin, LOW);
    }
  }*/

  if(String(topic) == "Braccio/Motori/Stepper1/set"){
    mqtt_publish("Braccio/Motori/Stepper1", messageTempChar);
    for(int i = 0; i < numPassi; i++){
      digitalWrite(26, HIGH);
      delay(1);
      digitalWrite(26, LOW);
      delay(10);
    }
  }
  else if(String(topic) == "Braccio/Motori/Stepper2/set"){
    mqtt_publish("Braccio/Motori/Stepper2", messageTempChar);

    for(int i = 0; i < numPassi; i++){
      digitalWrite(33, HIGH);
      delay(1);
      digitalWrite(33, LOW);
      delay(100);
    }
  }
}