#ifndef PASSENGER_H
#define PASSENGER_H
#include "User.h"
class Passenger :public User
{
public:
	Passenger();
	Passenger(int, string, string, string, float);
	void setWalletBalance(float);
	float getWalletBalance() const;
	void setPassengerID(int);
	int getPassengerID() const;
	void display() const override;
	void searchFlight(string, string);
	void bookTicket(int, int, MYSQL*);
	void cancelBooking(int,MYSQL*);
	void addBalance(MYSQL*);




private:
	float wallet_balance;




};
#endif

