#include "ESP.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
ESP::ESP(String _wifiName, String _wifiPass, String _ip) : espSerial(RXPin, TXPin)
{
	wifiName = _wifiName;
	wifiPass = _wifiPass;
	ip = _ip;
    espSerial.begin(9600); //ESP8266 Baud rate
}
void ESP::ConnectToIP(String ip, String port)
{
    SendCommand("AT+CIPMUX=1", 1000, true);
    SendCommand("AT+CIPSTART=0,\"TCP\",\"" + ip + "\"," + port, 5000, true);
}
void ESP::StartConnection()
{
	SendCommand("AT+RST", 2000, true); //ESP8266 Reset
	SendCommand("AT+CWMODE=1", 2000, true);
	SendCommand("AT+CWJAP=\"" + wifiName + "\",\"" + wifiPass + "\"", 7000, true);
    ConnectToIP(ip, port);
}
void ESP::SendData(String sensor, String type, String data)
{
    String cmd = "";
    type = "SET." + sensor + "." + type+ "." + data + ".";
    type.trim();
    cmd = "AT+CIPSEND=0," + String(type.length());
    SendCommand(cmd, 2000, true);
    SendCommand(type, 2000, true);
}
String ESP::getSensorData(String type)
{
    String cmd = "";
    String output = "";
    type = "GET." + type;
    cmd = "AT+CIPSEND=0," + String(type.length());
    SendCommand(cmd, 2000, true);
    output = SendCommand(type, 2000, false);
    String data = DecodeMessage(output);
    return data;
}
String ESP::SendCommand(String cmd, int _delay, bool stat)
{
    String inc;
    espSerial.print(cmd + "\r\n");
    long int passed = millis();
    while ((passed + _delay) > millis())
    {
        while (espSerial.available())
        {
            char c = espSerial.read();
            inc += c;
        }
    }
    if (stat)
    {
        Serial.println("Sending " + inc);
    }
    return inc;
}
String ESP::splitString(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String ESP::DecodeMessage(String msg)
{
    String ipdString = splitString(msg, '+', 1);
    String data = splitString(ipdString, ':', 1);
    return data;
}


