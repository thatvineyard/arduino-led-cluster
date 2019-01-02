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

    restartTimer();
  }
}

void init(String new_blink_delay) {
  setTimerDelay(new_blink_delay.toInt());
  restartTimer();
  led::setAuxColorToBase();
  led::setAuxBrightnessToBase();
  toggle_flag = 1;
}

}  // namespace m_blink