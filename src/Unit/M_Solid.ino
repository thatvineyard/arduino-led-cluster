#include <Arduino.h>
#include "Led.h"

namespace m_solid {

void tick() {
  led::setAuxColorToBase();
  led::setAuxBrightnessToBase();
}

void init() {
  led::setAuxColorToBase();
  led::setAuxBrightnessToBase();
}

}  // namespace m_solid