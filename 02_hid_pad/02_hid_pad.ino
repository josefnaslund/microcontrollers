/*
 * This program is made with SEEEDUINO XIAO microcontroller. It's small, cheap and uses USB C.
 * Program sends user input from button(s) and scroll wheel (rotary encoder) to computer as USB HID device.
 * It also uses external LED for notyfying about activity, which is the purpose of the observer pattern.
 * 
 * It can be uploaded with the Arduino IDE with the extension Seeeduino Xiao board manager. Or used with another board.
 * 
 * Files: hid_device.ino, Observers.h, Observers.cpp, Subjects.cpp, Subjects.h
 * 
 * Author: Josef Näslund, summer 2021.
 * Link: https://github.com/josefnaslund
 */

#include "Mouse.h"
#include "Observers.h"
#include "Subjects.h"

// ///////// ///////// ///////// /////////
// Some constants for pins used
// ///////// ///////// ///////// /////////

const int ledpin1 = 0; // continous blink every other second
const int ledpin2 = 0; // scroll indicator
const int ledpin3 = 0; // button press indicator
const int btnpin1 = 7;
const int rotarypin1 = 8;
const int rotarypin2 = 9;

// /////////////////////////////////////
// Observer LEDs
///////////////////////////////////////

Observer** myObservers;
const int observerCount = 3;

// ///////////////////////////////////
// Subjects (mouse actions, button presses, scroll wheel)
// ///////////////////////////////////

Subject** mySubjects;
const int subjectCount = 2;


// ///////////////////////////////////
// SETUP
// ///////////////////////////////////
void setup() {
    // put your setup code here, to run once:
    SerialUSB.begin(9600);
    Mouse.begin();
    pinMode(ledpin1, OUTPUT);
    pinMode(ledpin2, OUTPUT);
    pinMode(ledpin3, OUTPUT);
    pinMode(btnpin1, INPUT);
    pinMode(rotarypin1, INPUT);
    pinMode(rotarypin2, INPUT);

    myObservers = new Observer*[observerCount];
    myObservers[0] = new MyLed(ledpin1, 3000, 10, 1); // continious blink
    myObservers[1] = new MyLed(ledpin2, 0, 100, 0); // scroll indicator
    myObservers[2] = new MyLed(ledpin3, 50, 10, 0); // left click indicator

    // create the ptr array
    mySubjects = new Subject*[subjectCount];

    // Left click
    mySubjects[0] = new Button(btnpin1, MOUSE_LEFT);
    mySubjects[0]->registerObserver(myObservers[2]);

    // Scroll
    mySubjects[1] = new  Scroll(rotarypin1, rotarypin2);
    mySubjects[1]->registerObserver(myObservers[1]);
}


void loop() {
    // check buttons
    for (int i = 0; i != subjectCount; ++i){
        mySubjects[i]->tick();
    }

    // LEDs action
    for (int i = 0; i != observerCount; ++i){
        myObservers[i]->tick();
    }      
}
