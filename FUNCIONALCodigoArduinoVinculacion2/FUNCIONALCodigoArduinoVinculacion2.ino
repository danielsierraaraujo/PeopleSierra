#include <Wire.h>                               // Librería para comunicación I2C
#include "MAX30105.h"                           // Librería para el sensor MAX30105
#include "heartRate.h"                          // Librería para el cálculo de la frecuencia cardíaca
#include "ACROBOTIC_SSD1306.h"                  // Librería para controlar la pantalla OLED
MAX30105 particleSensor;                        // Instancia del objeto para el sensorMAX30105

const byte RATE_SIZE = 4;                       // Número de muestras para promediar, 4 esuna buena cantidad
byte rates[RATE_SIZE];                          // Arreglo para almacenar las lecturas defrecuencia cardíaca
byte rateSpot = 0;                              // Índice para el arreglo de tasas
long lastBeat = 0;                              // Tiempo en el que ocurrió el últimolatido 
float beatsPerMinute;                           // Frecuencia cardíaca en BPM
int beatAvg;   

const int luzPin = 16;   

// LEDs
const int ledVerde = 10;
const int ledAmarillo = 9;
const int ledRojo = 6;

void setup() {
  Serial.begin(115200);  // Inicia la comunicación serie con la velocidad de 115200 baudios
    Serial.println("Initializing...");
  // Inicializa el sensor MAX30105
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))  // Usa el puerto I2C por defecto a 400 kHz de velocidad 
  {
Serial.println("MAX30105 no encontrado. Verifique las conexiones o alimentación.");
while (1); // Si el sensor no se inicializa, detiene el programa
    }
  Serial.println("Coloca tu dedo en el sensor con presión constante.");
  // Configura el sensor con los valores predeterminados
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);  // Configura el LED rojo a baja intensidad
    particleSensor.setPulseAmplitudeGreen(0);  // Apaga el LED verde
  // Inicializa la pantalla OLED
  oled.init();          // Inicializa la pantalla OLED
  oled.clearDisplay();  // Limpia la pantalla
}

unsigned long lastOledUpdate = 0;  // Controla cuándo se actualiza la pantalla
const unsigned long oledInterval = 200; // Actualizar cada 200 ms


void loop() 

{ 

long irValue = particleSensor.getIR(); // Lee el valor IR del sensor 

if (checkForBeat(irValue) == true) // Si se detecta un latido 

{ 

// Se detectó un latido 

long delta = millis() - lastBeat; // Calcula el tiempo transcurrido  desde el último latido 

lastBeat = millis(); // Actualiza el tiempo del último  latido 

beatsPerMinute = 60 / (delta / 1000.0); // Calcula los latidos por  minuto (BPM) 

if (beatsPerMinute < 255 && beatsPerMinute > 20) // Si el BPM es  válido 

{ 

rates[rateSpot++] = (byte)beatsPerMinute; // Guarda el valor en el  arreglo 

rateSpot %= RATE_SIZE; // Hace que el índice  vuelva a cero cuando llega al tamaño del arreglo 

// Calcula el promedio de los BPM 

beatAvg = 0; 

for (byte x = 0 ; x < RATE_SIZE ; x++) 

beatAvg += rates[x]; // Suma los BPM en el  arreglo 

beatAvg /= RATE_SIZE; // Calcula el promedio 

} 

} 


  // Leer luminosidad
  int valorLuz = analogRead(luzPin);
  

Serial.println(valorLuz);

Serial.println(beatAvg);


int lastBpmShown = -1;
String lastFingerState = "";

if (millis() - lastOledUpdate > oledInterval) {
  lastOledUpdate = millis();

  int dato_oled = round(beatAvg);
  String texto = "BPM=" + String(dato_oled);
  String estadoDedo = (irValue < 50000) ? "No dedo" : "Si dedo";


     if (dato_oled != lastBpmShown || estadoDedo != lastFingerState) {
    oled.setTextXY(0, 0);
    oled.putString("                ");
    oled.setTextXY(0, (16 - texto.length()) / 2);
    oled.putString(texto.c_str());

    oled.setTextXY(1, 0);
    oled.putString("                ");
    oled.setTextXY(1, 4);
    oled.putString(estadoDedo.c_str());

    lastBpmShown = dato_oled;
    lastFingerState = estadoDedo;
  }

    // Mostrar luminosidad
    oled.setTextXY(2, 0);
    oled.putString("                ");
    oled.setTextXY(2, 0);
    oled.putString(("Luz=" + String(valorLuz)).c_str());

    // Control de LEDs según BPM
  if (beatAvg < 20 || valorLuz <= 100) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, LOW);
  } else if (beatAvg <= 50 || valorLuz <= 500) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledRojo, LOW);
  } else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, HIGH);
  }
  
  delay(100);
}
} 
