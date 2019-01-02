#include <Arduino.h>
#include "Commands.h"
#include "Globals.h"
#include "Led.h"
#include "Messaging.h"

// Identification
char column = 'A';
int row = 2;

void setup() {
  // Set the regex match state to the id.
  messaging::setRegexp(createId(column, row));
  // Open serial connection
  Serial.begin(BAUD_RATE);

  // initialize pins
  led::initLed(LED_TYPE);

  pinMode(LED_BUILTIN, OUTPUT);
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

String createId(char column, int row) {
  char id_string[3];
  sprintf(id_string, "%c%03u", column, row);
  return id_string;
}