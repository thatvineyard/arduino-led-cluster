#include <Arduino.h>
#include <Regexp.h>
#include "Commands.h"
#include "Led.h"
#include "Messaging.h"


// Identification
String id = "A01";

void setup() {
  // Set the regex match state to the id.
  setRegexp(id);
  // Open serial connection at 9600 Bd.
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  parseMessage();
  // if (newCommand) {
  //   initCommand();
  //   newCommand = false;
  // }
  doCommand();
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  readSerial();
}
