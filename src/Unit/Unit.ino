#include <Arduino.h>
#include "Commands.h"
#include "Led.h"
#include "Messaging.h"
#include "Globals.h"

// Identification
int row = 2;
int column = 1;
String id = "A02";

void setup() {
  // Set the regex match state to the id.
  messaging::setRegexp(id);
  // Open serial connection at 9600 Bd.
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  messaging::parseMessage();
  if (newCommand) {
    initCommand();
    newCommand = false;
  }
  doCommand();
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  messaging::readSerial();
}
