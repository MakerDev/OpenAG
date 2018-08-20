#include "LiquidCrystal_I2C.h"
#include "DhtControl.h"
#include "LiquidLevelSensor.h"

#define HITBED 8
#define COOLER 9
#define PUMP 10
#define DHT 43

const int fans[3] = {32, 45, 47};
const int liquidPin = A13;

//Legacy
//1550 > 이면 채우기 시작
//1400 이하가 되면 스톱
const int startPump =1800;
const int stopPump = 1700;

const int tempCoolerStart = 20;  //28
const int tempCoolerStop = 15;   //15

const int tempHitStop = 25;
const int tempHitStart = 10;

bool isBedOn = false;
String liquidState = "LOW";
int liquidLevel;

DhtControl dht(DHT);
LiquidCrystal_I2C lcd(0x3F, 20, 4); 
LiquidLevelSensor liquidSensor(liquidPin);

void setup()
{
  lcd.begin();
  pinMode(HITBED, OUTPUT);
  pinMode(COOLER, OUTPUT);
  pinMode(PUMP, OUTPUT);

  for(int i=0 ; i<3 ; i++)
  {
    pinMode(fans[i], OUTPUT);
  }

  digitalWrite(HITBED, LOW);
  digitalWrite(PUMP, LOW);
  digitalWrite(COOLER, LOW);
  
  digitalWrite(fans[0], HIGH); //항시 켜둠
}

void loop()
{
  float temp = dht.GetTemperature();

  liquidLevel = liquidSensor.GetLiquidLevel(); 

  if (temp < tempHitStart)
  {
    digitalWrite(HITBED, HIGH);
    isBedOn = true;
  }
  else if (temp > tempHitStop)
  {
    digitalWrite(HITBED, LOW);
    isBedOn = false;
  }

  if (temp >= tempCoolerStart)
  {
    digitalWrite(fans[1], HIGH);
    digitalWrite(fans[2], HIGH);
  }
  else if (temp <= tempCoolerStop)
  {
    digitalWrite(fans[1], LOW);
    digitalWrite(fans[2], LOW);
  }

  if (liquidLevel < stopPump)
  {
    liquidState = "HIGH";
    digitalWrite(PUMP, LOW);
  }
  else if (liquidLevel > startPump)
  {
    liquidState = "LOW";
    digitalWrite(PUMP, HIGH);
  }
  else
  {
    liquidState = "GOOD";
  }

  DisplayValue();
  delay(2000);
}

void DisplayValue()
{
  int errCode = dht.ReadData();
  lcd.clear();
  if (errCode==0)             
  {
    lcd.backlight();
    lcd.display();
    lcd.print("Temp :  ");
    lcd.print(dht.GetTemperature());
    lcd.setCursor(0, 1);
    lcd.print("Humi :  ");
    lcd.print(dht.GetHumidity());
    lcd.setCursor(0, 2);
    lcd.print("Liquid Level :  ");
    //lcd.print(liquidState);
    lcd.print(liquidLevel);
    lcd.setCursor(0, 3);
    lcd.print("Is Bed On :  ");
    lcd.print(isBedOn);
    //lcd.print(dht.GetHumidity());
  }
  else                            
  {
    lcd.backlight();
    lcd.display();
    lcd.print("Error No : ");
    lcd.print(errCode);
  }
}


