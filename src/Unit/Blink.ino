#include <Arduino.h>
#include "Led.h"

int red_value, green_value, blue_value;
int toggle_flag = 0;


namespace blink
{
    void toggle() {
        if (toggle_flag == 0) {
            led::setColor(red_value, green_value, blue_value);
            toggle_flag = 1;
        } else {    
            led::setColor(0, 0, 0);
            toggle_flag = 0;
        }
    }
    
    void tick() {
        if (timerLapsed()) {
            toggle();

            resetTimer();
        }  
    }

    void init(int new_red_value, int new_green_value, int new_blue_value, int new_blink_delay) {
        led::initLed();
        
        setTimer(new_blink_delay);
        red_value = new_red_value;
        green_value = new_green_value;
        blue_value = new_blue_value;
        resetTimer();
        led::setColor(255, 0, 0);
    }


} // blink