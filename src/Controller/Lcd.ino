#include <Arduino.h>

#define LCD_ROWS 2
#define LCD_COLUMNS 16

namespace lcd {

// LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
char lcd_buffer[16];
bool lcd_change = true;

void initLCD() {
  lcd.begin(LCD_COLUMNS,
            LCD_ROWS);  // Defining 16 columns and 2 rows of lcd display
  lcd.backlight();      // To Power ON the back light
  // lcd.backlight();// To Power OFF the back light
}

// ROWS\

void print_millis_row(int row) {
  lcd.setCursor(
      0,
      row);  // Defining positon to write from first row,first column .
  lcd.print(millis());  // You can write 16 Characters per line .
}

void print_macro_row(int row) {}

void print_parameter_row(int row) {
  for (int i = 0; i < LCD_COLUMNS / 4; i++) {
    char parameter_char =
        'a' + ((i + view::parameter_selector) % MAX_PARAMETERS);
    lcd.setCursor(i * 4, row);
    sprintf(
        lcd_buffer, "%03d",
        composer::parameters[(i + view::parameter_selector) % MAX_PARAMETERS]);
    lcd.print(String(parameter_char) + lcd_buffer);
  }
  lcd.setCursor(0, row);
  lcd.blink();
  lcd_change = false;
}

void updateDisplay() {
  if (lcd_change == true) {
    if (LCD_ROWS == 1) {
      print_parameter_row(0);
    }
    if (LCD_ROWS == 2) {
      print_millis_row(0);
      print_parameter_row(1);
    }
    if (LCD_ROWS == 3) {
      print_millis_row(0);
      print_millis_row(1);
      print_parameter_row(2);
    }
    if (LCD_ROWS == 4) {
      print_millis_row(1);
      print_millis_row(2);
      print_millis_row(3);
      print_parameter_row(4);
    }
  }
}

void requestUpdate() {
  lcd_change = true;
}
}  // namespace lcd