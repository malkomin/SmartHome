#ifndef _ESP_h
#define _ESP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#include <SoftwareSerial.h>
#else
	#include "WProgram.h"
#endif

class ESP
{
 protected:
	 String wifiName;
	 String wifiPass;
	 String ip; 
	 String port = "13000";
	 int RXPin = 2;
	 int TXPin = 3;
	 SoftwareSerial espSerial;
	 String SendCommand(String cmd, int _delay, bool stat);
	 void ConnectToIP(String ip, String port);
	 String DecodeMessage(String msg);
 public:
	ESP(String _wifiName, String _wifiPass, String _ip);
	void SendData(String sensor, String type, String data);
	String getSensorData(String type);
	void StartConnection();
	String splitString(String data, char separator, int index);
};


#endif

