#include <Arduino.h>
#include "Led.h"

namespace m_solid {

void tick() {}

void init() {
  color::setAuxColorToBase();
  color::setAuxBrightnessToBase();
}

}  // namespace m_solid