#include <Arduino.h>
#include "Led.h"

namespace m_colorshift {
int red = 100;
int blue = 100;
int green = 100;
int minimum_value = 100;
int step_size = 1;

void init(int delay, int new_step_size, int new_minimum_value) {
  minimum_value = new_minimum_value;
  step_size = new_step_size;
  red = minimum_value;
  green = minimum_value;
  blue = minimum_value;
}

void tick() {
  randomSeed(millis();
  if(red < minimum_value) {
    red = red + random(step_size);
  } else {
    red =
        constrain(red + random(step_size * -1, step_size), minimum_value, 255);
  }
  if(green < minimum_value) {
    green = green + random(step_size);
  } else {
    green = constrain(green + random(step_size * -1, step_size), minimum_value,
                      255);
  }
  if(blue < minimum_value) {
    blue = blue + random(step_size);
  } else {
    blue =
        constrain(blue + random(step_size * -1, step_size), minimum_value, 255);
  }
  color::setAuxColorValue(red, green, blue);
}

}  // namespace m_colorshift