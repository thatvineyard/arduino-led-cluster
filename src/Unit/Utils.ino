#include <Arduino.h>

int base_speed = 100;

String createId(char column, int row) {
  char id_string[3];
  sprintf(id_string, "%c%03u", column, row);
  return id_string;
}

void log(String message) {
  // if (DEBUG_MODE) {
  Serial.println(message);
  // }
}

void setTimerBaseSpeed(int new_base_speed) { base_speed = new_base_speed; }

bool timerLapsed() {
  bool result = millis() - timer > timer_delay;
  return result;
}

void setTimerDelay(long delay) {
  log("Timer set: " + String(delay) + "(+" + base_speed + "%)");

  timer_delay = (int)((long)delay * (long)base_speed / 100);
}

void restartTimer() { timer = millis(); }

unsigned long hash(unsigned char *str) {
  unsigned long hash = 5381;
  int c;

  while (c = *str++) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

int mapScale(Scale scale, int result_minimum, int result_maximum,
             int input_minimum, int input_maximum, int input) {
  if (result_minimum >= result_maximum || input_minimum >= input_maximum) {
    return result_maximum;
  }

  int result_difference = result_maximum - result_minimum;
  int input_difference = input_maximum - input_minimum;

  if (scale == LINEAR) {
    return result_minimum +
           ((long)input * (long)result_difference / input_difference);
  }
  // if (scale == EXPONENTIAL) {
  // }
  if (scale == QUADRATIC) {
    return result_minimum + (long)input * (long)input /
                                (((long)input_difference) *
                                 ((long)input_difference) / result_difference);
  }
}

int mapScale(Scale scale, int result_maximum, int input_maximum, int input) {
  return mapScale(scale, 0, result_maximum, 0, input_maximum, input);
}