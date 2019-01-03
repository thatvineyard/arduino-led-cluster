#include <Arduino.h>

// INPUTS

#define RED_BUTTON 10
#define ENCODER_WHEEL_BUTTON 2
#define ENCODER_WHEEL_CW 4
#define ENCODER_WHEEL_CCW 3

#define RED_BUTTON_ACTION sendMacroCommand()
#define ENCODER_WHEEL_BUTTON_ACTION parameterScroll()
#define ENCODER_WHEEL_CW_ACTION parameterIncrement()
#define ENCODER_WHEEL_CCW_ACTION parameterDecrement()
int red_button_state = 0;
int encoder_button_state = 0;
int encoder_wheel_state = 0;

#define MAX_VALUE 255
#define ENCODER_DELTA 2

void initInput() {
  pinMode(RED_BUTTON, INPUT);
  pinMode(ENCODER_WHEEL_BUTTON, INPUT);
  pinMode(ENCODER_WHEEL_CW, INPUT);
  pinMode(ENCODER_WHEEL_CCW, INPUT);

  encoder_wheel_state = digitalRead(ENCODER_WHEEL_CW);
}

void parseInputs() {
  // red button
  int red_button_state_old = red_button_state;
  red_button_state = digitalRead(RED_BUTTON);
  if (red_button_state == HIGH && red_button_state_old == LOW) {
    RED_BUTTON_ACTION;
  }

  // encoder button
  int encoder_button_state_old = encoder_button_state;
  encoder_button_state = digitalRead(ENCODER_WHEEL_BUTTON);
  if (encoder_button_state == HIGH && encoder_button_state_old == LOW) {
    ENCODER_WHEEL_BUTTON_ACTION;
  }

  // encoder wheel
  int encoder_wheel_state_old = encoder_wheel_state;

  encoder_wheel_state = digitalRead(ENCODER_WHEEL_CW);

  if (encoder_wheel_state == HIGH &&
      encoder_wheel_state != encoder_wheel_state_old) {
    if (digitalRead(ENCODER_WHEEL_CCW) == LOW) {
      ENCODER_WHEEL_CW_ACTION;
    } else {
      ENCODER_WHEEL_CCW_ACTION;
    }
  }
}

void parameterScroll() {
  parameter_scroll = (parameter_scroll + 1) % MAX_PARAMETERS;
  change = true;
}

void parameterIncrement() {
  parameters[parameter_scroll] =
      (parameters[parameter_scroll] + ENCODER_DELTA) % MAX_VALUE;
  change = true;
}

void parameterDecrement() {
  parameters[parameter_scroll] =
      (parameters[parameter_scroll] + MAX_VALUE - ENCODER_DELTA) % MAX_VALUE;
  change = true;
}