#include "Commands.h"

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