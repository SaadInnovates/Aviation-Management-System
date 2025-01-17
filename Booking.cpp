#include<iostream>
#include<sstream>
#include<mysql.h>
using namespace std;
#include "Booking.h"
Booking::Booking():Booking(0,0,"")
{

}
Booking::Booking(int bookID, int flightID, string a_status):booking_id(bookID),flight_id(flightID),status(a_status),seats(0)
{
	for (int i = 0; i < PASSENGER_SIZE; i++)
	{
		passenger_ids[i] = 0;
	}

}
void Booking::addPassengersToBooking(MYSQL* conn) 
{
    int passenger_id_input;

    while (true) 
    {
        cout << "Enter Passenger ID: ";
        cin >> passenger_id_input;

        stringstream passengerQueryStream;
        passengerQueryStream << "SELECT passenger_id FROM passenger WHERE passenger_id = " << passenger_id_input;
        string passengerQuery = passengerQueryStream.str();

        if (mysql_query(conn, passengerQuery.c_str())) 
        {
            cerr << "MySQL query error (passenger): " << mysql_error(conn) << endl;
            continue;
        }

        MYSQL_RES* passengerResult = mysql_store_result(conn);
        if (!passengerResult || mysql_num_rows(passengerResult) == 0) 
        {
            cout << "Error: Passenger ID " << passenger_id_input << " does not exist. Please try again." << endl;
            if (passengerResult) mysql_free_result(passengerResult);
        }
        else
        {
            mysql_free_result(passengerResult);
            break; 
        }
    }

    string query = "INSERT INTO booking_passenger (BOOKING_ID, PASSENGER_ID) VALUES (" +
        to_string(booking_id) + ", " + to_string(passenger_id_input) + ")";

    if (mysql_query(conn, query.c_str())) 
    {
        cerr << "MySQL insert error (booking_passenger): " << mysql_error(conn) << endl;
        return;
    }

    cout << "Passenger successfully added to the booking." << endl;
}


void Booking::displayBookingDetails()
{
	cout << "Booking ID : " << booking_id << endl;
	cout << "Flight ID : " << flight_id << endl;
	cout << "Seats : " << seats + 1 << endl;
	cout << "Status : " << status << endl;
	cout << "----------- Number of Passengers -----------\n";
	for (int i = 0; i <= seats; i++)
	{
		cout << "Passenger ID : " << passenger_ids[i] << endl;
	}
}
const int* Booking :: getPassengersList() const
{
	const int* ptr = &passenger_ids[0];
	return ptr;
}
void Booking::setBookingID(int b_id)
{
	booking_id = b_id;
}
void Booking::setStatus(string status)
{
	this->status = status;
}
void Booking::setFlightID(int f_id)
{
	flight_id = f_id;
}
void Booking::setCountSeats(int s)
{
	seats = s;
}

void Booking::setPassengersList(MYSQL* conn)
{
    stringstream queryStream;
    queryStream << "SELECT PASSENGER_ID FROM booking_passenger WHERE BOOKING_ID = " << booking_id;
    string query = queryStream.str();

    if (mysql_query(conn, query.c_str())) 
    {
        cerr << "MySQL query error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) 
    {
        cerr << "Error storing result: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_ROW row;
    int i = 0;
    while ((row = mysql_fetch_row(result)) && i < PASSENGER_SIZE) 
    {
        passenger_ids[i] = atoi(row[0]);
        i++;
    }

    seats = i;

    mysql_free_result(result);
}
