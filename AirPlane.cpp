#include<iostream>
using namespace std;
#include "AirPlane.h"

AirPlane::AirPlane():AirVehicle(),flight_range(0.0),wingspan(0.0),restricted(true),type("")
{

}
AirPlane::AirPlane(int v_id, string v_model, int v_cap, string v_date, string v_status, float a_wingspan, float a_flightRange, bool a_restricted, string a_type):AirVehicle(v_id, v_model, v_cap, v_date, v_status),wingspan(a_wingspan),type(a_type),restricted(a_restricted),flight_range(a_flightRange)
{

}
void AirPlane::setWingspan(float wing)
{
	wingspan = wing;
}
void AirPlane::setRestrictStatus(bool rSt)
{
	restricted = rSt;
}
void AirPlane::setFlightRange(float fRange)
{
	flight_range = fRange;
}
void AirPlane::setType(string type)
{
	this->type = type;
}
void AirPlane::display() const
{
	cout << "Airplane ID : " << vehicle_id << endl;
	cout << "Airplane Model : " << model << endl;
	cout << "Last Maintenance Date : " << last_maintenance_date << endl;
	cout << "Status : " << status << endl;
	cout << "Flight Range : " << flight_range << " meters" << endl;
	cout << "Wingspan : " << wingspan << endl;
	cout << "Type : " << type << endl;
	if (restricted == true)
	{
		cout << "Restricted Status : TRUE \n";
	}
	else
	{
		cout << "Restricted Status : FALSE \n";

	}

}