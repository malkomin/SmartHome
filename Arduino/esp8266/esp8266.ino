#include <SoftwareSerial.h>
String cmd,msg="Hello";
SoftwareSerial espSerial(2, 3); 
String wifi_name = "SUPERONLINE_WiFi_2499"; //Change it
String wifi_pass = "bekir2499"; //Change it
String ip = "192.168.1.6"; //Change it
String port = "13000";
void setup(){
Serial.begin(9600);
espSerial.begin(9600); //ESP8266 Baud rate
AT("AT+RST",2000,true); //ESP8266 Reset
AT("AT+CWMODE=1",2000,true);
AT("AT+CWJAP=\""+wifi_name+"\",\""+wifi_pass+"\"",2000,true);
}
void loop()
{
  AT("AT+CIPMUX=1", 1000, true);
 AT("AT+CIPSTART=0,\"TCP\",\""+ip+"\","+port, 5000, true);
 cmd="AT+CIPSEND=0,"+String(msg.length());
  AT(cmd,2000,true);
  AT(msg,2000,true);
}
String AT(String cmd,int del,boolean stat){
  String inc = "";
  espSerial.print(cmd+"\r\n");
  long int passed = millis();
  while((passed+del)>millis())
  {
    while(espSerial.available())
    {
      char c = espSerial.read();
      inc += c;
      
    }
  }
  if(stat)
  {
    Serial.println(inc);
  }
  return inc;
}
