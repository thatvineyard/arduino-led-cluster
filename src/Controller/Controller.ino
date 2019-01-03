#include <Arduino.h>
#include <DmxSimple.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Animation.h"
#include "Composer.h"
#include "Filter.h"
#include "Globals.h"

bool macro_toggle = false;

void setup() {
  // Open serial connection
  Serial.begin(BAUD_RATE);
  // while (!Serial) {
  //   ;
  // }
  initLCD();
  initInput();
}

void loop() {
  if (DMX_MODE) {
    parseDmx();
  } else {
    parseInputs();
  }
  composer::sendSettings();
  composer::sendMacro();
  updateDisplay();
}
