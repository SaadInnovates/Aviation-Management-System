#ifndef BOOKING_H
#define BOOKING_H
#define PASSENGER_SIZE 10

#include<string>
#include<mysql.h>
using namespace std;

class Booking
{
private:
	int booking_id;
	int passenger_ids[PASSENGER_SIZE];
	int seats;
	string status;
	int flight_id;





public:
	Booking();
	Booking(int,int,string);
	void setBookingID(int);
	void setStatus(string);
	void setFlightID(int);
	void setCountSeats(int);
	int getBookingID() const { return booking_id; }
	int getFlightID() const { return flight_id; }
	string getStatus() const { return status; }
	int getCountSeats() const { return seats; }
	void setPassengersList(MYSQL * );
	const int* getPassengersList() const;

	void addPassengersToBooking(MYSQL*);
	void displayBookingDetails();



};
#endif

