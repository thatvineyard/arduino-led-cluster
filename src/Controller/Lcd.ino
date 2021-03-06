#include <Arduino.h>

#define LCD_ROWS 4
#define LCD_COLUMNS 20
#define CLEAR_LINE F("                    ")

namespace lcd {

// LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
char lcd_buffer[16];
bool lcd_change = true;
bool lcd_change_parameter = true;
bool lcd_change_animation = true;

void initLCD() {
  lcd.begin(LCD_COLUMNS,
            LCD_ROWS);  // Defining 16 columns and 2 rows of lcd display
  lcd.backlight();      // To Power ON the back light
  // lcd.backlight();// To Power OFF the back light
}

void clearLine(int row) {
  lcd.setCursor(0, row);
  lcd.print(CLEAR_LINE);
}

// ROWS\

void print_millis_row(int row) {
  if (lcd_change) {
    clearLine(row);
  }

  lcd.setCursor(0, row);
  lcd.print(millis());  // You can write 16 Characters per line .
}

void print_macro_row(int row) {
  if (lcd_change) {
    clearLine(row);
  }

  lcd.setCursor(0, row);
  lcd.print(commandToString((Command)view::macro_selector));
}

void print_animation_row(int row) {
  if (lcd_change || lcd_change_animation) {
    clearLine(row);
  }

  lcd.setCursor(0, row);
  lcd.print(animation::animationToString(
      (animation::Animation)view::animation_selector));
  lcd.setCursor(LCD_COLUMNS - 2, row);
  lcd.print(String(animation::step));
}
void print_animation_speed_row(int row) {
  if (lcd_change || lcd_change_parameter) {
    clearLine(row);
  }

  lcd.setCursor(0, row);
  lcd.print(String(composer::animation_speed_value));
}

void print_filter_row(int row) {
  if (lcd_change) {
    clearLine(row);
  }

  lcd.setCursor(0, row);
  lcd.print(filter::filterToString((filter::Filter)view::filter_selector));
}

void print_control_row(int row) {
  switch ((view::View)view::view_scroll) {
    case view::MACRO:
      print_macro_row(row);
      break;
    case view::ANIMATION:
      print_animation_row(row);
      break;
    case view::FILTER:
      print_filter_row(row);
      break;
    case view::ANIMATION_SPEED:
      print_animation_speed_row(row);
      break;
  }
}

void print_parameter_row(int row) {
  clearLine(row);

  for (int i = 0; i < LCD_COLUMNS / 4; i++) {
    char parameter_char =
        'a' + ((i + view::parameter_selector) % MAX_PARAMETERS);
    lcd.setCursor(i * 4, row);
    sprintf(
        lcd_buffer, "%c%03d", parameter_char,
        composer::parameters[(i + view::parameter_selector) % MAX_PARAMETERS]);
    lcd.print(lcd_buffer);
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
      print_control_row(0);
      print_parameter_row(1);
    }
    if (LCD_ROWS == 3) {
      print_millis_row(0);
      print_millis_row(1);
      print_parameter_row(2);
    }
    if (LCD_ROWS == 4) {
      print_control_row(0);
      print_macro_row(1);
      print_animation_row(2);
      print_parameter_row(3);
    }
  }
}

void requestUpdate() {
  lcd_change = true;
}
void requestParameterUpdate() {
  lcd_change_parameter = true;
}
void requestAnimationUpdate() {
  lcd_change_animation = true;
}
}  // namespace lcd
