#include "MQTTmanager.h"
char* mqtt_server = "192.168.0.99";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  wifi_init(mqtt_server);

  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!wifi_isConnected()){
    mqtt_reconnect();
    if(!wifi_isConnected()){
      delay(5000);
    }
  }
  mqtt_loop();

  if(!wifi_isConnected()){
    digitalWrite(2, LOW);
  }
  else{
    digitalWrite(2, HIGH);
  }
}