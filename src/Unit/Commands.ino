#include <Arduino.h>
#include "Commands.h"

long timer;
long timer_delay = 1000;

Command currentMacro = NULL_COMMAND;
Command currentSetting = NULL_COMMAND;
String currentParameters[MAX_PARAMETERS];

int timerLapsed() {
  bool result = millis() - timer > timer_delay;
  if (DEBUG_MODE && result) {
    // Serial.println("Timer lapsed");
  }
  return result;
}

void setTimer(long delay) {
  if (DEBUG_MODE) {
    Serial.println("Timer set: " + String(delay));
  }
  timer_delay = delay;
}

void resetTimer() {
  timer = millis();
}

void setMacro(Command newMacro) {
  currentMacro = newMacro;
  isNewMacro = true;
}

void setSetting(Command newSetting) {
  currentSetting = newSetting;
  isNewSetting = true;
}

void setParameters(String newParameters[]) {
  for (int i = 0; i < MAX_PARAMETERS; i++) {
    currentParameters[i] = newParameters[i];
  }
}

void setBaseBrightness(String new_brightness_value) {
  led::setBaseBrightness(255);  // TODO
}

void setBaseColor(String red_value, String green_value, String blue_value) {
  led::setBaseColor(255, 255, 255);  // TODO
}

void applySetting() {
  if (DEBUG_MODE) {
    Serial.println("Applying setting: " + commandToString(currentSetting) +
                   ".");
  }
  switch (currentSetting) {
    case S_BASEBRIGHTNESS:
      setBaseBrightness(currentParameters[0]);
      break;
    case S_BASECOLOR:
      setBaseColor(currentParameters[0], currentParameters[1],
                   currentParameters[2]);
      break;
    case NULL_COMMAND:
    default:
      break;
  }
}

void initMacro() {
  if (DEBUG_MODE) {
    Serial.println("Initializing macro: " + commandToString(currentMacro) +
                   ".");
  }
  switch (currentMacro) {
    case M_BLINK:
      m_blink::init(currentParameters[0]);
      break;
    case M_FLICKER:
      m_flicker::init(currentParameters[0]);
      break;
    case NULL_COMMAND:
    default:
      break;
  }
}

void tickMacro() {
  switch (currentMacro) {
    case M_BLINK:
      m_blink::tick();
      break;
    case M_FLICKER:
      m_flicker::tick();
      break;
    case NULL_COMMAND:
    default:
      break;
  }
}
