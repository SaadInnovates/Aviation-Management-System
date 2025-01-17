#ifndef USER_H
#define USER_H

#include<string>
#include<mysql.h>
using namespace std;

class User
{
protected:
	int user_id;
	string name;
	string email;
	string phone;


public:
	User();
	User(int, string, string, string);
	void setID(int);
	void setName(string);
	void setEmail(string);
	void setPhone(string);
	int getID() const;
	string getName() const;
	string getEmail() const;
	string getPhone() const;
	virtual void display() const=0;
	virtual ~User();
	void viewFlights(MYSQL*);
	void viewBookingHistory(MYSQL*);
	void findTheBooking(MYSQL*, int);



};




#endif