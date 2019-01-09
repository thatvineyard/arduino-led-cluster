#include <Arduino.h>
#include "Commands.h"

Command current_macro = NULL_COMMAND;
Command current_setting = NULL_COMMAND;
String current_parameters[MAX_PARAMETERS];

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

void stopCommand() {
  setMacro(NULL_COMMAND);
  is_new_macro = false;

  setSetting(NULL_COMMAND);
  is_new_setting = false;

  color::setAuxBrightnessProcent(0);
  color::setAuxColorProcent(0, 0, 0);
}

void handleNewCommand(Command new_command) {
  if (isMacro(new_command)) {
    setMacro(new_command);
  } else if (isSetting(new_command)) {
    setSetting(new_command);
  } else if (new_command = STOP) {
    stopCommand();
  }
}

void setMacro(Command new_macro) {
  current_macro = new_macro;
  is_new_macro = true;
}

void setSetting(Command new_setting) {
  current_setting = new_setting;
  is_new_setting = true;
}

void setParameters(String new_parameters[]) {
  for (int i = 0; i < MAX_PARAMETERS; i++) {
    current_parameters[i] = new_parameters[i];
  }
}

void setBaseBrightness(String new_base_brightness_string) {
  if (new_base_brightness_string == "") {
    color::setBaseBrightness(255);
  } else {
    color::setBaseBrightness(new_base_brightness_string.toInt());
  }
}

void setBaseColor(String new_red_string,
                  String new_green_string,
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
  log("Applying setting: " + commandToString(current_setting) + ".");
  switch (current_setting) {
    case S_BASEBRIGHTNESS:
      setBaseBrightness(current_parameters[0]);
      break;
    case S_BASECOLOR:
      setBaseColor(current_parameters[0], current_parameters[1],
                   current_parameters[2]);
      break;
    case S_BASESPEED:
      setBaseSpeed(current_parameters[0]);
      break;
    case NULL_COMMAND:
    default:
      break;
  }
}

void initMacro() {
  log("Initializing macro: " + commandToString(current_macro) + ".");
  switch (current_macro) {
    case M_PULSE:
      m_pulse::init(current_parameters[0], current_parameters[1],
                    current_parameters[2], current_parameters[3]);
      break;
    case M_FLICKER:
      m_flicker::init(current_parameters[0], current_parameters[1]);
      break;
    case M_SOLID:
      m_solid::init();
      break;
    case M_SINGLEFLASH:
      m_singleflash::init(current_parameters[0], current_parameters[1]);
      break;
    case NULL_COMMAND:
    default:
      break;
  }
}

void tickMacro() {
  switch (current_macro) {
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
