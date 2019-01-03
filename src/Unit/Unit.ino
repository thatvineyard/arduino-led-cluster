#include <Arduino.h>
#include "Color.h"
#include "Commands.h"
#include "Globals.h"
#include "Led.h"
#include "Messaging.h"

void setup() {
  // Set the regex match state to the id.
  messaging::setRegexp(createId(UNIT_COLUMN, UNIT_ROW));
  // Open serial connection
  Serial.begin(BAUD_RATE);
  // while (!Serial) {
  //   ;
  // }

  // initialize pins
  led::initLed(LED_TYPE);
}

void loop() {
  messaging::parseMessage();

  if (isNewSetting) {
    applySetting();
    isNewSetting = false;
  }

  if (isNewMacro) {
    initMacro();
    isNewMacro = false;
  }

  tickMacro();
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  messaging::readSerial();
}
