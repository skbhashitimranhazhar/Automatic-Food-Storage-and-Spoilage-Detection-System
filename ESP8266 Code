// ESP 8266 (Node MCU Code)

#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#include <DTH.h>
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <servo.h>
#define GOOD_SERVO_PIN 4
#define BAD_SERVO_PIN 3
Servo goodServo;
Servo badServo;

#define IR_ENTRY_PIN 6
#define IR_EXIT_PIN 5

#define MQ_SENSOR_PIN A0

int goodCount = 0;

void setup() 
{
	lcd.begin(16, 2);
	Serial.begin(9600);
	dht.begin();
	pinMode(IR_ENTRY_PIN, INPUT);
	pinMode(IR_EXIT_PIN, INPUT);
	goodServo.attach(GOOD_SERVO_PIN);
	badServo.attach(BAD_SERVO_PIN);
	goodServo.write(0);
	badServo.write(90);
	displayGoodCount();
}
void loop()
{
	if (digitalRead(IR_ENTRY_PIN) == LOW) 
	{
		delay(5000);
		int gasLevel = analogRead(MQ_SENSOR_PIN);
		int humidity = dht.readHumidity();
		if (isnan(humidity)) 
		{
			Serial.println("Failed to read humidity");
			return; 
		}
		if (gasLevel > 500 || humidity > 50)
		{
			lcd.clear();
			lcd.print("Food is Bad");
			operateBadServo();
			delay(5000);
		}
		else
		{
			lcd.clear();
			lcd.print("Food is Good");
			operateGoodServo();
			goodCount++;
			delay(5000);
		}
		displayGoodCount();
	}
	if (digitalRead(IR_EXIT_PIN) == LOW)
	{
		if (goodCount > 0)
		{
			goodCount--;
			displayGoodCount();
			delay(1000);
		}
	}
}

void operateGoodServo()
{
	goodServo.write(90);
	delay(1000);
	goodServo.write(0);
}

void operateBadServo() 
{
	badServo.write(0);
	delay(1000);
	badServo.write(90);
}

void displayGoodCount()
{
	lcd.clear();
	lcd.print("Good Count: ");
	lcd.print(goodCount);
}
