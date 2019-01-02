#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

namespace color {

void displayColor();

void setBaseColor(int red_value, int green_value, int blue_value);

void setBaseBrightness(int brightness_value);

void resetBaseColor();

void setAuxBrightnessToBase();

void setAuxBrightnessValue(int aux_brightness_value);

void setAuxBrightnessProcent(int aux_brightness_procent);

void setAuxBrightnessDelta(int aux_brightness_delta);

void setAuxColorToBase();

void setAuxColorValue(int new_aux_red_value,
                      int new_aux_green_value,
                      int new_aux_blue_value);

void setAuxColorProcent(int aux_red_procent,
                        int aux_green_procent,
                        int aux_blue_procent);

void setAuxColorDelta(int aux_red_delta,
                      int aux_green_delta,
                      int aux_blue_delta);

}  // namespace color

#endif