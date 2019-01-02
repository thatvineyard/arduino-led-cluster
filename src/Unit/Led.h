#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

/**
 * LED
 *
 * This module handles the Led. It initializes the pins, can handle both common
 * anode and common cathode LEDs and will constrain and manipulate the pin
 * values to make the LED work.
 *
 * The acceptable range for red, green and blue values is 0 - 255.
 * Anything below of above that will be constrained to fit.
 *
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
