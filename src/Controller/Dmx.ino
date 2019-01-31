#include <Arduino.h>
// #include <Conceptinetics.h>

#define DMX_CHANNELS 9
#define DMX_START_ADDRESS 1

#define DMX_CHANNEL_1_ACTION(x) composer::setDimmer(x)
#define DMX_CHANNEL_2_ACTION(x) composer::setRed(x)
#define DMX_CHANNEL_3_ACTION(x) composer::setGreen(x)
#define DMX_CHANNEL_4_ACTION(x) composer::setBlue(x)
#define DMX_CHANNEL_5_ACTION(x) composer::setMacro(getMacro(x))
#define DMX_CHANNEL_6_ACTION(x) composer::setMacroSpeed(x)
#define DMX_CHANNEL_7_ACTION(x) composer::setAnimation(getAnimation(x))
#define DMX_CHANNEL_8_ACTION(x) composer::setAnimationSpeed(x)
#define DMX_CHANNEL_9_ACTION(x) composer::setFilter(getFilter(x))

#define MACRO_ZONE_1_LOWER_BOUND 20
#define MACRO_ZONE_2_LOWER_BOUND 40
#define MACRO_ZONE_3_LOWER_BOUND 60
#define MACRO_ZONE_4_LOWER_BOUND 80
#define MACRO_ZONE_5_LOWER_BOUND 90
#define MACRO_ZONE_6_LOWER_BOUND 100
#define MACRO_ZONE_7_LOWER_BOUND 120
#define MACRO_ZONE_8_LOWER_BOUND 140
#define MACRO_ZONE_9_LOWER_BOUND 160
#define MACRO_ZONE_10_LOWER_BOUND 180
#define MACRO_ZONE_11_LOWER_BOUND 200
#define MACRO_ZONE_12_LOWER_BOUND 220
#define MACRO_ZONE_13_LOWER_BOUND 240
#define MACRO_ZONE_14_LOWER_BOUND 250

#define MACRO_ZONE_0 STOP
#define MACRO_ZONE_1 M_SOLID
#define MACRO_ZONE_2 M_PULSE
#define MACRO_ZONE_3 M_PULSE
#define MACRO_ZONE_4 M_PULSE
#define MACRO_ZONE_5 M_PULSE
#define MACRO_ZONE_6 M_PULSE
#define MACRO_ZONE_7 M_FLICKER
#define MACRO_ZONE_8 M_FLICKER
#define MACRO_ZONE_9 M_FLICKER
#define MACRO_ZONE_10 M_SINGLEFLASH
#define MACRO_ZONE_11 M_SINGLEFLASH
#define MACRO_ZONE_12 M_SINGLEFLASH
#define MACRO_ZONE_13 M_SINGLEFLASH
#define MACRO_ZONE_14 M_SINGLEFLASH

#define MACRO_PARAMETERS_ZONE_0
#define MACRO_PARAMETERS_ZONE_1
#define MACRO_PARAMETERS_ZONE_2   \
  composer::setParameter(0, 100); \
  composer::setParameter(1, 50);  \
  composer::setParameter(2, 100); \
  composer::setParameter(3, 50)
#define MACRO_PARAMETERS_ZONE_3
#define MACRO_PARAMETERS_ZONE_4
#define MACRO_PARAMETERS_ZONE_5
#define MACRO_PARAMETERS_ZONE_6
#define MACRO_PARAMETERS_ZONE_7
#define MACRO_PARAMETERS_ZONE_8
#define MACRO_PARAMETERS_ZONE_9
#define MACRO_PARAMETERS_ZONE_10
#define MACRO_PARAMETERS_ZONE_11
#define MACRO_PARAMETERS_ZONE_12
#define MACRO_PARAMETERS_ZONE_13
#define MACRO_PARAMETERS_ZONE_14

#define ANIMATION_ZONE_1_LOWER_BOUND 20
#define ANIMATION_ZONE_2_LOWER_BOUND 40
#define ANIMATION_ZONE_3_LOWER_BOUND 60
#define ANIMATION_ZONE_4_LOWER_BOUND 80
#define ANIMATION_ZONE_5_LOWER_BOUND 90
#define ANIMATION_ZONE_6_LOWER_BOUND 100
#define ANIMATION_ZONE_7_LOWER_BOUND 120
#define ANIMATION_ZONE_8_LOWER_BOUND 140
#define ANIMATION_ZONE_9_LOWER_BOUND 160
#define ANIMATION_ZONE_10_LOWER_BOUND 180
#define ANIMATION_ZONE_11_LOWER_BOUND 200
#define ANIMATION_ZONE_12_LOWER_BOUND 220
#define ANIMATION_ZONE_13_LOWER_BOUND 240
#define ANIMATION_ZONE_14_LOWER_BOUND 250

#define ANIMATION_ZONE_0 animation::NO_ANIMATION
#define ANIMATION_ZONE_1 animation::BACK_TO_FRONT
#define ANIMATION_ZONE_2 animation::BACK_TO_FRONT
#define ANIMATION_ZONE_3 animation::FRONT_TO_BACK
#define ANIMATION_ZONE_4 animation::FRONT_TO_BACK
#define ANIMATION_ZONE_5 animation::LEFT_TO_RIGHT
#define ANIMATION_ZONE_6 animation::LEFT_TO_RIGHT
#define ANIMATION_ZONE_7 animation::RIGHT_TO_LEFT
#define ANIMATION_ZONE_8 animation::RIGHT_TO_LEFT
#define ANIMATION_ZONE_9 animation::CHEVRON_BTF
#define ANIMATION_ZONE_10 animation::CHEVRON_BTF
#define ANIMATION_ZONE_11 animation::CHEVRON_FTB
#define ANIMATION_ZONE_12 animation::CHEVRON_FTB
#define ANIMATION_ZONE_13 animation::NO_ANIMATION
#define ANIMATION_ZONE_14 animation::NO_ANIMATION

#define FILTER_ZONE_1_LOWER_BOUND 20
#define FILTER_ZONE_2_LOWER_BOUND 40
#define FILTER_ZONE_3_LOWER_BOUND 60
#define FILTER_ZONE_4_LOWER_BOUND 80
#define FILTER_ZONE_5_LOWER_BOUND 90
#define FILTER_ZONE_6_LOWER_BOUND 100
#define FILTER_ZONE_7_LOWER_BOUND 120
#define FILTER_ZONE_8_LOWER_BOUND 140
#define FILTER_ZONE_9_LOWER_BOUND 160
#define FILTER_ZONE_10_LOWER_BOUND 180
#define FILTER_ZONE_11_LOWER_BOUND 200
#define FILTER_ZONE_12_LOWER_BOUND 220
#define FILTER_ZONE_13_LOWER_BOUND 240
#define FILTER_ZONE_14_LOWER_BOUND 250

#define FILTER_ZONE_0 filter::NULL_FILTER
#define FILTER_ZONE_1 filter::NO_FILTER
#define FILTER_ZONE_2 filter::ODD_COLUMNS
#define FILTER_ZONE_3 filter::EVEN_COLUMNS
#define FILTER_ZONE_4 filter::ODD_ROWS
#define FILTER_ZONE_5 filter::EVEN_ROWS
#define FILTER_ZONE_6 filter::CHECKERBOARD
#define FILTER_ZONE_7 filter::LEFT_HALF
#define FILTER_ZONE_8 filter::RIGHT_HALF
#define FILTER_ZONE_9 filter::LEFT_THIRD
#define FILTER_ZONE_10 filter::MIDDLE_THIRD
#define FILTER_ZONE_11 filter::NULL_FILTER
#define FILTER_ZONE_12 filter::NULL_FILTER
#define FILTER_ZONE_13 filter::NULL_FILTER
#define FILTER_ZONE_14 filter::NULL_FILTER

// Configure a DMX slave controller
// DMX_Slave dmx_receiver(DMX_CHANNELS);

uint8_t old_state;
uint8_t state[DMX_CHANNELS];
bool state_change[DMX_CHANNELS];

void initDmx() {
  // dmx_receiver.enable();
  // dmx_receiver.setStartAddress(DMX_START_ADDRESS);

  for (int i = 0; i < DMX_CHANNELS; i++) {
    state[i] = 0;
    state_change[i] = false;
  }
}

void parseDmx() {
  for (int i = 0; i < DMX_CHANNELS; i++) {
    old_state = state[i];
    // state[i] = dmx_receiver.getChannelValue(i + 1);
    if (state[i] != old_state) {
      state_change[i] = true;
    }
  }

  if (state_change[0]) {
    DMX_CHANNEL_1_ACTION(state[0]);
    state_change[0] = false;
  }
  if (state_change[1]) {
    DMX_CHANNEL_2_ACTION(state[1]);
    state_change[1] = false;
  }
  if (state_change[2]) {
    DMX_CHANNEL_3_ACTION(state[2]);
    state_change[2] = false;
  }
  if (state_change[3]) {
    DMX_CHANNEL_4_ACTION(state[3]);
    state_change[3] = false;
  }
  if (state_change[4]) {
    DMX_CHANNEL_5_ACTION(state[4]);
    state_change[4] = false;
  }
  if (state_change[5]) {
    DMX_CHANNEL_6_ACTION(state[5]);
    state_change[5] = false;
  }
  if (state_change[6]) {
    DMX_CHANNEL_7_ACTION(state[6]);
    state_change[6] = false;
  }
  if (state_change[7]) {
    DMX_CHANNEL_8_ACTION(state[7]);
    state_change[7] = false;
  }
  if (state_change[8]) {
    DMX_CHANNEL_9_ACTION(state[7]);
    state_change[8] = false;
  }
}

Command getMacro(int value) {
  if (value >= 0 && value < MACRO_ZONE_1_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_0;
    return MACRO_ZONE_0;
  } else if (value >= MACRO_ZONE_1_LOWER_BOUND &&
             value < MACRO_ZONE_2_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_1;
    return MACRO_ZONE_1;
  } else if (value >= MACRO_ZONE_2_LOWER_BOUND &&
             value < MACRO_ZONE_3_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_2;
    return MACRO_ZONE_2;
  } else if (value >= MACRO_ZONE_3_LOWER_BOUND &&
             value < MACRO_ZONE_4_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_3;
    return MACRO_ZONE_3;
  } else if (value >= MACRO_ZONE_4_LOWER_BOUND &&
             value < MACRO_ZONE_5_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_4;
    return MACRO_ZONE_4;
  } else if (value >= MACRO_ZONE_5_LOWER_BOUND &&
             value < MACRO_ZONE_6_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_5;
    return MACRO_ZONE_5;
  } else if (value >= MACRO_ZONE_6_LOWER_BOUND &&
             value < MACRO_ZONE_7_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_6;
    return MACRO_ZONE_6;
  } else if (value >= MACRO_ZONE_7_LOWER_BOUND &&
             value < MACRO_ZONE_8_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_7;
    return MACRO_ZONE_7;
  } else if (value >= MACRO_ZONE_8_LOWER_BOUND &&
             value < MACRO_ZONE_9_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_8;
    return MACRO_ZONE_8;
  } else if (value >= MACRO_ZONE_9_LOWER_BOUND &&
             value < MACRO_ZONE_10_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_9;
    return MACRO_ZONE_9;
  } else if (value >= MACRO_ZONE_10_LOWER_BOUND &&
             value < MACRO_ZONE_11_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_10;
    return MACRO_ZONE_10;
  } else if (value >= MACRO_ZONE_11_LOWER_BOUND &&
             value < MACRO_ZONE_12_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_11;
    return MACRO_ZONE_11;
  } else if (value >= MACRO_ZONE_12_LOWER_BOUND &&
             value < MACRO_ZONE_13_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_12;
    return MACRO_ZONE_12;
  } else if (value >= MACRO_ZONE_13_LOWER_BOUND &&
             value < MACRO_ZONE_14_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_13;
    return MACRO_ZONE_13;
  } else if (value >= MACRO_ZONE_14_LOWER_BOUND) {
    MACRO_PARAMETERS_ZONE_14;
    return MACRO_ZONE_14;
  }
  return NULL_COMMAND;
}

animation::Animation getAnimation(int value) {
  if (value >= 0 && value < ANIMATION_ZONE_1_LOWER_BOUND) {
    return ANIMATION_ZONE_0;
  } else if (value >= ANIMATION_ZONE_1_LOWER_BOUND &&
             value < ANIMATION_ZONE_2_LOWER_BOUND) {
    return ANIMATION_ZONE_1;
  } else if (value >= ANIMATION_ZONE_2_LOWER_BOUND &&
             value < ANIMATION_ZONE_3_LOWER_BOUND) {
    return ANIMATION_ZONE_2;
  } else if (value >= ANIMATION_ZONE_3_LOWER_BOUND &&
             value < ANIMATION_ZONE_4_LOWER_BOUND) {
    return ANIMATION_ZONE_3;
  } else if (value >= ANIMATION_ZONE_4_LOWER_BOUND &&
             value < ANIMATION_ZONE_5_LOWER_BOUND) {
    return ANIMATION_ZONE_4;
  } else if (value >= ANIMATION_ZONE_5_LOWER_BOUND &&
             value < ANIMATION_ZONE_6_LOWER_BOUND) {
    return ANIMATION_ZONE_5;
  } else if (value >= ANIMATION_ZONE_6_LOWER_BOUND &&
             value < ANIMATION_ZONE_7_LOWER_BOUND) {
    return ANIMATION_ZONE_6;
  } else if (value >= ANIMATION_ZONE_7_LOWER_BOUND &&
             value < ANIMATION_ZONE_8_LOWER_BOUND) {
    return ANIMATION_ZONE_7;
  } else if (value >= ANIMATION_ZONE_8_LOWER_BOUND &&
             value < ANIMATION_ZONE_9_LOWER_BOUND) {
    return ANIMATION_ZONE_8;
  } else if (value >= ANIMATION_ZONE_9_LOWER_BOUND &&
             value < ANIMATION_ZONE_10_LOWER_BOUND) {
    return ANIMATION_ZONE_9;
  } else if (value >= ANIMATION_ZONE_10_LOWER_BOUND &&
             value < ANIMATION_ZONE_11_LOWER_BOUND) {
    return ANIMATION_ZONE_10;
  } else if (value >= ANIMATION_ZONE_11_LOWER_BOUND &&
             value < ANIMATION_ZONE_12_LOWER_BOUND) {
    return ANIMATION_ZONE_11;
  } else if (value >= ANIMATION_ZONE_12_LOWER_BOUND &&
             value < ANIMATION_ZONE_13_LOWER_BOUND) {
    return ANIMATION_ZONE_12;
  } else if (value >= ANIMATION_ZONE_13_LOWER_BOUND &&
             value < ANIMATION_ZONE_14_LOWER_BOUND) {
    return ANIMATION_ZONE_13;
  } else if (value >= ANIMATION_ZONE_14_LOWER_BOUND) {
    return ANIMATION_ZONE_14;
  }
  return animation::NO_ANIMATION;
}

filter::Filter getFilter(int value) {
  if (value >= 0 && value < FILTER_ZONE_1_LOWER_BOUND) {
    return FILTER_ZONE_0;
  } else if (value >= FILTER_ZONE_1_LOWER_BOUND &&
             value < FILTER_ZONE_2_LOWER_BOUND) {
    return FILTER_ZONE_1;
  } else if (value >= FILTER_ZONE_2_LOWER_BOUND &&
             value < FILTER_ZONE_3_LOWER_BOUND) {
    return FILTER_ZONE_2;
  } else if (value >= FILTER_ZONE_3_LOWER_BOUND &&
             value < FILTER_ZONE_4_LOWER_BOUND) {
    return FILTER_ZONE_3;
  } else if (value >= FILTER_ZONE_4_LOWER_BOUND &&
             value < FILTER_ZONE_5_LOWER_BOUND) {
    return FILTER_ZONE_4;
  } else if (value >= FILTER_ZONE_5_LOWER_BOUND &&
             value < FILTER_ZONE_6_LOWER_BOUND) {
    return FILTER_ZONE_5;
  } else if (value >= FILTER_ZONE_6_LOWER_BOUND &&
             value < FILTER_ZONE_7_LOWER_BOUND) {
    return FILTER_ZONE_6;
  } else if (value >= FILTER_ZONE_7_LOWER_BOUND &&
             value < FILTER_ZONE_8_LOWER_BOUND) {
    return FILTER_ZONE_7;
  } else if (value >= FILTER_ZONE_8_LOWER_BOUND &&
             value < FILTER_ZONE_9_LOWER_BOUND) {
    return FILTER_ZONE_8;
  } else if (value >= FILTER_ZONE_9_LOWER_BOUND &&
             value < FILTER_ZONE_10_LOWER_BOUND) {
    return FILTER_ZONE_9;
  } else if (value >= FILTER_ZONE_10_LOWER_BOUND &&
             value < FILTER_ZONE_11_LOWER_BOUND) {
    return FILTER_ZONE_10;
  } else if (value >= FILTER_ZONE_11_LOWER_BOUND &&
             value < FILTER_ZONE_12_LOWER_BOUND) {
    return FILTER_ZONE_11;
  } else if (value >= FILTER_ZONE_12_LOWER_BOUND &&
             value < FILTER_ZONE_13_LOWER_BOUND) {
    return FILTER_ZONE_12;
  } else if (value >= FILTER_ZONE_13_LOWER_BOUND &&
             value < FILTER_ZONE_14_LOWER_BOUND) {
    return FILTER_ZONE_13;
  } else if (value >= FILTER_ZONE_14_LOWER_BOUND) {
    return FILTER_ZONE_14;
  }
  return filter::NULL_FILTER;
}