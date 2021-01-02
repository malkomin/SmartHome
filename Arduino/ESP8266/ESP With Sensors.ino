/*
 Name:		ESP_With_Sensors.ino
 Created:	12/23/2020 12:18:33 PM
 Author:	Mehmet Ali
*/

// the setup function runs once when you press reset or power the board
#include <SoftwareSerial.h>
#include "ESP.h"
String wifiName = "WIFIBOX"; // Wifi SSID, Change it
String wifiPass = "1q1q1q1q"; //Wifi password , Change it
String ip = "192.168.1.92"; //IP of server, Change it
ESP esp(wifiName, wifiPass, ip);
String inputSTR;
String inputs[7];
String str;

int i = 0;
void setup() {
	Serial.begin(9600);
	esp.StartConnection();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	inputSTR = esp.getSensorData("AUTOPARK");
	while ((str = esp.splitString(inputSTR, ';', i)) != "")
	{
		inputs[i] = esp.splitString(str, '=', 1);
		i = i + 1;
	}
	i = 0;
	int a = inputs[2].toInt();
	a = a + 2;
	String value = String(a);
	esp.SendData("AUTOPARK", "CAPACITY", value);
	esp.SendData("THIEF", "THIEF", "WRONG PASS");
	esp.SendData("AUTOPARK", "INGATE", "0");
	esp.SendData("AUTOPARK", "OUTGATE", "0");
}




