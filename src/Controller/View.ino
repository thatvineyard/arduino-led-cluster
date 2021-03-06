#include <Arduino.h>

namespace view {

// SCROLL

void scrollParameter(bool direction) {
  if (direction) {
    parameter_selector =
        (parameter_selector + MAX_PARAMETERS + 1) % MAX_PARAMETERS;
  } else {
    parameter_selector =
        (parameter_selector + MAX_PARAMETERS - 1) % MAX_PARAMETERS;
  }
}

void scrollMacro(bool direction) {
  if (direction) {
    macro_selector =
        (macro_selector + NUMBER_OF_MACROS + 1 + 1) % (NUMBER_OF_MACROS + 1);
  } else {
    macro_selector =
        (macro_selector + NUMBER_OF_MACROS - 1 + 1) % (NUMBER_OF_MACROS + 1);
  }
}

void scrollAnimation(bool direction) {
  if (direction) {
    animation_selector =
        (animation_selector + NUMBER_OF_ANIMATIONS + 1) % NUMBER_OF_ANIMATIONS;
  } else {
    animation_selector =
        (animation_selector + NUMBER_OF_ANIMATIONS - 1) % NUMBER_OF_ANIMATIONS;
  }
}

void scrollFilter(bool direction) {
  if (direction) {
    filter_selector =
        (filter_selector + NUMBER_OF_FILTERS + 1) % NUMBER_OF_FILTERS;
  } else {
    filter_selector =
        (filter_selector + NUMBER_OF_FILTERS - 1) % NUMBER_OF_FILTERS;
  }
}

void scrollControl(bool direction) {
  if (direction) {
    view_scroll = (view_scroll + NUMBER_OF_VIEWS + 1) % NUMBER_OF_VIEWS;
  } else {
    view_scroll = (view_scroll + NUMBER_OF_VIEWS - 1) % NUMBER_OF_VIEWS;
  }
}

// VIEW

void initView() {
  composer::setMacro((Command)macro_selector);
  composer::setAnimation((animation::Animation)animation_selector);
  composer::setFilter((filter::Filter)filter_selector);
  composer::changeAnimationSpeed(0);
}

void changeSelectedParameter(int delta) {
  composer::changeParameter(parameter_selector, delta);
}

void changeSelectedControl(int delta) {
  bool direction = true;
  if (delta < 0) {
    direction = false;
  }

  switch (view_scroll) {
    case MACRO:
    default:
      scrollMacro(direction);
      composer::setMacro((Command)macro_selector);
      break;
    case ANIMATION:
      scrollAnimation(direction);
      composer::setAnimation((animation::Animation)animation_selector);
      break;
    case FILTER:
      scrollFilter(direction);
      composer::setFilter((filter::Filter)filter_selector);
      break;
    case ANIMATION_SPEED:
      composer::changeAnimationSpeed(delta);
      break;
  }
}

String viewToString(View view_to_convert) {
  switch (view_to_convert) {
    case MACRO:
      return F("MACRO");
    case ANIMATION:
      return F("ANIMATION");
    case FILTER:
      return F("FILTER");
    case ANIMATION_SPEED:
      return F("ANIMATION_SPEED");
    default:
      return F("NULL_VIEW");
  }
}

}  // namespace view