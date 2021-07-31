#ifndef SUBJECTS_H
#define SUBJECTS_H

#include "Mouse.h"
#include "Observers.h"

/*
 * Subjects are monitoring physical buttons. They are sending messages to observers and are performing mouse actions.
 */

class Subject {
    public:
        Subject();
        void registerObserver(Observer* observer);
        void notifyObservers(int val);

        virtual void tick() = 0;
        // needs a void tick()

    private:
        Observer** observerPointers;
        int observerCount; 
};

class Scroll : public Subject {
    public:
        //Scroll(){}; // to be removed
        //Scroll() = remove;
        Scroll(int pin1, int pin2);
        virtual void tick();

    private:
        int pin1, pin2;
        int previousStatePin1, previousStatePin2;
};

class Button : public Subject{
    public:

        //Button() {}; // to be removed
        //Button() = remove;

        Button(int pin, char button);

        virtual void tick();

    private:
        uint count;
        int pin;
        char button;
        bool pressed;
        bool prepressed;
        unsigned long firstPressed;
        unsigned long waitTime;
        byte state;
};

#endif
