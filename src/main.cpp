#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include <string>
#include <Potentio.h>
#include <Joystick.h>

long timer = 0;

//Here the name of the wifi is written
const char *ssid = "YourWIFI";
//Here the password of the wifi is written
const char *password = "YourPassword";

//We use a built in class called AsyncUDP - which is able to send messages through wifi
AsyncUDP udp;

//We initialize our objects Potentio, and Joystich here - with their given values.
Potentio potentio(34);
Joystick joystick(35, 33, 32);

void setup()
{
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Failed");
        while (1)
        {
            delay(1000);
        }
    }
    if (udp.listen(7007))
    {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
        });
    }
}

void loop()
{
    potentio.hueChange();
    joystick.movements();
}
