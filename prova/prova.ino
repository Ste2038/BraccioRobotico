#include <ESP32_Servo.h>
Servo myservo1;  // crea l'oggetto di tipo Servo, myservo sarà l'oggetto su cui opererai
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
void setup() {
  myservo1.attach(18);  // lega l'oggetto myservo al pin a cui abbiamo collegato il nostro servo, in questo caso il pin 8
  myservo2.attach(4);
  myservo3.attach(15);
  myservo4.attach(13);
  myservo5.attach(13);
  myservo6.attach(13);
  Serial.begin(9600);
    myservo1.write(90);//inizializz
    myservo2.write(90);
    myservo3.write(90);
    myservo4.write(90);
    myservo5.write(90);
    myservo6.write(90);
}
char tmp;
int mot=0;
int cnt=0;
int angolo=0;
int dato1=0;
int dato2=0;
int dato3=0;
int a=0;
//limiti
//gomito 2-9
void loop() {

   if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int dashIndex = input.indexOf('-');
    mot = input.substring(0, dashIndex).toInt();
    angolo = input.substring(dashIndex + 1).toInt();
     Serial.print("mot selez: ");
    Serial.println(mot);
    Serial.print("angolo: ");
    Serial.println(angolo);

    switch (mot) {
  case 1:
   myservo1.write(angolo);
  mot=0;
    break;
  case 2:
   myservo2.write(angolo);
   mot=0;
    break;
   case 3:
   myservo3.write(angolo);
   mot=0;
   break;
   case 4:
   myservo4.write(angolo);
   mot=0;
   break;
    case 5:
   myservo5.write(angolo);
  mot=0;
    break;
  case 6:
   myservo6.write(angolo);
   mot=0;
    break;
  default:
    Serial.println("motore non esistente");
    break;

  }
   }

}
 
