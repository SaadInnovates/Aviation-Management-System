#ifndef AIRVEHICLE_H
#define AIRVEHICLE_H
#include<string>
#include<mysql.h>
#include "Flight.h"
using namespace std;

class AirVehicle
{
protected:
	int vehicle_id;
	string model;
	int capacity;
	string last_maintenance_date;
	string status;
	Flight *flight=nullptr;


public:
	AirVehicle();
	AirVehicle(int,string,int,string,string);
	void setId(int);
	void setModel(string);
	void setCap(int);
	void setDate(string);
	void setStatus(string);
	int getID() const { return vehicle_id; }
	string getModel() const { return model; }
	string getDate() const { return last_maintenance_date; }
	int getCap() const { return capacity; }
	string getStatus() const { return status; }
	void setFlight(MYSQL* ,int);

	void updateStatus(string);
	void scheduleMaintenance(string, MYSQL*);
	virtual void display() const = 0;
	virtual ~AirVehicle();
	bool isAssignedOrNot();



	

};
#endif

