#ifndef COMMANDS_H_DEFINED
#define COMMANDS_H_DEFINED

#include "Globals.h"

/**
 *
 * Settings are changes that are made once and don't interrupt macros.
 *
 * Macros are ongoing changes that will keep going until another macro or the
 * STOP command is issued.
 *
 */
enum Command {
  // SPECIAL COMMANDS
  NULL_COMMAND = -1,
  STOP = 0,
  // SETTINGS
  S_BASECOLOR = 101,
  S_BASEBRIGHTNESS = 102,
  S_BASESPEED = 103,
  // MACROS
  M_SOLID = 1,
  M_PULSE = 2,
  M_FLICKER = 3,
  M_SINGLEFLASH = 4
};

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
  if (string_to_convert == "S_BASESPEED") {
    return S_BASESPEED;
  }
  if (string_to_convert == "M_PULSE") {
    return M_PULSE;
  }
  if (string_to_convert == "M_FLICKER") {
    return M_FLICKER;
  }
  if (string_to_convert == "M_SINGLEFLASH") {
    return M_SINGLEFLASH;
  }
  if (string_to_convert == "M_SOLID") {
    return M_SOLID;
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
  if (command_to_convert == S_BASESPEED) {
    return "S_BASESPEED";
  }
  if (command_to_convert == M_PULSE) {
    return "M_PULSE";
  }
  if (command_to_convert == M_FLICKER) {
    return "M_FLICKER";
  }
  if (command_to_convert == M_SINGLEFLASH) {
    return "M_SINGLEFLASH";
  }
  if (command_to_convert == M_SOLID) {
    return "M_SOLID";
  }

  return "NULL_COMMAND";
}

// MACROES

/**
 * M_PULSE
 *
 * Turns on and off the LED with a fade. Duration and fade time is decided by
 * parameters. If off_duration and fade_out_duration are omitted they will be
 * the same as on_duration and fade_in_duration. If on_duration is omitted it
 * will default to 1000ms. If fade_in_duration is omitted it will default to
 * 500ms.
 */
namespace m_pulse {
int num_params = 4;
void init(String on_duration, String fade_in_duration, String off_duration,
          String fade_out_duration);
void tick();
}  // namespace m_pulse

/**
 * M_FLICKER
 *
 * Very quickly changes the brightness of the LED in a way that emulates a
 * candle. Since this macro does not set any colors, the base color should be
 * set to something like (255, 50, 0) for the best candle effect.
 */
namespace m_flicker {
int num_params = 2;
void init(String flicker_delay, String minimum_procent);
void tick();
}  // namespace m_flicker

/**
 * M_SOLID
 *
 * Statically lights the LED in the base color and brightness.
 */
namespace m_solid {
int num_params = 0;
void init();
void tick();
}  // namespace m_solid

/**
 * M_SINGLEFLASH
 *
 * Turns on the LED instantly, waits the given flash_duration, then fades to 0
 * brightness during fade_duration.
 */
namespace m_singleflash {
int num_params = 2;
void init(String flash_duration, String fade_duration);
void tick();
}  // namespace m_singleflash

int number_of_parameters(Command macro) {
  switch (macro) {
    case M_FLICKER:
      return m_flicker::num_params;
      break;
    case M_SOLID:
      return m_solid::num_params;
      break;
    case M_PULSE:
      return m_pulse::num_params;
      break;
    case M_SINGLEFLASH:
      return m_singleflash::num_params;
      break;
    default:
      return 0;
      break;
  }
}
#endif