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

enum Scale {
  LINEAR,
  LINEAR_INVERSE,
  // LOGARITHMIC,
  // EXPONENTIAL,
  QUADRATIC,
  QUADRATIC_INVERSE
};

/**
 *
 */
void handleNewCommand(Command new_command);

/**
 * Sets a new macro. This will flag that a new macro is ready to be initialized.
 */
void setMacro(Command new_command);

/**
 * Sets a new setting. This will flag that a new setting is ready to be applied.
 */
void setSetting();

/**
 * Looks at the current macro and performs that macro's init-function.
 * Should only be called when a new function has been set.
 */
void initMacro();

/**
 * Looks at the current macro and performs that macro's tick-function. These
 * tick functions are parameter-less and therefore don't have to worry about
 * keeping track of the global list of parameters.
 */
void tickMacro();

/**
 * looks at the current setting and applies that setting.
 * Should only be called when a new setting has been set.
 */
void applySetting();

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
#define M_PULSE_MIN_DURATION 0
#define M_PULSE_MAX_DURATION 10000
#define M_PULSE_SCALE_TYPE QUADRATIC
namespace m_pulse {
int num_params = 4;
void init(int on_duration, int fade_in_duration, int off_duration,
          int fade_out_duration);
void tick();
}  // namespace m_pulse

/**
 * M_FLICKER
 *
 * Very quickly changes the brightness of the LED in a way that emulates a
 * candle. Since this macro does not set any colors, the base color should be
 * set to something like (255, 50, 0) for the best candle effect.
 */
#define M_FLICKER_MIN_DELAY 20
#define M_FLICKER_MAX_DELAY 100
#define M_FLICKER_SCALE_TYPE LINEAR
namespace m_flicker {
int num_params = 2;
void init(int flicker_delay, int minimum_procent);
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
#define M_SINGLEFLASH_MIN_DURATION 0
#define M_SINGLEFLASH_MAX_DURATION 10000
#define M_SINGLEFLASH_SCALE_TYPE LINEAR
namespace m_singleflash {
int num_params = 2;
void init(int flash_duration,
          int fade_duration);  // TODO: debug with 0-length fade
void tick();
}  // namespace m_singleflash

int number_of_parameters(Command macro) {
  switch (macro) {
  M_FLICKER:
    return m_flicker::num_params;
  M_SOLID:
    return m_solid::num_params;
  M_PULSE:
    return m_pulse::num_params;
  M_SINGLEFLASH:
    return m_singleflash::num_params;
    default:
      return 0;
      break;
  }
}
#endif