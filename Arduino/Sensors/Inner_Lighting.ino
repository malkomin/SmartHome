#include "ESP.h"
//LEDS
int RL=0;
int GL=1;
int BL=2;
int LED_1=3;
int LED_2=4;
int LED_3=5;
int LED_4=6;
String wifiName = "";
String wifiPass = "";
String ip = "";
ESP esp(wifiName, wifiPass, ip);
String inputSTR;
String inputs[7]; //R , G ,B , L1 , L2 ,L3 ,L4
String str;
int i = 0;
void setup()
{
    esp.StartConnection();
    pinMode(RL, OUTPUT);
    pinMode(GL, OUTPUT);
    pinMode(BL, OUTPUT);
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    pinMode(LED_4, OUTPUT);
}

void loop(){
    inputSTR = esp.getSensorData("INNER_LIGHT");
    while ((str = esp.splitString(inputSTR, ';', i)) != "")
    {
        inputs[i] = esp.splitString(str, '=', 1);
        
        i = i + 1;
    }
    i = 0;
//RGB PART
//BLUE LED WORKS.
    if(inputs[0] == "1"){
          digitalWrite(BL,HIGH);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}

    if(inputs[2] == "0"){
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}

    //RED LED WORKS.
    if(inputs[0] == "1"){
          digitalWrite(RL,HIGH);
          digitalWrite(BL,LOW);
          digitalWrite(GL,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}
    if(inputs[0] == "0"){
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}

    //GREEN LED WORKS.    
    if(inputs[1] == "1"){
          digitalWrite(GL,HIGH);
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}
    if(inputs[1] == "0"){
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}
      
    //YELLOW LED WORKS.
    if(inputs[1] == "1"&&inputs[0] == "1"){
          digitalWrite(GL,HIGH);
          digitalWrite(BL,LOW);
          digitalWrite(RL,HIGH);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}
    if(inputs[1] == "0"||inputs[1] == "0"){
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}
      
    //PURBLE LED WORKS.
    if(inputs[2] == "1"&&inputs[0] == "1"){
          digitalWrite(GL,LOW);
          digitalWrite(BL,HIGH);
          digitalWrite(RL,HIGH);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}
    if(inputs[2] == "0"||inputs[0] == "0"){
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}

    //WHİTE LED WORKS.
    if(inputs[2] == "1"&&inputs[0] == "1"&&inputs[1] == "1"){
          digitalWrite(GL,HIGH);
          digitalWrite(BL,HIGH);
          digitalWrite(RL,HIGH);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}
    if(inputs[2] == "0"||inputs[0] == "0"||inputs[1] == "0"){
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);}

    //NORMAL LED PART
    //LED_1 WORKS.
    if(inputs[3] == "1"){
          digitalWrite(LED_1,HIGH);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);}
    if(inputs[3] == "0"){
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);}
      
    //LED_2 WORKS.
    if(inputs[4] == "1"){
          digitalWrite(LED_2,HIGH);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);}
    if(inputs[4] == "0"){
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_4,LOW);
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);}
      
    //LED_3 WORKS.
    if(inputs[5] == "1"){
          digitalWrite(LED_3,HIGH);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_4,LOW);
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);}
    if(inputs[5] == "0"){
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(LED_4,LOW);
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);}

    //LED_4 WORKS.
    if(inputs[6] == "1"){
          digitalWrite(LED_4,HIGH);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);}
    if(inputs[6] == "0"){
          digitalWrite(LED_4,LOW);
          digitalWrite(LED_3,LOW);
          digitalWrite(LED_1,LOW);
          digitalWrite(LED_2,LOW);
          digitalWrite(BL,LOW);
          digitalWrite(RL,LOW);
          digitalWrite(GL,LOW);}
}
