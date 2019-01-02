#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#define BAUD_RATE 9600

#define MAX_PARAMETERS 10
#define DEBUG_MODE true

#define DELIM_MESSAGE_START '>'
#define DELIM_SELECTOR_START '{'
#define DELIM_SELECTOR_END '}'
#define DELIM_PARAMETERS_START '('
#define DELIM_PARAMETERS_END ')'
#define DELIM_MESSAGE_END '!'

#define LED_TYPE led::COMMON_ANODE

bool isNewMacro;
bool isNewSetting;

#endif