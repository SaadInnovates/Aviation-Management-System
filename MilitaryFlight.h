#ifndef MILFLIGHT_H
#define MILFLIGHT_H
#include "Flight.h"
#include<mysql.h>

class MilitaryFlight : public Flight
{
private:
	string missionType;
	char restrictedStatus;



public:
	MilitaryFlight();
	MilitaryFlight(int, string, string, string, string, int, string, string, char,Pilot *);
	void setMission(string);
	void setRestriction(char);
	string getMission() const;
	char getRestrictStatus() const;
	void display() const override;
	void scheduleMission(MYSQL*);
};
#endif

