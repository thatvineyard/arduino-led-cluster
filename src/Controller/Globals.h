#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

// UNIT ID
#define UNIT_COLUMN 'A'
#define UNIT_ROW 1

// PROJECT
#define NUM_COLUMNS 10
#define NUM_ROWS 20

// DEVELOPER SETTINGS
#define DEBUG_MODE true

// MESSAGING
#define BAUD_RATE 9600
#define DELIM_MESSAGE_START '>'
#define DELIM_SELECTOR_START '{'
#define DELIM_SELECTOR_AND '#'
#define DELIM_SELECTOR_OR '@'
#define DELIM_SELECTOR_END '}'
#define DELIM_PARAMETERS_START '('
#define DELIM_PARAMETERS_END ')'
#define DELIM_MESSAGE_END '!'

// PINOUT
#define LED_RED_PIN 9
#define LED_GREEN_PIN 10
#define LED_BLUE_PIN 11
#define LED_TYPE led::COMMON_ANODE

// COMMANDS
#define MAX_PARAMETERS 10
#define NUMBER_OF_MACROS 4
bool isNewMacro;
bool isNewSetting;
long timer;
long timer_delay;

/**
 *
 * Settings are changes that are made once and don't interrupt macros.
 *
 * Macros are ongoing changes that will keep going until another macro or the
 * STOP command is issued.
 *
 */
enum Command {
  // SPECIAL COMMANDS
  NULL_COMMAND = -1,
  STOP = 0,
  // SETTINGS
  S_BASECOLOR = 101,
  S_BASEBRIGHTNESS = 102,
  S_BASESPEED = 103,
  // MACROS
  M_SOLID = 1,
  M_PULSE = 2,
  M_FLICKER = 3,
  M_SINGLEFLASH = 4
};

// COLOR
// BASE_BRIGHTNESS_CONSTRAINS - if true the base brightness set will be the
// maximum allowed brightness
#define BASE_BRIGHTNESS_CONSTRAINS true
#define MAX_BRIGHTNESS 255
#define MAX_RED 255
#define MAX_GREEN 255
#define MAX_BLUE 255

#endif