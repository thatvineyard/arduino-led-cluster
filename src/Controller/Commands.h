#ifndef COMMANDS_H_DEFINED
#define COMMANDS_H_DEFINED

#include "Globals.h"

/**
 * Sets a new macro. This will flag that a new macro is ready to be initialized.
 */
void setMacro(Command newCommand);

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
void init(String on_duration,
          String fade_in_duration,
          String off_duration,
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