#ifndef MESSAGING_H_INCLUDED
#define MESSAGING_H_INCLUDED
#include <Regexp.h>

namespace messaging {

enum MessageState {
  NO_MESSAGE,
  START,
  SELECTOR,
  COMMAND,
  PARAMETERS,
  END,
  AWAITING_PARSING
};

MatchState match_state;

/**
 * setRegexp(String)
 *
 * Sets the regexp which messaging will match the selector on.
 *
 */
void setRegexp();

/**
 * parseMessage()
 *
 * Checks the message state for the parsing state, then reads the recorded
 * variables and parses them. First it checks the selector and matches this
 * unit's id so see if this unit is selected. Then it populates the parameters.
 * Then it reads the command and depending on if it's a setting or a macro it
 * sets the isNew[Macro/Setting] flag.
 */
void parseMessage();

/**
 * readSerial()
 *
 * Reads all available bytes, parses them and retransmits them one by one.
 */
void readSerial();

}  // namespace messaging

#endif