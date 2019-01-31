#include <Arduino.h>
#include <avr/power.h>
#include <avr/sleep.h>
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

  // Interrupt pin
  // pinMode(2, INPUT);

  // Turn off RX/TX LEDs
  TXLED0;
  RXLED0;
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

void startupSequence() {
  color::setBaseBrightness(255);
  color::setBaseColor(255, 255, 255);
  color::setAuxBrightnessToBase();

  int delay_time = 500;
  for (int i = 0; i < 3; i++) {
    color::setAuxColorValue(255, 0, 0);
    delay(delay_time);
    color::setAuxColorValue(0, 255, 0);
    delay(delay_time);
    color::setAuxColorValue(0, 0, 255);
    delay(delay_time);
    color::setAuxColorValue(0, 0, 0);
    delay(delay_time);
  }
}

void sleep() {
  // attachInterrupt(, wake,
  //                 FALLING);  // attach interrupt handler
  // radio.sleep();             // Set the radio transceiver in sleep mode
  // sleep_bod_disable();
  // power_adc_disable();
  // power_spi_disable();
  // power_timer0_disable();
  // power_timer1_disable();
  // power_timer2_disable();
  // power_twi_disable()

  PRR = PRR | 0b00100000;

  messaging::flush();

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // sleep mode is set here

  sleep_enable();  // enables the sleep bit in the mcucr register
                   // so sleep is possible. just a safety pin

  attachInterrupt(0, wake, CHANGE);  // use interrupt 0 (pin 2) and run
                                     // function wakeUpNow when pin 2 gets LOW
  log("SLEEPING");

  sleep_mode();  // here the device is actually put to sleep!!
                 // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

  sleep_disable();     // first thing after waking from sleep:
                       // disable sleep...
  detachInterrupt(0);  // disables interrupt 0 on pin 2 so the
                       // wakeUpNow code will not be executed
                       // during normal running time.
  PRR = PRR & 0b00000000;
}

void wake() {}