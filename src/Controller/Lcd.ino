#include <Arduino.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
char lcd_buffer[16];
bool lcd_change = true;

void initLCD() {
  lcd.begin(16, 2);  // Defining 16 columns and 2 rows of lcd display
  lcd.backlight();   // To Power ON the back light
  // lcd.backlight();// To Power OFF the back light
}

void updateDisplay() {
  if (lcd_change == true) {
    // Write your code
    lcd.setCursor(
        0,
        0);  // Defining positon to write from first row,first column .
    lcd.print(millis());  // You can write 16 Characters per line .
    for (int i = 0; i < 4; i++) {
      char parameter_char =
          'a' + ((i + composer::parameter_selector) % MAX_PARAMETERS);
      lcd.setCursor(i * 4, 1);
      sprintf(lcd_buffer, "%03d",
              composer::parameters[(i + composer::parameter_selector) %
                                   MAX_PARAMETERS]);
      lcd.print(String(parameter_char) + lcd_buffer);
    }
    lcd.setCursor(0, 1);
    lcd.blink();
    lcd_change = false;
  }
}

void requestUpdate() {
  lcd_change = true;
}