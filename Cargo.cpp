#include<iostream>
using namespace std;
#include "Cargo.h"

Cargo::Cargo(int c_id, float c_weight, string c_type, string c_dest, AirVehicle *c_transport):cargo_ID(c_id),weight(c_weight),type(c_type),destination(c_dest),transport(c_transport)
{

}
void Cargo::setId(int c_id)
{
	cargo_ID = c_id;
}
void Cargo::setWeight(float w)
{
	weight = w;
}
void Cargo::setTypeAndDestination(string type, string dest)
{
	this->type = type;
	this->destination = dest;
}
void Cargo::setTransport(AirVehicle *trans)
{
	this->transport = trans;
}

void Cargo::displayCargo() const
{
	cout << "Cargo ID : " << cargo_ID << endl;
	cout << "Weight : " << weight << " kg " << endl;
	cout << "Destination of Cargo : " << destination << endl;
	cout << "Cargo Type : " << type << endl;
	
	cout << "<<<<<<<<<<<< TRANSPORT USED >>>>>>>>>>>>" << endl;
	transport->display();
}
void Cargo::loadCargo(AirVehicle* ptr)
{
	transport = ptr;
}
void Cargo::trackCargoStatus()
{
	cout << "Cargo is currently in the proceeding stage.\n";
	cout << "---------------DETAILS---------------\n";
	displayCargo();
}

