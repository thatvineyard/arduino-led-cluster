#include <Arduino.h>

namespace sender {

char message_buffer[MAX_MESSAGE_LENGTH];
long previous_message_hash = 0;

void createMessage(char* message_buffer, char* selector, String command,
                   char* parameters) {
  strcpy(message_buffer, "");

  sprintf(message_buffer + strlen(message_buffer), "%c", DELIM_MESSAGE_START);
  sprintf(message_buffer + strlen(message_buffer), "%c", DELIM_SELECTOR_START);
  strcat(message_buffer, selector);
  sprintf(message_buffer + strlen(message_buffer), "%c", DELIM_SELECTOR_END);
  strcat(message_buffer, command.c_str());
  if (parameters != "") {
    sprintf(message_buffer + strlen(message_buffer), "%c",
            DELIM_PARAMETERS_START);
    strcat(message_buffer, parameters);
    sprintf(message_buffer + strlen(message_buffer), "%c",
            DELIM_PARAMETERS_END);
  }
  sprintf(message_buffer + strlen(message_buffer), "%c", DELIM_MESSAGE_END);
}

bool sameAsPreviousMessage(char* new_message) {
  return hash(new_message) == previous_message_hash;
}

void sendMessage(char* message) {
  if (!sameAsPreviousMessage(message) && message != "") {
    Serial.print(message);
    previous_message_hash = hash(message);
  }
}

void sendMessage(char* selector, String command, char* parameters) {
  createMessage(message_buffer, selector, command, parameters);
  sendMessage(message_buffer);
}

void sendDimmer(int dimmer_value) {
  String parameters = "(" + String(dimmer_value) + ")";
  createMessage(message_buffer, ".*", "S_BASEBRIGHTNESS", parameters.c_str());
  sendMessage(message_buffer);
}

void sendColor(int red_value, int green_value, int blue_value) {
  String parameters = "(";
  parameters += String(red_value) + " ";
  parameters += String(green_value) + " ";
  parameters += String(blue_value) + ")";
  createMessage(message_buffer, ".*", "S_BASECOLOR", parameters.c_str());
  sendMessage(message_buffer);
}

void sendMacroSpeed(int macro_speed_value) {
  String parameters = "(" + String(macro_speed_value) + ")";
  createMessage(message_buffer, ".*", "S_BASESPEED", parameters.c_str());
  sendMessage(message_buffer);
}

void sendSettings(int dimmer_value, int red_value, int green_value,
                  int blue_value, int macro_speed_value) {
  sendDimmer(dimmer_value);
  sendColor(red_value, green_value, blue_value);
  sendMacroSpeed(macro_speed_value);
}

}  // namespace sender