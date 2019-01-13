#include <Arduino.h>
#include "Color.h"
#include "Commands.h"
#include "Globals.h"
#include "Led.h"
#include "Messaging.h"

void setup() {
  // Open serial connection
  Serial.begin(BAUD_RATE);
  while (!Serial) {
    ;
  }
  // Set the regex match state to the id.
  messaging::setRegexp();

  // initialize pins
  led::initLed(LED_TYPE);

  log(String(getColumn()) + ":" + String(getRow()));
}

void loop() {
  messaging::parseMessage();

  if (is_new_setting) {
    applySetting();
    is_new_setting = false;
  }

  if (is_new_macro) {
    initMacro();
    is_new_macro = false;
  }

  tickMacro();
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() { messaging::readSerial(); }
