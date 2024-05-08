#include <Arduino.h>
#define LED_PIN 14  
#define BTN_PIN 13  
#define BTN_Start_PIN 15
unsigned long startTime;
unsigned long reactionTime;
bool testActive = false;
void startReactionTest() {
  Serial.println("Bereit... Achte auf die LED!");
  delay(random(1000, 10001));  
  digitalWrite(LED_PIN, HIGH);
  startTime = millis();
  testActive = true;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);  
  pinMode(BTN_Start_PIN, INPUT_PULLUP);  
  Serial.begin(115200);
  randomSeed(analogRead(0));  
  Serial.println("Drücke eine Taste, um zu starten.");
      if (digitalRead(BTN_Start_PIN) == LOW) {
      startReactionTest();
    }
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (digitalRead(BTN_Start_PIN) == LOW | command == 'r') {
      startReactionTest();
    }
  }

  if (testActive && digitalRead(BTN_PIN) == LOW) {
    digitalWrite(LED_PIN, LOW);  
    reactionTime = millis() - startTime;
    Serial.print("Reaktionszeit: ");
    Serial.print(reactionTime);
    Serial.println(" ms");
    testActive = false;  
    Serial.println("Drücke 'BTN4', um erneut zu starten.");
  }
}

