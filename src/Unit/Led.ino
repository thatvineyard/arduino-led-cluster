#include <Arduino.h>
#include "Led.h"

namespace led {

LedType current_led_type;

// LED Value manipulation
int constrain8BitValue(int value) {
  return constrain(value, 0, 255);
}

int invert8BitValue(int value) {
  return 255 - value;
}

int adjustLedValue(int value) {
  int result = value;

  result = constrain8BitValue(result);

  if (current_led_type == COMMON_ANODE) {
    result = invert8BitValue(result);
  }

  return result;
}

void setPinValues(int red_value, int green_value, int blue_value) {
  analogWrite(LED_RED_PIN, adjustLedValue(red_value));
  analogWrite(LED_GREEN_PIN, adjustLedValue(green_value));
  analogWrite(LED_BLUE_PIN, adjustLedValue(blue_value));
}

void initLed(LedType led_type) {
  current_led_type = led_type;
  // Turn on LED_PIN
  if (current_led_type == COMMON_CATHODE) {
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);
  } else {
    pinMode(LED_RED_PIN, INPUT);
    pinMode(LED_GREEN_PIN, INPUT);
    pinMode(LED_BLUE_PIN, INPUT);
  }
}

}  // namespace led