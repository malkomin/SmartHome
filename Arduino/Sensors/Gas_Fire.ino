#include <SoftwareSerial.h>
#include "ESP.h"
String wifiName = "WIFIBOX"; // Wifi SSID, Change it
String wifiPass = "1q1q1q1q"; //Wifi password , Change it
String ip = "192.168.1.2"; //IP of server, Change it
ESP esp(wifiName, wifiPass, ip);
//GAS
int gasLimit = 200;     //Determined gas threshold value. 
int gasLeds[] = { 7,6,5 };
uint8_t gasPin = A0;
//int value;                 //The value read from the sensor.  
//FÝRE
int fireLimit = 500;   //Determined fire threshold value.
uint8_t firePin = A1;
int fireLeds[] = { 3,2,1 }; //Red, Green , Buzzer
void setup() {
	Serial.begin(9600);
	esp.StartConnection();
	for (int i = 0; i < 3; i++)
	{
		pinMode(fireLeds[i], OUTPUT);
		pinMode(gasLeds[i], OUTPUT);
	}
}

// the loop function runs over and over again until power down or reset
void loop()
{
	ReadGas(gasPin, gasLimit, gasLeds);
	ReadFire(firePin, fireLimit, fireLeds);
}
void ReadGas(uint8_t pin, int limit, int leds[])
{
	int value = analogRead(pin);
	if (value > limit)
	{
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], LOW);
		digitalWrite(leds[2], HIGH);
		delay(50);
		esp.SendData("GAS","GAS","ALARM");
	}
	else
	{
		digitalWrite(leds[0], LOW);
		digitalWrite(leds[1], HIGH);
		digitalWrite(leds[2], LOW);
		esp.SendData("GAS", "GAS","Stable");
	}
}
void ReadFire(uint8_t pin, int limit, int leds[])
{
	int value = analogRead(pin);
	if (value > limit)
	{
		digitalWrite(leds[0], LOW);
		digitalWrite(leds[1], HIGH);
		digitalWrite(leds[2], LOW);
		esp.SendData("FIRE", "FIRE", "ALARM");
	}
	else
	{
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], LOW);
		digitalWrite(leds[2], HIGH);
		delay(50);
		esp.SendData("FIRE", "FIRE", "Stable");
	}
}