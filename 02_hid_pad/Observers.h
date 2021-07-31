#ifndef OBSERVERS_H
#define OBSERVERS_H

/* Observers are controlling LEDs. They are notified by Subjects */

class Observer {
    public:
        virtual void update(int val) = 0;
        virtual void tick() = 0;  
};


class MyLed : public Observer{
    public:
        MyLed(int pin, unsigned long interval, unsigned long len, int state);

        /*
         * val=0 no light
         * val=1 continous blink
         * val=2 blink once with "len" length
         */
        virtual void update(int val);
        virtual void tick();

    private:
        bool on;
        int pin;
        unsigned long interval;
        unsigned long len;
        unsigned long last;
        int state;
};

#endif
