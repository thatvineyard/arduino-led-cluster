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
  M_BLINK,
  M_FLICKER,
};

void setMacro(Command newCommand);

void setSetting();

void initMacro();

void tickMacro();

namespace m_blink {
void init(String blink_delay);
void tick();
}  // namespace m_blink

namespace m_flicker {
void init(String flicker_delay);
void tick();
}  // namespace m_flicker

namespace m_solid {
void init();
void tick();
}  // namespace m_solid

#endif