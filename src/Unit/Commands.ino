#include <Arduino.h>


#define NULL_COMMAND "NULL_COMMAND"

enum Commands { Null = -1, Blink };

long timer;
long timer_delay = 1000;


// Commands
String currentCommand = "";
int currentCommandId = -1;
bool newCommand = false;

String getCommandFromId(int id) {
  switch (id) {
    case 1:
      return "blink";
    default:
      return NULL_COMMAND;
  }
}

int getIdFromCommand(String command) {
  if (command == NULL_COMMAND) {
    return -1;
  }
  if (command == "blink") {
    return 1;
  }
}

int timerLapsed() { return millis() - timer > timer_delay; }

void resetTimer() { timer = millis(); }

void setCommand() {
  // currentCommandId = newCommandId;
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