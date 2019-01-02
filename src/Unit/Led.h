#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

/**
 * LED
 *
 * This module handles the Led. It initializes the pins, can handle both common
 * anode and common cathode LEDs and will constrain and manipulate the pin
 * values to make the LED work.
 *
 * The acceptable range for red, green, blue and brightness values is 0 - 255.
 * Anything below of above that will be constrained to fit.
 *
 * The module uses a base value and auxillary functions to set the color. By
 * setting the base color and brightness we can then use functions which
 * manipulate this value.
 *
 * This allows us to create macros which won't have to
 * handle setting the color, but can still manipulate it.
 *
 * Note: The base values are never actually used in calculating pin values, only
 * the aux values are. This means that if you just want to use the base values
 * you have to use setAux[brightness/colors]ToBase().
 *
 */

namespace led {

enum LedType { COMMON_CATHODE, COMMON_ANODE };

/** initLed(LedType)
 * Initialized the pins based on the LED type and calculates initial auxillary
 * rgb and brightness values.
 */
void initLed(LedType);

void setPinValues(int red_value, int green_value, int blue_value);

}  // namespace led
#endif
