#include "StepperManager.h"

void stepper_init(int step[], int dir[], int num){
  for(int i = 0; i < num; i++){
    pinMode(step[i], OUTPUT);
    pinMode(dir[i], OUTPUT);

    digitalWrite(step[i], LOW);
    digitalWrite(dir[i], LOW);
  }
}
