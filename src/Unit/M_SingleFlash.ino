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
      fade_start = millis();
      step = 2;
    }
  } else if (step == 2) {
    int fade = calculateFade();
    color::setAuxBrightnessProcent(fade);
    if (fade <= 0) {
      step = 3;
    }
  }
}

void init(String flash_duration,
          String new_fade_duration) {  // TODO: Handle parameters as 0-255
  if (flash_duration == "") {
    setTimerDelay(100);
  } else {
    setTimerDelay(flash_duration.toInt());
  }
  if (new_fade_duration == "") {
    fade_duration = 1000;
  } else {
    fade_duration = new_fade_duration.toInt();
  }

  color::setAuxColorToBase();
  color::setAuxBrightnessToBase();

  step = 1;
}

}  // namespace m_singleflash