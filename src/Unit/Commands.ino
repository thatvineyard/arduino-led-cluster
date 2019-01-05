#include <Arduino.h>
#include "Commands.h"

Command currentMacro = NULL_COMMAND;
Command currentSetting = NULL_COMMAND;
String currentParameters[MAX_PARAMETERS];

bool isSetting(Command command_to_check) {
  return ((command_to_check == S_BASEBRIGHTNESS) ||
          (command_to_check == S_BASECOLOR) ||
          (command_to_check == S_BASESPEED));
}

bool isMacro(Command command_to_check) {
  return ((command_to_check == M_PULSE) || (command_to_check == M_SOLID) ||
          (command_to_check == M_SINGLEFLASH) ||
          (command_to_check == M_SOLID) || (command_to_check == M_FLICKER));
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

void setBaseBrightness(String new_base_brightness_string) {
  if (new_base_brightness_string == "") {
    color::setBaseBrightness(255);
  } else {
    color::setBaseBrightness(new_base_brightness_string.toInt());
  }
}

void setBaseColor(String new_red_string, String new_green_string,
                  String new_blue_string) {
  int new_red = 255;
  int new_green = 255;
  int new_blue = 255;

  if (new_red_string != "") {
    new_red = new_red_string.toInt();
  }
  if (new_green_string != "") {
    new_green = new_green_string.toInt();
  }
  if (new_blue_string != "") {
    new_blue = new_blue_string.toInt();
  }
  color::setBaseColor(new_red, new_green, new_blue);
}

void setBaseSpeed(String new_base_speed_string) {
  if (new_base_speed_string == "") {
    setBaseSpeed(100);
  } else {
    setBaseSpeed(new_base_speed_string.toInt());
  }
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
    case S_BASESPEED:
      setBaseSpeed(currentParameters[0]);
      break;
    case NULL_COMMAND:
    default:
      break;
  }
}

void initMacro() {
  log("Initializing macro: " + commandToString(currentMacro) + ".");
  switch (currentMacro) {
    case M_PULSE:
      m_pulse::init(currentParameters[0], currentParameters[1],
                    currentParameters[2], currentParameters[3]);
      break;
    case M_FLICKER:
      m_flicker::init(currentParameters[0], currentParameters[1]);
      break;
    case M_SOLID:
      m_solid::init();
      break;
    case M_SINGLEFLASH:
      m_singleflash::init(currentParameters[0], currentParameters[1]);
      break;
    case NULL_COMMAND:
    default:
      break;
  }
}

void tickMacro() {
  switch (currentMacro) {
    case M_PULSE:
      m_pulse::tick();
      break;
    case M_FLICKER:
      m_flicker::tick();
      break;
    case M_SOLID:
      m_solid::tick();
      break;
    case M_SINGLEFLASH:
      m_singleflash::tick();
      break;
    case NULL_COMMAND:
    default:
      break;
  }
}
