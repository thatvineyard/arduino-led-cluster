#ifndef SENDER_H_INCLUDED
#define SENDER_H_INCLUDED

namespace sender {

String createMessage(String selector_string,
                     String command_string,
                     String parameters);

String createMessage(String selector, String command, int number_of_parameters);

void sendMessage(String message);

void sendMessage(String selector, String command, String adada);

void sendDimmer(int dimmer_value);

void sendColor(int red_value, int green_value, int blue_value);

void sendMacroSpeed(int macro_speed_value);

void sendSettings(int dimmer_value,
                  int red_value,
                  int green_value,
                  int blue_value,
                  int macro_speed_value);

void sendMacroPROTOTYPE();

}  // namespace sender

#endif