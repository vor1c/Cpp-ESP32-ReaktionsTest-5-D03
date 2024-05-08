#include <Arduino.h>

#define LED_PIN 14          
#define BTN_PIN 13          
#define BTN_START_PIN 15    

unsigned long startTime;
unsigned long reactionTime;
bool testActive = false;
unsigned long lastButtonPressTime = 0;
unsigned long debounceDelay = 50;

void startReactionTest() {
  Serial.println("Bereit... Achte auf die LED!");
  digitalWrite(LED_PIN, LOW);   
  delay(random(1000, 10001));   
  digitalWrite(LED_PIN, HIGH);  
  startTime = millis();         
  testActive = true;            
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(BTN_START_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  randomSeed(analogRead(0));
  Serial.println("Drücke den Startknopf oder sende 'r' oder 'd <ms>' im seriellen Monitor, um zu starten bzw. Debounce-Zeit zu setzen.");
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'd') {
      debounceDelay = Serial.parseInt();
      Serial.print("Debounce-Zeit gesetzt auf: ");
      Serial.print(debounceDelay);
      Serial.println(" ms");
    } else if (c == 'r') {
      startReactionTest();
    }
  }

  unsigned long currentMillis = millis();

  // Startknopf Debouncing
  if (digitalRead(BTN_START_PIN) == LOW) {
    if (currentMillis - lastButtonPressTime > debounceDelay) {
      lastButtonPressTime = currentMillis;
      startReactionTest();
    }
  }

  // Reaktionsknopf Debouncing
  if (testActive && digitalRead(BTN_PIN) == LOW) {
    if (currentMillis - lastButtonPressTime > debounceDelay) {
      digitalWrite(LED_PIN, LOW);
      reactionTime = currentMillis - startTime;
      Serial.print("Reaktionszeit: ");
      Serial.print(reactionTime);
      Serial.println(" ms");
      testActive = false;
      Serial.println("Drücke den Startknopf oder sende 'r', um erneut zu starten.");
      lastButtonPressTime = currentMillis;
    }
  }
}
