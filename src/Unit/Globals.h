#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

// UNIT ID
#define UNIT_ID "A00"

// CONTROLLER
#define DMX_MODE false

// PROJECT
#define NUM_COLUMNS 7
#define NUM_ROWS 19

// DEVELOPER SETTINGS
#define DEBUG_MODE true
#define MAX_MESSAGE_REGEX_LENTGH 200
#define MAX_MESSAGE_COMMAND_LENGTH MAX_COMMAND_NAME_LENGTH
#define MAX_MESSAGE_PARAMETER_LENGTH (4 * MAX_PARAMETERS + 1)
#define MAX_MESSAGE_LENGTH                                 \
  (MAX_MESSAGE_REGEX_LENTGH + MAX_MESSAGE_COMMAND_LENGTH + \
   MAX_MESSAGE_PARAMETER_LENGTH + 2)
char temp_number_buffer[3];
#define START_CHARACTER 'A'
#define START_NUMBER 0

// MESSAGING
#define BAUD_RATE 115200
#define DELIM_MESSAGE_START '>'
#define DELIM_SELECTOR_START '{'
#define DELIM_SELECTOR_AND '&'
#define DELIM_SELECTOR_OR '|'
#define DELIM_SELECTOR_END '}'
#define DELIM_PARAMETERS_START '('
#define DELIM_PARAMETERS_END ')'
#define DELIM_MESSAGE_END '!'

// PINOUT
#define LED_RED_PIN 9
#define LED_GREEN_PIN 10
#define LED_BLUE_PIN 11
#define LED_TYPE led::COMMON_CATHODE

// COMMANDS
#define MAX_COMMAND_NAME_LENGTH 15
#define MAX_PARAMETERS 6
#define NUMBER_OF_MACROS 4
#define MAX_TIME_SHIFT_MS 5000
bool is_new_macro;
bool is_new_setting;
long timer;
long timer_delay;

// COLOR
// BASE_BRIGHTNESS_CONSTRAINS - if true the base brightness set will be the
// maximum allowed brightness
#define BASE_BRIGHTNESS_CONSTRAINS true
#define MAX_VALUE 255
#define MAX_BRIGHTNESS 255
#define MAX_RED 255
#define MAX_GREEN 255
#define MAX_BLUE 255

#endif