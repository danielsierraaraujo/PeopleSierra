#include <Servo.h>

Servo myservo;         // Crea el objeto servo
int potPin = 14;       // Pin donde está conectado el potenciómetro
int valorPot;          // Valor leído del potenciómetro (0 a 1023)
int angulo;            // Ángulo calculado para el servo (0 a 180)

void setup() {
  myservo.attach(6);   // Conecta el servo al pin digital 6
}

void loop() {
  valorPot = analogRead(potPin);          // Lee el valor del potenciómetro
  angulo = map(valorPot, 0, 1023, 0, 180); // Convierte ese valor a un ángulo de servo
  myservo.write(angulo);                  // Mueve el servo a ese ángulo
  delay(15);                              // Espera pequeña para suavizar el movimiento
}
