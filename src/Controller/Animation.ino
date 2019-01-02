#include <Arduino.h>
#include "Animation.h"

namespace animation {

Command current_command;
int current_number_of_parameters;
Animation current_animation;
Filter current_filter;
int animation_delay = 20;
bool first = false;

int step;

String filterToSelector(Filter filter) {
  switch (filter) {
    case NO_FILTER:
    default:
      return "";
      break;
    case ODD_COLUMNS:
      return "";
      break;
    case EVEN_COLUMNS:
      return "";
      break;
    case ODD_ROWS:
      return "";
      break;
    case EVEN_ROWS:
      return "";
      break;
    case CHECKERBOARD:
      return "";
      break;
    case LEFT_HALF:
      return "";
      break;
    case RIGHT_HALF:
      return "";
      break;
    case LEFT_THIRD:
      return "";
      break;
    case MIDDLE_THIRD:
      return "";
      break;
    case RIGHT_THIRD:
      return "";
      break;
  }
}

String nextStepFilter() {
  switch (current_animation) {
    case NO_ANIMATION:
    default:
      return ".*";
      break;
    case RANDOM:
      return ".*";
      break;
    case LEFT_TO_RIGHT:
      return ".*";
      break;
    case RIGHT_TO_LEFT:
      return ".*";
      break;
    case BACK_TO_FRONT:
      return ".*";
      break;
    case FRONT_TO_BACK:
      return ".*";
      break;
  }
}

String andSelector(String selector_one, String selector_two) {
  return selector_one + DELIM_SELECTOR_AND + selector_two;
}

void tick() {
  if (timerLapsed || first) {
    sendMessage(createMessage(filterToSelector(current_filter), "",
                              current_number_of_parameters));
    restartTimer();
  }
}

void init(Command new_command,
          int new_number_of_parameters,
          Animation new_animation,
          Filter new_filter,
          int new_animation_delay) {
  current_command = new_command;
  current_number_of_parameters = new_number_of_parameters;
  current_animation = new_animation;
  current_filter = new_filter;
  animation_delay = new_animation_delay;

  setTimerDelay(animation_delay);
  step = 0;
  first = true;
}

}  // namespace animation