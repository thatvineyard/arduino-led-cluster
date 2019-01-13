#include <Arduino.h>
#include "Led.h"

namespace m_pulse {

int on_duration = 0;
int off_duration = 0;
int fade_in_duration = 0;
int fade_out_duration = 0;

long start_time = 0;

int step = 0;
int fade = 0;

int calculateFade(int fade_duration) {
  long time_passed = millis() - start_time;
  return ((time_passed * 100) / fade_duration);
}

void tick() {
  color::setAuxColorToBase();
  switch (step) {
    case 1:  // ON
      if (timerLapsed()) {
        start_time = millis();
        step = 2;
      }
      break;
    case 2:  // FADE OUT
      fade = 100 - calculateFade(fade_out_duration);
      color::setAuxBrightnessProcent(fade);
      if (fade <= 0 || fade_out_duration == 0) {
        color::setAuxBrightnessProcent(0);
        setTimerDelay(off_duration);
        restartTimer();
        step = 3;
      }
      break;
    case 3:  // OFF
      if (timerLapsed()) {
        start_time = millis();
        step = 4;
      }
      break;
    case 4:  // FADE IN
      fade = calculateFade(fade_in_duration);
      color::setAuxBrightnessProcent(fade);
      if (fade >= 100 || fade_in_duration == 0) {
        color::setAuxBrightnessProcent(100);
        setTimerDelay(on_duration);
        restartTimer();
        step = 1;
      }
      break;
    default:
      color::setAuxBrightnessProcent(0);
      start_time = millis();
      step = 4;
      break;
  }
}

void init(int new_on_duration, int new_fade_in_duration, int new_off_duration,
          int new_fade_out_duration) {
  if (new_on_duration != -1) {
    on_duration = mapScale(M_PULSE_SCALE_TYPE, M_PULSE_MIN_DURATION,
                           M_PULSE_MAX_DURATION, 0, 255, new_on_duration);
  } else {
    on_duration = 1000;
  }
  if (new_fade_in_duration != -1) {
    fade_in_duration =
        mapScale(M_PULSE_SCALE_TYPE, M_PULSE_MIN_DURATION, M_PULSE_MAX_DURATION,
                 0, 255, new_fade_in_duration);
  } else {
    fade_in_duration = 500;
  }
  if (new_off_duration != -1) {
    off_duration = mapScale(M_PULSE_SCALE_TYPE, M_PULSE_MIN_DURATION,
                            M_PULSE_MAX_DURATION, 0, 255, new_off_duration);
  } else {
    off_duration = on_duration;
  }
  if (new_fade_out_duration != -1) {
    fade_out_duration =
        mapScale(M_PULSE_SCALE_TYPE, M_PULSE_MIN_DURATION, M_PULSE_MAX_DURATION,
                 0, 255, new_fade_out_duration);
  } else {
    fade_out_duration = fade_in_duration;
  }

  step = -1;
  tick();
}

}  // namespace m_pulse