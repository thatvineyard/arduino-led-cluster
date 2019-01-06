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

void setBaseSpeed(int new_base_speed) { base_speed = new_base_speed; }

bool timerLapsed() {
  bool result = millis() - timer > timer_delay;
  return result;
}

void setTimerDelay(long delay) {
  // log("Timer set: " + String(delay) + "(+" + base_speed + "%)");

  timer_delay = (int)((long)delay * (long)base_speed / 100);
}

void restartTimer() { timer = millis(); }

String andSelector(String selector_one, String selector_two) {
  if (selector_one == "") {
    return selector_two;
  }
  if (selector_two == "") {
    return selector_one;
  }
  return selector_one + DELIM_SELECTOR_AND + selector_two;
}

String orSelector(String selector_one, String selector_two) {
  if (selector_one == "") {
    return selector_two;
  }
  if (selector_two == "") {
    return selector_one;
  }
  return selector_one + DELIM_SELECTOR_OR + selector_two;
}

void andSelector(char* selector_one, char* selector_two) {
  char new_regex[MAX_REGEX_LENGTH];
  if (strcmp(selector_one, "") == 0) {
    strcpy(selector_one, selector_two);
  } else {
    if (strcmp(selector_two, "") == 0) {
    } else {
      sprintf(new_regex, "%s%c%s", selector_one, DELIM_SELECTOR_AND,
              selector_two);
      strcpy(selector_one, new_regex);
    }
  }
}

void orSelector(char* selector_one, char* selector_two) {
  char new_regex[MAX_REGEX_LENGTH];
  if (strcmp(selector_one, "") == 0) {
    strcpy(selector_one, selector_two);
  } else {
    if (strcmp(selector_two, "") == 0) {
    } else {
      sprintf(new_regex, "%s%c%s", selector_one, DELIM_SELECTOR_OR,
              selector_two);
      strcpy(selector_one, new_regex);
    }
  }
}

long hash(char* str) {
  long hash = 5381;
  int c;

  while (c = *str++) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}