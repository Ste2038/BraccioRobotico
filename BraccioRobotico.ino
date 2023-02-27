#include "Config.h"
#include "ServoManager.h"
#include "StepperManager.h"
//#include "MQTTmanager.h"

//#include <Servo.h>
//Servo servos[];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Booting");

  stepper_init(stepper_step_pin, stepper_dir_pin, num_stepper);
  //servo_init(servos, servo_pin, num_servo);
  //wifi_init(mqtt_server);
  
  pinMode(led_pin, OUTPUT);
  Serial.println("Ready!");
}

void loop() {
  /*mqtt_loop();

  if(!wifi_isConnected()){
    digitalWrite(led_pin, LOW);
  }
  else{
    digitalWrite(led_pin, HIGH);
  }*/
}

void serialEvent() {
  while (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    int dashIndex = message.indexOf('-');
    int mot = message.substring(0, dashIndex).toInt();
    int angle = message.substring(dashIndex + 1).toInt();
    Serial.print(mot);
    Serial.print(".");
    Serial.println(angle);
  }
}