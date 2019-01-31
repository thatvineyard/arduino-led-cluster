#include <Arduino.h>

// PINOUT
#define FADER_A -1
#define FADER_B -1
#define FADER_C -1
#define FADER_D -1

// potentiometer pins are analog
#define POT_A 2
#define POT_B 3

#define POT_A_RESOLUTION 25
#define POT_B_RESOLUTION 25

#define BUTTON_A 11
#define BUTTON_B 12
#define BUTTON_C 13
#define BUTTON_D 10
#define BUTTON_E 9

#define BUTTON_A_GROUND true
#define BUTTON_B_GROUND true
#define BUTTON_C_GROUND true
#define BUTTON_D_GROUND true
#define BUTTON_E_GROUND true

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

#define POT_A_ACTION(x) composer::setDimmer(x)
#define POT_B_ACTION(x) halvan::setIntensity(x)

#define BUTTON_A_ACTION halvan::lightOneAtATime()
#define BUTTON_B_ACTION halvan::lightNextOneBad()
#define BUTTON_C_ACTION halvan::reset()
#define BUTTON_D_ACTION halvan::lightHarryPotterFirst()
#define BUTTON_E_ACTION halvan::lightHarryPotterSecond()

#define ENCODER_A_BUTTON_ACTION parameterScroll()
#define ENCODER_A_CW_ACTION parameterIncrement()
#define ENCODER_A_CCW_ACTION parameterDecrement()

#define ENCODER_B_BUTTON_ACTION controlScroll()
#define ENCODER_B_CW_ACTION controlIncrement()
#define ENCODER_B_CCW_ACTION controlDecrement()

byte button_a_state = 0;
byte button_b_state = 0;
byte button_c_state = 0;
byte button_d_state = 0;
byte button_e_state = 0;
int pot_a_state = 0;
int pot_b_state = 0;
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

  // if (POT_A != -1) {
  //   pinMode(POT_A, INPUT);
  // }

  // if (POT_B != -1) {
  //   pinMode(POT_B, INPUT);
  // }

  if (BUTTON_A != -1) {
    if (BUTTON_A_GROUND) {
      pinMode(BUTTON_A, INPUT_PULLUP);
    } else {
      pinMode(BUTTON_A, INPUT);
    }
  }
  if (BUTTON_B != -1) {
    if (BUTTON_B_GROUND) {
      pinMode(BUTTON_B, INPUT_PULLUP);
    } else {
      pinMode(BUTTON_B, INPUT);
    }
  }
  if (BUTTON_C != -1) {
    if (BUTTON_C_GROUND) {
      pinMode(BUTTON_C, INPUT_PULLUP);
    } else {
      pinMode(BUTTON_C, INPUT);
    }
  }
  if (BUTTON_D != -1) {
    if (BUTTON_D_GROUND) {
      pinMode(BUTTON_D, INPUT_PULLUP);
    } else {
      pinMode(BUTTON_D, INPUT);
    }
  }
  if (BUTTON_E != -1) {
    if (BUTTON_E_GROUND) {
      pinMode(BUTTON_E, INPUT_PULLUP);
    } else {
      pinMode(BUTTON_E, INPUT);
    }
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
  byte old_state;
  int old_int_state;

  // buttons
  if (BUTTON_A != -1) {
    old_state = button_a_state;
    button_a_state = digitalRead(BUTTON_A);
    if ((!BUTTON_A_GROUND && button_a_state == HIGH && old_state == LOW) ||
        (BUTTON_A_GROUND && button_a_state == LOW && old_state == HIGH)) {
      BUTTON_A_ACTION;
    }
  }

  if (BUTTON_B != -1) {
    old_state = button_b_state;
    button_b_state = digitalRead(BUTTON_B);
    if ((!BUTTON_B_GROUND && button_b_state == HIGH && old_state == LOW) ||
        (BUTTON_B_GROUND && button_b_state == LOW && old_state == HIGH)) {
      BUTTON_B_ACTION;
    }
  }

  if (BUTTON_C != -1) {
    old_state = button_c_state;
    button_c_state = digitalRead(BUTTON_C);
    if ((!BUTTON_C_GROUND && button_c_state == HIGH && old_state == LOW) ||
        (BUTTON_C_GROUND && button_c_state == LOW && old_state == HIGH)) {
      BUTTON_C_ACTION;
    }
  }

  if (BUTTON_D != -1) {
    old_state = button_d_state;
    button_d_state = digitalRead(BUTTON_D);
    if ((!BUTTON_D_GROUND && button_d_state == HIGH && old_state == LOW) ||
        (BUTTON_D_GROUND && button_d_state == LOW && old_state == HIGH)) {
      BUTTON_D_ACTION;
    }
  }

  if (BUTTON_E != -1) {
    old_state = button_e_state;
    button_e_state = digitalRead(BUTTON_E);
    if ((!BUTTON_E_GROUND && button_e_state == HIGH && old_state == LOW) ||
        (BUTTON_E_GROUND && button_e_state == LOW && old_state == HIGH)) {
      BUTTON_E_ACTION;
    }
  }

  // log("Old state" + String(old_state) + " new state" +
  //     String(button_d_state));

  // potentiometers
  if (POT_A != 1) {
    old_int_state = pot_a_state;
    pot_a_state = analogRead(POT_A);
    if (abs(old_int_state - pot_a_state) > POT_A_RESOLUTION) {
      POT_A_ACTION(mapScale(LINEAR, 255, 1023, pot_a_state));
    } else {
      pot_a_state = old_int_state;
    }
  }
  if (POT_B != 1) {
    old_int_state = pot_b_state;
    pot_b_state = analogRead(POT_B);
    if (abs(old_int_state - pot_b_state) > POT_B_RESOLUTION) {
      POT_B_ACTION(mapScale(LINEAR, 255, 1023, pot_b_state));
    } else {
      pot_b_state = old_int_state;
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
  lcd::requestParameterUpdate();
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
