#include "EEPROM.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <UTFT.h>

UTFT tft(QD220A,11,13,9,7,8); 
Adafruit_ADS1115 ads(0x48);

#define minus 5
#define plus  4 
#define fast  3 
#define curr  2 
#define vent  A0

float Voltage = 0.0;
float Voltagei = 0.0;
float curent = 0.0;

int h=0;
int c=0;
int prevh = 0;

int tempPin = A2;  //LM35
int val;
extern uint8_t SmallFont[];
extern uint8_t BigFont[];

void setup()
{
  Serial.begin(9600);
  
   Wire.begin();
   ads.begin();
   pinMode(6, OUTPUT);
   pinMode(plus, INPUT); 
pinMode(minus, INPUT);
pinMode(curr, INPUT);
digitalWrite(curr, HIGH);
digitalWrite(plus, HIGH);
digitalWrite(minus, HIGH);
 pinMode(fast, INPUT); 
digitalWrite(fast, HIGH);
pinMode(10, OUTPUT);
h=EEPROM.read(100);
analogWrite(10, h);
c=EEPROM.read(101);
analogWrite(6, c);

  tft.InitLCD(); 
    tft.clrScr(); 
    tft.setBackColor(0,0,0);
  tft.setColor(0,255 , 255);
 tft.drawRect(0,1,219,23);  
 tft.setColor(0,255 , 255);
   tft.setFont(BigFont);
    tft.print("V",125,5);
    tft.setFont(SmallFont);
      tft.print("U-iesire",155,7);
      tft.setColor(255,255 , 255);
 tft.drawRect(0,26,219,50);
  tft.setFont(BigFont);
  tft.print("A",125,30);  
  tft.setFont(SmallFont);
      tft.print("I-iesire",155,32);
      tft.setColor(255,0 , 0);
 tft.drawRect(0,54,219,76);
 tft.drawRoundRect(90,58,95,63);
tft.print("C ",97,57);
 tft.setFont(SmallFont); 
 tft.print("Temperatura",131,58);
 tft.setFont(SmallFont); tft.setColor(255,255 , 0);
  tft.print("PWM-U [8Bit]",121,83);
   tft.setFont(SmallFont);  tft.setColor(255,0 ,255);
 tft.print("PWM-i [8Bit]",121,107); tft.setFont(BigFont);
tft.setFont(SmallFont);  tft.setColor(0,0 ,255);
 tft.print("Vlad Gheorghe @2019",67,159);tft.setFont(BigFont);
 
tft.setColor(0,255 ,0);
 tft.drawRect(0,127,219,151);
 tft.setFont(SmallFont); // tft.setColor(255,0 ,255);
 tft.print("U-intrare",145,132);
  tft.setFont(BigFont);
  tft.print("V",125,132); 
}

void loop()
{
 h=EEPROM.read(100);
analogWrite(10, h);
c=EEPROM.read(101);
analogWrite(6, c);
 printt();
 if(!digitalRead(plus) && digitalRead(curr)==HIGH && digitalRead(fast)==HIGH)
    { 
    h = h+1;
   
     if (h > 255) {h=254;}
   
analogWrite(10, h);
    delay(10);
   
//Serial.println(h);
}

    EEPROM.write(100, h);
    
if(!digitalRead(plus) && !digitalRead(fast))
    {  
    h = h+10;
   
     if (h > 255) {h=254;}
  
analogWrite(10, h);
    delay(10);
  
}

    EEPROM.write(100, h);
    // }

if(!digitalRead(minus) && !digitalRead(fast))
    {
   
    h = h-10;
   
     if (h < 0) {h=1;}
   
analogWrite(10, h);
    delay(10);
 
//Serial.println(h);
}


    EEPROM.write(100, h);
    // }
     if (!digitalRead(minus) && digitalRead(curr)==HIGH && digitalRead(fast)==HIGH)

    {  
    h = h-1;
     if (h < 0) {h=1;}
  
analogWrite(10, h);
    delay(10);
 
//Serial.println(h);
}
   
   EEPROM.write(100, h);
   //  } 
//reglaj pwm curent cu pas de 10

if(!digitalRead(curr) && !digitalRead(minus))
    {
   
   c = c-10;
   
     if (c < 0) {c=1;}
   
analogWrite(6, c);
 //   delay(1);
 
Serial.println(c);
}
  EEPROM.write(101, c);
   
  if(!digitalRead(curr) && !digitalRead(plus))
    {  
    c = c+10;
   
     if (c > 255) {c=254;}
  
analogWrite(6, c);
   // delay(1);
    
  Serial.println(c);
   EEPROM.write(101, c);
}
}

void printt()
{
   int16_t adc0;  // we read from the ADC, we have a sixteen bit integer as a result
int16_t adc1;
int16_t adc2;
  adc0 = ads.readADC_SingleEnded(0);
  Voltage = (adc0 * 0.1875)/1000;
  Voltage=Voltage*15;
  adc1 = ads.readADC_SingleEnded(1);
  curent = (adc1 * 0.1875)/1000;
   adc2 = ads.readADC_SingleEnded(2);
  Voltagei = (adc2 * 0.1875)/1000;
  
 
  val = analogRead(tempPin);
float mv = ( val/1024.0)*1000; 
float cel = mv/10;
  

tft.setFont(BigFont);
 tft.setColor(0,255 , 255);
if (Voltage <10)
{tft.print(String(Voltage,4),18,5);tft.print(String(0),5,5);}
 else
   tft.print(String(Voltage,4),5,5);
tft.setColor(255,255 , 255);
  tft.print(String(curent,4),18,30);
 tft.setColor(255,0 , 0);
 tft.print(String(cel),5,57);
 tft.setColor(255,255 , 0);
 tft.drawRect(0,79,219,100);
  tft.setColor(0,0 , 0);
 tft.fillRect(1,80,120,99);
 tft.setColor(255,255 , 0);
   tft.printNumI(h,5,81);
  tft.setFont(BigFont);
  tft.setColor(0,0 , 0);
 tft.fillRect(1,106,120,120);
  tft.setColor(255,0 ,255);
 tft.drawRect(0,103,219,122);
  tft.printNumI(c,5,105);

tft.setColor(0,255 ,0);
// tft.printNumI(Voltagei,5,132);
 if (Voltagei <10)
{tft.print(String(Voltagei,4),18,132);tft.print(String(0),5,132);}
 else
   tft.print(String(Voltagei,4),5,132);
  
// termostat
   if (cel > 35)
  {digitalWrite(vent, HIGH); }
  if (cel < 30)
  digitalWrite(vent, LOW);
  //delay(10);
}

