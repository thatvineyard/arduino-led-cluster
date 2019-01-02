#include <Arduino.h>

bool timerLapsed() {
  bool result = millis() - timer > timer_delay;
  if (DEBUG_MODE && result) {
    // Serial.println("Timer lapsed");
  }
  return result;
}

void setTimerDelay(long delay) {
  if (DEBUG_MODE) {
    Serial.println("Timer set: " + String(delay));
  }
  timer_delay = delay;
}

void restartTimer() {
  timer = millis();
}
