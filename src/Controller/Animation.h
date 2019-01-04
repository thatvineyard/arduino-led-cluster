#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#define NUMBER_OF_ANIMATIONS 10
#define NUMBER_OF_FILTERS 11

enum Animation {
  NO_ANIMATION,
  RANDOM,
  LEFT_TO_RIGHT,
  RIGHT_TO_LEFT,
  BACK_TO_FRONT,
  FRONT_TO_BACK,
  OUTWARD,
  INWARD,
  CHEVRON_FTB,
  CHEVRON_BTF
};

void setAnimationSpeed(int value);

bool nextFrameReady();

String getNextFrame();

void startAnimation(Animation new_animation, int new_animation_delay);

#endif