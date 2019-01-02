#include <Arduino.h>
#include "Led.h"

namespace led {

LedType current_led_type;

int base_brightness_value = 255;
int base_red_value = 0;
int base_green_value = 0;
int base_blue_value = 0;

int aux_brightness_value = 255;
int aux_red_value = 0;
int aux_green_value = 0;
int aux_blue_value = 0;

// LED Value manipulation
int constrain8BitValue(int value) {
  return constrain(value, 0, 255);
}

int applyBrightness(int value) {
  long val = ((long)value * (long)aux_brightness_value) / 255;
  return (int)val;
}

int invert8BitValue(int value) {
  return 255 - value;
}

int adjustLedValue(int value) {
  int result = value;

  result = constrain8BitValue(result);

  result = applyBrightness(result);

  if (current_led_type == COMMON_ANODE) {
    result = invert8BitValue(result);
  }

  return result;
}

void commitPinValues() {
  analogWrite(LED_RED_PIN, adjustLedValue(aux_red_value));
  analogWrite(LED_GREEN_PIN, adjustLedValue(aux_green_value));
  analogWrite(LED_BLUE_PIN, adjustLedValue(aux_blue_value));
}

void setBaseColor(int red_value, int green_value, int blue_value) {
  if (DEBUG_MODE) {
    Serial.println("BaseColor set to " + String(red_value) + " " +
                   String(green_value) + ", " + String(blue_value) + ".");
  }

  base_red_value = red_value;
  base_green_value = green_value;
  base_blue_value = blue_value;
}

void setBaseBrightness(int new_brightness_value) {
  if (DEBUG_MODE) {
    Serial.println("Base brightness set to " + String(new_brightness_value));
  }

  base_brightness_value = new_brightness_value;
}

void setAuxBrightnessToBase() {
  aux_brightness_value = base_brightness_value;
}

void setAuxBrightnessValue(int aux_brightness_value) {}

void setAuxBrightnessProcent(int aux_brightness_procent) {}

void setAuxBrightnessDelta(int aux_brightness_delta) {}

void setAuxColorToBase() {
  aux_red_value = base_red_value;
  aux_green_value = base_blue_value;
  aux_blue_value = base_blue_value;
}

void setAuxColorValue(int new_aux_red_value,
                      int new_aux_green_value,
                      int new_aux_blue_value) {
  aux_red_value = constrain(new_aux_red_value, 0, 255);
  aux_green_value = constrain(new_aux_blue_value, 0, 255);
  aux_blue_value = constrain(new_aux_blue_value, 0, 255);
}

void setAuxColorProcent(int aux_red_procent,
                        int aux_green_procent,
                        int aux_blue_procent) {
  aux_red_value =
      constrain(base_red_value * (long)aux_red_procent / 100, 0, 255);
  aux_green_value =
      constrain(base_green_value * (long)aux_blue_procent / 100, 0, 255);
  aux_blue_value =
      constrain(base_blue_value * (long)aux_green_procent / 100, 0, 255);
}

void setAuxColorDelta(int aux_red_delta,
                      int aux_green_delta,
                      int aux_blue_delta) {
  aux_red_value = constrain(base_red_value + aux_red_value, 0, 255);
  aux_green_value = constrain(base_blue_value + aux_red_value, 0, 255);
  aux_blue_value = constrain(base_blue_value + aux_red_value, 0, 255);
}

void reset() {
  base_red_value = 0;
  base_green_value = 0;
  base_blue_value = 0;
  base_brightness_value = 255;
  commitPinValues();
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

  setAuxBrightnessToBase();
  setAuxColorToBase();
}

}  // namespace led