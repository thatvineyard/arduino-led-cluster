#ifndef COMPOSER_H_INCLUDED
#define COMPOSER_H_INCLUDED

#include "Animation.h"
#include "Filter.h"
#include "Globals.h"

/**
 * COMPOSER
 *
 * This modules compiles the many different variables that are required and
 * handles them, sending out relevant updates every time update() is called.
 *
 * The set-functions will change variables that will take effect upon then next
 * update().
 *
 * freezeAnimation() will stop the changing of frames, blocking all changes made
 * to the following until unfreezeAnimation() is called.
 *  - Macro
 *  - Parameters
 *  - Animation
 *  - Animation speed
 *  - Filter
 *
 * freezeSettings() will stop the updating of settings, blocking all changes
 * made to the following until unfreezeSetting() is called.
 *  - Dimmer
 *  - Red, green and blue values
 *  - Macro speed
 *
 */

namespace composer {

void update();

void freezeAnimation();

void unfreezeAnimation();

void freezeSettings();

void unfreezeSetting();

// SETTING

void setMacro(Command new_macro, int number_of_parameters);

void setParameter(int parameter_number, int value);
void changeParameter(int parameter_number, int delta);

void setMacroSpeed(int value);
void changeMacroSpeed(int delta);

void setFilter(Filter new_filter);

void setAnimation(Animation new_animation);

void setAnimationSpeed(int value);
void changeAnimationSpeed(int delta);

void setDimmer(int value);
void changeDimmer(int delta);

void setRed(int value);
void changeRed(int delta);

void setGreen(int value);
void changeGreen(int delta);

void setBlue(int value);
void changeBlue(int delta);

void setColor(int red_value, int green_value, int blue_value);
void changeColor(int red_delta, int green_delta, int blue_delta);

}  // namespace composer

#endif