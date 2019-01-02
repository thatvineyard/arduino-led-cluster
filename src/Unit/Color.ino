#include <Arduino.h>

namespace color {

int base_brightness_value = 255;
int base_red_value = 0;
int base_green_value = 0;
int base_blue_value = 0;

int aux_brightness_value = 255;
int aux_red_value = 0;
int aux_green_value = 0;
int aux_blue_value = 0;

int applyBrightness(int value) {
  long val = ((long)value * (long)aux_brightness_value) / 255;
  return (int)val;
}

void displayColor() {
  led::setPinValues(applyBrightness(aux_red_value),
                    applyBrightness(aux_green_value),
                    applyBrightness(aux_blue_value));
}

void setBaseColor(int red_value, int green_value, int blue_value) {
  log("BaseColor set to " + String(red_value) + " " + String(green_value) +
      ", " + String(blue_value) + ".");

  base_red_value = red_value;
  base_green_value = green_value;
  base_blue_value = blue_value;
}
void setBaseBrightness(int new_brightness_value) {
  log("Base brightness set to " + String(new_brightness_value));

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

void resetBaseValues() {
  base_red_value = 0;
  base_green_value = 0;
  base_blue_value = 0;
  base_brightness_value = 255;
}

}  // namespace color