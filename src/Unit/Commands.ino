#include <Arduino.h>
#include "Commands.h"

Command current_macro = NULL_COMMAND;
Command current_setting = NULL_COMMAND;
int current_parameters[MAX_PARAMETERS];

bool isSetting(Command command_to_check) {
  return ((command_to_check == S_BASEBRIGHTNESS) ||
          (command_to_check == S_BASECOLOR) ||
          (command_to_check == S_BASESPEED) ||
          (command_to_check == S_BASECOLORGRADIENT));
}

bool isMacro(Command command_to_check) {
  return ((command_to_check == M_PULSE) || (command_to_check == M_SOLID) ||
          (command_to_check == M_SINGLEFLASH) ||
          (command_to_check == M_SOLID) || (command_to_check == M_FLICKER));
}

bool isSpecial(Command command_to_check) {
  return ((command_to_check == STOP));
}

void stopCommand() {
  setMacro(NULL_COMMAND);
  is_new_macro = false;

  setSetting(NULL_COMMAND);
  is_new_setting = false;

  color::setAuxBrightnessProcent(0);
  color::setAuxColorProcent(0, 0, 0);
  log("Stopping macro");
}

void handleNewCommand(Command new_command) {
  if (isMacro(new_command)) {
    setMacro(new_command);
  } else if (isSetting(new_command)) {
    setSetting(new_command);
  } else if (new_command == STOP) {
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
    if (new_parameters[i] != "") {
      current_parameters[i] =
          constrain(new_parameters[i].toInt(), 0, MAX_VALUE);
    } else {
      current_parameters[i] = -1;
    }
  }
}

void setBaseBrightness(int new_base_brightness) {
  color::setBaseBrightness(new_base_brightness);
}

void setBaseColor(int new_red, int new_green, int new_blue) {
  color::setBaseColor(new_red, new_green, new_blue);
}

void setBaseSpeed(int new_base_speed_string) {
  if (new_base_speed_string == -1) {
    setTimerBaseSpeed(100);
  } else {
    setTimerBaseSpeed(new_base_speed_string);
  }
}

void setBaseColorGradient(int new_red_start, int new_green_start,
                          int new_blue_start, int new_red_end,
                          int new_green_end, int new_blue_end) {
  setBaseColor(
      (mapScale(LINEAR, new_red_start, new_red_end, 0, NUM_ROWS, getRow()) +
       mapScale(LINEAR, new_red_start, new_red_end, 0, NUM_COLUMNS,
                getColumn())) /
          2,
      (mapScale(LINEAR, new_green_start, new_green_end, 0, NUM_ROWS, getRow()) +
       mapScale(LINEAR, new_green_start, new_green_end, 0, NUM_COLUMNS,
                getColumn())) /
          2,
      (mapScale(LINEAR, new_blue_start, new_blue_end, 0, NUM_ROWS, getRow()) +
       mapScale(LINEAR, new_blue_start, new_blue_end, 0, NUM_COLUMNS,
                getColumn())) /
          2);
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
    case S_BASECOLORGRADIENT:
      setBaseColorGradient(current_parameters[0], current_parameters[1],
                           current_parameters[2], current_parameters[3],
                           current_parameters[4], current_parameters[5]);
    case NULL_COMMAND:
    default:
      break;
  }
}

void initMacro() {
  log("Initializing macro: " + commandToString(current_macro) + ".");
  for (int i = 0; i < MAX_PARAMETERS; i++) {
    // log("parameter " + String(i) + ": " + String(current_parameters[i]));
  }
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
