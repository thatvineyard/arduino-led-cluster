#ifndef COMMANDS_H_DEFINED
#define COMMANDS_H_DEFINED

#define NULL_COMMAND "NULL_COMMAND"

enum Commands { Null = -1, Blink };

String getCommandFromId(int id);

int getIdFromCommand(String command);

int timerLapsed();

void resetTimer();

void initCommand();

void doCommand();

#endif