#ifndef HELICOPTER_H
#define HELICOPTER_H
#include "AirVehicle.h"
class Helicopter :public AirVehicle
{
private:
	float rotor_diameter;
	float max_altitude;


public:
	Helicopter();
	Helicopter(int, string, int, string, string,float,float);
	void setRotorDiameter(float);
	void setMaxAltitude(float);
	float getRotorDiameter() const { return rotor_diameter; }
	float getMaxAltitude() const { return max_altitude; }
	void display() const override;

};
#endif

