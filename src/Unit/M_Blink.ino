#include <Arduino.h>
#include "Led.h"

namespace m_blink {
int toggle_flag = 0;

void toggle() {
  if (toggle_flag == 0) {
    toggle_flag = 1;
  } else {
    toggle_flag = 0;
  }
}

void tick() {
  if (timerLapsed()) {
    toggle();
    restartTimer();
  }
  color::setAuxBrightnessProcent(100 * toggle_flag);
}

void init(String new_blink_delay) {
  setTimerDelay(new_blink_delay.toInt());
  restartTimer();
  color::setAuxColorToBase();
  color::setAuxBrightnessToBase();
  toggle_flag = 1;
}

}  // namespace m_blink