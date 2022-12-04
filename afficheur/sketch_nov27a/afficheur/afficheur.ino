
#include <LiquidCrystal.h>
#include "LiquidCrystal_I2C.h"
#include <Wire.h>


#define PIN_MQ2 A1
int value;
 int etat = 1;
int k = 0;
char arr[6];
char data,nom;
String tab;
int buzz = 13; // buzzer
LiquidCrystal_I2C lcd(0x27, 16, 2);
int test =0;
void setup()
{
  lcd.init();
  lcd.backlight();
pinMode(buzz, OUTPUT);
  Serial.begin(9600);
   pinMode(PIN_MQ2, INPUT);
}

void loop()
{if(test==0)
    { value = analogRead(PIN_MQ2);
 

   if (value > 30) { test=1;Serial.write("1");
   }
    }
if(test==1){
   if (etat == 1) //etat intial
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*AHLA_BIK*");
    delay(2000);
  }
  if (Serial.available()) //code introuvable
  {
    etat = 1;
    k = 0;
    data = Serial.read();
    lcd.clear();
    lcd.setCursor(0, 0);
    if (data == '0')
    {
      lcd.print("T7AR9ET");
      tone(buzz, 261);
      delay(4000);
      noTone(buzz);
      lcd.clear();
    }test=1;
    
  }}
}
