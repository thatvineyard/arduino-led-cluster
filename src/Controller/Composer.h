#ifndef COMPOSER_H_INCLUDED
#define COMPOSER_H_INCLUDED

#include "Globals.h"

namespace composer {

enum view { MACRO = 0, ANIMATION = 1, FILTER = 2, ANIMATION_SPEED = 3 };

// DIMMER
int dimmer_value = 255;
bool dimmer_changed;

// RGB
int red_value = 0;
int green_value = 0;
int blue_value = 0;
bool color_changed;

// SPEED
int macro_speed_value = 100;
bool macro_speed_changed;

// MACRO

// ANIMATION
int animation_speed = 100;

void sendSettings();

void sendMacro();

}  // namespace composer

#endif