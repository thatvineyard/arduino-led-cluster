#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

/**
 * The module uses a base value and auxillary functions to set the color. By
 * setting the base color and brightness we can then use functions which
 * manipulate this value.
 *
 * This allows us to create macros which won't have to
 * handle setting the color, but can still manipulate it.
 *
 * Note: The base values are never actually used in calculating color values,
 * only the aux values are. This means that if you just want to use the base
 * values you have to use setAux[brightness/colors]ToBase().
 *
 * displayColor() updates the LED pin values to show the appropriate color, but
 * you should know that all functions call on this function, so it should not be
 * used unless you suspect a bug.
 *
 */
namespace color {

void displayColor();

void setBaseColor(int red_value, int green_value, int blue_value);

void setBaseBrightness(int brightness_value);

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