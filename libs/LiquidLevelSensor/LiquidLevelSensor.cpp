#include <Arduino.h>
#include "LiquidLevelSensor.h"

LiquidLevelSensor::LiquidLevelSensor(int pin)
	: mPin(pin)
{
}

int LiquidLevelSensor::GetLiquidLevel()
{
	float value;

	value = analogRead(mPin);

	value = (1023 / value) - 1;

	if (value <= 0)
	{
		return 0;
	}

	value = SeriesResistor / value;

	return value;
}

int LiquidLevelSensor::GetCurrentCm()
{
	float value;

	value = analogRead(mPin);

	value = (1023 / value) - 1;
	value = SeriesResistor / value;
	float cm = (value - 1400) / 21.4;
	cm = 7 - cm;
	cm = (cm < 0) ? 0 : cm;

	return cm;
}
