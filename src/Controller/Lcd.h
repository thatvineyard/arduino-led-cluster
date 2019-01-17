#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

namespace lcd {

void initLCD();

void updateDisplay();

void requestUpdate();
void requestParameterUpdate();
void requestAnimationUpdate();

}  // namespace lcd

#endif