#ifndef COMMANDS_H_DEFINED
#define COMMANDS_H_DEFINED

enum Command {
  // SPECIAL COMMANDS
  NULL_COMMAND = -1,
  STOP,
  // SETTINGS
  S_BASECOLOR,
  S_BASEBRIGHTNESS,
  // MACROS
  M_SOLID,
  M_PULSE,
  M_FLICKER,
  M_SINGLEFLASH
};

void setMacro(Command newCommand);

void setSetting();

void initMacro();

void tickMacro();

/** M_PULSE
 * Turns on and off the LED with a fade. Duration and fade time is decided by
 * parameters. If off_duration and fade_out_duration are omitted they will be
 * the same as on_duration and fade_in_duration. If on_duration is omitted it
 * will default to 1000ms. If fade_in_duration is omitted it will default to
 * 500ms.
 */
namespace m_pulse {
void init(String on_duration,
          String fade_in_duration,
          String off_duration,
          String fade_out_duration);
void tick();
}  // namespace m_pulse

namespace m_flicker {
void init(String flicker_delay);
void tick();
}  // namespace m_flicker

namespace m_solid {
void init();
void tick();
}  // namespace m_solid

namespace m_singleflash {
void init(String flash_duration, String fade_duration);
void tick();
}  // namespace m_singleflash

#endif