#include < Arduino.h >

String createId(char column, int row) {
  char id_string[3];
  sprintf(id_string, "%c%03u", column, row);
  return id_string;
}

void log(String message) {
  if (DEBUG_MODE) {
    Serial.println(message);
  }
}