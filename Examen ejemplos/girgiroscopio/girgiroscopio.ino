#include <Arduino_LSM6DS3.h>
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>  // Usa esta si tu pantalla OLED usa esta librería

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Wire.begin();        // Inicializa I2C
  oled.init();         // Inicializa la pantalla OLED
  oled.setFont(font5x7);
  oled.clearDisplay();

  if (!IMU.begin()) {
    oled.setTextXY(0, 0);
    oled.putString("IMU ERROR");
    while (1);  // Detiene ejecución
  }

  oled.setTextXY(0, 0);
  oled.putString("Gyro Ready!");
  delay(1000);  // Mensaje de inicio
  oled.clearDisplay();
}

void loop() {
  float x, y, z;

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

    oled.clearDisplay();  // Limpia pantalla
    oled.setTextXY(0, 0);
    oled.putString("Gyroscope");

    oled.setTextXY(1, 0);
    oled.putString("X: " + String(x, 2) + " d/s");

    oled.setTextXY(2, 0);
    oled.putString("Y: " + String(y, 2) + " d/s");

    oled.setTextXY(3, 0);
    oled.putString("Z: " + String(z, 2) + " d/s");

    delay(500);  // Refresco cada 200 ms
  }
}
