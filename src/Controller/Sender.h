#ifndef SENDER_H_INCLUDED
#define SENDER_H_INCLUDED

namespace sender {

void initSender();

void createMessage(char* message_buffer, char* selector_string,
                   String command_string, char* parameters);

void sendMessage(char* message);

void sendMessage(char* selector, String command, char* parameters);

void sendDimmer(int dimmer_value);

void sendColor(int red_value, int green_value, int blue_value);

void sendMacroSpeed(int macro_speed_value);

void sendSettings(int dimmer_value, int red_value, int green_value,
                  int blue_value, int macro_speed_value);

void sendMacroPROTOTYPE();

}  // namespace sender

#endif