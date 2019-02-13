//An Arduino based Weather station built around an Arduino Uno, XD-05 Data logging shield , tipping bucket rain gauge and 3D printed anemometer
//          by
//    Chris van Gerve
//    v.0.1.0
//     8 Feb.2019

//Libraries
#include <Wire.h>                   //I2C for sensors
#include <DS1307.h>                 //RT clock
#include <SPI.h>                    // SPI for datalogger shield
#include <SD.h>                     // Library for SD card
#include <Nokia_5110.h>             // Nokia 5110 LCD library
#include <OneWire.h>                // One wire library for DBS 18 Temp sensor
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5
#define RST 4
#define CE 6
#define DC 7
#define DIN 8
#define CLK 9
Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);
DS1307 clock;                   //define a object of DS1307 class
const int chipSelect = 10;      // Chipselect for the datalogging shield
//Global variables
int lasthour = 0;
int minutes = 0;
int seconds = 0;
int midnight = 00;
float dailyrainin = 0;          //Accumulated rain over the day - so far - in mm
volatile float rain;
float temp = 0;
float hightemp = 0;
float  lowtemp = 50;
//volatile float wind;
//volatile float windSpeed;
// float lowwind;
// float highwind;
//Hardware pins
//Digital pins
const byte RAIN = 2;                 //Rain meter
//  const byte wSpeed = 3;                 //Anemometer
//Initiate required instances
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{
  dailyrainin = 0.00; 
  rain = 0;   //Reset rainguage count
  Serial.begin(9600);
  sensors.begin();
  clock.begin();
  lcd.setContrast(40);
  lcd.clear();
  lcd.println("SD card initializing...");
  delay(50);
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    lcd.clear();
    lcd.println("Card failed");
    // don't do anything more:
    while (1);
  }
  lcd.println("Card OK");
  delay(2000);

  //  pinMode(wSpeed, INPUT_PULLUP);       //Input from anemometer
  pinMode(RAIN, INPUT_PULLUP);         //Input from rain gauge


  //Initate interrupts
  interrupts();
  //Attach wind and rain interrupts to the respective IRQ functions
  attachInterrupt(0, rainIRQ, FALLING);
  //  attachInterrupt(1, wSpeedIRQ, FALLING);


}

void loop()
{
  clock.getTime();
  minutes = clock.minute, DEC;
  seconds = clock.second, DEC;
  lasthour = clock.hour, DEC;

  sensors.requestTemperatures();
  sensors.getTempCByIndex(0);

  tempCalc();
  calcWeather ();
  lcd.clear();
  lcd.setContrast(40);
  printTime();
  lcd.print(temp);
  lcd.println("C");
  lcd.print (hightemp);
  lcd.print("");
  lcd.print("-");
  lcd.print (lowtemp);
  lcd.println("");
  lcd.print("Reenval");
  lcd.print("=");
  lcd.print (dailyrainin);
  lcd.println ("mm");
  //lcd.println(windSpeed);
  delay(1000);

  if (lasthour == midnight && minutes == 1 && seconds <= 5)
  {
    resetDay();                          //Reset all the variables that need daily resetting
  }
  delay(3000);
}
