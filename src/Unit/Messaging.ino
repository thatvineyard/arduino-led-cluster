#include <Arduino.h>
#include <Regexp.h>
#include "Messaging.h"

#define DELIM_MESSAGE_START     '>'
#define DELIM_SELECTOR_START    '['
#define DELIM_SELECTOR_END      ']'
#define DELIM_PARAMETERS_START  '('
#define DELIM_PARAMETERS_END    ')'
#define DELIM_MESSAGE_END       '!'

#define MAX_PARAMETERS 10

// Global parameters used to collect a regex selector and command parameters.
String selector = "";
String command = "";
String parameters[MAX_PARAMETERS];
int parameter_index = 0;

MessageState message_state;
MatchState match_state;

// MESSAGE PARSING
void setRegexp(String new_regexp) {
    match_state.Target(const_cast<char*>(new_regexp.c_str()));
}

void parseMessage() {
  if (message_state == AWAITING_PARSING) {
    Serial.println("Matching on selector");
    Serial.println(selector);

    char res = match_state.Match(const_cast<char*>(selector.c_str()), 0);

    if (res > 0) {
      String parameter_list = "";
      for(int i = 0; i < MAX_PARAMETERS; i++) {
        if(parameters[i] != "") {
          parameter_list += parameters[i] + " ";
        }
      }
      Serial.println("Should execute command: " + command + "with parameters: " + parameter_list);
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

void parseSelector() {

}

void parseCommand() {

}

void parseParameters() {

}

// MESSAGE RECIEVING

void reset() {
  selector = "";
  command = "";
  for(int i = 0; i < MAX_PARAMETERS; i++) {
    parameters[i] = "";
  }
  parameter_index = 0;
}

void addToSelector(char inChar) {
    selector += inChar;
}

void addToParameters(char inChar) {
    if(inChar != ' ') {
      parameters[parameter_index] += inChar;
    } else {
      parameter_index++;
    }
}

void addToCommand(char inChar) {
  if(inChar != ' ') {
    command += inChar;
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

    // TODO: transmit byte
  }
}

void parseChar(char inChar) {

  // Whenever we see a '>' we reset, otherwise we check the state 
  // and act accordingly.
  if (inChar == DELIM_MESSAGE_START) {
    message_state = START;
    reset();
  } else {
    switch(message_state) {
      case NO_MESSAGE:
      break;
      
      case START:
        if(inChar == DELIM_SELECTOR_START) {
          message_state = SELECTOR;
        }
      break;

      case SELECTOR:
        if(inChar == DELIM_SELECTOR_END) {
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
          message_state = AWAITING_PARSING; // MESSAGE ACCEPTED
        } else {
          addToCommand(inChar);
        }      
      break;
      
      case PARAMETERS:
        if(inChar == DELIM_PARAMETERS_END) {
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
          message_state = AWAITING_PARSING; // MESSAGE ACCEPTED
        }
      default:
      break;
    }
  }
}