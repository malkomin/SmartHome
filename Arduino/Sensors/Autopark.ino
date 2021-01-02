#include <Servo.h>
#include "ESP.h"
Servo myservo;


#define ServoM    12
#define Bright    11
#define Exit      9         //çıkış butonu tanımlanmış
#define In        8         //Giriş butonu tanımlanmış

#define BarLow    177       //Bariyerin en düşük pozisyonu ayarlanmış
#define BarUp     95        //Bariyerin en yüksek pozisyonu ayarlanmış
#define CAPACITY  3         //Otopark kapasitesi belirlenmiş
#define INTEN     80        

//7segment display bacakları tanımlanmış
#define  segA  0
#define  segB  1
#define  segC  2
#define  segD  3
#define  segE  4
#define  segF  5
#define  segG  6

String wifiName = "";
String wifiPass = "";
String ip = "";
ESP esp(wifiName, wifiPass, ip);
String inputSTR;
String inputs[3]; //IN GATE, OUT GATE, CAPACITY
String str;
int i = 0;
//0-9 arasındaki rakamların 7 segmente gönderilmesi için bir dizi tanımlanmış
byte segments[10] = {

  B00111111, //  0
  B00000110, //  1
  B01011011, //  2
  B01001111, //  3
  B01100110, //  4
  B01101101, //  5
  B01111101, //  6
  B00000111, //  7
  B01111111, //  8
  B01101111  //  9
};

void setup(){
  myservo.attach(ServoM);
  esp.StartConnection();
  pinMode(Exit, INPUT); // çıkış butonu pini input olarak ayarlandı
  pinMode(In, INPUT);   // Giriş butonu input olarak ayarlandı
  digitalWrite(Exit, HIGH);// pull up direnci ile kullanılacak
  digitalWrite(In, HIGH);  // pull up direnci ile kullanılacak
  pinMode(segA,OUTPUT);   //her bir 7segment display bacagına gidecek pin output oldu
  pinMode(segB,OUTPUT);
  pinMode(segC,OUTPUT);
  pinMode(segD,OUTPUT);
  pinMode(segE,OUTPUT);
  pinMode(segF,OUTPUT);
  pinMode(segG,OUTPUT);
  pinMode(Bright,OUTPUT);
  analogWrite(Bright,255*INTEN/100);//parlaklık ayarı yapıldı
  myservo.write(BarLow);//servo motor bariyerin en dusuk pozisyonuna kadar hareket etti
//  delay(1000);
}

int  Available= 3;// Otoparktaki boş alan bilgisi integer olarak ayarlandı

//================================================================
void loop(){
    inputSTR = esp.getSensorData("AUTOPARK");
    while ((str = esp.splitString(inputSTR, ';', i)) != "")
    {
        inputs[i] = esp.splitString(str, '=', 1);
        i = i + 1;
    }
    i = 0;
    Available = inputs[2].toInt();
    Display(Available); // otoparktaki boş alan sayısı diplaye yazdırıldı
    if(inputs[0] == "1")//giriş butonuna basıldımı
    {
      if(Available != 0)
      {//otoparkta boş alan var mı ?
          Available--;// boş alan var ise boş alan sayısını 1 azalt
          myservo.write(BarUp);//bariyeri aç
          delay(3000);//3 sn gecikme
          myservo.write(BarLow);//bariyeri kapat
          esp.sendData("AUTOPARK", "INGATE", "0");

      }
    }
    if(inputs[1] == "1")// çıkış butonuna basıldı mı?
    {
      if(Available != CAPACITY){//boş alan sayısı toplam kapasiteye eşit mi?
        Available++;//değilse boş alan sayısını 1 arttır
        myservo.write(BarUp);//bariyeri kaldır
        delay(3000);//3 sn bekle
        myservo.write(BarLow);// bariyeri kapat
        esp.sendData("AUTOPARK", "OUTGATE", "0");
        }
    }
    esp.sendData("AUTOPARK", "CAPACITY", String(Available));
}


void Display(int number){// 7segment displaye deger yazdırma fonksiyonumuz
byte segs =  segments[number];//"" ortak anot için kullanıldı

digitalWrite(segA, bitRead(segs, 0) );
digitalWrite(segB, bitRead(segs, 1) );
digitalWrite(segC, bitRead(segs, 2) );
digitalWrite(segD, bitRead(segs, 3) );
digitalWrite(segE, bitRead(segs, 4) );
digitalWrite(segF, bitRead(segs, 5) );
digitalWrite(segG, bitRead(segs, 6) );
}