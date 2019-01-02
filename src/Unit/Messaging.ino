#include <Arduino.h>
#include <Regexp.h>
#include "Messaging.h"

namespace messaging {

// Parameters used to collect the message.
String input_selector = "";
String input_command = "";
String input_parameters[MAX_PARAMETERS];
int input_parameter_index = 0;

// Parsed message
bool selector_match = false;
Command parsed_command = NULL_COMMAND;

// State handlers
MessageState message_state;
MatchState match_state;

// MESSAGE PARSING
void resetMessaging() {
  input_selector = "";
  input_command = "";
  for (int i = 0; i < MAX_PARAMETERS; i++) {
    input_parameters[i] = "";
  }
  input_parameter_index = 0;

  message_state = NO_MESSAGE;
}

void setRegexp(String new_regexp) {
  match_state.Target(const_cast<char*>(new_regexp.c_str()));
}

bool parseSelector() {
  char res = match_state.Match(const_cast<char*>(input_selector.c_str()), 0);
  if (res > 0) {
    return true;
  } else {
    return false;
  }
}

void parseCommand() {
  Command new_command = stringToCommand(input_command);
  if (isMacro(new_command)) {
    setMacro(new_command);
    isNewMacro = true;
  } else if (isSetting(new_command)) {
    setSetting(new_command);
    isNewSetting = true;
  }
}

void parseParameters() {
  setParameters(input_parameters);
}

void parseMessage() {
  if (message_state == AWAITING_PARSING) {
    if (parseSelector()) {
      parseCommand();
      parseParameters();

      if (DEBUG_MODE) {
        String parameter_list = "";
        for (int i = 0; i < MAX_PARAMETERS; i++) {
          if (input_parameters[i] != "") {
            parameter_list += input_parameters[i] + " ";
          }
        }
        Serial.println("Matched input_selector: excecuting input_command: " +
                       input_command +
                       " with input_parameters: " + parameter_list + ".");
      }
    }
    resetMessaging();
  }
}

// MESSAGE RECIEVING

void addToSelector(char inChar) {
  input_selector += inChar;
}

void addToParameters(char inChar) {
  if (inChar != ' ') {
    input_parameters[input_parameter_index] += inChar;
  } else {
    input_parameter_index++;
  }
}

void addToCommand(char inChar) {
  if (inChar != ' ') {
    input_command += inChar;
  }
}

void parseChar(char inChar) {
  // Whenever we see a '>' we resetMessaging, otherwise we check the state
  // and then look at the character and either record into the right
  // spot or change state.
  if (inChar == DELIM_MESSAGE_START) {
    message_state = START;
    resetMessaging();
  } else {
    switch (message_state) {
      case NO_MESSAGE:
        break;

      case START:
        if (inChar == DELIM_SELECTOR_START) {
          message_state = SELECTOR;
        }
        break;

      case SELECTOR:
        if (inChar == DELIM_SELECTOR_END) {
          message_state = COMMAND;
        } else if (inChar == DELIM_MESSAGE_END) {
          message_state = NO_MESSAGE;
        } else {
          addToSelector(inChar);
        }
        break;

      case COMMAND:
        if (inChar == DELIM_PARAMETERS_START) {
          message_state = PARAMETERS;
        } else if (inChar == DELIM_MESSAGE_END) {
          message_state = AWAITING_PARSING;  // MESSAGE ACCEPTED
        } else {
          addToCommand(inChar);
        }
        break;

      case PARAMETERS:
        if (inChar == DELIM_PARAMETERS_END) {
          message_state = END;
        } else if (inChar == DELIM_MESSAGE_END) {
          message_state = NO_MESSAGE;
        } else {
          addToParameters(inChar);
        }
        break;

      case END:
        // If we see a '!' we accept the message, signal that the message is
        // ready for parsing.
        if (inChar == DELIM_MESSAGE_END) {
          message_state = AWAITING_PARSING;  // MESSAGE ACCEPTED
        }
      default:
        break;
    }
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void readSerial() {
  while (Serial.available()) {
    // Read the new byte:
    char inChar = (char)Serial.read();
    // Record it
    parseChar(inChar);

    Serial.write(inChar);
  }
}

}  // namespace messaging