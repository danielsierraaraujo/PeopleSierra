#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(9600);
  Serial.println(F("Iniciando sensor DHT y pantalla OLED..."));


  dht.begin();


  Wire.begin();	
  oled.init();                
  oled.setFont(font5x7);      
  oled.clearDisplay();       
}

void loop() {
  delay(200);  

  // Lectura de temperatura y humedad
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Validación
  if (isnan(h) || isnan(t)) {
    Serial.println(F("¡Error leyendo el sensor DHT!"));
    oled.clearDisplay();
    oled.setTextXY(0, 0);
    oled.putString("Error DHT!");
    return;
  }

  // Mostrar en el monitor serial
  Serial.print(F("Humedad: "));
  Serial.print(h);
  Serial.print(F("Temp: "));
  Serial.print(t);

  // Mostrar en la pantalla OLED
  oled.clearDisplay();
  oled.setTextXY(0, 0);
  oled.putString("Temp: " + String(t, 1));
  oled.setTextXY(1, 0);
  oled.putString("Humedad: " + String(h, 1));
}
