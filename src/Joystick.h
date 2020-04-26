#include "AsyncUDP.h"
#include <Arduino.h>

class Joystick
{
public:
    //Initiating the variables that will be needed.
    int pinX;
    int pinY;
    int valX;
    int valY;
    int SW;
    
    //A constructor for the joystick object containing a pin number for X,
    //a pin number for Y and a pin number for the switch.
    Joystick(int pinX, int pinY, int SW)
    {
        this->pinX = pinX;
        pinMode(this->pinX, INPUT);
        this->pinY = pinY;
        pinMode(this->pinY, INPUT);
        this->SW = SW;
        pinMode(this->SW, INPUT_PULLUP);
    }
    //This method returns -1 if the change in the X-direction is negative,
    //1 if the change in the X-direction is positive, and 0 if there is no change in the X direction.

    int hasChangedX()
    {
        valX = analogRead(pinX);
        if (valX < 500)
        {
            return -1;
        }
        else if (valX > 4000)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    //This method returns -1 if the change in the Y-direction is negative,
    //1 if the change in the Y-direction is positive, and 0 if there is no change in the Y direction.
    int hasChangedY()
    {
        valY = analogRead(pinY);
        if (valY < 500)
        {
            return -1;
        }
        else if (valY > 4000)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    // This method is checking whether the switch is pressed or not.
    bool isPressed()
    {
        if (digitalRead(SW) == LOW)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    AsyncUDP udp;
    //method sends the appropriate message in the direction we move the joystick to the drone emulator.
    void movements()
    {
        if (hasChangedX() == -1)
        {
            udp.broadcastTo("moveleft", 7000);
        }
        else if (hasChangedX() == 1)
        {
            udp.broadcastTo("moveright", 7000);
        }
        if (hasChangedY() == -1)
        {
            udp.broadcastTo("moveup", 7000);
        }
        else if (hasChangedY() == 1)
        {
            udp.broadcastTo("movedown", 7000);
        }

        if (isPressed() == true)
        {
            udp.broadcastTo("center", 7000);
        }
    }
};