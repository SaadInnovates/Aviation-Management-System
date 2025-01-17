#include<iostream>
using namespace std;
#include "UtilityVehicle.h"

UtilityVehicle::UtilityVehicle(int v_id, string v_purpose, string v_status, AirVehicle* a_vehicle):vehicle_id(v_id),purpose(v_purpose),status(v_status),assigned_vehicle(a_vehicle)
{

}
void UtilityVehicle::setVehicleID(int v_id)
{
	vehicle_id = v_id;
}
void UtilityVehicle::setPurpose(string p)
{
	purpose = p;
}
void UtilityVehicle::setStatus(string st)
{
	status = st;
}
void UtilityVehicle::setAssignedVehicle(AirVehicle* a_vehicle)
{
	assigned_vehicle = a_vehicle;
}
void UtilityVehicle::display() const
{
	cout << "Vehicle ID : " << vehicle_id << endl;
	cout << "Purpose : " << purpose << endl;
	cout << "Status : " << status << endl;
	if (assigned_vehicle != nullptr)
	{
		cout << "----------------------- Assigned Air-Vehicle -----------------------\n";
		assigned_vehicle->display();

	}
}
void UtilityVehicle::assignToAirVehicle(AirVehicle* v)
{
	assigned_vehicle = v;
}
void UtilityVehicle::update_status(string new_status)
{
	status = new_status;
}