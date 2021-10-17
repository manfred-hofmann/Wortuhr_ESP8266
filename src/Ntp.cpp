//******************************************************************************
// Ntp.cpp - Get UTC time from NTP
//******************************************************************************

#include "Ntp.h"

Ntp::Ntp()
{
}

Ntp::~Ntp()
{
}

time_t Ntp::getTime(char* server)
{
    uint8_t packetBuffer[49] = {};
    packetBuffer[0] = 0xE3;
    packetBuffer[1] = 0x00;
    packetBuffer[2] = 0x06;
    packetBuffer[3] = 0xEC;
    packetBuffer[12] = 0x31;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 0x31;
    packetBuffer[15] = 0x34;
    WiFiUDP wifiUdp;
    wifiUdp.begin(2390);
    IPAddress timeServerIP;
    WiFi.hostByName(server, timeServerIP);
    wifiUdp.beginPacket(timeServerIP, 123);
    wifiUdp.write(packetBuffer, 48);
    wifiUdp.endPacket();
    uint32_t beginWait = millis();
    while ((millis() - beginWait) < 5000)
    {
        if (wifiUdp.parsePacket() >= 48)
        {
            wifiUdp.read(packetBuffer, 48);
            uint32_t ntpTime = (packetBuffer[40] << 24) + (packetBuffer[41] << 16) + (packetBuffer[42] << 8) + packetBuffer[43];
            // NTP time is seconds from 1900, TimeLib.h needs seconds from 1970
            ntpTime -= 2208988800;
            return ntpTime;
        }
    }
    return 0;
}
