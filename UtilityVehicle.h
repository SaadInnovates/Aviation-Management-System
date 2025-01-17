#ifndef UTIL_H
#define UTIL_H

#include<string>
using namespace std;
#include "AirVehicle.h"

class UtilityVehicle
{
private:

	int vehicle_id;
	string purpose;
	string status;
	AirVehicle *assigned_vehicle;

public:
	UtilityVehicle(int, string, string, AirVehicle*);
	void setVehicleID(int);
	void setPurpose(string);
	void setStatus(string);
	void setAssignedVehicle(AirVehicle*);
	int getVehicleId() const { return vehicle_id; }
	string getStatus() const { return status; }
	string getPurpose() const { return purpose; }
	AirVehicle* getAirVehicle() const { return assigned_vehicle; }
	int getAirVehicleId() const { return assigned_vehicle->getID(); }
	void display() const;
	void assignToAirVehicle(AirVehicle*);
	void update_status(string);
};
#endif

