#include <Arduino.h>

namespace sender {

String previous_message = "";

String createMessage(String selector, String command, String parameters) {
  String message = "";

  message += DELIM_MESSAGE_START;
  message += DELIM_SELECTOR_START;
  message += selector;
  message += DELIM_SELECTOR_END;
  message += command;
  if (parameters != "") {
    message += DELIM_PARAMETERS_START;
    message += parameters;
    message += DELIM_PARAMETERS_END;
  }
  message += DELIM_MESSAGE_END;

  return message;
}

bool sameAsPreviousMessage(String new_message) {
  return new_message == previous_message;
}

void sendMessage(String message) {
  if (!sameAsPreviousMessage(message)) {
    Serial.print(message);
    previous_message = message;
  }
}

void sendMessage(String selector, String command, String parameters) {
  sendMessage(createMessage(selector, command, parameters));
}

void sendDimmer(int dimmer_value) {
  String parameters = "(" + String(dimmer_value) + ")";
  sendMessage(createMessage(".*", "S_BASEBRIGHTNESS", parameters));
}

void sendColor(int red_value, int green_value, int blue_value) {
  String parameters = "(";
  parameters += String(red_value) + " ";
  parameters += String(green_value) + " ";
  parameters += String(blue_value) + ")";
  sendMessage(createMessage(".*", "S_BASECOLOR", parameters));
}

void sendMacroSpeed(int macro_speed_value) {
  String parameters = "(" + String(macro_speed_value) + ")";
  sendMessage(createMessage(".*", "S_BASESPEED", parameters));
}

void sendMacroPROTOTYPE() {
  if (macro_toggle) {
    sendMessage(createMessage(".*", "S_BASECOLOR", "(255 30 0)"));
    macro_toggle = false;
  } else {
    sendMessage(createMessage(".*", "M_FLICKER", "(20 200)"));
    macro_toggle = true;
  }
}

void sendSettings(int dimmer_value, int red_value, int green_value,
                  int blue_value, int macro_speed_value) {
  sendDimmer(dimmer_value);
  sendColor(red_value, green_value, blue_value);
  sendMacroSpeed(macro_speed_value);
}

}  // namespace sender