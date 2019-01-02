#include <Arduino.h>

int base_speed = 100;

String createId(char column, int row) {
  char id_string[3];
  sprintf(id_string, "%c%03u", column, row);
  return id_string;
}

void log(String message) {
  if (DEBUG_MODE) {
    Serial.println(message);
  }
}

void setBaseSpeed(int new_base_speed) {
  base_speed = new_base_speed;
}

bool timerLapsed() {
  bool result = millis() - timer > timer_delay;
  return result;
}

void setTimerDelay(long delay) {
  log("Timer set: " + String(delay) + "(+" + base_speed + "%)");

  timer_delay = (int)((long)delay * (long)base_speed / 100);
}

void restartTimer() {
  timer = millis();
}
