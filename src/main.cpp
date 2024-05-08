#include <Arduino.h>

#define LED_PIN 14          // Pin für die LED
#define BTN_PIN 13          // Pin für den Reaktionsknopf
#define BTN_START_PIN 15    // Pin für den Startknopf

unsigned long startTime;
unsigned long reactionTime;
bool testActive = false;

void startReactionTest() {
  Serial.println("Bereit... Achte auf die LED!");
  digitalWrite(LED_PIN, LOW);   // Sicherstellen, dass die LED aus ist
  delay(random(1000, 10001));   // Warte eine zufällige Zeit zwischen 1 und 10 Sekunden
  digitalWrite(LED_PIN, HIGH);  // LED einschalten
  startTime = millis();         // Startzeit festlegen
  testActive = true;            // Test als aktiv markieren
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(BTN_START_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  randomSeed(analogRead(0));
  Serial.println("Drücke den Startknopf oder sende 'r' im seriellen Monitor, um zu starten.");
}

void loop() {
  // Überprüfen, ob der Startknopf gedrückt wird oder ein Befehl im seriellen Monitor vorliegt
  if (digitalRead(BTN_START_PIN) == LOW || (Serial.available() > 0 && Serial.read() == 'r')) {
    startReactionTest();
  }

  // Überprüfen, ob der Test aktiv ist und der Reaktionsknopf gedrückt wird
  if (testActive && digitalRead(BTN_PIN) == LOW) {
    digitalWrite(LED_PIN, LOW); // LED ausschalten
    reactionTime = millis() - startTime; // Reaktionszeit berechnen
    Serial.print("Reaktionszeit: ");
    Serial.print(reactionTime);
    Serial.println(" ms");
    testActive = false; // Test als nicht aktiv markieren
    Serial.println("Drücke den Startknopf oder sende 'r', um erneut zu starten.");
  }
}
