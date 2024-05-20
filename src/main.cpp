#include <Arduino.h>
#define IR_USE_AVR_TIMER1
#include <IRremote.hpp>
#define red 3
#define green 5
#define blue 6
#define gnd 2
#define pot A0
#define IR_RECEIVE_PIN 12
unsigned long CHmin = 3125149440;
unsigned long CH = 3108437760;
unsigned long CHplus = 3091726080;
int count = 0;
int zaplo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int dec = 0;
unsigned long cislo[] =
    {
        3910598400,                               // 0
        4077715200,                               // 1
        3877175040,                               // 2
        2707357440,                               // 3
        4144561920,                               // 4
        3810328320,                               // 5
        2774204160,                               // 6
        3175284480,                               // 7
        2907897600,                               // 8
        3041591040,                               // 9
}; 
void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(gnd, LOW);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.begin(9600);
}

void loop() {
  if (IrReceiver.decode()) {
      unsigned long kod = IrReceiver.decodedIRData.decodedRawData;
      Serial.println(kod);
      if (kod == CHmin) //red
        {
          if (count < 4)
          {
            if (dec < 256)
            {
              analogWrite(red, dec);
            }else{
            Serial.println("Prilis velke cislo");
            }
          } else{
            Serial.println("Prilis velke cislo");
          }
          dec = 0;
          count = 0;
        } else if (kod == CH) //green
        {
          if (count < 4)
          {
            if (dec < 256)
            {
              analogWrite(green, dec);
            }else{
            Serial.println("Prilis velke cislo");
            }
          } else{
            Serial.println("Prilis velke cislo");
          }
          dec = 0;
          count = 0;
        } else if (kod == CHplus) //blue
        {
          if (count < 4)
          {
            if (dec < 256)
            {
              analogWrite(blue, dec);
            }else{
            Serial.println("Prilis velke cislo");
            }
          } else{
            Serial.println("Prilis velke cislo");
          }
          dec = 0;
          count = 0;
        }
        else{
          for (int i = 0; i < 10; i++)
            {
              if (kod == cislo[i])
              {
                dec = dec * 10 + i;
                count++;
                }
              }
            }
      delay(50);
      IrReceiver.resume();
  }
}