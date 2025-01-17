#ifndef CARGO_H
#define CARGO_H

#include<string>
using namespace std;
#include"AirVehicle.h"

class Cargo
{
private:
	int cargo_ID;
	float weight;
	string type, destination;
	AirVehicle *transport;

public:
	Cargo(int, float, string, string, AirVehicle*);
	void setId(int);
	void setWeight(float);
	void setTypeAndDestination(string, string);
	void setTransport(AirVehicle*);
	int getId() const { return cargo_ID; }
	float getWeight() const { return weight; }
	string getType() const { return type; }
	string getDest() const { return destination; }
	AirVehicle *getTransport() const { return transport; }
	void displayCargo() const;
	void loadCargo(AirVehicle*);
	void trackCargoStatus();



};
#endif
