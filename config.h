#define P1 3
#define P2 2
#define P3 5
#define P4 4

#define MAX_Dose_Level 13
#define MIN_Dose_Level 1

LiquidCrystal_I2C lcd(0x27, 20, 4); // just some gay shit
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = { 10,11,12,13 };//connect to the row pinouts of the keypad - four in a row
byte colPins[COLS] = { 6,7,8,9 }; //connect to the column pinouts of the keypad - four in a row
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String msg = "";

// Dosing Settings, tsp/gal
int currentDose = 1;
int gallonsToDose = 0;

//Pumps
bool P1state = true;
bool P2state = true;
bool P3state = true;
bool P4state = true;

//PH Sensor
float calibration = 21.23; //change this value to calibrate
const int analogInPin = A0;
int sensorValue = 0;
unsigned long int avgValue;
float b;
int buf[10], temp;

// variables used on more than 1 function need to be declared here
unsigned long start, finished, elapsed;
boolean r = false;

// Variables for button debounce time
long lastButtonPressTime = 0; // the last time the button was pressed
long debounceDelay = 50; // the debounce time; keep this as low as possible
char x;

//ratios
float tsp_per_sec = 3.4;
float gal_per_sec = 0.05;
float ml_per_tsp = 5.0;

// Pump rates (seconds per milliliter)
float P2Rate = 0.81;
float P1Rate = 0.68;
float P4Rate = 0.79;
float P3Rate = 0.81;

// Variable to store mL of nutirent per Dosed Gallon
float mLperGal[3];

bool AutoDose = false;
int DoseDelay = 1000;