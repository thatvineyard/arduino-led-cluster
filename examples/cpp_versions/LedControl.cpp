#include <Arduino.h>
#include "LedControl.h"
#include "Commands.h"

#define LED_RED_PIN 9
#define LED_GREEN_PIN 10
#define LED_BLUE_PIN 11

int brightness_procent = 5;
int fade_time_bpm = 60;

int current_red_value;
int current_green_value;
int current_blue_value;

int invert8BitValue(int value) { return 255 - value; }

int constrain8BitValue(int value) { return constrain(value, 0, 255); }

int adjustBrightness(int value) { return (value * brightness_procent) / 100; }

int adjustLedValue(int value) {
  int result = value;
  result = constrain8BitValue(result);
  result = adjustBrightness(result);
  result = invert8BitValue(result);

  return result;
}

void setColor(int red_value, int green_value, int blue_value) {
  current_red_value = red_value;
  current_green_value = green_value;
  current_blue_value = blue_value;

  analogWrite(LED_RED_PIN, adjustLedValue(current_red_value));
  analogWrite(LED_GREEN_PIN, adjustLedValue(current_green_value));
  analogWrite(LED_BLUE_PIN, adjustLedValue(current_blue_value));
}

void switchColor() {
  setColor(current_blue_value, current_red_value, current_green_value);
}

void blink() {
  if (timerLapsed()) {
    switchColor();

    resetTimer();
  }
}

void init_blink() {
  // Turn on LED_PIN
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  resetTimer();
  setColor(255, 0, 0);
}