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

String andSelector(String selector_one, String selector_two) {
  return selector_one + DELIM_SELECTOR_AND + selector_two;
}

String orSelector(String selector_one, String selector_two) {
  return selector_one + DELIM_SELECTOR_OR + selector_two;
}

String filterToSelector(Filter filter) {
  switch (filter) {
    case NO_FILTER:
    default:
      return ".*";
      break;
    case ODD_COLUMNS:
      return ".*";
      break;
    case EVEN_COLUMNS:
      return ".*";
      break;
    case ODD_ROWS:
      return ".*";
      break;
    case EVEN_ROWS:
      return ".*";
      break;
    case CHECKERBOARD:
      return ".*";
      break;
    case LEFT_HALF:
      return ".*";
      break;
    case RIGHT_HALF:
      return ".*";
      break;
    case LEFT_THIRD:
      return ".*";
      break;
    case MIDDLE_THIRD:
      return ".*";
      break;
    case RIGHT_THIRD:
      return ".*";
      break;
  }
}

String a_random() {
  String result = "";
  String column_regex;
  char column_character;

  randomSeed(millis());

  for (int i = 0; i < NUM_COLUMNS; i++) {
    column_character = 'A' + i;

    column_regex = String(column_character) + "[";

    for (int j = 0; j < NUM_ROWS; j++) {
      if (random(1) == 1) {
        column_regex += String(j);
      }
    }

    column_regex += "]";

    if (i == 0) {
      result = column_regex;
    } else {
      result = orSelector(result, column_regex);
    }
  }
}

String a_horizontal_sweep(bool left_to_right) {
  String result = "";

  if (step > NUM_COLUMNS) {
    step = 0;
  }

  char column_character;
  if (left_to_right) {
    column_character = 'A' + step;
  } else {
    column_character = 'A' + (NUM_COLUMNS - step);
  }

  result = String(column_character) + "..";

  return result;
}

String a_vertical_sweep(bool front_to_back) {
  String result = "";

  if (step > NUM_ROWS) {
    step = 0;
  }

  result = ".";

  char row_string[2];

  if (front_to_back) {
    sprintf(row_string, "%02d", NUM_ROWS - step);
  } else {
    sprintf(row_string, "%02d", step);
  }

  result += row_string;

  return result;
}

String a_mirrored(bool inward) {
  String result = "";

  if (step > NUM_COLUMNS / 2) {
    step = 0;
  }

  char column_character;
  if (inward) {
    column_character = 'A' + step;
  } else {
    column_character = 'A' + ((NUM_COLUMNS / 2) + step);
  }
  result = String(column_character) + "..";

  if (inward) {
    column_character = 'A' + (NUM_COLUMNS - step);
  } else {
    column_character = 'A' + ((NUM_COLUMNS / 2) - step);
  }

  result = orSelector(result, String(column_character) + "..");

  return result;
}

String a_chevron(bool front_to_back) {
  String result = "";

  if (step > NUM_ROWS) {
    step = 0;
  }

  char column_character_left;
  char column_character_right;
  String column_regex;
  char row_string[2];
  for (int i = 0; i < NUM_COLUMNS / 2; i++) {
    column_character_left = 'A' + (NUM_COLUMNS / 2) - i;
    column_character_right = 'A' + (NUM_COLUMNS / 2) + i;

    column_regex = "[" + String(column_character_left) +
                   String(column_character_right) + "]";

    if (front_to_back) {
      sprintf(row_string, "%02d", NUM_ROWS - (step - i));
    } else {
      sprintf(row_string, "%02d", (step - i));
    }

    if (i == 0) {
      result = column_regex + row_string;
    } else {
      result = orSelector(result, column_regex + row_string);
    }
  }
  return result;
}

String animationToSelector() {
  switch (current_animation) {
    case NO_ANIMATION:
    default:
      return ".*";
      break;
    case RANDOM:
      return a_random();
      break;
    case LEFT_TO_RIGHT:
      return a_horizontal_sweep(true);
      break;
    case RIGHT_TO_LEFT:
      return a_horizontal_sweep(false);
      break;
    case BACK_TO_FRONT:
      return a_vertical_sweep(false);
      break;
    case FRONT_TO_BACK:
      return a_vertical_sweep(true);
      break;
    case OUTWARD:
      return a_mirrored(false);
      break;
    case INWARD:
      return a_mirrored(true);
      break;
    case CHEVRON_FTB:
      return a_chevron(true);
      break;
    case CHEVRON_BTF:
      return a_chevron(false);
      break;
  }
}

void tick() {
  if (timerLapsed || first) {
    sendMessage(createMessage(
        andSelector(animationToSelector(), filterToSelector(current_filter)),
        String(current_command), current_number_of_parameters));

    step++;
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

  log("New animation set: " + String(current_animation) + " (" +
      String(animation_delay) + "ms) with filter: " + String(current_filter) +
      " executing command: " + String(current_command) + ".");
}

}  // namespace animation