#include <Arduino.h>
#include "Led.h"


namespace setColor
{
    int red_value, green_value, blue_value;

    void tick() {}

    void init(int new_red_value, int new_green_value, int new_blue_value) {
        led::initLed();
        red_value = new_red_value;
        green_value = new_green_value;
        blue_value = new_blue_value;
        led::setColor(255, 0, 0);
    }

} // setColor