#include <Arduino.h>

// PINOUT
#define FADER_A -1
#define FADER_B -1
#define FADER_C -1
#define FADER_D -1

#define POT_A -1

#define BUTTON_A -1

#define ENCODER_A_BUTTON 3
#define ENCODER_A_CW 5
#define ENCODER_A_CCW 4
#define ENCODER_B_BUTTON 6
#define ENCODER_B_CW 8
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

byte button_a_state = 0;
byte encoder_a_button_state = 0;
byte encoder_a_wheel_state = 0;
byte encoder_b_button_state = 0;
byte encoder_b_wheel_state = 0;

#define ENCODER_DELTA 5

void initInput() {
  if (FADER_A != -1) {
    pinMode(FADER_A, INPUT);
  }
  if (FADER_B != -1) {
    pinMode(FADER_B, INPUT);
  }
  if (FADER_C != -1) {
    pinMode(FADER_C, INPUT);
  }

  if (POT_A != -1) {
    pinMode(POT_A, INPUT);
  }

  if (BUTTON_A != -1) {
    pinMode(BUTTON_A, INPUT);
  }

  if (ENCODER_A_BUTTON != -1) {
    pinMode(ENCODER_A_BUTTON, INPUT);
  }

  if (ENCODER_A_CW != -1 && ENCODER_B_CCW != -1) {
    pinMode(ENCODER_A_CW, INPUT);
    pinMode(ENCODER_A_CCW, INPUT);
    encoder_a_wheel_state = digitalRead(ENCODER_A_CW);
  }
}

void parseInputs() {
  int old_state;

  // faders

  // buttons
  if (BUTTON_A != -1) {
    old_state = button_a_state;
    button_a_state = digitalRead(BUTTON_A);
    if (button_a_state == HIGH && old_state == LOW) {
      BUTTON_A_ACTION;
    }
  }

  // encoder buttons

  if (ENCODER_A_BUTTON != -1) {
    old_state = encoder_a_button_state;
    encoder_a_button_state = digitalRead(ENCODER_A_BUTTON);
    if (encoder_a_button_state == HIGH && old_state == LOW) {
      ENCODER_A_BUTTON_ACTION;
    }
  }
  if (ENCODER_B_BUTTON != -1) {
    old_state = encoder_b_button_state;
    encoder_b_button_state = digitalRead(ENCODER_B_BUTTON);
    if (encoder_b_button_state == HIGH && old_state == LOW) {
      ENCODER_B_BUTTON_ACTION;
    }
  }

  // encoder wheels
  if (ENCODER_A_CW != -1 && ENCODER_A_CCW != -1) {
    old_state = encoder_a_wheel_state;
    encoder_a_wheel_state = digitalRead(ENCODER_A_CW);
    if (encoder_a_wheel_state == HIGH && encoder_a_wheel_state != old_state) {
      if (digitalRead(ENCODER_A_CCW) == LOW) {
        ENCODER_A_CW_ACTION;
      } else {
        ENCODER_A_CCW_ACTION;
      }
    }
  }
  if (ENCODER_B_CW != -1 && ENCODER_B_CCW != -1) {
    old_state = encoder_b_wheel_state;
    encoder_b_wheel_state = digitalRead(ENCODER_B_CW);
    if (encoder_b_wheel_state == HIGH && encoder_b_wheel_state != old_state) {
      if (digitalRead(ENCODER_B_CCW) == LOW) {
        ENCODER_B_CW_ACTION;
      } else {
        ENCODER_B_CCW_ACTION;
      }
    }
  }
}

void parameterScroll() {
  view::scrollParameter(ENCODER_DELTA);
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
