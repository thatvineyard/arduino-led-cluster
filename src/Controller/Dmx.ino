#include <Arduino.h>
// #include <Conceptinetics.h>

#define DMX_RX_PIN 3
#define DMX_TX_PIN 4

#define DMX_CHANNELS 8
#define DMX_START_ADDRESS 1

#define DMX_CHANNEL_1_ACTION(x) composer::setDimmer(x)
#define DMX_CHANNEL_2_ACTION(x) composer::setRed(x)
#define DMX_CHANNEL_3_ACTION(x) composer::setBlue(x)
#define DMX_CHANNEL_4_ACTION(x) composer::setGreen(x)
#define DMX_CHANNEL_5_ACTION(x) composer::setMacro(getMacro(x))
#define DMX_CHANNEL_6_ACTION(x) composer::setAnimation(getAnimation(x))
#define DMX_CHANNEL_7_ACTION(x) composer::setAnimationSpeed(x)
#define DMX_CHANNEL_8_ACTION(x) composer::setFilter(x)

#define MACRO_ZONE_1_LOWER_BOUND 20
#define MACRO_ZONE_2_LOWER_BOUND 40
#define MACRO_ZONE_3_LOWER_BOUND 60
#define MACRO_ZONE_4_LOWER_BOUND 80
#define MACRO_ZONE_5_LOWER_BOUND 90
#define MACRO_ZONE_6_LOWER_BOUND 100

#define MACRO_ZONE_0 NULL_COMMAND
#define MACRO_ZONE_1 NULL_COMMAND
#define MACRO_ZONE_2 NULL_COMMAND
#define MACRO_ZONE_3 NULL_COMMAND
#define MACRO_ZONE_4 NULL_COMMAND
#define MACRO_ZONE_5 NULL_COMMAND
#define MACRO_ZONE_6 NULL_COMMAND

#define ANIMATION_ZONE_1_LOWER_BOUND 20
#define ANIMATION_ZONE_2_LOWER_BOUND 40
#define ANIMATION_ZONE_3_LOWER_BOUND 60
#define ANIMATION_ZONE_4_LOWER_BOUND 80
#define ANIMATION_ZONE_5_LOWER_BOUND 90
#define ANIMATION_ZONE_6_LOWER_BOUND 100

#define ANIMATION_ZONE_0 NULL_COMMAND
#define ANIMATION_ZONE_1 NULL_COMMAND
#define ANIMATION_ZONE_2 NULL_COMMAND
#define ANIMATION_ZONE_3 NULL_COMMAND
#define ANIMATION_ZONE_4 NULL_COMMAND
#define ANIMATION_ZONE_5 NULL_COMMAND
#define ANIMATION_ZONE_6 NULL_COMMAND

// Configure a DMX slave controller
// DMX_Slave dmx_receiver(DMX_CHANNELS);

int old_state;
int state[DMX_CHANNELS];
bool state_change[DMX_CHANNELS];

void initDmx() {
  //   dmx_receiver.enable();
  //   dmx_receiver.setStartAddress(DMX_START_ADDRESS);

  for (int i = 0; i < DMX_CHANNELS; i++) {
    state[i] = 0;
    state_change[i] = false;
  }
}

void parseDmx() {
  for (int i = 0; i < DMX_CHANNELS; i++) {
    old_state = state[i];
    // state[i] = dmx_receiver.getChannelValue(i);
    if (state[i] != old_state) {
      state_change[i] = true;
    }
  }

  if (state_change[0]) {
    DMX_CHANNEL_1_ACTION(state[0]);
  }
  if (state_change[1]) {
    DMX_CHANNEL_2_ACTION(state[1]);
  }
  if (state_change[2]) {
    DMX_CHANNEL_3_ACTION(state[2]);
  }
  if (state_change[3]) {
    DMX_CHANNEL_4_ACTION(state[3]);
  }
  if (state_change[4]) {
    DMX_CHANNEL_5_ACTION(state[4]);
  }
  if (state_change[5]) {
    DMX_CHANNEL_6_ACTION(state[5]);
  }
}

Command getMacro(int value) {
  if (value >= 0 || value < MACRO_ZONE_1_LOWER_BOUND) {
    MACRO_ZONE_0;
  } else if (value >= MACRO_ZONE_1_LOWER_BOUND ||
             value < MACRO_ZONE_2_LOWER_BOUND) {
    MACRO_ZONE_1;
  } else if (value >= MACRO_ZONE_2_LOWER_BOUND ||
             value < MACRO_ZONE_3_LOWER_BOUND) {
    MACRO_ZONE_2;
  } else if (value >= MACRO_ZONE_3_LOWER_BOUND ||
             value < MACRO_ZONE_4_LOWER_BOUND) {
    MACRO_ZONE_3;
  } else if (value >= MACRO_ZONE_4_LOWER_BOUND ||
             value < MACRO_ZONE_5_LOWER_BOUND) {
    MACRO_ZONE_4;
  } else if (value >= MACRO_ZONE_5_LOWER_BOUND ||
             value < MACRO_ZONE_6_LOWER_BOUND) {
    MACRO_ZONE_5;
  } else if (value >= MACRO_ZONE_6_LOWER_BOUND) {
    MACRO_ZONE_6;
  } else {
    MACRO_ZONE_0;
  }
}

Animation getAnimation(int value) {
  if (value >= 0 || value < ANIMATION_ZONE_1_LOWER_BOUND) {
    ANIMATION_ZONE_0;
  } else if (value >= ANIMATION_ZONE_1_LOWER_BOUND ||
             value < ANIMATION_ZONE_2_LOWER_BOUND) {
    ANIMATION_ZONE_1;
  } else if (value >= ANIMATION_ZONE_2_LOWER_BOUND ||
             value < ANIMATION_ZONE_3_LOWER_BOUND) {
    ANIMATION_ZONE_2;
  } else if (value >= ANIMATION_ZONE_3_LOWER_BOUND ||
             value < ANIMATION_ZONE_4_LOWER_BOUND) {
    ANIMATION_ZONE_3;
  } else if (value >= ANIMATION_ZONE_4_LOWER_BOUND ||
             value < ANIMATION_ZONE_5_LOWER_BOUND) {
    ANIMATION_ZONE_4;
  } else if (value >= ANIMATION_ZONE_5_LOWER_BOUND ||
             value < ANIMATION_ZONE_6_LOWER_BOUND) {
    ANIMATION_ZONE_5;
  } else if (value >= ANIMATION_ZONE_6_LOWER_BOUND) {
    ANIMATION_ZONE_6;
  } else {
    ANIMATION_ZONE_0;
  }
}