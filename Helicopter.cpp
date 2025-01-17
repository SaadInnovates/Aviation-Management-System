#include<iostream>
using namespace std;
#include "Helicopter.h"
Helicopter::Helicopter():AirVehicle(),rotor_diameter(0.0),max_altitude(0.0)
{

}
Helicopter::Helicopter(int v_id, string v_model, int v_cap, string v_date, string v_status,float rotorDiameter,float maxAlt):AirVehicle(v_id,v_model,v_cap,v_date,v_status),rotor_diameter(rotorDiameter),max_altitude(maxAlt)
{

}
void Helicopter::setRotorDiameter(float rDiameter)
{
	rotor_diameter = rDiameter;
}
void Helicopter::setMaxAltitude(float rMaxAlt)
{
	max_altitude = rMaxAlt;
}
void Helicopter::display() const
{
	cout << "Helicopter ID : " << vehicle_id << endl;
	cout << "Helicopter Model : " << model << endl;
	cout << "Last Maintenance Date : " << last_maintenance_date << endl;
	cout << "Status : " << status << endl;
	cout << "Rotor Diameter : " << rotor_diameter << endl;
	cout << "Max Altitude : " << max_altitude << " meters " << endl;
}
