#include <Arduino.h>

#define NUMBER_OF_VIEWS 3
#define MAX_VALUE 255

namespace composer {

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
Command current_macro = NULL_COMMAND;
bool macro_changed = false;
int current_number_of_parameters = 0;

int parameters[MAX_PARAMETERS];
bool parameters_changed = false;

// ANIMATION
Animation current_animation = NO_ANIMATION;
bool animation_changed = false;
int animation_speed_value = 100;
bool animation_speed_changed = false;
bool freeze_animation = false;

// FILTER
Filter current_filter = NO_FILTER;
bool filter_changed = false;

// SET

void setMacro(Command new_macro, int number_of_parameters) {
  current_macro = new_macro;
  current_number_of_parameters = number_of_parameters;
  macro_changed = true;
}

void setMacro(Command new_macro) {
  setMacro(new_macro, number_of_parameters(new_macro));
}

void setParameter(int parameter_number, int value) {
  parameters[parameter_number] = value % MAX_VALUE;
  parameters_changed = true;
}

void changeParameter(int parameter_number, int delta) {
  setParameter(parameter_number, parameters[parameter_number] + delta);
}

void setMacroSpeed(int value) {
  macro_speed_value = value;
  macro_speed_changed = true;
}

void changeMacroSpeed(int delta) {
  setMacroSpeed((macro_speed_value + MAX_VALUE + delta) % MAX_VALUE);
}

void setFilter(Filter new_filter) {
  current_filter = new_filter;
  filter_changed = true;
}

void setAnimation(Animation new_animation) {
  current_animation = new_animation;
  animation_changed = true;
}

void setAnimationSpeed(int value) {
  animation_speed_value = constrain(value, 0, MAX_VALUE);
  animation_speed_changed = true;
}

void changeAnimationSpeed(int delta) {
  setAnimationSpeed(animation_speed_value + delta);
}

void setDimmer(int value) {
  dimmer_value = constrain(value, 0, MAX_BRIGHTNESS);
  color_changed = true;
}

void changeDimmer(int delta) {
  setDimmer(dimmer_value + delta);
}

void setRed(int value) {
  red_value = constrain(value, 0, MAX_RED);
  color_changed = true;
}

void changeRed(int delta) {
  setRed(red_value + delta);
}

void setGreen(int value) {
  green_value = constrain(value, 0, MAX_GREEN);
  color_changed = true;
}
void changeGreen(int delta) {
  setGreen(green_value + delta);
}

void setBlue(int value) {
  blue_value = constrain(value, 0, MAX_BLUE);
  color_changed = true;
}

void changeBlue(int delta) {
  setBlue(blue_value + delta);
}

void setColor(int red_value, int green_value, int blue_value) {
  setRed(red_value);
  setGreen(green_value);
  setBlue(blue_value);
}

void changeColor(int red_delta, int green_delta, int blue_delta) {
  setColor(red_value + red_delta, green_value + green_delta,
           blue_value + blue_delta);
}

// CHANGE

// ANIMATION

void sendNextFrame() {
  if (animation::nextFrameReady()) {
    String animation_regex = animation::getNextFrame();
    String filter_regex = filterToSelector(current_filter);
    if (animation_regex != "") {
      String parameters = "";
      for (int i = 0; i < current_number_of_parameters; i++) {
        parameters += composer::parameters[i];
        if (i + 1 != current_number_of_parameters) {
          parameters += " ";
        }
      }
      sender::sendMessage(andSelector(animation_regex, filter_regex),
                          String((Command)current_macro), parameters);
    }
  }
}

void sendSettings() {
  if (dimmer_changed) {
    sender::sendDimmer(dimmer_value);
    dimmer_changed = false;
  }
  if (color_changed) {
    sender::sendColor(red_value, green_value, blue_value);
    color_changed = false;
  }
  if (macro_speed_changed) {
    sender::sendMacroSpeed(macro_speed_value);
    macro_speed_changed = false;
  }
}
void update() {
  if (animation_changed) {
    animation::startAnimation(current_animation);
    animation_changed = false;
  }
  if (animation_speed_changed) {
    animation::setAnimationSpeed(animation_speed_value);
    animation_speed_changed = false;
  }
  if (!freeze_animation) {
    sendNextFrame();
  }
  sendSettings();
}

void freezeAnimation() {
  freeze_animation = true;
}

void unfreezeAnimation() {
  freeze_animation = false;
}

}  // namespace composer