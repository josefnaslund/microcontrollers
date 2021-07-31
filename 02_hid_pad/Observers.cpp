#include "Arduino.h"
#include "Observers.h"

MyLed::MyLed(int pin, unsigned long interval, unsigned long len, int state) : pin(pin), interval(interval), len(len), state(state) {
    last = millis(); 
    on = false;
}

void MyLed::update(int val){
    SerialUSB.print("Hey MyLed object (");
    SerialUSB.print("pin ");
    SerialUSB.print(pin);
    SerialUSB.print(") received update: "); SerialUSB.println(val);
    state = val;
}

void MyLed::tick(){
    // normal constant flashing state
    if (state == 1){
        if (!on && millis() - last > interval){
            on = true;
            last = millis();
            digitalWrite(pin, HIGH);
        }

        else if (on && millis() - last > len){
            on = false;
            last = millis();
            digitalWrite(pin, LOW);
        }
    }

    else if (state == 0){
        if (on){on = false;
        digitalWrite(pin, LOW);
        }
    }

    else if (state == 2){
        if (!on){
            on = true;
            last = millis();
            digitalWrite(pin, HIGH);
        }
        else {
            if (millis() - last > len){
                on = false;
                state = 0;
                digitalWrite(pin, LOW);
            }
        }
    }

}
