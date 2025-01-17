#include<iostream>
using namespace std;
#include "Flight.h"

Flight::Flight():flightID(0),source(""),destination(""),arrivalTime(""),departureTime(""),bookedSeats(0),status(""),pilot(nullptr)
{

}
Flight::Flight(int f_id, string src, string dest, string arriveTime, string departTime, int f_bookedSeats, string st,Pilot *f_pilot) :flightID(f_id), source(src), destination(dest), arrivalTime(arriveTime), departureTime(departTime), bookedSeats(f_bookedSeats), status(st),pilot(f_pilot)
{

}
void Flight::setPilot(Pilot* ptr)
{
	pilot = ptr;
}
void Flight::setID(int id)
{
	flightID = id;
}
void Flight::setSourceAndDestination(string src, string dest)
{
	source = src;
	destination = dest;
}
void Flight::setDepartureTime(string departTime)
{
	departureTime = departTime;
}
void Flight::setArrivalTime(string arriveTime)
{
	arrivalTime = arriveTime;
}
void Flight::setBookedSeats(int bSeats)
{
	bookedSeats = bSeats;
}
void Flight::setStatus(string st)
{
	status = st;
}
string Flight::getDepartureTime() const
{
	return departureTime;
}
string Flight::getArrivalTime() const
{
	return arrivalTime;
}
void Flight::display() const
{
	cout << "Flight ID : " << flightID << endl;
	cout << "Source : " << source << endl;
	cout << "Destination : " << destination << endl;
	cout << "Departure Time : " << departureTime << endl;
	cout << "Arrival Time : " << arrivalTime << endl;
	cout << "Booked Number of Seats : " << bookedSeats << endl;
	cout << "Status : " << status << endl;
	if (pilot != nullptr)
	{
		cout << "Pilot Details :- \n\n";
		pilot->displayPilot();
	}
	
}
Pilot* Flight::getPilot() const
{
	Pilot * ptr =this->pilot;
	return ptr;

}
Flight:: ~Flight()
{


}
