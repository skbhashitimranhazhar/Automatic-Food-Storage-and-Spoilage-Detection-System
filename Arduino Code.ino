Detection and Sorting Code and Storage Alert -

#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
int count=0;
int flag=0;
int GoodCount=0;
int BadCount=0;
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <Servo.h>
Servo GoodServo; 
Servo BadServo;

void setup() 
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  dht.begin();
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  GoodServo.attach(4);
  BadServo.attach(3);
}

void loop() 
{
  int ir1=digitalRead(6);
  if(ir1==0)
  {
    flag=1;
    delay(5000);
    if(flag==1)
    {
      test();
      return;
    }
    flag=0;
  }
  else
  {
    flag=0;
  }
  display();
  Storage();
}

void display()
{
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int a=analogRead(A0);
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.print(h);
  lcd.print(", T:");
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("G:");
  lcd.print(a);
  lcd.setCursor(14,1);
  lcd.print(count);
  return;
}

void test()
{
  {
    int a=analogRead(A0);
    int h=dht.readHumidity();
    if (a>500 || h>50)
    {
      BadCount=BadCount+1;
      Serial.println("Bad");
      ActBadServo();
      BadLCD();
      flag=0;
      return;
    }
    else if(a<500 && h<50)
    {
      count=count+1;
      Serial.println("Good");
      ActGoodServo();
      GoodLCD();
      return;
      flag=0;
    }
    return;
  }
}

void ActGoodServo()
{
  GoodServo.write(90);
  delay(1000);
  GoodServo.write(0);
}

void ActBadServo()
{
  BadServo.write(0);
  delay(1000);
  BadServo.write(90);
}

void GoodLCD()
{
  lcd.clear();
  lcd.print("Good Food");
  delay(2500);
}

void BadLCD()
{
  lcd.clear();
  lcd.print("Spoiled Food");
  delay(2500);
}

void Storage()
{
  int gaslvl=analogRead(A1);
  if (gaslvl>500)
  {
    lcd.clear();
    lcd.print("Spoilage Alert");
    delay(2500);
  }
  else
  {

  }
}
