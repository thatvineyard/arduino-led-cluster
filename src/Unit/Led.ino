#include <Arduino.h>
#include "Led.h"

#define LED_RED_PIN 9
#define LED_GREEN_PIN 10
#define LED_BLUE_PIN 11


namespace led {

    int brightness_value = 200;

    int current_red_value = 0;
    int current_green_value = 0;
    int current_blue_value = 0;
    
    void initLed() {
        // Turn on LED_PIN
        pinMode(LED_RED_PIN, OUTPUT);
        pinMode(LED_GREEN_PIN, OUTPUT);
        pinMode(LED_BLUE_PIN, OUTPUT);
    }

    // LED Value manipulation
    int constrain8BitValue(int value) { return constrain(value, 0, 255); }

    int applyBrightness(int value) { 
        long val = ((long) value * (long) brightness_value) / 255;
        return (int) val;
    }

    int invert8BitValue(int value) { return 255 - value; }

    int adjustLedValue(int value) {
        int result = value;
       
        result = constrain8BitValue(result);
       
        result = applyBrightness(result);
        
        //result = invert8BitValue(result);
        
        return result;
    }
    
    void commitPinValues() {
        analogWrite(LED_RED_PIN, adjustLedValue(current_red_value));
        analogWrite(LED_GREEN_PIN, adjustLedValue(current_green_value));
        analogWrite(LED_BLUE_PIN, adjustLedValue(current_blue_value));
    }


    void setColor(int red_value, int green_value, int blue_value) {
        if(DEBUG_MODE) {
            //Serial.println("Color set to " + String(red_value) + " " + String(green_value) + ", " + String(blue_value) + ".");
        }

        current_red_value = red_value;
        current_green_value = green_value;
        current_blue_value = blue_value;
        commitPinValues();
    }

    void setBrightness(int new_brightness_value) {
        if(DEBUG_MODE) {
            Serial.println("Brightness set to " + String(new_brightness_value));
        }

        brightness_value = new_brightness_value;

        commitPinValues();
    }

    void reset() {
        current_red_value = 0;
        current_green_value = 0;
        current_blue_value = 0;
        commitPinValues();
    }


} // led