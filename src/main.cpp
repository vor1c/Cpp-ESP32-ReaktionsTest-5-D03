#include <Arduino.h>

#define LED_PIN 14
#define BTN_PIN 13
#define BTN_START_PIN 15

#define LEDV1 14
#define LEDV2 27
#define LEDV3 32
#define LEDV4 33

unsigned long startTime;
unsigned long reactionTime;
bool testActive = false;

void ledlauflicht()
{
  digitalWrite(LEDV1, HIGH);
  delay(100);
  digitalWrite(LEDV1, LOW);
  digitalWrite(LEDV2, HIGH);
  delay(100);
  digitalWrite(LEDV2, LOW);
  digitalWrite(LEDV3, HIGH);
  delay(100);
  digitalWrite(LEDV3, LOW);
  digitalWrite(LEDV4, HIGH);
  delay(100);
  digitalWrite(LEDV4, LOW);
}

void startReactionTest()
{
  ledlauflicht();
  Serial.println("Bereit... Achte auf die LED!");
  digitalWrite(LED_PIN, LOW);
  delay(random(1000, 10001));
  digitalWrite(LED_PIN, HIGH);
  startTime = millis();
  testActive = true;
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(LEDV1, OUTPUT);
  pinMode(LEDV2, OUTPUT);
  pinMode(LEDV3, OUTPUT);
  pinMode(LEDV4, OUTPUT);

  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(BTN_START_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  randomSeed(analogRead(0));
  Serial.println("Drücke den Startknopf oder sende 'r' im seriellen Monitor, um zu starten.");
}

void loop()
{

  if (digitalRead(BTN_START_PIN) == LOW || (Serial.available() > 0 && Serial.read() == 'r'))
  {
    startReactionTest();
  }

  if (testActive && digitalRead(BTN_PIN) == LOW)
  {
    digitalWrite(LED_PIN, LOW);
    reactionTime = millis() - startTime;
    Serial.print("Reaktionszeit: ");
    Serial.print(reactionTime);
    Serial.println(" ms");
    testActive = false;
    Serial.println("Drücke den Startknopf oder sende 'r', um erneut zu starten.");
    ledlauflicht();
  }
}
