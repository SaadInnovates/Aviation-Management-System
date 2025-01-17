#ifndef ENG_H
#define ENG_H

#include "AirVehicle.h"
#include<string>
using namespace std;

class Engineer
{
private:
	int engineer_id;
	string name;
	string specialization;
	AirVehicle *vehicle;

public:
	Engineer(int, string, string, AirVehicle*);
	void setID(int);
	void setName(string);
	void setSpecialization(string);
	void setAirVehicle(AirVehicle*);
	int getId() const { return engineer_id; }
	string getName() const { return name; }
	string getSpecialization() const { return specialization; }
	AirVehicle* getVehicle() const { return vehicle; }
	void display() const;

};
#endif
