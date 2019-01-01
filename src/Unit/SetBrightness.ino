#include <Arduino.h>
#include "Led.h"

namespace setBrightness {
void tick() {}

void init(int brightness_value) { led::setBrightness(brightness_value); }

}  // namespace setBrightness