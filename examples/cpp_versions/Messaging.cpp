#include <Arduino.h>
#include <Regexp.h>
#include "Messaging.h"


// Global parameters used to collect a regex selector and command parameters.
String selector = "";
bool selectorRead = false;
String parameters = "";
bool parametersRead = false;

MatchState match_state;

void setRegexp(String newRegexp) {
    match_state.Target(const_cast<char*>(newRegexp.c_str()));
}

// MESSAGE PARSING
void parseMessage() {
  if (selectorRead && parametersRead) {
    Serial.println("Matching on selector");
    Serial.println(selector);

    char res = match_state.Match(const_cast<char*>(selector.c_str()), 0);
    if (res > 0) {
      Serial.println("Should execute command: " + parameters);
      // currentCommand = parameters;
      // if (currentCommand == "blink") {
      //   currentCommandId = 1;
      // }
      // newCommand = true;
      reset();
    } else if (res == 0) {
      Serial.println("Should not execute command");
      reset();
    } else {
      Serial.println("Error while matching regex");
      reset();
    }
  }
}

void reset() {
  selectorRead = false;
  parametersRead = false;
  selector = "";
  parameters = "";
}

void addToCommandRegex(char inChar) {
  if (inChar != ';') {
    selector += inChar;
  } else {
    selectorRead = true;
  }
}

void addToParameters(char inChar) {
  if (inChar != ';') {
    parameters += inChar;
  } else {
    parametersRead = true;
  }
}

// MESSAGE RECIEVING

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void readSerial() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();

    if (!selectorRead) {
      addToCommandRegex(inChar);
    } else {
      addToParameters(inChar);
    }
  }
}