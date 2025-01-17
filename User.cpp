#include<iostream>
#include <mysql.h>
#include <sstream>
using namespace std;
#include"User.h"
#include "Flight.h"
#include "Booking.h"
#include "Functions.h"
#include "Pilot.h"

User::User() :User(0, "", "", "")
{

}

User::User(int a_id, string a_name, string a_email, string a_phone) :user_id(a_id), name(a_name), email(a_email), phone(a_phone)
{

}

void User::setID(int id)
{
    user_id = id;
}

void User::setName(string name)
{
    this->name = name;
}

void User::setEmail(string email)
{
    this->email = email;
}

void User::setPhone(string ph)
{
    phone = ph;
}

int User::getID() const
{
    return user_id;
}

string User::getName() const
{
    return name;
}

string User::getEmail() const
{
    return email;
}

string User::getPhone() const
{
    return phone;
}

void User::display() const
{
    cout << "Name : " << name << endl;
    cout << "Email : " << email << endl;
    cout << "Phone : " << phone << endl;
}

void User::viewFlights(MYSQL* conn) {
    string query = "SELECT * FROM flight WHERE STATUS = 'Available'";

    if (mysql_query(conn, query.c_str())) {
        cerr << "Query failed: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        cerr << "Error retrieving result: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_ROW row;
    cout << "Available Flights:\n";
    cout << "----------------------------------------------\n";

    while ((row = mysql_fetch_row(result))) {
        int flightID = atoi(row[0]);
        string startSource = row[1] ? row[1] : "";
        string destination = row[2] ? row[2] : "";
        string departureTime = row[3] ? row[3] : "";
        string arrivalTime = row[4] ? row[4] : "";
        int bookedSeats = atoi(row[5]);
        string status = row[6] ? row[6] : "";

        string pilotQuery = "SELECT p.PILOT_ID, p.NAME, p.LICENSE_NUMBER, p.EXPERIENCE_YEARS "
            "FROM pilot p "
            "JOIN flight f ON p.flight_id = f.FLIGHT_ID "
            "WHERE f.FLIGHT_ID = " + to_string(flightID);

        if (mysql_query(conn, pilotQuery.c_str())) {
            cerr << "Query failed for pilot: " << mysql_error(conn) << endl;
            continue;
        }

        MYSQL_RES* pilotResult = mysql_store_result(conn);
        if (pilotResult == NULL) {
            cerr << "Error retrieving pilot: " << mysql_error(conn) << endl;
            continue;
        }

        MYSQL_ROW pilotRow = mysql_fetch_row(pilotResult);
        Pilot* pilotPtr = nullptr;

        if (pilotRow != NULL) {
            int pilotID = atoi(pilotRow[0]);
            string pilotName = pilotRow[1] ? pilotRow[1] : "";
            string pilotLicense = pilotRow[2] ? pilotRow[2] : "";
            int experienceYears = atoi(pilotRow[3]);

            Pilot* pilotObj = new Pilot(pilotID, pilotName, pilotLicense, experienceYears);
            pilotPtr = pilotObj;
        }

        Flight flight(flightID, startSource, destination, departureTime, arrivalTime, bookedSeats, status, pilotPtr);
        flight.display();

        mysql_free_result(pilotResult);
        delete pilotPtr;
    }

    mysql_free_result(result);
}

void User::viewBookingHistory(MYSQL* conn) {
    int user_id = this->user_id;

    string query = "SELECT * FROM booking_passenger WHERE passenger_id = " + to_string(user_id);

    if (mysql_query(conn, query.c_str())) {
        cerr << "Query failed: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        cerr << "Error retrieving result: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_ROW row;
    cout << "Booking History for User ID: " << user_id << endl;
    cout << "----------------------------------------" << endl;

    while ((row = mysql_fetch_row(result))) {
        int booking_id = atoi(row[0]);
        int flight_id = atoi(row[1]);

        cout << "Booking ID: " << booking_id << ", Flight ID: " << flight_id << endl;
    }

    mysql_free_result(result);
}

User:: ~User()
{

}

void User::findTheBooking(MYSQL* conn, int bId)
{
    string query = "SELECT BOOKING_ID, FLIGHT_ID, SEATS, BSTATUS FROM booking WHERE BOOKING_ID = " + to_string(bId) + ";";

    if (mysql_query(conn, query.c_str()))
    {
        cerr << "MySQL query failed: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (res == nullptr)
    {
        cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
        return;
    }

    int num_rows = mysql_num_rows(res);
    if (num_rows == 0)
    {
        cout << "No booking found with BOOKING_ID: " << bId << endl;
        mysql_free_result(res);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);

    int booking_id = stoi(row[0]);
    int flight_id = stoi(row[1]);
    int seats = stoi(row[2]);
    string booking_status = row[3] ? row[3] : "";

    cout << "Booking Details:" << endl;
    cout << "Booking ID: " << booking_id << endl;
    cout << "Flight ID: " << flight_id << endl;
    cout << "Seats: " << seats << endl;
    cout << "Booking Status: " << booking_status << endl;

    mysql_free_result(res);
}
