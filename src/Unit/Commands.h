#ifndef COMMANDS_H_DEFINED
#define COMMANDS_H_DEFINED

enum Command { 
    NULL_COMMAND = -1, 
    STOP,
    SETCOLOR,
    BLINK
};

void setCommand(Command newCommand);

void initCommand();

void doCommand();


namespace setColor
{
    void init(int red_value, int green_value, int blue_value); 
    void tick();
} // setColor

namespace blink
{
    void init(int red_value, int green_value, int blue_value, int blink_delay); 
    void tick();
} // blink



#endif