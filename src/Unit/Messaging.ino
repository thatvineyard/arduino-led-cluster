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

// MESSAGE RECORDING
void resetMessaging() {
  input_selector = "";
  input_command = "";
  for (int i = 0; i < MAX_PARAMETERS; i++) {
    input_parameters[i] = "";
  }
  input_parameter_index = 0;

  message_state = NO_MESSAGE;
}

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

// MESSAGE PARSING

void setRegexp(String new_regexp) {
  log("Setting regexp to: " + new_regexp + ".");
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
      parseParameters();
      parseCommand();

      String parameter_list = "";
      for (int i = 0; i < MAX_PARAMETERS; i++) {
        if (input_parameters[i] != "") {
          parameter_list += input_parameters[i] + " ";
        }
      }
      log("Matched input_selector: excecuting input_command: " + input_command +
          " with input_parameters: " + parameter_list + ".");
    }
    resetMessaging();
  }
}  // namespace messaging

/**
 * parseChar(char)
 * Reads the character and matches is against the delimiters defined in
 * globals.h. Depending on which MessageState the program is in it will record
 * the char in the appropriate variable or change state.
 */
void parseChar(char inChar) {
  // No matter what the state, if we meet a DELIM_MESSAGE_START, we reset.
  if (inChar == DELIM_MESSAGE_START) {
    message_state = START;
    resetMessaging();
  } else {
    switch (message_state) {
      case START:
        // If we see a DELIM_SELECTOR_START we move to the SELECTOR state. If we
        // see a DELIM_MESSAGE_END we reset to the NO_MESSAGE state.
        if (inChar == DELIM_SELECTOR_START) {
          message_state = SELECTOR;
        } else if (inChar == DELIM_MESSAGE_END) {
          message_state = NO_MESSAGE;
        }
        break;

      case SELECTOR:
        // If we see a DELIM_SELECTOR_END we move to the COMMAND state. If we
        // see a DELIM_MESSAGE_END we reset to the NO_MESSAGE state. Otherwise
        // we record the selector.
        if (inChar == DELIM_SELECTOR_END) {
          message_state = COMMAND;
        } else if (inChar == DELIM_MESSAGE_END) {
          message_state = NO_MESSAGE;
        } else {
          addToSelector(inChar);
        }
        break;

      case COMMAND:
        // If we see a DELIM_PARAMETERS_START we move to the PARAMETERS state.
        // If we see a DELIM_MESSAGE_END we move to the AWAITING_PARSING state.
        // Otherwise we record the command.
        if (inChar == DELIM_PARAMETERS_START) {
          message_state = PARAMETERS;
        } else if (inChar == DELIM_MESSAGE_END) {
          message_state = AWAITING_PARSING;  // MESSAGE ACCEPTED
        } else {
          addToCommand(inChar);
        }
        break;

      case PARAMETERS:
        // If we see a DELIM_PARAMETERS_END we move to the END state. If we see
        // a DELIM_MESSAGE_END we reset to the NO_MESSAGE state. Otherwise we
        // record the parameter.
        if (inChar == DELIM_PARAMETERS_END) {
          message_state = END;
        } else if (inChar == DELIM_MESSAGE_END) {
          message_state = NO_MESSAGE;
        } else {
          addToParameters(inChar);
        }
        break;

      case END:
        // If we see a DELIM_MESSAGE_END we accept the message, signal that the
        // message is ready for parsing.
        if (inChar == DELIM_MESSAGE_END) {
          message_state = AWAITING_PARSING;  // MESSAGE ACCEPTED
        }

      case NO_MESSAGE:
      default:
        // In the NO_MESSAGE state and default state we ignore all characters.
        break;
    }
  }
}

// MESSAGE RECEIVING

void readSerial() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    parseChar(inChar);
    Serial.write(inChar);
  }
}

}  // namespace messaging