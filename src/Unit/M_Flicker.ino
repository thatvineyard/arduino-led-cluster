#include <Arduino.h>
#include "Led.h"

namespace m_flicker {
int procent = 100;
int minimum = 50;

int small_delta = 5;
int big_delta = 20;

int changeColor(int delta) {
  procent = constrain(procent + delta, minimum, 100);
}

void init(int delay,
          int minimum_procent) {  // TODO: Handle parameters as 0-255
  if (delay == -1) {
    setTimerDelay(30);
  } else {
    setTimerDelay(delay);
  }
  if (minimum_procent == -1) {
    minimum = 80;
  } else {
    minimum = constrain(minimum_procent, 0, 100);
  }

  color::setAuxBrightnessProcent(procent);
  restartTimer();
}

void tick() {
  if (timerLapsed()) {
    restartTimer();
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
    color::setAuxColorToBase();
    color::setAuxBrightnessProcent(procent);
  }
}

}  // namespace m_flicker