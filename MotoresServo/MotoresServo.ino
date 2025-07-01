#include <Servo.h>

Servo servo1;  
Servo servo2;

const int potPin = A0; 
int angle1 = 0;        
int step = 1;          

void setup() {
  servo1.attach(6);  // Pin D6
  servo2.attach(5);  // Pin D5
}

void loop() {
 
  servo1.write(angle1);
  angle1 += step;

  
  if (angle1 >= 90 || angle1 <= 0) {
    step = -step;
  }

 
  int potValue = analogRead(potPin); 
  int angle2 = map(potValue, 0, 1023, 0, 180); 
  servo2.write(angle2);

  delay(15); 
}
