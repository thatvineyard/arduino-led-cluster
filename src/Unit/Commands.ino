#include <Arduino.h>
#include "Commands.h"

long timer;
long timer_delay = 1000;

Command currentMacro = NULL_COMMAND;
Command currentSetting = NULL_COMMAND;
String currentParameters[MAX_PARAMETERS];

Command stringToCommand(String string_to_convert) {
  string_to_convert.toUpperCase();
  if (string_to_convert == "NULL_COMMAND") {
    return NULL_COMMAND;
  }
  if (string_to_convert == "STOP") {
    return STOP;
  }
  if (string_to_convert == "S_BASECOLOR") {
    return S_BASECOLOR;
  }
  if (string_to_convert == "S_BASEBRIGHTNESS") {
    return S_BASEBRIGHTNESS;
  }
  if (string_to_convert == "M_BLINK") {
    return M_BLINK;
  }
  if (string_to_convert == "M_FLICKER") {
    return M_FLICKER;
  }

  return NULL_COMMAND;
}

String commandToString(Command command_to_convert) {
  if (command_to_convert == NULL_COMMAND) {
    return "NULL_COMMAND";
  }
  if (command_to_convert == STOP) {
    return "STOP";
  }
  if (command_to_convert == S_BASECOLOR) {
    return "S_BASECOLOR";
  }
  if (command_to_convert == S_BASEBRIGHTNESS) {
    return "S_BASEBRIGHTNESS";
  }
  if (command_to_convert == M_BLINK) {
    return "M_BLINK";
  }
  if (command_to_convert == M_FLICKER) {
    return "M_FLICKER";
  }

  return "NULL_COMMAND";
}

bool isSetting(Command command_to_check) {
  return ((command_to_check == S_BASEBRIGHTNESS) ||
          (command_to_check == S_BASECOLOR));
}

bool isMacro(Command command_to_check) {
  return ((command_to_check == M_BLINK) || (command_to_check == M_SOLID) ||
          (command_to_check == M_FLICKER));
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
  color::setBaseBrightness(255);  // TODO
}

void setBaseColor(String red_value, String green_value, String blue_value) {
  color::setBaseColor(255, 255, 255);  // TODO
}

void applySetting() {
  log("Applying setting: " + commandToString(currentSetting) + ".");
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
  log("Initializing macro: " + commandToString(currentMacro) + ".");
  switch (currentMacro) {
    case M_BLINK:
      m_blink::init(currentParameters[0]);
      break;
    case M_FLICKER:
      m_flicker::init(currentParameters[0]);
      break;
    case M_SOLID:
      m_solid::init();
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
    case M_SOLID:
      m_solid::tick();
      break;
    case NULL_COMMAND:
    default:
      break;
  }
}
