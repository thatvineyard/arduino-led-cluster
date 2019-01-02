#include <Arduino.h>

void initLCD() {
  lcd.begin(16, 2);  // Defining 16 columns and 2 rows of lcd display
  lcd.backlight();   // To Power ON the back light
  // lcd.backlight();// To Power OFF the back light
}

void updateDisplay() {
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