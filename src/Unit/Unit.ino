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

  log(String(UNIT_ID) + " (" + String(getColumn()) + ":" + String(getRow()) +
      ")");

  startupSequence();
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
void serialEvent() {
  messaging::readSerial();
}

void startupSequence() {
  color::setBaseBrightness(255);
  color::setBaseColor(255, 255, 255);
  color::setAuxBrightnessToBase();
  color::setAuxColorToBase();

  int delay_time = 20;

  for (int i = 0; i < 100; i++) {
    color::setAuxBrightnessProcent(100 - i);
    delay(delay_time);
  }
  for (int i = 0; i < 100; i++) {
    color::setAuxBrightnessProcent(i);
    delay(delay_time);
  }
  color::setAuxColorProcent(0, 0, 0);
  for (int i = 0; i < 100; i++) {
    color::setAuxColorProcent(i, 0, 0);
    delay(delay_time);
  }
  for (int i = 0; i < 100; i++) {
    color::setAuxColorProcent(100 - i, 0, 0);
    delay(delay_time);
  }
  for (int i = 0; i < 100; i++) {
    color::setAuxColorProcent(0, i, 0);
    delay(delay_time);
  }
  for (int i = 0; i < 100; i++) {
    color::setAuxColorProcent(0, 100 - i, 0);
    delay(delay_time);
  }
  for (int i = 0; i < 100; i++) {
    color::setAuxColorProcent(0, 0, i);
    delay(delay_time);
  }
  for (int i = 0; i < 100; i++) {
    color::setAuxColorProcent(0, 0, 100 - i);
    delay(delay_time);
  }
}