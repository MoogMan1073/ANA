#include "Arduino.h"
#include "Keypad.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "config.h"
#include "setup.h"

void setup()
{

	lcd.init();
	lcd.backlight();
	Serial.begin(9600);

	lcd.print("     Automated");
	lcd.setCursor(0, 1);
	lcd.print("      Nutrient");
	lcd.setCursor(0, 2);
	lcd.print("     Assistant");
	lcd.setCursor(0, 3);
	lcd.print("       (ANA)");

	// Setup Pumps
	pinMode(P1, OUTPUT);
	pinMode(P2, OUTPUT);
	pinMode(P3, OUTPUT);
	pinMode(P4, OUTPUT);

	digitalWrite(P1, P1state);
	digitalWrite(P2, P2state);
	digitalWrite(P3, P1state);
	digitalWrite(P4, P1state);

	delay(1000);

	setMainMenu();
}

void loop()
{

	char key = keypad.getKey();
	if (key != NO_KEY) {
		//Serial.println(key);
		msg += key;

		if (key == '#')
		{
			lcd.clear();
			msg.remove(msg.length() - 1, 1);
			gayB(msg);
			Serial.println(msg);
			msg = "";
		}

		if (key == 'A') 
		{
			dosingSetupScreen();
		}

		if (key == 'B') 
		{
			togglePumps();
		}

		if (key == 'C') 
		{
			readPH();
			key = NO_KEY;
			while (key != 'D') 
			{
				key = keypad.getKey();
				readPH();
			}
			setMainMenu();
		}

		if (key == 'D')
		{
			dosingScreen();
		}
	}
}



void readPH()
{

	for (int i = 0; i < 10; i++) {
		buf[i] = analogRead(analogInPin);
		delay(30);
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (buf[i] > buf[j])
			{
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}

	avgValue = 0;
	for (int i = 2; i < 8; i++)
		avgValue += buf[i];
	float pHVol = (float)avgValue * 5.0 / 1024 / 6;
	float phValue = -5.70 * pHVol + calibration;
	lcd.clear();
	lcd.setCursor(0, 1);
	lcd.print("sensor = ");
	lcd.print(phValue, 2);
	//Serial.println(phValue, 2);

	delay(10);
}

