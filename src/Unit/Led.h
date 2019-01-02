#ifndef LEDCONTROL_H_INCLUDED
#define LEDCONTROL_H_INCLUDED

namespace led {

enum LedType { COMMON_CATHODE, COMMON_ANODE };

void initLed(LedType);

void setBaseColor(int red_value, int green_value, int blue_value);

void setBaseBrightness(int brightness_value);

void reset();

}  // namespace led
#endif
