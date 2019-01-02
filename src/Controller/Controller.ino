#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Animation.h"
#include "Globals.h"

// LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int command_scroll = 0;
int parameter_scroll = 0;
char lcd_buffer[16];
bool change = true;

// DIMMER
int dimmer = 255;
bool dimmer_changed;

// RGB
int red = 0;
int green = 0;
int blue = 0;
bool color_changed;

// speed
int macro_speed = 100;
bool macro_speed_changed;

// MACRO
int parameters[MAX_PARAMETERS];
Command command;
int command_selector;
int parameter_selector;
bool macro_changed;

void setup() {
  // Open serial connection
  Serial.begin(BAUD_RATE);
  initLCD();
  initInput();
}

void loop() {
  parseInputs();
  sendSettings();
  updateDisplay();
}

void sendSettings() {
  if (dimmer_changed) {
    sendDimmerCommand();
    dimmer_changed = false;
  }
  if (color_changed) {
    sendColorCommand();
    color_changed = false;
  }
  if (macro_speed_changed) {
    sendMacroSpeedCommand();
    macro_speed_changed = false;
  }
}

String createMessage(String selector,
                     String command,
                     int number_of_parameters) {
  String message = "";

  message += DELIM_MESSAGE_START;
  message += DELIM_SELECTOR_START;
  message += selector;
  message += DELIM_SELECTOR_END;
  message += command;
  if (number_of_parameters > 0) {
    message += DELIM_PARAMETERS_START;
    for (int i = 0; i < number_of_parameters; i++) {
      message += parameters[i];
      if (i + 1 == number_of_parameters) {
        message += " ";
      }
    }
    message += DELIM_MESSAGE_END;
  }
  message += DELIM_MESSAGE_END;

  return message;
}

void sendMessage(String message) {
  Serial.print(message);
}

void sendDimmerCommand() {
  parameters[0] = dimmer;
  createMessage(".*", "S_BASEBRIGHTNESS", 1);
}

void sendColorCommand() {
  parameters[0] = red;
  parameters[1] = green;
  parameters[2] = blue;
  createMessage(".*", "S_SETBASECOLOR", 3);
}

void sendMacroSpeedCommand() {
  parameters[0] = macro_speed;
  createMessage(".*", "S_BASESPEED", 1);
}

void sendMacroCommand() {}
