#ifndef MESSAGING_H_INCLUDED
#define MESSAGING_H_INCLUDED

enum MessageState {
  NO_MESSAGE,
  START,
  SELECTOR,
  COMMAND, 
  PARAMETERS,
  END,
  AWAITING_PARSING
};


namespace messaging
{

  void setRegexp(String id);

  void parseMessage();

  void reset();

  void addToCommandRegex(char inChar);

  void addToParameters(char inChar);

  void readSerial();
    
} // Messaging

#endif