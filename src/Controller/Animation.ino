#include <Arduino.h>
#include "Animation.h"

namespace animation {

#define MIN_ANIMATION_DELAY 20
#define MAX_ANIMATION_DELAY 5000
#define MIDDLE_SHIFT ((NUM_COLUMNS + 1) % 2)
#define START_CHARACTER 'A'

Animation current_animation;
int animation_delay = 1000;
bool first = false;
bool finished = false;
bool looping = false;

int step = 0;

void lastStepReached() {
  if (looping) {
    step = 0;
  } else {
    finished = true;
  }
}

String a_random() {
  String result = "";

  if (step > 0) {
    lastStepReached();
  }

  char column_character;
  String column_regex = "";
  bool first_column = true;

  randomSeed(millis());

  for (int i = 0; i < NUM_COLUMNS; i++) {
    // This randomization is lazy. It will allow a random last digit, but will
    // match on any tens digit. For example is 2 is randomly selected then 02,
    // 12 and 22 will match.
    // TODO: This can be improved with multiple or-selectors, but that is a
    // future improvement.

    column_character = START_CHARACTER + i;
    column_regex += String(column_character);
    column_regex += "[012]";
    column_regex += +"[";

    for (int j = 0; j < 10; j++) {
      if (random(2) == 1) {
        // column_regex += String(j);
      }
    }

    column_regex += "]";

    if (i == 0) {
      result = column_regex;
      // first_column = false;
    } else {
      result = orSelector(result, column_regex);
    }
  }

  return result;
}

String a_horizontal_sweep(bool left_to_right) {
  String result = "";

  if (step >= NUM_COLUMNS) {
    lastStepReached();
  }

  char column_character;
  if (left_to_right) {
    column_character = START_CHARACTER + step;
  } else {
    column_character = START_CHARACTER + ((NUM_COLUMNS - 1) - step);
  }

  result = String(column_character) + "..";

  return result;
}

String a_vertical_sweep(bool front_to_back) {
  String result = "";

  if (step >= NUM_ROWS) {
    lastStepReached();
  }

  result = ".";

  char row_string[2];

  if (front_to_back) {
    sprintf(row_string, "%02d", NUM_ROWS - step);
  } else {
    sprintf(row_string, "%02d", (step + 1));
  }

  result += row_string;

  return result;
}

String a_mirrored(bool inward) {
  String result = "";

  if (step >= NUM_COLUMNS / 2) {
    lastStepReached();
  }

  char column_character;
  if (inward) {
    column_character = START_CHARACTER + step;
  } else {
    column_character = START_CHARACTER + ((NUM_COLUMNS / 2) - step - 1);
  }
  result = String(column_character) + "..";

  if (inward) {
    column_character = START_CHARACTER + ((NUM_COLUMNS - 1) - step);
  } else {
    column_character =
        START_CHARACTER + ((NUM_COLUMNS / 2) + step - 1) + MIDDLE_SHIFT;
  }

  result = orSelector(result, String(column_character) + "..");

  return result;
}

String a_chevron(bool front_to_back) {
  String result = "";

  if (step > NUM_ROWS) {
    lastStepReached();
  }

  char column_character_left;
  char column_character_right;
  String column_regex;
  char row_string[3];
  for (int i = 0; i < NUM_COLUMNS / 2; i++) {
    column_character_left = START_CHARACTER + (NUM_COLUMNS / 2) - i - 1;
    column_character_right =
        START_CHARACTER + (NUM_COLUMNS / 2) + i - 1 + MIDDLE_SHIFT;

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

String animationToString(Animation animation_to_convert) {
  switch (animation_to_convert) {
    case NO_ANIMATION:
      return "NO_ANIMATION";
    case RANDOM:
      return "RANDOM";
    case LEFT_TO_RIGHT:
      return "LEFT_TO_RIGHT";
    case RIGHT_TO_LEFT:
      return "RIGHT_TO_LEFT";
    case BACK_TO_FRONT:
      return "BACK_TO_FRONT";
    case FRONT_TO_BACK:
      return "FRONT_TO_BACK";
    case OUTWARD:
      return "OUTWARD";
    case INWARD:
      return "INWARD";
    case CHEVRON_FTB:
      return "CHEVRON_FTB";
    case CHEVRON_BTF:
      return "CHEVRON_BTF";
    default:
      return "NULL_ANIMATION";
  }
}

bool nextFrameReady() { return (timerLapsed() || first); }

String getNextFrame() {
  String result = animationToSelector();
  first = false;
  step++;
  restartTimer();
  return result;
}

void startAnimation(Animation new_animation, bool new_looping) {
  current_animation = new_animation;
  looping = new_looping;
  finished = false;

  setTimerDelay(animation_delay);
  step = 0;
  first = true;

  log("animation: Animation started: " + animationToString(current_animation) +
      " (" + String(animation_delay) + "ms)" + ".");
}

void setAnimationSpeed(int value) {
  animation_delay = MIN_ANIMATION_DELAY +
                    (((long)(MAX_ANIMATION_DELAY - MIN_ANIMATION_DELAY)) *
                     constrain(value, 0, 255) / 255);
  setTimerDelay(animation_delay);
}

}  // namespace animation