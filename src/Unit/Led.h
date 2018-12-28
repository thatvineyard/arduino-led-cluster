#ifndef LEDCONTROL_H_INCLUDED
#define LEDCONTROL_H_INCLUDED


namespace led
{
    void initLed();

    void setColor(int red_value, int green_value, int blue_value);

    void setBrightness(int brightness_value);

} 
#endif
