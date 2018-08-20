#ifndef _LIQUIDSENSOR_
#define _LIQUIDSENSOR_

class LiquidLevelSensor
{
public:
	LiquidLevelSensor(int pin);
	int GetLiquidLevel();
	int GetCurrentCm();

private:
	int mPin;
	const int SeriesResistor = 560;
};

#endif