#include <Arduino.h>

namespace color {

enum AuxType { NONE, VALUE, PROCENT, DELTA };

int base_brightness_value = 255;
int base_red_value = 255;
int base_green_value = 30;
int base_blue_value = 0;

AuxType brightness_aux_type = NONE;
AuxType color_aux_type = NONE;

int aux_brightness_value = 255;
int aux_red_value = 0;
int aux_green_value = 0;
int aux_blue_value = 0;

int aux_brightness_procent = 0;
int aux_red_procent = 0;
int aux_blue_procent = 0;
int aux_green_procent = 0;

int aux_brightness_delta = 0;
int aux_red_delta = 0;
int aux_blue_delta = 0;
int aux_green_delta = 0;

int final_brightness_value = 0;
int final_red_value = 0;
int final_green_value = 0;
int final_blue_value = 0;

int applyBrightness(int value) {
  long val = ((long)value * (long)final_brightness_value) / 255;
  return (int)val;
}

void calculateBrightness() {
  int result = 0;

  switch (brightness_aux_type) {
    case NONE:
    default:
      result = base_brightness_value;
      break;
    case VALUE:
      result = aux_brightness_value;
      break;
    case PROCENT:
      result = (int)((long)base_brightness_value *
                     (long)aux_brightness_procent / 100);
      break;
    case DELTA:
      result = base_brightness_value + aux_brightness_delta;
      break;
  }
  result = constrain(result, 0, MAX_BRIGHTNESS);
  if (BASE_BRIGHTNESS_CONSTRAINS) {
    result = constrain(result, 0, base_brightness_value);
  }
  final_brightness_value = result;
}

void calculateColor() {
  int red_result = 0;
  int green_result = 0;
  int blue_result = 0;

  switch (color_aux_type) {
    case NONE:
    default:
      red_result = base_red_value;
      green_result = base_green_value;
      blue_result = base_blue_value;
      break;
    case VALUE:
      red_result = aux_red_value;
      green_result = aux_green_value;
      blue_result = aux_blue_value;
      break;
    case PROCENT:
      red_result = (int)((long)base_red_value * (long)aux_red_procent / 100);
      green_result =
          (int)((long)base_green_value * (long)aux_green_procent / 100);
      blue_result = (int)((long)base_blue_value * (long)aux_blue_procent / 100);
      break;
    case DELTA:
      red_result = base_red_value + aux_red_delta;
      green_result = base_green_value + aux_green_delta;
      blue_result = base_blue_value + aux_blue_delta;
      break;
  }
  red_result = constrain(red_result, 0, MAX_RED);
  green_result = constrain(green_result, 0, MAX_GREEN);
  blue_result = constrain(blue_result, 0, MAX_BLUE);

  final_red_value = red_result;
  final_green_value = green_result;
  final_blue_value = blue_result;
}

void displayColor() {
  calculateBrightness();
  calculateColor();
  led::setPinValues(applyBrightness(final_red_value),
                    applyBrightness(final_green_value),
                    applyBrightness(final_blue_value));
}

void setBaseColor(int new_red_value, int new_green_value, int new_blue_value) {
  randomSeed(millis());
  if (new_red_value == -1) {
    base_red_value = random(255);
  } else {
    base_red_value = constrain(new_red_value, 0, 255);
  }
  if (new_green_value == -1) {
    base_green_value = random(255);
  } else {
    base_green_value = constrain(new_green_value, 0, 255);
  }
  if (new_blue_value == -1) {
    base_blue_value = random(255);
  } else {
    base_blue_value = constrain(new_blue_value, 0, 255);
  }
  log("BaseColor set to " + String(base_red_value) + " " +
      String(base_green_value) + ", " + String(base_blue_value) + ".");

  displayColor();
}
void setBaseBrightness(int new_brightness_value) {
  randomSeed(millis());

  if (new_brightness_value == -1) {
    base_brightness_value = random(255);
  } else {
    base_brightness_value = constrain(new_brightness_value, 0, 255);
  }
  log("Base brightness set to " + String(base_brightness_value));

  displayColor();
}

void setAuxBrightnessToBase() {
  brightness_aux_type = NONE;
  displayColor();
}

void setAuxBrightnessValue(int new_aux_brightness_value) {
  brightness_aux_type = VALUE;
  aux_brightness_value = new_aux_brightness_value;
  displayColor();
}

void setAuxBrightnessProcent(int new_aux_brightness_procent) {
  brightness_aux_type = PROCENT;
  aux_brightness_procent = new_aux_brightness_procent;
  displayColor();
}

void setAuxBrightnessDelta(int new_aux_brightness_delta) {
  brightness_aux_type = DELTA;
  aux_brightness_delta = new_aux_brightness_delta;
  displayColor();
}

void setAuxColorToBase() {
  color_aux_type = NONE;
  displayColor();
}

void setAuxColorValue(int new_aux_red_value,
                      int new_aux_green_value,
                      int new_aux_blue_value) {
  color_aux_type = VALUE;
  aux_red_value = constrain(new_aux_red_value, 0, 255);
  aux_green_value = constrain(new_aux_blue_value, 0, 255);
  aux_blue_value = constrain(new_aux_blue_value, 0, 255);
  displayColor();
}

void setAuxColorProcent(int new_aux_red_procent,
                        int new_aux_green_procent,
                        int new_aux_blue_procent) {
  color_aux_type = PROCENT;
  aux_red_procent = new_aux_red_procent;
  aux_green_value = new_aux_green_procent;
  aux_blue_value = new_aux_blue_procent;
  displayColor();
}

void setAuxColorDelta(int new_aux_red_delta,
                      int new_aux_green_delta,
                      int new_aux_blue_delta) {
  aux_red_delta = new_aux_red_delta;
  aux_green_delta = new_aux_green_delta;
  aux_blue_delta = new_aux_blue_delta;
  displayColor();
}

}  // namespace color