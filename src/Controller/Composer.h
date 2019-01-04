#ifndef COMPOSER_H_INCLUDED
#define COMPOSER_H_INCLUDED

#include "Animation.h"
#include "Filter.h"
#include "Globals.h"

namespace composer {

void update();

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

// SEND

}  // namespace composer

#endif