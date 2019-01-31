#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Animation.h"
#include "Commands.h"
#include "Composer.h"
#include "Filter.h"
#include "Globals.h"
#include "Lcd.h"
#include "Repeater.h"
#include "Sender.h"
#include "View.h"

void setup() {
  sender::initSender();
  initLogging();
  while (!Serial) {
    ;
  }
  initDmx();
  lcd::initLCD();
  initInput();

  view::initView();

  repeater::init();
}

void loop() {
  // if (DMX_MODE) {
  parseDmx();
  // } else {
  parseInputs();
  // }

  composer::update();
  lcd::updateDisplay();
}

void serialEvent() {
  if (REPEATER_MODE) {
    repeater::readSerial();
  }
}
