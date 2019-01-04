#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#define NUMBER_OF_ANIMATIONS 10
#define NUMBER_OF_FILTERS 11

/**
 * ANIMATION
 *
 * This module handles the possible animations.
 *
 * Animations are the different combinations of units to which macros are sent.
 * By sending commands with the regex provided from this module continuously it
 * will create the animation. Keep in mind that it is up to the user to send any
 * terminating commands to the units. In order to create good one-shot
 * animations it's recommended to use non-looping macros and set looping to
 * false when calling startAnimation().
 *
 * Animations are started by calling startAnimation(). By calling getNextFrame()
 * the next frame will be returned regardless of whether the timer has lapsed.
 * This means that it is your responsibility to use nextFrameRead() to make the
 * frequency match.
 *
 * getNextFrame() returns a selector regex which is used to select the units
 * which are activated during that frame.
 *
 */

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

void startAnimation(Animation new_animation, bool looping);

#endif