#include <Arduino.h>

bool timerLapsed() {
  bool result = millis() - timer > timer_delay;
  return result;
}

void setTimerDelay(long delay) {
  log("Timer set: " + String(delay));

  timer_delay = delay;
}

void restartTimer() {
  timer = millis();
}
