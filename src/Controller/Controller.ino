#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Animation.h"
#include "Commands.h"
#include "Composer.h"
#include "Filter.h"
#include "Globals.h"
#include "Lcd.h"
#include "Sender.h"
#include "View.h"

void setup() {
  // Open serial connection
  Serial.begin(BAUD_RATE);
  while (!Serial) {
    ;
  }
  lcd::initLCD();
  initInput();

  view::initView();
}

void loop() {
  if (DMX_MODE) {
    parseDmx();
  } else {
    parseInputs();
  }
  composer::update();
  lcd::updateDisplay();
}
