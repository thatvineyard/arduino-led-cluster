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
char column_character;
char column_regex[10];
char row_regex[10];
char iteration_regex[20];

byte step = 0;

void lastStepReached() {
  if (looping) {
    step = 0;
  } else {
    finished = true;
  }
}

void a_random(char* regex_buffer) {
  strcpy(regex_buffer, "");

  if (step > 0) {
    lastStepReached();
  }

  char column_character;
  bool first_column = true;

  randomSeed(millis());

  for (int i = 0; i < NUM_COLUMNS; i++) {
    // This randomization is lazy. It will allow a random last digit, but will
    // match on any tens digit. For example is 2 is randomly selected then 02,
    // 12 and 22 will match.
    // TODO: This can be improved with multiple or-selectors, but that is a
    // future improvement.

    strcpy(iteration_regex, "");
    strcpy(column_regex, "");
    column_character = START_CHARACTER + i;
    strncat(column_regex, &column_character, 1);
    strcat(column_regex, ".");

    strcpy(row_regex, "[");
    for (int j = 0; j < 1; j++) {
      if (random(2) == 1) {
        sprintf(temp_number_buffer, "%d", j);
        strcat(row_regex, temp_number_buffer);
      }
    }
    strcat(row_regex, "]");

    strcat(iteration_regex, column_regex);
    strcat(iteration_regex, row_regex);

    if (i == 0) {
      strcpy(regex_buffer, iteration_regex);
    } else {
      orSelector(regex_buffer, iteration_regex);
    }
  }
}

void a_horizontal_sweep(char* regex_buffer, bool left_to_right) {
  strcpy(regex_buffer, "");

  if (step >= NUM_COLUMNS) {
    lastStepReached();
  }

  if (left_to_right) {
    column_character = START_CHARACTER + step;
  } else {
    column_character = START_CHARACTER + ((NUM_COLUMNS - 1) - step);
  }

  strncat(regex_buffer, &column_character, 1);
  strcat(regex_buffer, "..");
}

void a_vertical_sweep(char* regex_buffer, bool front_to_back) {
  strcpy(regex_buffer, "");

  if (step >= NUM_ROWS) {
    lastStepReached();
  }

  strcat(column_regex, ".");

  if (front_to_back) {
    sprintf(row_regex, "%02d", NUM_ROWS - step);
  } else {
    sprintf(row_regex, "%02d", (step + 1));
  }

  strcat(regex_buffer, column_regex);
  strcat(regex_buffer, row_regex);
}

void a_mirrored(char* regex_buffer, bool inward) {
  strcpy(regex_buffer, "");

  if (step >= NUM_COLUMNS / 2) {
    lastStepReached();
  }

  if (inward) {
    column_character = START_CHARACTER + step;
  } else {
    column_character = START_CHARACTER + ((NUM_COLUMNS / 2) - step - 1);
  }

  sprintf(column_regex, "%d", column_character);
  strcpy(row_regex, "..");
  strcpy(iteration_regex, column_regex);
  strcat(iteration_regex, row_regex);
  strcpy(regex_buffer, iteration_regex);

  if (inward) {
    column_character = START_CHARACTER + ((NUM_COLUMNS - 1) - step);
  } else {
    column_character =
        START_CHARACTER + ((NUM_COLUMNS / 2) + step - 1) + MIDDLE_SHIFT;
  }

  sprintf(iteration_regex, "%c..", column_character);
  orSelector(regex_buffer, iteration_regex);
}

void a_chevron(char* regex_buffer, bool front_to_back) {
  strcpy(regex_buffer, "");

  if (step > NUM_ROWS) {
    lastStepReached();
  }

  char column_character_left;
  char column_character_right;
  for (int i = 0; i < NUM_COLUMNS / 2; i++) {
    column_character_left = START_CHARACTER + (NUM_COLUMNS / 2) - i - 1;
    column_character_right =
        START_CHARACTER + (NUM_COLUMNS / 2) + i - 1 + MIDDLE_SHIFT;

    sprintf(column_regex, "[%c%c]", column_character_left,
            column_character_right);

    if (front_to_back) {
      sprintf(row_regex, "%02d", NUM_ROWS - (step - i));
    } else {
      sprintf(row_regex, "%02d", (step - i));
    }

    if (i == 0) {
      strcpy(regex_buffer, column_regex);
      strcat(regex_buffer, row_regex);
    } else {
      strcpy(iteration_regex, column_regex);
      strcat(iteration_regex, row_regex);
      orSelector(regex_buffer, iteration_regex);
    }
  }
}

void animationToSelector(char* regex_buffer) {
  switch (current_animation) {
    case NO_ANIMATION:
    default:
      strcpy(regex_buffer, ".*");
      step = 0;
      break;
    case RANDOM:
      a_random(regex_buffer);
      break;
    case LEFT_TO_RIGHT:
      a_horizontal_sweep(regex_buffer, true);
      break;
    case RIGHT_TO_LEFT:
      a_horizontal_sweep(regex_buffer, false);
      break;
    case BACK_TO_FRONT:
      a_vertical_sweep(regex_buffer, false);
      break;
    case FRONT_TO_BACK:
      a_vertical_sweep(regex_buffer, true);
      break;
    case OUTWARD:
      a_mirrored(regex_buffer, false);
      break;
    case INWARD:
      a_mirrored(regex_buffer, true);
      break;
    case CHEVRON_FTB:
      a_chevron(regex_buffer, true);
      break;
    case CHEVRON_BTF:
      a_chevron(regex_buffer, false);
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

void getNextFrame(char* regex_buffer) {
  animationToSelector(regex_buffer);
  first = false;
  step++;
  restartTimer();
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