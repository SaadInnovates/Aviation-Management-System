#include<iostream>
#include<sstream>
#include<iomanip>
#include<mysql.h>
using namespace std;
#include "Passenger.h"
#include "Booking.h"

Passenger::Passenger() :Passenger(0, "", "", "", 0.0)
{

}
Passenger::Passenger(int a_id, string a_name, string a_email, string a_ph, float wallet) :User(a_id, a_name, a_email, a_ph), wallet_balance(wallet)
{

}
void Passenger::setWalletBalance(float wallet)
{
    wallet_balance = wallet;
}
float Passenger::getWalletBalance() const
{
    return wallet_balance;
}
void Passenger::setPassengerID(int pID)
{
    user_id = pID;
}
int Passenger::getPassengerID() const
{
    return user_id;
}
void Passenger::display() const
{
    User::display();
    cout << "Passenger ID : " << user_id << endl;
    cout << "Wallet Balance : PKR " << wallet_balance << endl;
}
void Passenger::searchFlight(string source, string destination)
{
    extern MYSQL* conn;

    string query = "SELECT FLIGHT_ID, START_SOURCE, DESTINATION, DEPARTURETIME, ARRIVALTIME, STATUS "
        "FROM flight "
        "WHERE START_SOURCE = '" + source + "' AND DESTINATION = '" + destination + "' ";

    if (mysql_query(conn, query.c_str()))
    {
        cerr << "MySQL query error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result)
    {
        cerr << "MySQL store result error: " << mysql_error(conn) << endl;
        return;
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    if (num_fields == 0)
    {
        cout << "No Flight Found!\a\n";
        return;
    }
    cout << "Available flights:\n";
    cout << "+-----------+---------------+-------------+---------------+-------------+-----------+\n";
    cout << "| FLIGHT_ID | START_SOURCE  | DESTINATION | DEPARTURETIME | ARRIVALTIME | STATUS    |\n";
    cout << "+-----------+---------------+-------------+---------------+-------------+-----------+\n";

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            cout << "| " << setw(10) << left << (row[i] ? row[i] : "NULL") << " ";
        }
        cout << "|" << endl;
        cout << "+-----------+---------------+-------------+---------------+-------------+-----------+\n";
    }

    mysql_free_result(result);
}
int getNextBookingId(MYSQL* conn) 
{
    string query = "SELECT MAX(BOOKING_ID) FROM booking";
    if (mysql_query(conn, query.c_str())) 
    {
        cerr << "MySQL query error: " << mysql_error(conn) << endl;
        return -1;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        cerr << "MySQL store result error: " << mysql_error(conn) << endl;
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int max_booking_id = 0;

    if (row && row[0]) {
        max_booking_id = stoi(row[0]);
    }

    mysql_free_result(result);

    return max_booking_id + 1;
}

void Passenger::bookTicket(int flight_id, int seats, MYSQL* conn)
{
    string query = "SELECT BOOKED_SEATS, STATUS FROM flight WHERE FLIGHT_ID = " + to_string(flight_id);
    if (mysql_query(conn, query.c_str()))
    {
        cerr << "MySQL query error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        cerr << "MySQL store result error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (!row) 
    {
        cout << "Error: Flight with ID " << flight_id << " does not exist." << endl;
        mysql_free_result(result);
        return;
    }

    int booked_seats = stoi(row[0]);
    string status = row[1];
    mysql_free_result(result);

    if (status != "Available")
    {
        cout << "Error: Flight is not available for booking." << endl;
        return;
    }

    int max_seats = 200;
    if (booked_seats + seats > max_seats) 
    {
        cout << "Error: Not enough seats available on this flight." << endl;
        return;
    }

    int booking_id = getNextBookingId(conn);
    string booking_status = "Confirmed";
    Booking booking(booking_id, flight_id, booking_status);

    query = "INSERT INTO booking (BOOKING_ID, FLIGHT_ID, SEATS, BSTATUS) VALUES (" +
        to_string(booking_id) + ", " + to_string(flight_id) + ", " + to_string(seats) + ", '" + booking_status + "')";
    if (mysql_query(conn, query.c_str()))
    {
        cerr << "MySQL insert error (booking): " << mysql_error(conn) << endl;
        return;
    }

    query = "UPDATE flight SET BOOKED_SEATS = BOOKED_SEATS + " + to_string(seats) +
        " WHERE FLIGHT_ID = " + to_string(flight_id);
    if (mysql_query(conn, query.c_str())) 
    {
        cerr << "MySQL update error (flight): " << mysql_error(conn) << endl;
        return;
    }

    for (int i = 0; i < seats; i++) 
    {
        cout << "Adding passenger " << (i + 1) << " of " << seats << "...\n";
        booking.addPassengersToBooking(conn);
    }

    cout << "Booking successful! Booking ID: " << booking_id << endl;
}

void Passenger::cancelBooking(int booking_id, MYSQL* conn)
{
    string query_check = "SELECT * FROM booking WHERE booking_id = " + to_string(booking_id) + ";";

    if (mysql_query(conn, query_check.c_str()))
    {
        cerr << "MySQL Error (checking booking existence): " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result_check = mysql_store_result(conn);
    if (!result_check)
    {
        cerr << "MySQL Error (result_check): " << mysql_error(conn) << endl;
        return;
    }

    int num_rows = mysql_num_rows(result_check);
    if (num_rows == 0)
    {
        cout << "Error: Booking ID " << booking_id << " not found." << endl;
        mysql_free_result(result_check);
        return;
    }

    mysql_free_result(result_check);

    string query1 = "DELETE FROM booking_passenger WHERE booking_id = " + to_string(booking_id) + ";";

    if (mysql_query(conn, query1.c_str()))
    {
        cerr << "MySQL Error (booking_passenger): " << mysql_error(conn) << endl;
        return;
    }
    else
    {
        cout << "Related passenger record(s) removed from 'booking_passenger' table." << endl;
    }

    string query2 = "DELETE FROM booking WHERE booking_id = " + to_string(booking_id) + ";";

    if (mysql_query(conn, query2.c_str()))
    {
        cerr << "MySQL Error (booking): " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Booking with ID " << booking_id << " has been successfully cancelled." << endl;
    }
}

void Passenger::addBalance(MYSQL* conn)
{
    float amount;
    cout << "Enter the amount to add in wallet : ";
    cin >> amount;
    while (amount <= 0)
    {
        cout << "ERROR!!\a\n";
        cout << "Re-enter the amount : ";
        cin >> amount;
    }
    this->wallet_balance += amount;
    string query = "UPDATE passenger SET wallet_balance = wallet_balance + " + to_string(amount) +
        " WHERE passenger_id = " + to_string(this->user_id) + ";";

    if (mysql_query(conn, query.c_str()))
    {
        cerr << "MySQL Error: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Balance updated successfully!" << endl;
    }
}
