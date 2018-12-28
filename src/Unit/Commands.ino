#include <Arduino.h>
#include "Commands.h"

long timer;
long timer_delay = 1000;

Command currentCommand = NULL_COMMAND;
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

void initCommand() {
  switch (currentCommand) {
    case NULL_COMMAND:
    break;
    case STOP: 
    break;
    case SETCOLOR:
      setColor::init(255, 255, 255);
    break;
    case SETBRIGHTNESS:
      setBrightness::init(255);
    break;
    case BLINK:
      blink::init(255, 255, 255, 1000);
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