#ifndef HANGAR_H
#define HANGAR_H
#include<string>
#include<mysql.h>
using namespace std;
#include "AirVehicle.h"

class Hangar
{
private:
	int hangar_ID;
	string loc;
	int capacity;
	int currentCount;
	int occupied_spaces;
	AirVehicle* ptr[10];


public:
	Hangar(int, string, int, int);
	void setId(int);
	void setLoc(string);
	void setCapacity(int);
	void setOccupiedSpaces(int);
	void addAirplane(MYSQL* , AirVehicle*);
	void display() const;
	int getId() const;
	string getLoc() const;
	int getCap() const;
	int getSpaces() const;
	void parkVehicle(MYSQL* , AirVehicle*);
	void freeSpace(MYSQL* ,int);


};
#endif

