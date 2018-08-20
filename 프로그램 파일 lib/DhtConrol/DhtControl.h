#ifndef _DhtControl_
#define _DhtControl_

#include <DHT11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class DhtControl
{
public:
	DhtControl(int signalPin);
	int ReadData(); //Read 성공 여부 반환
	float GetHumidity() const;
	float GetTemperature() const;

private:
	DHT11* mDht;
	LiquidCrystal_I2C* mLcd;

	int mSignalPin = -1;
	float mHumidity;
	float mTemp;
};

#endif