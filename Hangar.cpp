#include<iostream>
#include <mysql.h>
using namespace std;
#include "Hangar.h"
#include "AirVehicle.h"

Hangar::Hangar(int h_id, string h_loc, int h_cap, int h_spaces)
    : hangar_ID(h_id), loc(h_loc), capacity(h_cap), occupied_spaces(h_spaces)
{
    currentCount = 0;
    for (int i = 0; i < 10; i++)
    {
        ptr[i] = nullptr;
    }
}

void Hangar::setId(int h_id)
{
    hangar_ID = h_id;
}

void Hangar::setLoc(string loc)
{
    this->loc = loc;
}

void Hangar::setCapacity(int cap)
{
    capacity = cap;
}

void Hangar::setOccupiedSpaces(int sp)
{
    occupied_spaces = sp;
}

void Hangar::addAirplane(MYSQL*conn, AirVehicle* aeroplane)
{
    this->ptr[currentCount] = aeroplane;
    currentCount++;

    // SQL query to insert airplane into hangar_airplanes table
    string query = "INSERT INTO hangar_airplanes (HANGAR_ID, AIRPLANE_ID) VALUES ("
        + to_string(hangar_ID) + ", " + to_string(aeroplane->getID()) + ")";
    if (mysql_query(conn, query.c_str()))
    {
        cerr << "INSERT failed. Error: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Airplane added to hangar in database.\n";
    }
}

void Hangar::display() const
{
    cout << "Hangar ID : " << hangar_ID << endl;
    cout << "Hangar Capacity : " << capacity << endl;
    cout << "Hangar Loc : " << loc << endl;
    cout << "Hangar Occupied Space : " << occupied_spaces << endl;
    for (int i = 0; i <= currentCount; i++)
    {
        if (ptr[i] != nullptr)
        {
            ptr[i]->display();

        }
    }
}

int Hangar::getId() const
{
    return hangar_ID;
}

string Hangar::getLoc() const
{
    return loc;
}

int Hangar::getCap() const
{
    return capacity;
}

int Hangar::getSpaces() const
{
    return occupied_spaces;
}

void Hangar::parkVehicle(MYSQL* conn , AirVehicle* vehicle)
{
    if (currentCount == 9)
    {
        cout << "Capacity Full! Can't Park more vehicles here.\n";
        return;
    }
    ptr[currentCount] = vehicle;
    currentCount++;

    // SQL query to insert parked airplane into hangar_airplanes table
    string query = "INSERT INTO hangar_airplanes (HANGAR_ID, AIRPLANE_ID) VALUES ("
        + to_string(hangar_ID) + ", " + to_string(vehicle->getID()) + ")";
    if (mysql_query(conn, query.c_str()))
    {
        cerr << "INSERT failed. Error: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Airplane parked in hangar in database.\n";
    }
}

void Hangar::freeSpace(MYSQL *conn , int airplane_id)
{

    // Remove the airplane from the hangar in the database
    string query = "DELETE FROM hangar_airplanes WHERE HANGAR_ID = " + to_string(hangar_ID)
        + " AND AIRPLANE_ID = " + to_string(airplane_id);
    if (mysql_query(conn, query.c_str()))
    {
        cerr << "DELETE failed. Error: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Airplane removed from hangar in database.\n";
    }

    
}
