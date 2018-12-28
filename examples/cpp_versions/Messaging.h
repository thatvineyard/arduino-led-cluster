#ifndef MESSAGING_H_INCLUDED
#define MESSAGING_H_INCLUDED

void setRegexp(String id);

void parseMessage();

void reset();

void addToCommandRegex(char inChar);

void addToParameters(char inChar);

void readSerial();

#endif