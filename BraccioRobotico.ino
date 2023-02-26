#include "MQTTmanager.h"
char* mqtt_server = "192.168.0.99";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Booting");

  wifi_init(mqtt_server);

  pinMode(2, OUTPUT);
}

void loop() {
  mqtt_loop();

  if(!wifi_isConnected()){
    digitalWrite(2, LOW);
  }
  else{
    digitalWrite(2, HIGH);
  }
}