#include <LiquidCrystal.h>

#define rs 13
#define en 12
#define d4 4
#define d5 5
#define d6 6
#define d7 7
#define wavePin A0
#define lampPin 2

const uint16_t UPDATING_DELAY = 5000;
const uint8_t MAX_VOLTAGE = 5;
const uint8_t MIN_VOLTAGE = 0;

long updatedTime;
uint16_t tempMaxV;
uint16_t tempMinV;
uint16_t maxV;
uint16_t minV;
double currV;

LiquidCrystal Lcd(rs, en, d4, d5, d6, d7);

void settingValues();
void printValuesOnLcd();
void updatingValues();
void calculateWaveVoltages();
void generateImpulse();

void setup() 
{
  updatedTime = millis();
  pinMode(wavePin, INPUT);
  tempMaxV = MIN_VOLTAGE;
  tempMinV = MAX_VOLTAGE;
  maxV = 0;
  minV = 0;
  Lcd.begin(20, 4);
}

void loop() 
{
  if(millis() - updatedTime >= UPDATING_DELAY)
  {
    settingValues();
    printValuesOnLcd();
  }

  updatingValues();
  generateImpulse();
}

    /*Prototyoe of private functions*/
  
void settingValues()
{
  updatedTime = millis();
  maxV = tempMaxV;
  minV = tempMinV;
  tempMaxV = MIN_VOLTAGE;
  tempMinV = MAX_VOLTAGE;
}

void printValuesOnLcd()
{
  Lcd.setCursor(0, 0);
  Lcd.print("MAX:");
  Lcd.setCursor(5, 0);
  Lcd.print((maxV / 1023.0) * 5.0);
  Lcd.setCursor(0, 1);
  Lcd.print("MIN:");
  Lcd.setCursor(5, 1);
  Lcd.print((minV / 1023.0) * 5.0);
//  Lcd.setCursor(0, 1);
//  Lcd.print("Hz: ");
//  double hz = 1.0 / (2.0 * (logicalHighTime / 1000.0));
//  Lcd.setCursor(5, 1);
//  Lcd.print((int)hz);
}

void updatingValues()
{
  calculateWaveVoltages();
  generateImpulse();
}

void calculateWaveVoltages()
{
  currV = analogRead(wavePin);
  
  if(currV > tempMaxV)
  {
    tempMaxV = currV;
  }
  
  if(currV < tempMinV)
  {
    tempMinV = currV;
  }
}

void generateImpulse()
{
  if(currV >= (maxV + minV) / 2)
  {
    digitalWrite(lampPin, HIGH);
  }

  if(currV < (maxV + minV) / 2)
  {
    digitalWrite(lampPin, LOW);
  }
}
