#include <Arduino.h>
#include "Led.h"


namespace setColor
{
    void tick() {}

    void init(int red_value, int green_value, int blue_value) {
        led::initLed();
        led::setColor(red_value, green_value, blue_value);
    }

} // setColor