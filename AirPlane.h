#ifndef AIRPLANE_H
#define AIRPLANE_H
#include "AirVehicle.h"
#include<string>
using namespace std;

class AirPlane :public AirVehicle
{
private:
	float wingspan;
	bool restricted;
	float flight_range;
	string type;


public:
	AirPlane();
	AirPlane(int, string, int, string, string, float, float, bool, string);
	void setWingspan(float);
	void setRestrictStatus(bool);
	void setFlightRange(float);
	void setType(string type);
	float getWingspan() const { return wingspan; }
	bool getRestrict() const { return restricted; }
	float getFlightRange() const { return flight_range; }
	string getType() const { return type; }
	void display() const override;
};
#endif

