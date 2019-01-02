#include <Arduino.h>
#include "Led.h"

namespace m_flicker {
int procent = 100;

int small_delta = 5;
int big_delta = 20;

int changeColor(int delta) {
  procent = constrain(procent + delta, 0, 100);
}

void init(String delay) {
  if (delay == "") {
    setTimerDelay(100);
  } else {
    setTimerDelay(delay.toInt());
  }

  color::setAuxColorProcent(procent, procent, procent);
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
    color::setAuxColorProcent(procent, procent, procent);
  }
}

}  // namespace m_flicker