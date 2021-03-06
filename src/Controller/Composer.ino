#include <Arduino.h>

namespace composer {

char regex_string[MAX_MESSAGE_REGEX_LENTGH];
char parameter_string[MAX_PARAMETERS * 4 + 5];

// DIMMER
byte dimmer_value = 255;
bool dimmer_changed;

// RGB
byte red_value = 0;
byte green_value = 0;
byte blue_value = 0;
bool color_changed;

// SPEED
byte macro_speed_value = 100;
bool macro_speed_changed;

// MACRO
Command current_macro = NULL_COMMAND;
bool macro_changed = true;
byte current_number_of_parameters = 0;

byte parameters[MAX_PARAMETERS];
bool parameters_changed = false;

// ANIMATION
animation::Animation current_animation = animation::NULL_ANIMATION;
bool animation_changed = true;
byte animation_speed_value = 200;
bool animation_speed_changed = true;
long previous_animation_regex_hash = 0;
bool animation_loop = false;

// FILTER
filter::Filter current_filter = filter::NULL_FILTER;
bool filter_changed = true;

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

void setFilter(filter::Filter new_filter) {
  if (current_filter != new_filter) {
    current_filter = new_filter;
    filter_changed = true;
    log("composer: filter set to " + filter::filterToString(current_filter));
  }
}

void setAnimation(animation::Animation new_animation, bool new_animation_loop) {
  if (current_animation != new_animation) {
    current_animation = new_animation;
    animation_changed = true;
    animation_loop = new_animation_loop;
    log("composer: animation set to " +
        animation::animationToString(current_animation) +
        " looping: " + String(animation_loop));
  }
}

void setAnimation(animation::Animation new_animation) {
  setAnimation(new_animation, true);
}

void setAnimationForceUpdate(animation::Animation new_animation,
                             bool new_animation_loop) {
  current_animation = animation::NULL_ANIMATION;
  setAnimation(new_animation, new_animation_loop);
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
    dimmer_changed = true;
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
  bool send = false;
  if (animation::nextFrameReady() || macro_changed || parameters_changed ||
      filter_changed) {
    strcpy(regex_string, "");
    strcpy(parameter_string, "");
    if (animation::nextFrameReady()) {
      animation::getNextFrame(regex_string);
      lcd::requestAnimationUpdate();
    } else {
      animation::getPreviousFrame(regex_string);
    }
    macro_changed = false;
    parameters_changed = false;
    filter_changed = false;

    andSelectorCharBuffer(regex_string,
                          filterToSelector(current_filter).c_str());

    for (int i = 0; i < current_number_of_parameters; i++) {
      sprintf(parameter_string + strlen(parameter_string), "%d", parameters[i]);
      if (i + 1 != current_number_of_parameters) {
        strcat(parameter_string, " ");
      }
    }
    sender::sendMessage(regex_string, commandToString(current_macro),
                        parameter_string);
  }
}  // namespace composer

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
    log("composer: starting animation " +
        animation::animationToString(current_animation) +
        " with looping:" + String(animation_loop));
    if (current_animation == animation::NO_ANIMATION) {
      animation::startAnimation(current_animation, false);
    } else {
      animation::startAnimation(current_animation, animation_loop);
    }
    animation_changed = false;
  }
  if (animation_speed_changed) {
    animation::setAnimationSpeed(animation_speed_value);
    animation_speed_changed = false;
  }
  if (!freeze_settings) {
    sendSettings();
  }
  if (!freeze_animation) {
    sendNextFrame();
  }
}

void freezeAnimation() { freeze_animation = true; }

void unfreezeAnimation() { freeze_animation = false; }

void freezeSettings() { freeze_settings = true; }

void unfreezeSetting() { freeze_settings = false; }

}  // namespace composer