#include "AsyncUDP.h"
#include <Arduino.h>
class Potentio
{
public:
    int pinNumber;
    int tolerance = 10;
    int sensorValue;
    int preValue;

    //A constructor for the Potentio object. It takes the pinNumber as input.
    Potentio(int pinNumber)
    {
        //this refers to the class that you are inside
        this->pinNumber = pinNumber;
        pinMode(this->pinNumber, INPUT);
    }
    //This method will return the value (of type int) of what it reads from the potentiometer.
    int readPotentiometer()
    {
        sensorValue = analogRead(pinNumber);
        return sensorValue;
    }

    // This methods maps the potentiometer to be of interval ]0;255[. 
    //It also returns true if the value of the last read is more than 10 larger tham the new read.
    bool hasChanged()
    {
        sensorValue = map(readPotentiometer(), 0, 4095, 0, 255);
        if (sensorValue > preValue + tolerance || sensorValue < preValue - tolerance)
        {
            preValue = sensorValue;
            return true;
        }
        else
        {
            sensorValue = preValue;
            return false;
        }
    }

    //This method broadcasts a message containing the new read if it has changed according to the conditions in hasChanged().
    AsyncUDP udp;
    void hueChange()
    {
        int sensorValue = map(readPotentiometer(), 0, 4095, 0, 255);
        if (hasChanged() == true)
        {
            String text1 = "color ";
            String text2 = text1 + sensorValue;

            udp.broadcastTo(text2.c_str(), 7000);
            preValue = sensorValue;
        }
        else
        {
            sensorValue = preValue;
        }
    }
};
