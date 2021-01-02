#define LED_1 1          //Pin where the LED_1 is located.
#define LED_2 2          //Pin where the LED_2 is located.
#define LED_3 3          //Pin where the LED_3 is located.
#define LED_4 4          //Pin where the LED_4 is located.
#define LED_5 5          //Pin where the LED_5 is located.
#define LED_6 6          //Pin where the LED_6 is located.
#define LED_7 7          //Pin where the LED_7 is located.
#define LED_8 8          //Pin where the LED_8 is located.
#define LED_9 9          //Pin where the LED_9 is located.
#define LED_10 10        //Pin where the LED_10 is located.

void setup() {
pinMode (LED_1, OUTPUT);          //LED_1 is set as output.
pinMode (LED_2, OUTPUT);          //LED_2 is set as output.
pinMode (LED_3, OUTPUT);          //LED_3 is set as output.
pinMode (LED_4, OUTPUT);          //LED_4 is set as output.
pinMode (LED_5, OUTPUT);          //LED_5 is set as output.
pinMode (LED_6, OUTPUT);          //LED_6 is set as output.
pinMode (LED_7, OUTPUT);          //LED_7 is set as output.
pinMode (LED_8, OUTPUT);          //LED_8 is set as output.
pinMode (LED_9, OUTPUT);          //LED_9 is set as output.
pinMode (LED_10,OUTPUT);          //LED_10 is set as output.

}

void loop() {
int value =analogRead(A0);       //Value that comes from LDR.
if (value < 650) 
{               //If value is smaller than 650,thıs statement works.                                    
    setLeds(LOW);
}
else  //If the value is bigger than 650, this statement works.
{      
    setLeds(HIGH);
}
}
void setLeds(int status)
{
    digitalWrite(LED_1, status);          //All LEDs are HIGH.          
    digitalWrite(LED_2, status);
    digitalWrite(LED_3, status);
    digitalWrite(LED_4, status);
    digitalWrite(LED_5, status);
    digitalWrite(LED_6, status);
    digitalWrite(LED_7, status);
    digitalWrite(LED_8, status);
    digitalWrite(LED_9, status);
    digitalWrite(LED_10, status);
}

  
