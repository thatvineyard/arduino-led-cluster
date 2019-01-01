#ifndef COMMANDS_H_DEFINED
#define COMMANDS_H_DEFINED

enum Command {
  NULL_COMMAND = -1,
  STOP,
  SETCOLOR,
  SETBRIGHTNESS,
  BLINK,
  FLICKER,
};

void setCommand(Command newCommand);

void initCommand();

void doCommand();

namespace setColor {
void init(int red_value, int green_value, int blue_value);
void tick();
}  // namespace setColor

namespace setBrightness {
int num_params = 1;
void init(int brightness_value);
void tick();
}  // namespace setBrightness

namespace blink {
int num_params = 4;
void init(String red_value, String green_value, String blue_value,
          String blink_delay);
void tick();
}  // namespace blink

namespace flicker {
int num_params = 1;
void init(String delay);
void tick();
}  // namespace flicker

#endif