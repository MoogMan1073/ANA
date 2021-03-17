void setMainMenu()
{
	lcd.clear();
	lcd.print("A - Set Water Dose");
	lcd.setCursor(0, 1);
	lcd.print("B - Toggle Pumps");
	lcd.setCursor(0, 2);
	lcd.print("C - Read PH");
	lcd.setCursor(0, 3);
	lcd.print("D - Begin Dosing");
}

void dose(int pump, float rate, float mLperGal)
{
	int time_on = (int)(rate * mLperGal * 1000);
	digitalWrite(pump, LOW);
	Serial.print("gallons to Dose: ");
	Serial.println(gallonsToDose);
	for (int i = 0; i < gallonsToDose; i++) {
		delay(time_on);
		Serial.print("Pump Cycle: ");
		Serial.print(i);
		Serial.print("Cycle time: ");
		Serial.println(time_on);
	}

	digitalWrite(pump, HIGH);
}

void UpdatemLperGal()
{
	switch (currentDose)
	{
	case 1: // Seedling1
		mLperGal[0] = 1.25;
		mLperGal[1] = 1.25;
		mLperGal[2] = 1.25;
		break;
	case 2: // General Purpose
		mLperGal[0] = 5.0;
		mLperGal[1] = 5.0;
		mLperGal[2] = 5.0;
		break;
	case 3: // Aggessive Vegetative Growth
		mLperGal[0] = 15.0;
		mLperGal[1] = 10.0;
		mLperGal[2] = 5.0;
		break;
	case 4: // Transition to Bloom
		mLperGal[0] = 10.0;
		mLperGal[1] = 10.0;
		mLperGal[2] = 10.0;
		break;
	case 5: // Blooming and Ripening
		mLperGal[0] = 5.0;
		mLperGal[1] = 10.0;
		mLperGal[2] = 15.0;
		break;
	case 6: // Seedling
		mLperGal[0] = 2.5;
		mLperGal[1] = 2.5;
		mLperGal[2] = 2.5;
		break;
	case 7: // Early Growth
		mLperGal[0] = 7.5;
		mLperGal[1] = 10.0;
		mLperGal[2] = 2.5;
		break;
	case 8: // Late Growth
		mLperGal[0] = 10.0;
		mLperGal[1] = 10.0;
		mLperGal[2] = 5.0;
		break;
	case 9: // Transition
		mLperGal[0] = 7.5;
		mLperGal[1] = 7.5;
		mLperGal[2] = 7.5;
		break;
	case 10: // Early Bloom
		mLperGal[0] = 7.5;
		mLperGal[1] = 2.5;
		mLperGal[2] = 10.0;
		break;
	case 11: // Mid Bloom 1
		mLperGal[0] = 7.5;
		mLperGal[1] = 2.5;
		mLperGal[2] = 12.5;
		break;
	case 12: // Late Bloom
		mLperGal[0] = 7.5;
		mLperGal[1] = 0.0;
		mLperGal[2] = 15.0;
		break;
	case 13: // Ripen
		mLperGal[0] = 5.0;
		mLperGal[1] = 0.0;
		mLperGal[2] = 15.0;
		break;
	}
}

void togglePumps()
{
	lcd.clear();
	char key = keypad.getKey();

	lcd.setCursor(0, 0);
	lcd.print("Toggle Pumps");
	lcd.setCursor(0, 1);
	lcd.print("P1: ");
	lcd.setCursor(5, 1);
	lcd.print((int)!P1state);
	lcd.setCursor(7, 1);
	lcd.print("P2: ");
	lcd.setCursor(11, 1);
	lcd.print((int)!P2state);
	lcd.setCursor(0, 2);
	lcd.print("P3: ");
	lcd.setCursor(5, 2);
	lcd.print((int)!P3state);
	lcd.setCursor(7, 2);
	lcd.print("P4: ");
	lcd.setCursor(11, 2);
	lcd.print((int)!P4state);

	while (key != 'D')
	{

		key = keypad.getKey();

		if (key != NO_KEY)
		{

			if (key == '1')
			{
				if (P1state)
				{
					P1state = false;
					digitalWrite(P1, P1state);
					Serial.print(P1state);
					lcd.setCursor(5, 1);
					lcd.print(!P1state);
				}
				else
				{
					P1state = true;
					digitalWrite(P1, P1state);
					Serial.print(P1state);
					lcd.setCursor(5, 1);
					lcd.print(!P1state);
				}
			}

			if (key == '2')
			{
				if (P2state)
				{
					P2state = false;
					digitalWrite(P2, P2state);
					Serial.print(P2state);
					lcd.setCursor(11, 1);
					lcd.print(!P2state);
				}
				else
				{
					P2state = true;
					digitalWrite(P2, P2state);
					Serial.print(P2state);
					lcd.setCursor(11, 1);
					lcd.print(!P2state);
				}
			}

			if (key == '3')
			{
				if (P3state)
				{
					P3state = false;
					digitalWrite(P3, P3state);
					Serial.print(P3state);
					lcd.setCursor(5, 2);
					lcd.print(!P3state);
				}
				else
				{
					P3state = true;
					digitalWrite(P3, P3state);
					Serial.print(P3state);
					lcd.setCursor(5, 2);
					lcd.print(!P3state);
				}

			}

			if (key == '4')
			{
				if (P4state) {
					P4state = false;
					digitalWrite(P4, P4state); Serial.print(P4state);
					lcd.setCursor(11, 2); lcd.print(!P4state);
				}
				else
				{
					P4state = true;
					digitalWrite(P4, P4state);
					Serial.print(P4state);
					lcd.setCursor(11, 2);
					lcd.print(!P4state);
				}
			}

			if (key == 'D')
			{
				break;
			}
		}
	}

	//exit;
	setMainMenu();
	return;
}

void dosingSetupScreen()
{
	lcd.clear();
	char key = keypad.getKey();
	int dose = currentDose;
	int idx = 1;
	String doseName = "Seedling";

	while (key != 'D')
	{
		key = keypad.getKey();
		lcd.setCursor(0, 0);
		lcd.print("Choose dosing level:");
		lcd.setCursor(0, 1);
		lcd.print("1: Inc 2: Dec");
		lcd.setCursor(0, 2);
		lcd.print("Current:");

		if (key != NO_KEY) {

			if (key == '1')
			{
				if (idx < MAX_Dose_Level)
					++idx;
			}

			if (key == '2')
			{
				if (idx > MIN_Dose_Level)
					--idx;
			}

			if (key == '#')
			{
				currentDose = idx;
				//lcd.setCursor(0, 3);
				//lcd.print("Updated");
			}

			switch (idx)
			{

			case 1:
				doseName = "Seedling1";
				break;
			case 2:
				doseName = "Gen Purpose";
				break;
			case 3:
				doseName = "Agg Growth";
				break;
			case 4:
				doseName = "Trans2Bloom";
				break;
			case 5:
				doseName = "Bloom&Ripe";
				break;
			case 6:
				doseName = "Seedling";
				break;
			case 7:
				doseName = "Early Growth";
				break;
			case 8:
				doseName = "Late Growth";
				break;
			case 9:
				doseName = "Transition";
				break;
			case 10:
				doseName = "Early Bloom";
				break;
			case 11:
				doseName = "Mid Bloom";
				break;
			case 12:
				doseName = "Late Bloom";
				break;
			case 13:
				doseName = "Ripen";
				break;
			default:
				break;
			}
			lcd.setCursor(8, 2);
			lcd.print("            ");
			lcd.setCursor(8, 2);
			lcd.print(doseName);
			lcd.setCursor(0, 3);
			lcd.print("Selected ID: ");
			lcd.print(currentDose);

		}

		Serial.println(currentDose);
		delay(10);

	}
	setMainMenu();
	return;
}

void PumpScreen()
{
	lcd.clear();
	char key = keypad.getKey();

	while (key != 'D')
	{
		togglePumps();
		key = keypad.getKey();
	}
	lcd.clear();
	return;
}

void confirmDosingScreen()
{
	UpdatemLperGal();
	lcd.clear();
	char key = keypad.getKey();
	lcd.setCursor(0, 0);
	lcd.print("dose level: ");
	lcd.print(currentDose);
	lcd.setCursor(0, 1);
	lcd.print("# of gallons: ");
	lcd.print(gallonsToDose);
	lcd.setCursor(0, 2);
	lcd.print("A - Continue");
	lcd.setCursor(0, 3);
	lcd.print("D - Exit");

	while (key != 'D')
	{
		key = keypad.getKey();

		if (key == 'A')
		{
			if (mLperGal[0] > 0.001) // dont fuck up your relays if the level is too quick between on/off times
				dose(P2, P2Rate, mLperGal[0]);
			lcd.clear();
			lcd.print("FloraMicro Dosed");
			lcd.setCursor(0, 1);
			lcd.print("Press A to Continue");
			lcd.setCursor(0, 2);
			lcd.print("If Manually Dosing");

			if (!AutoDose)
				key = 'X';
			else
				delay(DoseDelay);

			while (key != 'A')
			{
				key = keypad.getKey();
			}

			if (mLperGal[1] > 0.001)
				dose(P3, P3Rate, mLperGal[1]);
			lcd.clear();
			lcd.print("FloraGro Dosed");
			lcd.setCursor(0, 1);
			lcd.print("Press A to Continue");
			lcd.setCursor(0, 2);
			lcd.print("If Manually Dosing");

			if (!AutoDose)
				key = 'X';
			else
				delay(DoseDelay);

			while (key != 'A')
			{
				key = keypad.getKey();
			}

			if (mLperGal[2] > 0.001)
				dose(P4, P4Rate, mLperGal[2]);
			lcd.clear();

			delay(100);
			lcd.setCursor(0, 0);
			lcd.print("FloraBloom Dosed");
			lcd.setCursor(0, 1);
			lcd.print("Press D to Exit");

			while (key != 'D')
			{
				key = keypad.getKey();
			}
		}
	}

	setMainMenu();
	return;
}

void setAutoDose()
{
	lcd.clear();
	char key = keypad.getKey();
	lcd.setCursor(0, 0);
	lcd.print("Auto or Manually");
	lcd.setCursor(0, 1);
	lcd.print("Switch Nutrients");
	lcd.setCursor(0, 2);
	lcd.print("1 - Auto | 2 - Man");

	int x = 0;
	while (x != 1)
	{
		key = keypad.getKey();
		if (key != NO_KEY)
		{
			if (key == '1')
			{
				AutoDose = true;
				x = 1;
			}

			if (key == '2')
			{
				AutoDose = false;
				x = 1;
			}
		}
	}
	confirmDosingScreen();
	return;

}

void dosingScreen()
{
	lcd.clear();
	char key = keypad.getKey();
	msg = "";

	while (key != 'D')
	{
		key = keypad.getKey();
		lcd.setCursor(0, 0);
		lcd.print("Number of Gallons");
		lcd.setCursor(0, 1);
		lcd.print("to Dose: ");
		lcd.setCursor(9, 1);

		if (key != NO_KEY)
		{
			msg += key;
			lcd.print(msg);
			if (key == '#')
			{
				//lcd.clear();
				msg.remove(msg.length() - 1, 1);
				gallonsToDose = msg.toInt();
				msg = "";

				setAutoDose();

				return;
			}
		}
	}
	setMainMenu();
	return;
}

void doseTime(float x)
{
	float NutriNeeded = x * gal_per_sec * currentDose;
	float dTime = NutriNeeded / tsp_per_sec * 1000;
	Serial.println(dTime);
	P1state = false;
	digitalWrite(P1, P1state);
	delay((int)dTime);
	P1state = true;
	digitalWrite(P1, P1state);
}
