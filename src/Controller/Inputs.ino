#include <Arduino.h>

// INPUTS
#define SCROLL_BUTTON 2
int scroll_button_state = 0;

#define ENCODER_WHEEL_CW 4
#define ENCODER_WHEEL_CCW 3
int encoder_wheel_state = 0;

#define MAX_VALUE 255
#define ENCODER_DELTA 2

void initInput() {
  pinMode(SCROLL_BUTTON, INPUT);
  pinMode(ENCODER_WHEEL_CW, INPUT);
  pinMode(ENCODER_WHEEL_CCW, INPUT);

  encoder_wheel_state = digitalRead(ENCODER_WHEEL_CW);
}

void parseInputs() {
  // scroll button
  int scroll_button_state_old = scroll_button_state;
  scroll_button_state = digitalRead(SCROLL_BUTTON);
  if (scroll_button_state == HIGH && scroll_button_state_old == LOW) {
    parameter_scroll = (parameter_scroll + 1) % MAX_PARAMETERS;
    change = true;
  }

  // encoder wheel
  int encoder_wheel_state_old = encoder_wheel_state;

  encoder_wheel_state = digitalRead(ENCODER_WHEEL_CW);

  if (encoder_wheel_state == HIGH &&
      encoder_wheel_state != encoder_wheel_state_old) {
    if (digitalRead(ENCODER_WHEEL_CCW) == LOW) {
      parameters[parameter_scroll] =
          (parameters[parameter_scroll] + ENCODER_DELTA) % MAX_VALUE;
    } else {
      parameters[parameter_scroll] =
          (parameters[parameter_scroll] + MAX_VALUE - ENCODER_DELTA) %
          MAX_VALUE;
    }
    change = true;
  }
}
