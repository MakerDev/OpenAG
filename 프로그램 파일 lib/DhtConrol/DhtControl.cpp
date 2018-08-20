#include <Arduino.h>
#include <Wire.h>
#include <DHT11.h>
#include <LiquidCrystal_I2C.h>
#include "DhtControl.h"

DhtControl::DhtControl(int signalPin)
{
	mSignalPin = signalPin;
	mDht = new DHT11(mSignalPin);
}

int DhtControl::ReadData()
{
	int errCode;

	//습도, 온도 읽어오기
	errCode = mDht->read(mHumidity, mTemp);

	return errCode;

}

float DhtControl::GetHumidity() const
{
	return mHumidity;
}

float DhtControl::GetTemperature() const
{
	return mTemp;
}