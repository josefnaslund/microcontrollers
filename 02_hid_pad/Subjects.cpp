#include "Subjects.h"

Subject::Subject(){
    observerCount = 0;
}

void Subject::registerObserver(Observer* observer){
    // create new arr and copy
    Observer** newList = new Observer*[observerCount + 1]; 
    for (int i = 0; i != observerCount; ++i){newList[i] = observerPointers[i];}
    observerPointers = newList;

    // add new and postincrement
    observerPointers[observerCount++] = observer;  
}

void Subject::notifyObservers(int val) {
    for (int i = 0; i != observerCount; ++i) {observerPointers[i]->update(val);}
}



Scroll::Scroll(int pin1, int pin2) : pin1(pin1), pin2(pin2){
    previousStatePin1 = digitalRead(pin1);
    previousStatePin2 = digitalRead(pin2);
}

void Scroll::tick(){
    int currentStatePin1 = digitalRead(pin1);

    if (currentStatePin1 != previousStatePin1){
        if (digitalRead(pin2) != currentStatePin1){
            notifyObservers(2);
            Mouse.move(0, 0, -1);
            SerialUSB.println("Scrolling down, -1");
        }
        else {
            //notifyObservers(1);
            notifyObservers(2);
            Mouse.move(0, 0, 1);
            SerialUSB.println("Scrolling up, +1");
        }
    }

    previousStatePin1 = currentStatePin1;    
}



Button::Button(int pin, char button) : pin(pin), button(button){
    count = 0;
    waitTime = 50;
    pressed = false;
    prepressed = false;
    state = digitalRead(pin);
}

void Button::tick(){

    if (state != digitalRead(pin)){
        firstPressed = millis();
        state = digitalRead(pin);
    }

    // turn on
    if (digitalRead(pin) == LOW && !pressed && prepressed && millis() - firstPressed > waitTime){
        pressed = true;
        SerialUSB.print("Button is now pressed! Time to notify observers.... ");
        SerialUSB.println(++count);
        notifyObservers(1);
        Mouse.press(button);

        // Temporary. Make mouse click (and release - don't forget) an observer
        //Mouse.press(MOUSE_LEFT);
    }

    // before turning on, to avoid multiple keypresses
    else if (digitalRead(pin) == LOW && !pressed && !prepressed){
        prepressed = true;
        firstPressed = millis();
    }

    else if (!pressed && prepressed && millis() - firstPressed > waitTime){
        prepressed = false;
    }

    // turn off
    else if (pressed && digitalRead(pin) == HIGH && millis() - firstPressed > waitTime){
        pressed = false;
        prepressed = false;

        SerialUSB.println("Button is now released! Let's notify observers... ");
        notifyObservers(0);

        // Temp. Mouse click/releas to be implemented as observer
        //Mouse.release(MOUSE_LEFT);
        Mouse.release(button);
    }
}
