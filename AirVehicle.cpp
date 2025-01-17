#include<iostream>
#include<mysql.h>
using namespace std;
#include "AirVehicle.h"

AirVehicle::AirVehicle() :AirVehicle(0, "", 0, "", "")
{

}
AirVehicle::AirVehicle(int v_id, string v_model, int v_cap, string v_date, string v_status) :vehicle_id(v_id), model(v_model), capacity(v_cap), last_maintenance_date(v_date), status(v_status)
{

}
void AirVehicle::setId(int v_id)
{
	vehicle_id = v_id;
}
void AirVehicle::setModel(string v_model)
{
	model = v_model;
}
void AirVehicle::setCap(int v_cap)
{
	capacity = v_cap;
}
void AirVehicle::setDate(string v_Date)
{
	last_maintenance_date = v_Date;
}
void AirVehicle::setStatus(string st)
{
	status = st;
}
void AirVehicle::updateStatus(string newStatus)
{
	status = newStatus;
}
void AirVehicle::scheduleMaintenance(string date, MYSQL* conn)
{
    if (conn == NULL)
    {
        cerr << "Connection is not initialized properly.\n";
        return;
    }

    int vehicle_id = 101;  // Example vehicle ID
    string checkQuery = "SELECT VEHICLE_ID FROM airvehicle WHERE VEHICLE_ID = " + to_string(vehicle_id);

    if (mysql_query(conn, checkQuery.c_str())) 
    {
        cerr << "Query failed: " << mysql_error(conn) << "\n";
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (mysql_num_rows(res) == 0) 
    {
        cerr << "Vehicle ID does not exist in airvehicle table.\n";
        mysql_free_result(res);
        return;
    }
    mysql_free_result(res);

    string query = "INSERT INTO maintenance_log (VEHICLE_ID, maintenance_date) "
        "VALUES ('" + to_string(vehicle_id) + "', '" + date + "')";

    if (mysql_query(conn, query.c_str()))
    {
        cerr << "Failed to schedule maintenance: " << mysql_error(conn) << "\n";
        return;
    }

    cout << "Maintenance for vehicle " << vehicle_id << " scheduled on " << date << "\n";
}

AirVehicle::~AirVehicle()
{
	if (flight != nullptr)
	{
		delete flight;
		flight = nullptr;
	}
}
void AirVehicle::setFlight(MYSQL*conn , int flightId)
{
	string query = "SELECT FLIGHT_ID, START_SOURCE, DESTINATION, DEPARTURETIME, ARRIVALTIME, BOOKED_SEATS, STATUS FROM flight WHERE FLIGHT_ID = " + to_string(flightId);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		flight = nullptr;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		flight = nullptr;
	}

	int num_rows = mysql_num_rows(res);
	if (num_rows == 0)
	{
		cout << "No flight found with flight_id: " << flightId << endl;
		mysql_free_result(res);
		flight= nullptr;
	}

	MYSQL_ROW row = mysql_fetch_row(res);

	int id = stoi(row[0]);
	string start_source = row[1] ? row[1] : "";
	string destination = row[2] ? row[2] : "";
	string departure_time = row[3] ? row[3] : "";
	string arrival_time = row[4] ? row[4] : "";
	int booked_seats = row[5] ? stoi(row[5]) : 0;
	string status = row[6] ? row[6] : "";

	flight = new Flight(id, start_source, destination, departure_time, arrival_time, booked_seats, status, nullptr);
    string update_query;
    if (flightId == 0) 
    {
        update_query = "UPDATE airvehicle SET ASSIGNED_FLIGHT_ID = NULL WHERE VEHICLE_ID = " + to_string(vehicle_id);
    }
    else 
    {
        update_query = "UPDATE airvehicle SET ASSIGNED_FLIGHT_ID = " + to_string(flightId) + " WHERE VEHICLE_ID = " + to_string(vehicle_id);
    }

    if (mysql_query(conn, update_query.c_str())) 
    {
        cerr << "MySQL update failed: " << mysql_error(conn) << endl;
    }
    else 
    {
        cout << "Assigned flight ID updated in the database." << endl;
    }
}

bool AirVehicle :: isAssignedOrNot()
{
	return flight != nullptr;
}