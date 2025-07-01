#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const int led_RED = 9,
            led_YELLOW = 10,
            led_GREEN = 6;

const int BTN_PIN = 20;

bool showTemp = true;
bool lastBtn = HIGH;

unsigned long lastDebounce = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led_RED, OUTPUT);
  pinMode(led_YELLOW, OUTPUT);
  pinMode(led_GREEN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  clearLeds();
  dht.begin();
}

void clearLeds() {
  digitalWrite(led_RED, LOW);
  digitalWrite(led_YELLOW, LOW);
  digitalWrite(led_GREEN, LOW);
}


