#include <Arduino.h>
#include "Animation.h"

#define NUMBER_OF_VIEWS 3
#define MAX_VALUE 255

namespace composer {

// VIEW
int view_scroll = 0;

// MACRO
Command current_macro = NULL_COMMAND;
int macro_selector = 0;
bool macro_changed = false;

int parameters[MAX_PARAMETERS];
int current_number_of_parameters = 0;
int parameter_selector = 0;
bool parameters_changed = false;

// ANIMATION
Animation current_animation = NO_ANIMATION;
int animation_selector = 0;
bool animation_changed = false;

// FILTER
Filter current_filter = NO_FILTER;
int filter_selector = 0;
bool filter_changed = false;

// SET

void setAnimationSpeed(int value) {
  animation_speed = value;
  animation::setAnimationSpeed(animation_speed);
  macro_speed_changed = true;
}

void setFilter(Filter new_filter) {
  current_filter = new_filter;
  filter_changed = true;
}

void setAnimation(Animation new_animation) {
  current_animation = new_animation;
  animation_changed = true;
}

void setMacro(Command new_macro) {
  current_macro = new_macro;
  macro_changed = true;
}

void setMacroSpeed(int value) {
  macro_speed_value = value;
  macro_speed_changed = true;
}

void setDimmer(int value) {
  dimmer_value = value;
  color_changed = true;
}

void setRed(int value) {
  red_value = value;
  color_changed = true;
}

void setGreen(int value) {
  green_value = value;
  color_changed = true;
}

void setBlue(int value) {
  blue_value = value;
  color_changed = true;
}

// CHANGE

void changeAnimationSpeed(int delta) {
  setAnimationSpeed((animation_speed + MAX_VALUE + delta) % MAX_VALUE);
}

void changeSelectedParameter(int delta) {
  parameters[parameter_selector] =
      (parameters[parameter_selector] + MAX_VALUE + delta) % MAX_VALUE;
}

void changeSelectedViewSetting(int delta) {
  switch (view_scroll) {
    case MACRO:
    default:
      macro_selector =
          (macro_selector + NUMBER_OF_MACROS + delta) % NUMBER_OF_MACROS;
      break;
    case ANIMATION:
      animation_selector = (animation_selector + NUMBER_OF_ANIMATIONS + delta) %
                           NUMBER_OF_ANIMATIONS;
      break;
    case FILTER:
      filter_selector =
          (filter_selector + NUMBER_OF_FILTERS + delta) % NUMBER_OF_FILTERS;
      break;
    case ANIMATION_SPEED:
      changeAnimationSpeed(delta);
      break;
  }
}

// SCROLL

void scrollParameter() {
  parameter_selector = (parameter_selector + 1) % MAX_PARAMETERS;
}

void scrollMacro() {
  macro_selector = (macro_selector + 1) % NUMBER_OF_MACROS;
}

void scrollView() {
  view_scroll = (view_scroll + 1) % NUMBER_OF_VIEWS;
}

// COMMIT

void commitMacro() {
  setMacro((Command)macro_selector);
}

void commitAnimation() {
  setAnimation((Animation)animation_selector);
}

void commitFilter() {
  setFilter((Filter)filter_selector);
}

// MESSAGES

String createMessage(String selector, String command, String parameters) {
  String message = "";

  message += DELIM_MESSAGE_START;
  message += DELIM_SELECTOR_START;
  message += selector;
  message += DELIM_SELECTOR_END;
  message += command;
  if (parameters != "") {
    message += DELIM_PARAMETERS_START;
    message += parameters;
    message += DELIM_PARAMETERS_END;
  }
  message += DELIM_MESSAGE_END;

  return message;
}

String createMessage(String selector,
                     String command,
                     int number_of_parameters) {
  String parameters = "";
  for (int i = 0; i < number_of_parameters; i++) {
    parameters += composer::parameters[i];
    if (i + 1 != number_of_parameters) {
      parameters += " ";
    }
  }
  return createMessage(selector, command, parameters);
}

void sendMessage(String message) {
  Serial.print(message);
}

void sendMacro() {
  if (animation::nextFrame()) {
    String animation_selector = animation::getNextFrame();
    String filter_selector = filterToSelector(current_filter);
    if (animation_selector != "") {
      sendMessage(createMessage(
          andSelector(animation_selector, filter_selector),
          String((Command)macro_selector), current_number_of_parameters));
    }
  }
}

void sendDimmerCommand() {
  parameters[0] = dimmer_value;
  sendMessage(createMessage(".*", "S_BASEBRIGHTNESS", 1));
}

void sendColorCommand() {
  parameters[0] = red_value;
  parameters[1] = green_value;
  parameters[2] = blue_value;
  sendMessage(createMessage(".*", "S_BASECOLOR", 3));
}

void sendMacroSpeedCommand() {
  parameters[0] = macro_speed_value;
  sendMessage(createMessage(".*", "S_BASESPEED", 1));
}

void sendMacroCommand() {
  if (macro_toggle) {
    sendMessage(createMessage(".*", "S_BASECOLOR", 3));
    macro_toggle = false;
  } else {
    sendMessage(createMessage(".*", "M_FLICKER", 2));
    macro_toggle = true;
  }
}

void sendSettings() {
  if (dimmer_changed) {
    sendDimmerCommand();
    dimmer_changed = false;
  }
  if (color_changed) {
    sendColorCommand();
    color_changed = false;
  }
  if (macro_speed_changed) {
    sendMacroSpeedCommand();
    macro_speed_changed = false;
  }
}

}  // namespace composer