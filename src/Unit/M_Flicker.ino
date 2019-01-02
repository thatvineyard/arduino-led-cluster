#include <Arduino.h>
#include "Led.h"

namespace m_flicker {
int red_value = 255;
int green_value = 50;
int blue_value = 0;

int small_delta = 5;
int big_delta = 20;

int changeColor(int delta) {
  red_value = constrain(red_value + delta, 150, 255);
  green_value = constrain(green_value + delta, 30, 80);
  blue_value = constrain(blue_value + delta, 0, 0);
}

void init(String delay) {
  if (delay == "") {
    setTimer(100);
  } else {
    setTimer(delay.toInt());
  }

  // led::setColor(red_value, green_value, blue_value);
  resetTimer();
}

void tick() {
  if (timerLapsed()) {
    // led::setColor(red_value, green_value, blue_value);
    resetTimer();
    switch (random(0, 5)) {
      case 0:  // go down big
        changeColor(big_delta * -1);
        break;

      case 1:  // go down small
        changeColor(small_delta * -1);
        break;

      case 2:  // stay
        break;

      case 3:  // go up small
        changeColor(small_delta);
        break;

      case 4:  // go up big
        changeColor(big_delta);
        break;

      default:
        break;
    }
  }
}

}  // namespace m_flicker