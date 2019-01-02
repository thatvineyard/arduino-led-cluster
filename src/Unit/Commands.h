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

#endif