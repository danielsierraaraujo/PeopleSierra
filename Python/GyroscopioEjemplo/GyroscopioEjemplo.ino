#include <Arduino_LSM6DS3.h>

const int led1 = 10;
const int led2 = 9;
const int led3 = 6;

// Umbral de giro mínimo para considerar "movimiento"
const float limiteX = 1;
const float limiteY = 1;
const float limiteZ = 0.2;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  if (!IMU.begin()) {
    Serial.println("¡Fallo al iniciar el IMU!");
    while (1);
  }

  Serial.print("Tasa de muestreo del giroscopio = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println("Giroscopio en grados/segundo");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);

    // Verificar umbral de giro en cada eje
    if (abs(x) > limiteX) {
      digitalWrite(led1, HIGH);
    } else {
      digitalWrite(led1, LOW);
    }

    if (abs(y) > limiteY) {
      digitalWrite(led2, HIGH);
    } else {
      digitalWrite(led2, LOW);
    }

    if (abs(z) > limiteZ) {
      digitalWrite(led3, HIGH);
    } else {
      digitalWrite(led3, LOW);
    }

    delay(150);
  }
}
