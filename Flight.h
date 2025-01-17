#ifndef FLIGHT_H
#define FLIGHT_H
#include<string>
using namespace std;

#include"Pilot.h"


class Flight
{
protected:
	int flightID;
	string source, destination;
	string departureTime;
	string arrivalTime;
	int bookedSeats;
	string status;
	Pilot* pilot;




public:
	Flight();
	Flight(int, string, string, string, string, int, string,Pilot *);
	void setID(int);
	void setSourceAndDestination(string, string);
	void setDepartureTime(string);
	void setArrivalTime(string);
	void setBookedSeats(int);
	void setStatus(string);
	void setPilot(Pilot*);
	int getId() const { return flightID; }
	string getSource() const { return source; }
	string getDestination() const { return destination; }
	string getDepartureTime() const;
	string getArrivalTime() const;
	int getBookedSeats() const { return bookedSeats; }
	Pilot * getPilot() const;
	string getStatus() const { return status; }
	virtual void display() const;
	virtual ~Flight();
};
#endif

