#include <Arduino.h>
#include "Led.h"


namespace setBrightness
{
    void tick() {}

    void init(int brightness_value) {
        led::initLed();
        led::setBrightness(brightness_value);
    }

} // setBrightness