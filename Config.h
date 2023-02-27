#ifndef Config_H
#define Config_H

char* mqtt_server = "192.168.0.99";

int led_pin = 2;

int servo_pin[] = {15, 4, 18, 13, 27, 12};
int num_servo = 6;

int stepper_step_pin[] = {26, 33, 35}; //pin 35 solo input, da cambiare
int stepper_dir_pin[] = {25, 32, 34}; //pin 34 solo input, da cambiare
int num_stepper = 2;

#endif