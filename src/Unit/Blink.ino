#include <Arduino.h>
#include "Led.h"

namespace blink {
int red_value, green_value, blue_value;
int toggle_flag = 0;

void toggle() {
  if (toggle_flag == 0) {
    led::setColor(red_value, green_value, blue_value);
    toggle_flag = 1;
  } else {
    led::setColor(0, 0, 0);
    toggle_flag = 0;
  }
}

void tick() {
  if (timerLapsed()) {
    toggle();

    resetTimer();
  }
}

void init(String new_red_value, String new_green_value, String new_blue_value,
          String new_blink_delay) {
  setTimer(new_blink_delay.toInt());
  red_value = new_red_value.toInt();
  green_value = new_green_value.toInt();
  blue_value = new_blue_value.toInt();
  resetTimer();
  led::setColor(red_value, green_value, blue_value);
  toggle_flag = 1;
}

}  // namespace blink