#include <Arduino.h>
#include "Led.h"

namespace m_blink {
int toggle_flag = 0;

void toggle() {
  if (toggle_flag == 0) {
    led::setAuxBrightnessProcent(100);
    toggle_flag = 1;
  } else {
    led::setAuxBrightnessProcent(0);
    toggle_flag = 0;
  }
}

void tick() {
  if (timerLapsed()) {
    toggle();

    resetTimer();
  }
}

void init(String new_blink_delay) {
  setTimer(new_blink_delay.toInt());
  resetTimer();
  led::setAuxColorToBase();
  led::setAuxBrightnessToBase();
  toggle_flag = 1;
}

}  // namespace m_blink