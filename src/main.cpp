#include <Arduino.h>
#define IR_USE_AVR_TIMER1
#include <IRremote.hpp>
//Nastaveni jednotlivych pinu
#define red 3 
#define green 5
#define blue 6
#define gnd 2
#define IR_RECEIVE_PIN 12
unsigned long CHmin = 3125149440; //tlacitko pro Red -> Ch-
unsigned long CH = 3108437760; //tlacitko pro Green -> Ch
unsigned long CHplus = 3091726080; //tlacitko pro Blue -> Ch+
//pomocne integry
int count = 0;
int dec = 0;
//list jednotlivych cisel z ovladace
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
  //nastaveni definovanych pinu na output
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(gnd, LOW); //gnd nastaveny na low, a pouzity jako ground pro ledku
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); //aktivace Ir prijimace
  Serial.begin(9600); //zapnuti serialu
}

void loop() {
  if (IrReceiver.decode()) { //pokud Ir prijimac neco detekuje, tak se stane nasledujici
      unsigned long kod = IrReceiver.decodedIRData.decodedRawData; //do promene kod se ulozi data z Ir prijimace
      Serial.println(kod); //kod se vypise do serialu
      if (kod == CHmin) //pokud se kod prijateho tlacitka rovna Ch-, tak se stane nasledujici 
        {
          if (count < 4) //zkontroluje se jestli nebylo zadano vice jak 4 ciferne cislo, pouzito jako dalsi kontrola, aby zadana hodnota neprekrocila limit int
          {
            if (dec < 256) //zkontroluje se jestli neni dec vetsi nez 255 
            {
              analogWrite(red, dec); //pokud je zadane cislo vporadku, tak se red nastavi na hodnotu v dec
            }else{
            Serial.println("Prilis velke cislo"); //pokud je cislo prilis velke tak to do serialu vypise
            }
          } else{
            Serial.println("Prilis velke cislo");
          }
          dec = 0; //dec a count nastavi na nulu
          count = 0;
        } else if (kod == CH) //to stejne co pro red ledku jen pro green
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
        } else if (kod == CHplus) ////to stejne co pro red ledku jen pro blue
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
              if (kod == cislo[i]) //zkontroluje se zda je hodnota z Ir prijimace rovna nejakemu cislu z listu
              {
                dec = dec * 10 + i; //do hodnoty dec uklada zadane hodnoty
                count++; //prida cifru
                }
              }
            }
      delay(50); //delay aby se nespamovalo s nekterymi ovladaci
      IrReceiver.resume(); //Ir prijimac zacne znova prijimat
  }
}
