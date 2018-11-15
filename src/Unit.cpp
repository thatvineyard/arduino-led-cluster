#include <Arduino.h>
#include <Regexp.h>
#include "LedControl/LedControl.cpp"
// For some reason including the .h file didn't work. I have to look into this.

// Global parameters used to collect a regex selector and command parameters.
String selector = "";
bool selectorRead = false;
String parameters = "";
bool parametersRead = false;

// Identification
String id = "A01";

// Commands
String currentCommand = "";
int currentCommandId = -1;
bool newCommand = false;

MatchState match_state;

void setup() {
  match_state.Target(const_cast<char*>(id.c_str()));
  // Open serial connection at 9600 Bd.
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  parseMessage();
  if (newCommand) {
    initCommand();
    newCommand = false;
  }
  doCommand();
}

void initCommand() {
  switch (currentCommandId) {
    case 1:
      init_blink();
      break;
    default:
      break;
  }
}

void doCommand() {
  switch (currentCommandId) {
    case 1:
      blink();
      break;
    default:
      break;
  }
}

// MESSAGE PARSING
void parseMessage() {
  if (selectorRead && parametersRead) {
    Serial.println("Matching on selector");
    Serial.println(selector);

    char res = match_state.Match(const_cast<char*>(selector.c_str()), 0);
    if (res > 0) {
      Serial.println("Should execute command: " + parameters);
      currentCommand = parameters;
      if (currentCommand == "blink") {
        currentCommandId = 1;
      }
      newCommand = true;
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
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);

    if (!selectorRead) {
      addToCommandRegex(inChar);
    } else {
      addToParameters(inChar);
    }
  }
}