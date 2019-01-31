namespace repeater {

void init() {
  // Serial.begin(BAUD_RATE);
}

void readSerial() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    Serial.write(inChar);
  }
}
}  // namespace repeater