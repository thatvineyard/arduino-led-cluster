#include <Arduino.h>
#include "Commands.h"

long timer;
long timer_delay = 1000;

Command currentCommand = NULL_COMMAND;
String currentParameters[MAX_PARAMETERS]; 
bool isNewCommand = false;

int timerLapsed() { 
  return millis() - timer > timer_delay; 
}

void setTimer(long delay) {
  timer_delay = delay;
}

void resetTimer() { 
  timer = millis(); 
}

void setCommand(Command newCommand) {
  currentCommand = newCommand;
  isNewCommand = true;
}

void setParameters(String newParameters[]) {
  for(int i = 0; i < MAX_PARAMETERS; i++) {
    currentParameters[i] = newParameters[i];
  }
}

void initCommand() {
  switch (currentCommand) {
    case NULL_COMMAND:
    break;
    case STOP:
      led::reset(); 
    break;
    case SETCOLOR:
      setColor::init(255, 255, 255);
    break;
    case SETBRIGHTNESS:
      setBrightness::init(255);
    break;
    case BLINK:
      blink::init(currentParameters[0], currentParameters[1], currentParameters[2], currentParameters[3]);
      break;
    default:
      break;
  }
}

void doCommand() {
  switch (currentCommand) {
    case NULL_COMMAND:
    break;
    case STOP:
    break;
    case SETCOLOR:
      setColor::tick();
    break;
    case SETBRIGHTNESS:
      setBrightness::tick();
    break;
    case BLINK:
      blink::tick();
      break;
    default:
      break;
  }
}

Command stringToCommand(String string_to_convert) {
  string_to_convert.toUpperCase();
  if(string_to_convert == "NULL_COMMAND") {return NULL_COMMAND;}
  if(string_to_convert == "STOP") {return STOP;}
  if(string_to_convert == "SETCOLOR") {return SETCOLOR;}
  if(string_to_convert == "SETBRIGHTNESS") {return SETBRIGHTNESS;}
  if(string_to_convert == "BLINK") {return BLINK;}

  return NULL_COMMAND;
}