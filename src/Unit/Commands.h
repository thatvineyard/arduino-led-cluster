#ifndef COMMANDS_H_DEFINED
#define COMMANDS_H_DEFINED

enum Command { 
    NULL_COMMAND = -1, 
    STOP,
    SETCOLOR,
    SETBRIGHTNESS,
    BLINK
};

void setCommand(Command newCommand);

void initCommand();

void doCommand();


namespace setColor {
    void init(int red_value, int green_value, int blue_value); 
    void tick();
} // setColor

namespace setBrightness {
    void init(int brightness_value);
    void tick();
} // setBrightness

namespace blink {
    void init(int red_value, int green_value, int blue_value, int blink_delay); 
    void tick();
} // blink



#endif