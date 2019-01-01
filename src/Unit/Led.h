#ifndef LEDCONTROL_H_INCLUDED
#define LEDCONTROL_H_INCLUDED

namespace led {

enum LedType { COMMON_CATHODE, COMMON_ANODE };

void initLed(LedType);

void setColor(int red_value, int green_value, int blue_value);

void setBrightness(int brightness_value);

void reset();

}  // namespace led
#endif
