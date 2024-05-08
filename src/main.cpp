#include <Arduino.h>

#define LED_PIN 14  // Definiere den Pin, an dem die LED angeschlossen ist
#define BTN_PIN 13  // Definiere den Pin, an dem der Knopf angeschlossen ist

unsigned long startTime;
unsigned long reactionTime;
bool testActive = false;
void startReactionTest() {
  Serial.println("Bereit... Achte auf die LED!");
  delay(random(1000, 10001));  // Zufällige Verzögerung zwischen 1 und 10 Sekunden
  digitalWrite(LED_PIN, HIGH);
  startTime = millis();
  testActive = true;
  // Die LED bleibt an, bis der Benutzer reagiert
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);  // Der Knopf ist mit einem internen Pull-up-Widerstand versehen
  Serial.begin(115200);
  randomSeed(analogRead(0));  // Initialisiere den Zufallsgenerator
  Serial.println("Drücke eine Taste, um zu starten.");
}

void loop() {
  // Warte auf eine Eingabe im seriellen Monitor
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'r') {
      startReactionTest();
    }
  }

  // Überprüfe den Knopfdruck, wenn der Test aktiv ist
  if (testActive && digitalRead(BTN_PIN) == LOW) {
    digitalWrite(LED_PIN, LOW);  // Schalte die LED sofort aus
    reactionTime = millis() - startTime;
    Serial.print("Reaktionszeit: ");
    Serial.print(reactionTime);
    Serial.println(" ms");
    testActive = false;  // Setze den Teststatus zurück
    Serial.println("Drücke 'r', um erneut zu starten.");
  }
}

