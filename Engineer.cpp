#include<iostream>
#include<mysql.h>
using namespace std;
#include "Engineer.h"
Engineer::Engineer(int e_id, string ename, string espec, AirVehicle *evehicle):engineer_id(e_id),name(ename),specialization(espec),vehicle(evehicle)
{

}
void Engineer::setID(int id)
{
	engineer_id = id;
}
void Engineer::setName(string n)
{
	name = n;
}
void Engineer::setSpecialization(string sp)
{
	specialization = sp;
}
void Engineer::setAirVehicle(AirVehicle* v)
{
	vehicle = v;
}
void Engineer::display() const
{
	cout << "Engineer ID : " << engineer_id << endl;
	cout << "Name : " << name << endl;
	cout << "Specialization : " << specialization << endl;
    if (vehicle != nullptr)
    {
        cout << "--------------------------> ASSIGNED AIR VEHICLE <--------------------------" << endl;
        vehicle->display();
    }

}

