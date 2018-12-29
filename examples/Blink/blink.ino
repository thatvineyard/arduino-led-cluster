#include <Arduino.h>

#define LED_COMMON 6
#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11

void setup() {

    pinMode(LED_COMMON, INPUT);
    pinMode(LED_RED,   OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE,  OUTPUT);
}

void loop() {

    delay(1000);
    digitalWrite(LED_COMMON, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);

    delay(1000);
    digitalWrite(LED_COMMON, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, LOW);
}