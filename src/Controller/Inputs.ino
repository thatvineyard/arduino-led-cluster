#include <Arduino.h>

// PINOUT
#define FADER_A 8
#define FADER_B 9
#define FADER_C 11
#define FADER_D 12

// #define POT_A -1

#define BUTTON_A 10

#define ENCODER_A_BUTTON 2
#define ENCODER_A_CW 4
#define ENCODER_A_CCW 3
#define ENCODER_B_BUTTON 5
#define ENCODER_B_CW 6
#define ENCODER_B_CCW 7

// ACTIONS

#define FADER_A_ACTION(x) composer::setDimmer(x)
#define FADER_B_ACTION(x) composer::setRed(x)
#define FADER_C_ACTION(x) composer::setGreen(x)
#define FADER_D_ACTION(x) composer::setBlue(x)

// #define POT_A_ACTION(x) setMacroSpeed(x)

#define BUTTON_A_ACTION sender::sendMacroPROTOTYPE()

#define ENCODER_A_BUTTON_ACTION parameterScroll()
#define ENCODER_A_CW_ACTION parameterIncrement()
#define ENCODER_A_CCW_ACTION parameterDecrement()

#define ENCODER_B_BUTTON_ACTION controlScroll()
#define ENCODER_B_CW_ACTION controlIncrement()
#define ENCODER_B_CCW_ACTION controlDecrement()

int button_a_state = 0;
int encoder_a_button_state = 0;
int encoder_a_wheel_state = 0;
int encoder_b_button_state = 0;
int encoder_b_wheel_state = 0;

#define ENCODER_DELTA 2

void initInput() {
  pinMode(FADER_A, INPUT);
  pinMode(FADER_B, INPUT);
  pinMode(FADER_C, INPUT);

  // pinMode(POT_A, INPUT);

  pinMode(BUTTON_A, INPUT);

  pinMode(ENCODER_A_BUTTON, INPUT);
  pinMode(ENCODER_A_CW, INPUT);
  pinMode(ENCODER_A_CCW, INPUT);

  encoder_a_wheel_state = digitalRead(ENCODER_A_CW);
}

void parseInputs() {
  int old_state;

  // faders

  // buttons
  old_state = button_a_state;
  button_a_state = digitalRead(BUTTON_A);
  if (button_a_state == HIGH && old_state == LOW) {
    BUTTON_A_ACTION;
  }

  // encoder buttons

  old_state = encoder_a_button_state;
  encoder_a_button_state = digitalRead(ENCODER_A_BUTTON);
  if (encoder_a_button_state == HIGH && old_state == LOW) {
    ENCODER_A_BUTTON_ACTION;
  }
  old_state = encoder_b_button_state;
  encoder_b_button_state = digitalRead(ENCODER_B_BUTTON);
  if (encoder_b_button_state == HIGH && old_state == LOW) {
    ENCODER_B_BUTTON_ACTION;
  }

  // encoder wheels
  old_state = encoder_a_wheel_state;
  encoder_a_wheel_state = digitalRead(ENCODER_A_CW);
  if (encoder_a_wheel_state == HIGH && encoder_a_wheel_state != old_state) {
    if (digitalRead(ENCODER_A_CCW) == LOW) {
      ENCODER_A_CW_ACTION;
    } else {
      ENCODER_A_CCW_ACTION;
    }
  }
  old_state = encoder_b_wheel_state;
  encoder_b_wheel_state = digitalRead(ENCODER_B_CW);
  if (encoder_b_wheel_state == HIGH && encoder_b_wheel_state != old_state) {
    if (digitalRead(ENCODER_A_CCW) == LOW) {
      ENCODER_B_CW_ACTION;
    } else {
      ENCODER_B_CCW_ACTION;
    }
  }
}

void parameterScroll() {
  parameterScroll();
  lcd::requestUpdate();
}

void parameterIncrement() {
  view::changeSelectedParameter(ENCODER_DELTA);
  lcd::requestUpdate();
}

void parameterDecrement() {
  view::changeSelectedParameter(ENCODER_DELTA * -1);
  lcd::requestUpdate();
}

void controlScroll() {
  view::scrollControl(ENCODER_DELTA);
  lcd::requestUpdate();
}

void controlIncrement() {
  view::changeSelectedControl(ENCODER_DELTA);
  lcd::requestUpdate();
}
void controlDecrement() {
  view::changeSelectedControl(ENCODER_DELTA * -1);
  lcd::requestUpdate();
}
