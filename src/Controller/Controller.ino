#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Commands.h"
#include "Globals.h"

// INPUTS
#define SCROLL_BUTTON 2
int scroll_button_state = 0;

#define ENCODER_WHEEL_CW 4
#define ENCODER_WHEEL_CCW 3
int encoder_wheel_state = 0;

#define MAX_VALUE 255
#define ENCODER_DELTA 2

// LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int command_scroll = 0;
int parameter_scroll = 0;
char lcd_buffer[16];
bool change = true;

// DIMMER
int dimmer;
bool dimmer_changed;

// RGB
int red;
int green;
int blue;
bool color_changed;

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
  if (dimmer_changed) {
    sendDimmerCommand();
  }
  if (color_changed && command == NULL_COMMAND) {
  }
  if (command != NULL_COMMAND) {
  }
  display();
}

String createMessage(String selector, String command,
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

void sendMessage(String message) { Serial.print(message); }

void sendDimmerCommand() {
  parameters[0] = dimmer;
  createMessage(".*", "setBrightness", 1);
  dimmer_changed = false;
}

void initInput() {
  pinMode(SCROLL_BUTTON, INPUT);
  pinMode(ENCODER_WHEEL_CW, INPUT);
  pinMode(ENCODER_WHEEL_CCW, INPUT);

  encoder_wheel_state = digitalRead(ENCODER_WHEEL_CW);
}

void parseInputs() {
  // scroll button
  int scroll_button_state_old = scroll_button_state;
  scroll_button_state = digitalRead(SCROLL_BUTTON);
  if (scroll_button_state == HIGH && scroll_button_state_old == LOW) {
    parameter_scroll = (parameter_scroll + 1) % MAX_PARAMETERS;
    change = true;
  }

  // encoder wheel
  int encoder_wheel_state_old = encoder_wheel_state;

  encoder_wheel_state = digitalRead(ENCODER_WHEEL_CW);

  if (encoder_wheel_state == HIGH &&
      encoder_wheel_state != encoder_wheel_state_old) {
    if (digitalRead(ENCODER_WHEEL_CCW) == LOW) {
      parameters[parameter_scroll] =
          (parameters[parameter_scroll] + ENCODER_DELTA) % MAX_VALUE;
    } else {
      parameters[parameter_scroll] =
          (parameters[parameter_scroll] + MAX_VALUE - ENCODER_DELTA) %
          MAX_VALUE;
    }
    change = true;
  }
}

void initLCD() {
  lcd.begin(16, 2);  // Defining 16 columns and 2 rows of lcd display
  lcd.backlight();   // To Power ON the back light
  // lcd.backlight();// To Power OFF the back light
}

void display() {
  if (change == true) {
    // Write your code
    lcd.setCursor(
        0,
        0);  // Defining positon to write from first row,first column .
    lcd.print(millis());  // You can write 16 Characters per line .
    for (int i = 0; i < 4; i++) {
      char parameter_char = 'a' + ((i + parameter_scroll) % MAX_PARAMETERS);
      lcd.setCursor(i * 4, 1);
      sprintf(lcd_buffer, "%03d",
              parameters[(i + parameter_scroll) % MAX_PARAMETERS]);
      lcd.print(String(parameter_char) + lcd_buffer);
    }
    lcd.setCursor(0, 1);
    lcd.blink();
    change = false;
  }
}