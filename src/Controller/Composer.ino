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

// FILTER
Filter current_filter = NO_FILTER;
bool filter_changed = false;

// FREEZE
bool freeze_animation = false;
bool freeze_settings = false;

// SET
void setMacro(Command new_macro, int number_of_parameters) {
  if (current_macro != new_macro) {
    current_macro = new_macro;
    current_number_of_parameters = number_of_parameters;
    macro_changed = true;
    log("composer: macro set to " + commandToString(current_macro) + " with " +
        number_of_parameters + " parameters");
  }
}

void setMacro(Command new_macro) {
  setMacro(new_macro, number_of_parameters(new_macro));
}

void setParameter(int parameter_number, int value) {
  value = constrain(value, 0, MAX_VALUE);
  if (parameters[parameter_number] != value) {
    parameters[parameter_number] = value;
    parameters_changed = true;
    log("composer: parameter " + String(parameter_number) + " set to " +
        String(parameters[parameter_number]));
  }
}

void changeParameter(int parameter_number, int delta) {
  setParameter(parameter_number, parameters[parameter_number] + delta);
}

void setMacroSpeed(int value) {
  value = constrain(value, 0, MAX_VALUE);
  if (macro_speed_value != value) {
    macro_speed_value = value;
    macro_speed_changed = true;
    log("composer: macro speed set to " + String(macro_speed_value));
  }
}

void changeMacroSpeed(int delta) { setMacroSpeed(macro_speed_value + delta); }

void setFilter(Filter new_filter) {
  if (current_filter != new_filter) {
    current_filter = new_filter;
    filter_changed = true;
    log("composer: filter set to " + String((Filter)current_filter));
  }
}

void setAnimation(Animation new_animation) {
  if (current_animation != new_animation) {
    current_animation = new_animation;
    animation_changed = true;
    log("composer: animation set to " + String((Animation)current_animation));
  }
}

void setAnimationSpeed(int value) {
  value = constrain(value, 0, MAX_VALUE);
  if (animation_speed_value != value) {
    animation_speed_value = value;
    animation_speed_changed = true;
    log("composer: animation speed set to " + String(animation_speed_value));
  }
}

void changeAnimationSpeed(int delta) {
  setAnimationSpeed(animation_speed_value + delta);
}

void setDimmer(int value) {
  value = constrain(value, 0, MAX_BRIGHTNESS);
  if (dimmer_value != value) {
    dimmer_value = value;
    color_changed = true;
    log("composer: dimmer set to " + String(dimmer_value));
  }
}

void changeDimmer(int delta) { setDimmer(dimmer_value + delta); }

void setRed(int value) {
  value = constrain(value, 0, MAX_RED);
  if (red_value != value) {
    red_value = value;
    color_changed = true;
    log("composer: red set to " + String(red_value));
  }
}

void changeRed(int delta) { setRed(red_value + delta); }

void setGreen(int value) {
  value = constrain(value, 0, MAX_GREEN);
  if (green_value != value) {
    green_value = value;
    color_changed = true;
    log("composer: green set to " + String(green_value));
  }
}
void changeGreen(int delta) { setGreen(green_value + delta); }

void setBlue(int value) {
  value = constrain(value, 0, MAX_BLUE);
  if (blue_value != value) {
    blue_value = value;
    color_changed = true;
    log("composer: blue set to " + String(blue_value));
  }
}

void changeBlue(int delta) { setBlue(blue_value + delta); }

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

    String parameter_string = "";
    for (int i = 0; i < current_number_of_parameters; i++) {
      parameter_string += String(parameters[i]);
      if (i + 1 != current_number_of_parameters) {
        parameter_string += " ";
      }
    }
    sender::sendMessage(andSelector(animation_regex, filter_regex),
                        commandToString(current_macro), parameter_string);
  }
}

void sendSettings() {
  if (dimmer_changed) {
    sender::sendDimmer(dimmer_value);
    dimmer_changed = false;
    log("composer: sending dimmer (" + String(dimmer_value) + ")");
  }
  if (color_changed) {
    sender::sendColor(red_value, green_value, blue_value);
    color_changed = false;
    log("composer: sending color (" + String(red_value) + ", " +
        String(green_value) + "," + String(blue_value) + ")");
  }
  if (macro_speed_changed) {
    sender::sendMacroSpeed(macro_speed_value);
    macro_speed_changed = false;
    log("composer: sending macro speed (" + String(macro_speed_value) + ")");
  }
}

void update() {
  if (animation_changed) {
    log("composer: starting animation " + String(current_animation));
    animation::startAnimation(current_animation, true);
    animation_changed = false;
  }
  if (animation_speed_changed) {
    animation::setAnimationSpeed(animation_speed_value);
    animation_speed_changed = false;
  }
  if (!freeze_animation) {
    sendNextFrame();
  }
  if (!freeze_settings) {
    sendSettings();
  }
}

void freezeAnimation() { freeze_animation = true; }

void unfreezeAnimation() { freeze_animation = false; }

void freezeSettings() { freeze_settings = true; }

void unfreezeSetting() { freeze_settings = false; }

}  // namespace composer