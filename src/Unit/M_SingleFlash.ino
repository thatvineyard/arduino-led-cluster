#include <Arduino.h>
#include "Led.h"

namespace m_singleflash {

int fade_duration = 0;

long fade_start = 0;

int step = 0;

int calculateFade() {
  long time_passed = millis() - fade_start;
  return 100 - ((time_passed * 100) / fade_duration);
}

void tick() {
  if (step == 1) {
    if (timerLapsed()) {
      if (fade_duration > 0) {
        fade_start = millis();
        step = 2;
      } else {
        color::setAuxBrightnessProcent(0);
        step = 3;
      }
    }
  } else if (step == 2) {
    int fade = calculateFade();
    color::setAuxBrightnessProcent(fade);
    if (fade <= 0) {
      step = 3;
    }
  }
}

void init(int flash_duration, int new_fade_duration) {
  if (flash_duration == -1) {
    setTimerDelay(100);
  } else {
    setTimerDelay(mapScale(M_SINGLEFLASH_SCALE_TYPE, M_SINGLEFLASH_MIN_DURATION,
                           M_SINGLEFLASH_MAX_DURATION, 0, 255, flash_duration));
  }
  if (new_fade_duration == -1) {
    fade_duration = 1000;
  } else {
    fade_duration =
        mapScale(M_SINGLEFLASH_SCALE_TYPE, M_SINGLEFLASH_MIN_DURATION,
                 M_SINGLEFLASH_MAX_DURATION, 0, 255, new_fade_duration);
  }

  color::setAuxColorToBase();
  color::setAuxBrightnessToBase();

  restartTimer();
  step = 1;
}

}  // namespace m_singleflash