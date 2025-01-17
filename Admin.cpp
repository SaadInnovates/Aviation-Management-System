#include<iostream>
#include<mysql.h>
using namespace std;
#include "UtilityVehicle.h"
#include "Admin.h"
#include"Booking.h"
#include "Passenger.h"
#include "Pilot.h"
#include "Functions.h"
#include "AirVehicle.h"
#include "AirPlane.h"
#include "Helicopter.h"
#include "Cargo.h"
#include "Flight.h"
#include "MilitaryFlight.h"
#include "Engineer.h"
#include "Hangar.h"

//DEFAULT CONSTRUCTOR
Admin::Admin() :Admin(0, "", "", "")
{

}
//OVERLOADED
Admin::Admin(int id, string name, string email, string phone) :User(id, name, email, phone)
{

}
//SETTERS AND GETTERS 
void Admin::setAdminID(int ad_id)
{
	user_id = ad_id;
}
int Admin::getAdminID() const
{
	return user_id;
}
void Admin::display() const
{
	User::display();
	cout << "Admin ID : " << user_id << endl;

}
//ADD FLIGHT 
void Admin::addFlight(MYSQL* conn)
{
	int flightID;
	string startSource, destination, departureTime, arrivalTime, status;
	int bookedSeats;

	flightID = getNextFlightId(conn);

	cout << "Enter Start Source: ";
	getline(cin, startSource);

	cout << "Enter Destination: ";
	getline(cin, destination);

	cout << "Enter Departure Time (HH:MM:SS): ";
	cin >> departureTime;
	cout << "Enter Arrival Time (HH:MM:SS): ";
	cin >> arrivalTime;
	cout << "Enter Booked Seats: ";
	cin >> bookedSeats;
	while (bookedSeats <= 0)
	{
		cout << "\aRe-enter Booked Seats: ";
		cin >> bookedSeats;
	}
	cout << "Enter Status (e.g., Active): ";
	cin >> status;

	string query = "INSERT INTO flight (FLIGHT_ID, START_SOURCE, DESTINATION, DEPARTURETIME, ARRIVALTIME, BOOKED_SEATS, STATUS) "
		"VALUES (" + to_string(flightID) + ", '" + startSource + "', '" + destination + "', '" + departureTime + "', '" + arrivalTime + "', "
		+ to_string(bookedSeats) + ", '" + status + "')";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "Query failed: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Flight added successfully!" << endl;
}

//UPDATING FLIGHT
void Admin::updateFlight(MYSQL* conn, int flightID)
{
	string startSource, destination, departureTime, arrivalTime, status;
	int bookedSeats;

	cin.ignore();

	cout << "Enter Start Source: ";
	getline(cin, startSource);
	cout << "Enter Destination: ";
	getline(cin, destination);

	cout << "Enter Departure Time (HH:MM:SS): ";
	cin >> departureTime;
	cout << "Enter Arrival Time (HH:MM:SS): ";
	cin >> arrivalTime;
	cout << "Enter Booked Seats: ";
	cin >> bookedSeats;
	while (bookedSeats <= 0)
	{
		cout << "\aRe-enter Booked Seats: ";
		cin >> bookedSeats;
	}
	cout << "Enter Status: ";
	cin >> status;

	string query = "UPDATE flight SET START_SOURCE = '" + startSource + "', DESTINATION = '" + destination + "', DEPARTURETIME = '" + departureTime +
		"', ARRIVALTIME = '" + arrivalTime + "', BOOKED_SEATS = " + to_string(bookedSeats) + ", STATUS = '" + status + "' WHERE FLIGHT_ID = " +
		to_string(flightID);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "Query failed: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Flight updated successfully!" << endl;
}

//TO VIEW ALL BOOKINGS
void Admin::viewAllBookings(MYSQL* conn)
{
	string query = "SELECT * FROM booking";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "Query failed: " << mysql_error(conn) << endl;
		return;
	}

	MYSQL_RES* result = mysql_store_result(conn);
	if (result == NULL)
	{
		cerr << "Error retrieving result: " << mysql_error(conn) << endl;
		return;
	}
	int num_Rows = mysql_num_rows(result);
	if (num_Rows == 0)
	{
		cout << "No Booking found!\a\n";
	}

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)))
	{
		int bookingID = atoi(row[0]);
		int flightID = atoi(row[1]);
		string status = row[2] ? row[2] : "";

		Booking booking(bookingID, flightID, status);
		booking.setPassengersList(conn);
		booking.displayBookingDetails();
	}

	mysql_free_result(result);
}

//ADDING A NEW PILOT 
void Admin::addPilot(MYSQL* conn)
{
	int pilot_id;
	string name, license_number;
	int experience_years;
	int flight_id;

	pilot_id = getNextPilotId(conn);

	cout << "Enter Pilot Name: ";
	getline(cin, name);

	cout << "Enter License Number: ";
	getline(cin, license_number);
	while (license_number.length() != 10)
	{
		cout << "Enter License Number: ";
		getline(cin, license_number);
	}

	cout << "Enter Experience Years: ";
	cin >> experience_years;
	while (experience_years <= 0)
	{
		cout << "\aRe-enter Experience Years: ";
		cin >> experience_years;
	}
	cout << "Enter Flight ID: ";
	cin >> flight_id;
	while (flightExists(conn, flight_id) == false)
	{
		cout << "\aRe-enter Flight ID: ";
		cin >> flight_id;
	}

	Pilot* ptr = new Pilot(pilot_id, name, license_number, experience_years);

	string query = "INSERT INTO pilot (PILOT_ID, NAME, LICENSE_NUMBER, EXPERIENCE_YEARS, flight_id) "
		"VALUES (" + to_string(ptr->getId()) + ", '" + ptr->getName() + "', '" + ptr->getLicense() + "', " + to_string(ptr->getExperienceYears()) + ", " + to_string(flight_id) + ");";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Pilot added successfully!" << endl;
	}
}

//UPDATING THE PILOT 
void Admin::updatePilot(MYSQL* conn, int pilot_id)
{
	string name, license_number;
	int experience_years;
	int flight_id;

	cout << "Enter new Pilot Name: ";
	cin.ignore();
	getline(cin, name);

	cout << "Enter new License Number: ";
	getline(cin, license_number);

	cout << "Enter new Experience Years: ";
	cin >> experience_years;
	while (experience_years <= 0)
	{
		cout << "\aRe-enter Experience Years: ";
		cin >> experience_years;
	}
	cout << "Enter new Flight ID: ";
	cin >> flight_id;
	while (flightExists(conn, flight_id) == false)
	{
		cout << "The Flight with the given Flight_ID does not exist , Re-enter the Flight ID : ";
		cin >> flight_id;
	}
	if (isFlightAssignedToPilot(conn, flight_id) == true)
	{
		cout << "Sorry!!\a This Flight is already assigned to a Pilot.\n";
		return;
	}

	Pilot* updatedPilot = new Pilot(pilot_id, name, license_number, experience_years);

	string query = "UPDATE pilot SET NAME = '" + updatedPilot->getName() + "', LICENSE_NUMBER = '" + updatedPilot->getLicense() + "', "
		"EXPERIENCE_YEARS = " + to_string(updatedPilot->getExperienceYears()) + ", flight_id = " + to_string(flight_id) +
		" WHERE PILOT_ID = " + to_string(updatedPilot->getId()) + ";";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Pilot updated successfully!" << endl;
	}
}

//DELETING A PILOT

void Admin::deletePilot(MYSQL* conn, int pilot_id)
{
	string query = "DELETE FROM pilot WHERE PILOT_ID = " + to_string(pilot_id) + ";";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Pilot deleted successfully!" << endl;
	}
}

//VIEWING ALL PILOTS

void Admin::viewAllPilots(MYSQL* conn)
{
	string query = "SELECT * FROM pilot;";
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

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != nullptr)
	{
		setColor(96);
		cout << "------------------------------------------------------------------------\n";
		int pilot_id = stoi(row[0]);
		string name = row[1];
		string license_number = row[2] ? row[2] : "";
		int experience_years = row[3] ? stoi(row[3]) : 0;

		int flight_id = 0;
		if (row[4] != nullptr)
		{
			flight_id = stoi(row[4]);
		}

		Pilot pilot(pilot_id, name, license_number, experience_years);
		setColor(37);
		pilot.displayPilot();
	}

	mysql_free_result(res);
}

//GETTING AIRVEHICLE BY THE VEHICLE_ID 
AirVehicle* Admin::getAirVehicleById(MYSQL* conn, int air_vehicle_id)
{
	AirVehicle* transport = nullptr;

	string query = "SELECT * FROM airvehicle WHERE VEHICLE_ID = " + to_string(air_vehicle_id) + ";";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return nullptr;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		return nullptr;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	if (row == nullptr)
	{
		cerr << "AirVehicle with ID " << air_vehicle_id << " not found." << endl;
		mysql_free_result(res);
		return nullptr;
	}

	int vehicle_id = stoi(row[0]);
	string model = row[1];
	int capacity = stoi(row[2]);
	string last_maintenance_date = (row[3] != nullptr) ? row[3] : "";
	string status = row[4];
	string type = row[5];

	if (type == "Airplane")
	{
		string airplane_query = "SELECT * FROM airplane WHERE AIRPLANE_ID = " + to_string(vehicle_id) + ";";
		if (mysql_query(conn, airplane_query.c_str()))
		{
			cerr << "MySQL query failed: " << mysql_error(conn) << endl;
			mysql_free_result(res);
			return nullptr;
		}

		MYSQL_RES* airplane_res = mysql_store_result(conn);
		if (airplane_res == nullptr)
		{
			cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
			mysql_free_result(res);
			return nullptr;
		}

		MYSQL_ROW airplane_row = mysql_fetch_row(airplane_res);
		if (airplane_row != nullptr)
		{
			float wingspan = stof(airplane_row[1]);
			bool restricted = (airplane_row[2][0] == 'Y');
			float flight_range = stof(airplane_row[3]);

			transport = new AirPlane(vehicle_id, model, capacity, last_maintenance_date, status, wingspan, flight_range, restricted, type);
		}
		mysql_free_result(airplane_res);
	}
	else if (type == "Helicopter")
	{
		string helicopter_query = "SELECT * FROM helicopter WHERE HELICOPTER_ID = " + to_string(vehicle_id) + ";";
		if (mysql_query(conn, helicopter_query.c_str()))
		{
			cerr << "MySQL query failed: " << mysql_error(conn) << endl;
			mysql_free_result(res);
			return nullptr;
		}

		MYSQL_RES* helicopter_res = mysql_store_result(conn);
		if (helicopter_res == nullptr)
		{
			cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
			mysql_free_result(res);
			return nullptr;
		}

		MYSQL_ROW helicopter_row = mysql_fetch_row(helicopter_res);
		if (helicopter_row != nullptr)
		{
			float rotor_diameter = stof(helicopter_row[1]);
			float max_altitude = stof(helicopter_row[2]);

			transport = new Helicopter(vehicle_id, model, capacity, last_maintenance_date, status, rotor_diameter, max_altitude);
		}
		mysql_free_result(helicopter_res);
	}
	else
	{
		cerr << "Unknown Air Vehicle type: " << type << endl;
	}

	mysql_free_result(res);
	return transport;
}


//ADDING THE CARGO


void Admin::addCargo(MYSQL* conn)
{
	int cargo_id;
	float weight;
	string type, destination;
	int air_vehicle_id;


	cargo_id = getNextCargoId(conn);

	cout << "Enter Weight: ";
	cin >> weight;
	while (weight <= 0)
	{
		cout << "\aRe-enter Weight: ";
		cin >> weight;
		while (weight <= 0)
		{
			cout << "\aRe-enter Weight: ";
			cin >> weight;
		}
	}
	cin.ignore();

	cout << "Enter Type: ";
	getline(cin, type);

	cout << "Enter Destination: ";
	getline(cin, destination);

	cout << "Enter Air Vehicle ID: ";
	cin >> air_vehicle_id;

	AirVehicle* transport = getAirVehicleById(conn, air_vehicle_id);

	if (transport == nullptr)
	{
		cout << "No Air Vehicle with ID " << air_vehicle_id << " exists.\n";
		return;
	}

	Cargo cargo(cargo_id, weight, type, destination, transport);
	string query = "INSERT INTO cargo (CARGO_ID, WEIGHT, CTYPE, DESTINATION, AIR_VEHICLE_ID) "
		"VALUES (" + to_string(cargo.getId()) + ", " + to_string(cargo.getWeight()) + ", '" + cargo.getType() + "', '" + cargo.getDest() + "', " + to_string(air_vehicle_id) + ");";

	cargo.displayCargo();

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Cargo added successfully!" << endl;
	}
	delete transport;
	transport = nullptr;
}
//UPDATING THE CARGO

void Admin::updateCargo(MYSQL* conn, int cargo_id)
{
	float weight;
	string type, destination;
	int air_vehicle_id;

	cout << "Enter new Weight: ";
	cin >> weight;
	while (weight <= 0)
	{
		cout << "\aRe-enter Weight: ";
		cin >> weight;
	}

	cin.ignore();

	cout << "Enter new Type: ";
	getline(cin, type);

	cout << "Enter new Destination: ";
	getline(cin, destination);

	cout << "Enter new Air Vehicle ID: ";
	cin >> air_vehicle_id;

	AirVehicle* transport = getAirVehicleById(conn, air_vehicle_id);
	if (transport == nullptr)
	{
		cout << "No Air Vehicle with ID " << air_vehicle_id << " exists.\n";
		return;
	}

	Cargo cargo(cargo_id, weight, type, destination, transport);
	string query = "UPDATE cargo SET WEIGHT = " + to_string(cargo.getWeight()) + ", CTYPE = '" + cargo.getType() + "', DESTINATION = '" + cargo.getDest() + "', "
		"AIR_VEHICLE_ID = " + to_string(air_vehicle_id) + " WHERE CARGO_ID = " + to_string(cargo.getId()) + ";";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Cargo updated successfully!" << endl;
	}
}

//DELETING THE CARGO
void Admin::deleteCargo(MYSQL* conn, int cargo_id)
{
	if (isCargoAssignedToVehicle(conn, cargo_id))
	{
		cout << "Cargo is assigned to an Air Vehicle. Are you sure you want to delete it? (y/n): ";
		char choice;
		cin >> choice;
		if (choice != 'y' && choice != 'Y')
		{
			cout << "Deletion cancelled.\n";
			return;
		}
	}

	string query = "DELETE FROM cargo WHERE CARGO_ID = " + to_string(cargo_id) + ";";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Cargo deleted successfully!" << endl;
	}
}
//VIEWING ALL CARGO
void Admin::viewAllCargo(MYSQL* conn)
{
	string query = "SELECT * FROM cargo;";
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

	MYSQL_ROW row;
	AirVehicle* transport;
	while ((row = mysql_fetch_row(res)) != nullptr)
	{
		setColor(96);
		cout << "------------------------------------------------------------------------\n";
		int cargo_id = stoi(row[0]);
		float weight = stof(row[1]);
		string type = row[2];
		string destination = row[3];
		int air_vehicle_id = stoi(row[4]);

		transport = getAirVehicleById(conn, air_vehicle_id);
		Cargo cargo(cargo_id, weight, type, destination, transport);

		setColor(37);
		cargo.displayCargo();
		delete transport;

	}

	transport = nullptr;

	mysql_free_result(res);
}
//FINDING A CARGO
void Admin::viewSpecificCargo(MYSQL* conn, int cargo_id)
{
	string query = "SELECT * FROM cargo WHERE CARGO_ID = " + to_string(cargo_id) + ";";

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

	MYSQL_ROW row = mysql_fetch_row(res);

	if (row != nullptr)
	{
		float weight = stof(row[1]);
		string type = row[2];
		string destination = row[3];
		int air_vehicle_id = stoi(row[4]);

		AirVehicle* transport = getAirVehicleById(conn, air_vehicle_id);

		if (transport != nullptr)
		{
			Cargo cargo(cargo_id, weight, type, destination, transport);
			cargo.displayCargo();
			delete transport;
		}
		else
		{
			cerr << "No air vehicle found for Cargo ID " << cargo_id << endl;
		}
	}
	else
	{
		cout << "No cargo found with ID " << cargo_id << endl;
	}

	mysql_free_result(res);
}
//VIEW ALL PASSENGERS
void Admin::viewAllPassengers(MYSQL* conn)
{
	string query = "SELECT p.passenger_id, u.name, u.email, u.phone, p.wallet_balance FROM passenger p "
		"JOIN user u ON p.passenger_id = u.user_id;";
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

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != nullptr)
	{
		int passenger_id = stoi(row[0]);
		string name = row[1];
		string email = row[2];
		string phone = row[3];
		float wallet_balance = stof(row[4]);

		Passenger passenger(passenger_id, name, email, phone, wallet_balance);

		passenger.display();
	}

	mysql_free_result(res);
}
//VIEWING ALL ADMINS
void Admin::viewAllAdmins(MYSQL* conn)
{
	string query = "SELECT a.admin_id, u.name, u.email, u.phone FROM admin a "
		"JOIN user u ON a.admin_id = u.user_id;";

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

	int num_Rows = mysql_num_rows(res);
	if (num_Rows == 0)
	{
		cout << "No Booking found!\a\n";
	}

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != nullptr)
	{
		int admin_id = stoi(row[0]);
		string name = row[1];
		string email = row[2];
		string phone = row[3];

		Admin admin(admin_id, name, email, phone);
		admin.display();
	}

	mysql_free_result(res);
}

//DELETING A PASSENGER

void Admin::deletePassenger(MYSQL* conn, int pId)
{
	string query = "DELETE FROM booking_passenger WHERE passenger_id = " + to_string(pId);
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL Error (booking_passenger): " << mysql_error(conn) << endl;
		return;
	}

	query = "DELETE FROM passenger WHERE passenger_id = " + to_string(pId);
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL Error (passenger): " << mysql_error(conn) << endl;
		return;
	}

	query = "DELETE FROM user_passwords WHERE user_id = " + to_string(pId);
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL Error (user): " << mysql_error(conn) << endl;
		return;
	}

	query = "DELETE FROM user WHERE user_id = " + to_string(pId);
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL Error (user): " << mysql_error(conn) << endl;
		return;
	}

	cout << "Passenger with ID " << pId << " has been successfully deleted." << endl;
}

//FINDING A PASSENGER

void Admin::findPassenger(MYSQL* conn, int pId)
{
	string query = "SELECT p.passenger_id, u.name, u.email, u.phone, p.wallet_balance FROM passenger p "
		"JOIN user u ON p.passenger_id = u.user_id "
		"WHERE p.passenger_id = " + to_string(pId) + ";";


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

	MYSQL_ROW row = mysql_fetch_row(res);
	if (row != nullptr)
	{
		int passenger_id = stoi(row[0]);
		string name = row[1];
		string email = row[2];
		string phone = row[3];
		float wallet_balance = stof(row[4]);

		Passenger passenger(passenger_id, name, email, phone, wallet_balance);
		passenger.display();
	}
	else
	{
		cout << "Passenger with ID " << pId << " not found." << endl;
	}

	mysql_free_result(res);
}
//VIEWING ALL FLIGHTS
void Admin::viewAllFlights(MYSQL* conn)
{
	MYSQL_RES* res;
	MYSQL_ROW row;

	const char* query = "SELECT * FROM flight";

	if (mysql_query(conn, query))
	{
		cerr << "SELECT failed. Error: " << mysql_error(conn) << endl;
		return;
	}

	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res)))
	{
		setColor(96);
		cout << "------------------------------------------------------------------------\n";
		int flight_id = atoi(row[0]);
		string source = row[1];
		string destination = row[2];
		string departureTime = row[3];
		string arrivalTime = row[4];
		int bookedSeats = atoi(row[5]);
		string status = row[6];

		Flight flight(flight_id, source, destination, departureTime, arrivalTime, bookedSeats, status, nullptr);

		setColor(37);
		flight.display();
	}

	mysql_free_result(res);
}
//VIEWING A FLIGHT PILOT
void Admin::updateFlightPilot(MYSQL* conn, Flight* flight, Pilot* pilot)
{
	flight->setPilot(pilot);
	int flightID = flight->getId();
	int pilotID = pilot->getId();

	string pilotQuery = "UPDATE pilot SET flight_id = " + to_string(flightID) + " WHERE PILOT_ID = " + to_string(pilotID);

	if (mysql_query(conn, pilotQuery.c_str()))
	{
		cerr << "UPDATE failed in pilot table. Error: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Pilot for flight ID " << flightID << " has been updated to pilot ID " << pilotID << endl;
		flight->display();
	}
}
//UPDATING THE STATUS OF FLIGHT
void Admin::updateFlightCredentials(MYSQL* conn, int flightID, string newStatus)
{
	string query = "UPDATE flight SET STATUS = '" + newStatus + "' WHERE FLIGHT_ID = " + to_string(flightID);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "UPDATE failed. Error: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Flight ID " << flightID << " status has been updated to " << newStatus << endl;
	}
}
//DELETING THE FLIGHT
void Admin::deleteFlight(MYSQL* conn, int flightId)
{

	string query = "DELETE FROM flight WHERE flight_id = " + to_string(flightId);
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL Error (flight): " << mysql_error(conn) << endl;
		return;
	}

	if (mysql_affected_rows(conn) == 0)
	{
		cout << "Simple flight with ID " << flightId << " not found in flight table." << endl;
	}



	cout << "Simple flight with ID " << flightId << " has been successfully deleted." << endl;
}
//VIEWING ALL UTILITY VEHICLES
void Admin::viewAllUtilityVehicles(MYSQL* conn)
{
	const char* query = "SELECT * FROM utility_vehicle";
	MYSQL_RES* result;
	MYSQL_ROW row;

	if (mysql_query(conn, query))
	{
		cerr << "MySQL query error: " << mysql_error(conn) << endl;
		return;
	}

	result = mysql_store_result(conn);
	if (result == nullptr)
	{
		cerr << "MySQL store result error: " << mysql_error(conn) << endl;
		return;
	}

	AirVehicle* assignedAirVehicle;

	while ((row = mysql_fetch_row(result)))
	{
		int vehicleID = stoi(row[0]);
		string purpose = row[1];
		string vStatus = row[2];
		int assignedAirVehicleID = stoi(row[3]);

		assignedAirVehicle = getAirVehicleById(conn, assignedAirVehicleID);

		UtilityVehicle utilityVehicle(vehicleID, purpose, vStatus, assignedAirVehicle);

		utilityVehicle.display();
		delete assignedAirVehicle;
	}

	mysql_free_result(result);
}

//UPDATING UTILITY VEHICLE
void Admin::updateUtilityVehicleProps(MYSQL* conn, UtilityVehicle* utilityVehicle)
{
	cin.ignore();
	string newPurpose, newStatus;
	cout << "Enter new purpose: ";
	getline(cin, newPurpose);
	cout << "Enter new status: ";
	getline(cin, newStatus);

	utilityVehicle->setPurpose(newPurpose);
	utilityVehicle->setStatus(newStatus);

	string query = "UPDATE utility_vehicle SET PURPOSE = '" + newPurpose + "', VSTATUS = '" + newStatus +
		"' WHERE VEHICLE_ID = " + to_string(utilityVehicle->getVehicleId());

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL update error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Utility vehicle properties updated successfully." << endl;
}
//UPDATING THE AIRVEHICLE *PTR FOR UTILITY VEHICLE
void Admin::updateUtilityVehicleAirVehicle(MYSQL* conn, UtilityVehicle* utilityVehicle, AirVehicle* newAirVehicle)
{
	int airVehicleID = newAirVehicle->getID();

	utilityVehicle->assignToAirVehicle(newAirVehicle);

	string query = "UPDATE utility_vehicle SET ASSIGNED_AIRVEHICLE_ID = " + to_string(airVehicleID) +
		" WHERE VEHICLE_ID = " + to_string(utilityVehicle->getVehicleId());

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL update error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Utility vehicle's assigned air vehicle updated successfully." << endl;
}
//VIEWING ALL AIR VEHICLES

void Admin::viewAllAirVehicles(MYSQL* conn)
{
	const char* query = "SELECT * FROM airvehicle";
	MYSQL_RES* result;
	MYSQL_ROW row;

	if (mysql_query(conn, query))
	{
		cerr << "MySQL query error: " << mysql_error(conn) << endl;
		return;
	}

	result = mysql_store_result(conn);
	if (result == nullptr)
	{
		cerr << "MySQL store result error: " << mysql_error(conn) << endl;
		return;
	}

	int num_Rows = mysql_num_rows(result);
	if (num_Rows == 0)
	{
		cout << "No Booking found!\a\n";
	}
	while ((row = mysql_fetch_row(result)))
	{
		int vehicle_id = stoi(row[0]);
		string model = row[1];
		int capacity = stoi(row[2]);
		string last_maintenance_date = row[3] ? row[3] : "N/A";
		string status = row[4];
		string type = row[5];
		int assigned_flight_id = (row[6] == nullptr || row[6][0] == '\0' || strcmp(row[6], "NULL") == 0) ? 0 : stoi(row[6]);



		cout << "---------------------------------------------------------------------\n";
		cout << "Vehicle ID: " << vehicle_id
			<< ", Model: " << model
			<< ", Capacity: " << capacity
			<< ", Last Maintenance Date: " << last_maintenance_date
			<< ", Status: " << status
			<< ", Type: " << type << endl;
		if (assigned_flight_id != 0)
		{
			cout << "Flight ID : " << assigned_flight_id << endl;
		}
	}

	mysql_free_result(result);
}
//ADDING A NEW AIR VEHICLE
void Admin::addAirVehicle(MYSQL* conn)
{
	string model, status, type;
	int capacity;

	int id;
	id = getNextAirVehicleId(conn);

	cout << "Enter vehicle model: ";
	getline(cin, model);
	cout << "Enter capacity: ";
	cin >> capacity;
	while (capacity <= 0)
	{
		cout << "\aRe-enter capacity: ";
		cin >> capacity;
	}
	cin.ignore();
	cout << "Enter status: ";
	getline(cin, status);
	cout << "Enter vehicle type (Airplane/Helicopter): ";
	getline(cin, type);
	while (type != "Airplane" && type != "Helicopter")
	{
		cout << "\aRe-enter vehicle type (Airplane/Helicopter): ";
		getline(cin, type);
	}

	string query = "INSERT INTO airvehicle (VEHICLE_ID, MODEL, CAPACITY, STATUS, type) VALUES ("
		+ to_string(id) + ", '" + model + "', " + to_string(capacity) + ", '" + status + "', '" + type + "');";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL insert error for airvehicle: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Air vehicle added successfully!" << endl;

	if (type == "Airplane")
	{
		float flight_range;
		cout << "Enter flight range for the airplane: ";
		cin >> flight_range;
		cin.ignore();

		float wingspan;
		cout << "Enter wingspan for the airplane: ";
		cin >> wingspan;
		cin.ignore();

		char restricted;
		cout << "Enter restricted status (Y/N): ";
		cin >> restricted;
		cin.ignore();

		string airplane_query = "INSERT INTO airplane (AIRPLANE_ID, FLIGHT_RANGE, WINGSPAN, RESTRICTED, TYPE) VALUES ("
			+ to_string(id) + ", " + to_string(flight_range) + ", " + to_string(wingspan) + ", '"
			+ restricted + "', '" + type + "');";

		if (mysql_query(conn, airplane_query.c_str()))
		{
			cerr << "MySQL insert error for airplane: " << mysql_error(conn) << endl;
			return;
		}

		cout << "Airplane added successfully!" << endl;
	}
	else if (type == "Helicopter")
	{
		float rotor_diameter, max_altitude;
		cout << "Enter rotor diameter for the helicopter: ";
		cin >> rotor_diameter;
		cout << "Enter max altitude for the helicopter: ";
		cin >> max_altitude;
		cin.ignore();

		string helicopter_query = "INSERT INTO helicopter (HELICOPTER_ID, ROTOR_DIAMETER, MAX_ALTITUDE) VALUES ("
			+ to_string(id) + ", " + to_string(rotor_diameter) + ", " + to_string(max_altitude) + ");";

		if (mysql_query(conn, helicopter_query.c_str()))
		{
			cerr << "MySQL insert error for helicopter: " << mysql_error(conn) << endl;
			return;
		}

		cout << "Helicopter added successfully!" << endl;
	}
	else
	{
		cout << "Invalid vehicle type." << endl;
	}
}
//DELETING AIR VEHICLE

void Admin::deleteAirVehicle(MYSQL* conn, int vehicle_id)
{

	string query = "DELETE FROM airvehicle WHERE VEHICLE_ID = " + to_string(vehicle_id);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL delete error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Air vehicle deleted successfully." << endl;
}
//UPDATING IT
void Admin::updateAirVehicle(MYSQL* conn, int vehicle_id)
{
	string new_model, new_status;
	int new_capacity;
	cin.ignore();
	cout << "Enter new model: ";
	getline(cin, new_model);
	cout << "Enter new capacity: ";
	cin >> new_capacity;
	while (new_capacity <= 0)
	{
		cout << "\aRe-enter new capacity: ";
		cin >> new_capacity;
	}
	cin.ignore();
	cout << "Enter new status: ";
	getline(cin, new_status);

	string query = "UPDATE airvehicle SET MODEL = '" + new_model + "', CAPACITY = " + to_string(new_capacity)
		+ ", STATUS = '" + new_status + "' WHERE VEHICLE_ID = " + to_string(vehicle_id);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL update error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Air vehicle updated successfully." << endl;
}
//GETTING A FLIGHT BY FLIGHT ID
Flight* Admin::getFlightById(MYSQL* conn, int flight_id)
{
	string query = "SELECT FLIGHT_ID, START_SOURCE, DESTINATION, DEPARTURETIME, ARRIVALTIME, BOOKED_SEATS, STATUS FROM flight WHERE FLIGHT_ID = " + to_string(flight_id);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return nullptr;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		return nullptr;
	}

	int num_rows = mysql_num_rows(res);
	if (num_rows == 0)
	{
		cout << "No flight found with flight_id: " << flight_id << endl;
		mysql_free_result(res);
		return nullptr;
	}

	MYSQL_ROW row = mysql_fetch_row(res);

	int id = stoi(row[0]);
	string start_source = row[1] ? row[1] : "";
	string destination = row[2] ? row[2] : "";
	string departure_time = row[3] ? row[3] : "";
	string arrival_time = row[4] ? row[4] : "";
	int booked_seats = row[5] ? stoi(row[5]) : 0;
	string status = row[6] ? row[6] : "";

	Flight* flight = new Flight(id, start_source, destination, departure_time, arrival_time, booked_seats, status, nullptr);

	mysql_free_result(res);
	return flight;
}

//GETTING PILOT BY PILOT ID
Pilot* Admin::getPilotById(MYSQL* conn, int pilot_id)
{
	string query = "SELECT PILOT_ID, NAME, LICENSE_NUMBER, EXPERIENCE_YEARS FROM pilot WHERE PILOT_ID = " + to_string(pilot_id);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return nullptr;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		return nullptr;
	}

	int num_rows = mysql_num_rows(res);
	if (num_rows == 0)
	{
		cout << "No pilot found with pilot_id: " << pilot_id << endl;
		mysql_free_result(res);
		return nullptr;
	}

	MYSQL_ROW row = mysql_fetch_row(res);

	int id = stoi(row[0]);
	string name = row[1] ? row[1] : "";
	string license_number = row[2] ? row[2] : "";
	int experience_years = row[3] ? stoi(row[3]) : 0;

	Pilot* pilot = new Pilot(id, name, license_number, experience_years);

	mysql_free_result(res);
	return pilot;
}

//GETTING PILOT BY FLIGHT_ID
Pilot* Admin::getPilotByFlightId(MYSQL* conn, int flight_id)
{
	try
	{
		string query = "SELECT PILOT_ID, NAME, LICENSE_NUMBER, EXPERIENCE_YEARS FROM pilot WHERE flight_id = " + to_string(flight_id);

		if (mysql_query(conn, query.c_str()))
		{
			throw runtime_error("MySQL query failed: " + string(mysql_error(conn)));
		}

		MYSQL_RES* res = mysql_store_result(conn);
		if (res == nullptr)
		{
			throw runtime_error("MySQL store result failed: " + string(mysql_error(conn)));
		}

		int num_rows = mysql_num_rows(res);
		if (num_rows == 0)
		{
			cout << "No pilot found for flight_id: " << flight_id << endl;
			mysql_free_result(res);
			return nullptr;
		}

		MYSQL_ROW row = mysql_fetch_row(res);

		int pilot_id = stoi(row[0]);
		string pilot_name = row[1] ? row[1] : "";
		string license_number = row[2] ? row[2] : "";
		int experience_years = row[3] ? stoi(row[3]) : 0;

		Pilot* pilot = new Pilot(pilot_id, pilot_name, license_number, experience_years);

		mysql_free_result(res);
		return pilot;
	}
	catch (const std::bad_alloc& e)
	{
		cerr << "Memory allocation failed: " << e.what() << endl;
		return nullptr;
	}
	catch (const std::exception& e)
	{
		cerr << "An error occurred: " << e.what() << endl;
		return nullptr;
	}
}
//ADDIGN A NEW ENGINEER
void Admin::addEngineer(MYSQL* conn)
{
	string name, specialization;
	int engineer_id, assigned_airvehicle_id;

	engineer_id = getNextEngineerId(conn);

	cout << "Enter engineer's name: ";
	getline(cin, name);
	cout << "Enter engineer's specialization: ";
	getline(cin, specialization);
	cout << "Enter assigned air vehicle ID: ";
	cin >> assigned_airvehicle_id;
	AirVehicle* ptr;
	ptr = getAirVehicleById(conn, assigned_airvehicle_id);
	if (ptr == nullptr)
	{
		cout << "No Such Air Vehicle Found !!!\a\n";
		return;
	}
	delete ptr;
	ptr = nullptr;

	cin.ignore();

	string query = "INSERT INTO engineer (ENGINEER_ID, ENAME, SPECIALIZATION, ASSIGNED_AIRVEHICLE_ID) VALUES ("
		+ to_string(engineer_id) + ", '" + name + "', '" + specialization + "', " + to_string(assigned_airvehicle_id) + ")";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL insert error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Engineer added successfully!" << endl;
}
//UPDATING ENGINEER

void Admin::updateEngineer(MYSQL* conn, int engineer_id)
{
	string new_name, new_specialization;
	int new_assigned_airvehicle_id;

	cin.ignore();

	cout << "Enter new name: ";
	getline(cin, new_name);
	cout << "Enter new specialization: ";
	getline(cin, new_specialization);
	cout << "Enter new assigned air vehicle ID: ";
	cin >> new_assigned_airvehicle_id;
	AirVehicle* ptr;
	ptr = getAirVehicleById(conn, new_assigned_airvehicle_id);
	if (ptr == nullptr)
	{
		cout << "No Such Air Vehicle Found !!!\a\n";
		return;
	}
	delete ptr;
	ptr = nullptr;
	cin.ignore();

	string query = "UPDATE engineer SET ENAME = '" + new_name + "', SPECIALIZATION = '"
		+ new_specialization + "', ASSIGNED_AIRVEHICLE_ID = " + to_string(new_assigned_airvehicle_id)
		+ " WHERE ENGINEER_ID = " + to_string(engineer_id);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL update error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Engineer updated successfully!" << endl;
}
//VIEWING ALL ENGS
void Admin::viewAllEngineers(MYSQL* conn)
{
	const char* query = "SELECT * FROM engineer";
	MYSQL_RES* result;
	MYSQL_ROW row;

	if (mysql_query(conn, query))
	{
		cerr << "MySQL query error: " << mysql_error(conn) << endl;
		return;
	}

	result = mysql_store_result(conn);
	if (result == nullptr)
	{
		cerr << "MySQL store result error: " << mysql_error(conn) << endl;
		return;
	}
	int num_Rows = mysql_num_rows(result);
	if (num_Rows == 0)
	{
		cout << "No Booking found!\a\n";
	}
	bool hasRecords = false;
	AirVehicle* vehicle;

	while ((row = mysql_fetch_row(result)))
	{
		setColor(96);
		cout << "------------------------------------------------------------------------\n";
		hasRecords = true;

		int engineer_id = stoi(row[0]);
		string name = row[1];
		string specialization = row[2];
		int assigned_airvehicle_id = stoi(row[3]);

		vehicle = getAirVehicleById(conn, assigned_airvehicle_id);

		if (vehicle == nullptr)
		{
			cerr << "Error: No air vehicle found for Engineer ID " << engineer_id << endl;
			continue;
		}

		Engineer engineer(engineer_id, name, specialization, vehicle);
		setColor(37);

		engineer.display();

		delete vehicle;
		vehicle = nullptr;
	}

	if (!hasRecords)
	{
		cout << "No engineers found in the database." << endl;
	}

	mysql_free_result(result);
}
//DELETING AN ENGINEER

void Admin::deleteEngineer(MYSQL* conn, int engineer_id)
{
	string query = "DELETE FROM engineer WHERE ENGINEER_ID = " + to_string(engineer_id);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL delete error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Engineer with ID " << engineer_id << " deleted successfully!" << endl;
}
//CREATING MILITARY FLIGHT
void Admin::createMilitaryFlight(MYSQL* conn)
{
	int mFlightId;
	string missionType;
	char restricted;

	cout << "Enter Military Flight ID: ";
	cin >> mFlightId;
	if (flightExists(conn, mFlightId) == false)
	{
		cout << "ERROR!!\a First Create the Flight !! \n";
		return;
	}

	cout << "Enter Mission Type: ";
	cin.ignore();
	getline(cin, missionType);

	cout << "Enter Restricted (Y/N): ";
	cin >> restricted;
	while (restricted != 'Y' && restricted != 'N')
	{
		cout << "\aRe-enter restricted status (Y/N): ";
		cin >> restricted;
	}

	string query = "INSERT INTO military_flight (MFLIGHT_ID, MISSION_TYPE, RESTRICTED) "
		"VALUES (" + to_string(mFlightId) + ", '" + missionType + "', '" + restricted + "');";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Military flight created successfully!" << endl;
}

//UPDATE MISSION 
void Admin::viewMissionsMilitary(MYSQL* conn)
{
	const char* query = "SELECT MFLIGHT_ID, MISSION_TYPE, RESTRICTED FROM military_flight";
	MYSQL_RES* result;
	MYSQL_ROW row;

	if (mysql_query(conn, query))
	{
		cerr << "MySQL query error: " << mysql_error(conn) << endl;
		return;
	}

	result = mysql_store_result(conn);
	if (result == nullptr)
	{
		cerr << "MySQL store result error: " << mysql_error(conn) << endl;
		return;
	}

	int num_Rows = mysql_num_rows(result);
	if (num_Rows == 0)
	{
		cout << "No Booking found!\a\n";

	}

	bool found = false;
	while ((row = mysql_fetch_row(result)))
	{
		int flight_id = stoi(row[0]);
		string mission_type = (row[1] != nullptr) ? row[1] : "N/A";
		string restricted = (row[2] != nullptr) ? row[2] : "N/A";

		cout << "Flight ID: " << flight_id << ", Mission Type: " << mission_type << ", Restricted: " << restricted << endl;
		found = true;
	}

	if (!found)
	{
		cout << "No military missions found." << endl;
	}

	mysql_free_result(result);
}

//CHECKING WHETHER MIL FLIGHT EXISTS
bool Admin::MilflightExists(MYSQL* conn, int flight_id)
{
	string query = "SELECT MFLIGHT_ID FROM military_flight WHERE MFLIGHT_ID = " + to_string(flight_id);
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query error: " << mysql_error(conn) << endl;
		return false;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result error: " << mysql_error(conn) << endl;
		return false;
	}

	bool exists = mysql_num_rows(res) > 0;
	mysql_free_result(res);
	return exists;
}
//UPDATING THE MIL MISSIONS
void Admin::updateMissions(MYSQL* conn, int flight_id)
{
	if (!flightExists(conn, flight_id))
	{
		cout << "No mission found with Flight ID " << flight_id << endl;
		return;
	}

	string new_mission_type;
	char new_restricted;

	cin.ignore();
	cout << "Enter new mission type: ";
	getline(cin, new_mission_type);

	cout << "Enter new restricted status (Y/N): ";
	cin >> new_restricted;
	while (new_restricted != 'Y' && new_restricted != 'N')
	{
		cout << "\aRe-enter new restricted status (Y/N): ";
		cin >> new_restricted;
	}
	cin.ignore();

	string query = "UPDATE military_flight SET MISSION_TYPE = '" + new_mission_type + "', RESTRICTED = '" + new_restricted + "' WHERE MFLIGHT_ID = " + to_string(flight_id);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL update error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Mission with Flight ID " << flight_id << " updated successfully." << endl;
}

//deleting missions

void Admin::deleteMissions(MYSQL* conn, int flight_id)
{
	if (!flightExists(conn, flight_id))
	{
		cout << "No mission found with Flight ID " << flight_id << endl;
		return;
	}

	string query = "DELETE FROM military_flight WHERE MFLIGHT_ID = " + to_string(flight_id);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL delete error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Mission with Flight ID " << flight_id << " deleted successfully." << endl;
}
//deleting admin

void Admin::deleteAdmin(MYSQL* conn, int admin_id)
{
	string checkQuery = "SELECT admin_id FROM admin WHERE admin_id = " + to_string(admin_id) + ";";

	if (mysql_query(conn, checkQuery.c_str()))
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
		cout << "Admin with ID " << admin_id << " not found." << endl;
		mysql_free_result(res);
		return;
	}

	string deleteQuery = "DELETE FROM admin WHERE admin_id = " + to_string(admin_id) + ";";

	if (mysql_query(conn, deleteQuery.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Admin with ID " << admin_id << " has been deleted." << endl;

	mysql_free_result(res);
}

//adding utility vehicle

void Admin::addUtilityVehicle(MYSQL* conn, UtilityVehicle* vehicle)
{
	string query = "INSERT INTO utility_vehicle (VEHICLE_ID, PURPOSE, VSTATUS, ASSIGNED_AIRVEHICLE_ID) "
		"VALUES (" + to_string(vehicle->getVehicleId()) + ", '"
		+ vehicle->getPurpose() + "', '"
		+ vehicle->getStatus() + "', "
		+ to_string(vehicle->getAirVehicleId()) + ");";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL insert error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Utility Vehicle with ID " << vehicle->getVehicleId() << " has been added." << endl;
}

//deleting utility vehicle

void Admin::deleteUtilityVehicle(MYSQL* conn, int vehicle_id)
{
	string query = "DELETE FROM utility_vehicle WHERE VEHICLE_ID = " + to_string(vehicle_id) + ";";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL delete error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Utility Vehicle with ID " << vehicle_id << " has been deleted." << endl;
}
//finding an engineer
void Admin::findEngineer(MYSQL* conn, int engineer_id)
{
	string query = "SELECT ENGINEER_ID, ENAME, SPECIALIZATION, ASSIGNED_AIRVEHICLE_ID "
		"FROM engineer "
		"WHERE ENGINEER_ID = " + to_string(engineer_id) + ";";

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

	MYSQL_ROW row = mysql_fetch_row(res);
	if (row != nullptr)
	{
		int id = stoi(row[0]);
		string name = row[1];
		string specialization = row[2];
		int assigned_airvehicle_id = stoi(row[3]);

		AirVehicle* vehicle = getAirVehicleById(conn, assigned_airvehicle_id);

		if (vehicle != nullptr)
		{
			Engineer engineer(id, name, specialization, vehicle);
			engineer.display();
			delete vehicle;
		}
		else
		{
			cout << "No air vehicle assigned to Engineer with ID " << engineer_id << "." << endl;
		}
	}
	else
	{
		cout << "Engineer with ID " << engineer_id << " not found." << endl;
	}

	mysql_free_result(res);
}
//getter for utility vehicle

UtilityVehicle* Admin::findUtiltyVehicle(MYSQL* conn, int uVID)
{
	string query = "SELECT VEHICLE_ID, PURPOSE, VSTATUS, ASSIGNED_AIRVEHICLE_ID FROM utility_vehicle WHERE VEHICLE_ID = " + to_string(uVID) + ";";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query error: " << mysql_error(conn) << endl;
		return nullptr;
	}

	MYSQL_RES* result = mysql_store_result(conn);
	if (result == nullptr)
	{
		cerr << "MySQL store result error: " << mysql_error(conn) << endl;
		return nullptr;
	}

	MYSQL_ROW row = mysql_fetch_row(result);
	if (row == nullptr)
	{
		mysql_free_result(result);
		return nullptr;
	}

	int vehicle_id = stoi(row[0]);
	string purpose = row[1];
	string status = row[2];
	int assigned_airvehicle_id = stoi(row[3]);

	UtilityVehicle* utilityVehicle = new UtilityVehicle(vehicle_id, purpose, status, nullptr);

	mysql_free_result(result);

	return utilityVehicle;
}
void Admin::viewAllHangars(MYSQL* conn)
{
	string query = "SELECT h.HANGAR_ID, h.LOC, h.CAPACITY, h.OCCUPIED_SPACES, ha.AIRPLANE_ID "
		"FROM hangar h "
		"LEFT JOIN hangar_airplanes ha ON h.HANGAR_ID = ha.HANGAR_ID ";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "SELECT failed. Error: " << mysql_error(conn) << endl;
		return;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "Error storing result: " << mysql_error(conn) << endl;
		return;
	}

	int num_rows = mysql_num_rows(res);
	if (num_rows == 0)
	{
		cout << "No Hangar Found!\n\a";

	}
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != nullptr)
	{
		int hangar_id = atoi(row[0]);
		string location = row[1];
		int capacity = atoi(row[2]);
		int occupied_spaces = atoi(row[3]);
		int airplane_id = (row[4] != nullptr) ? atoi(row[4]) : 0;

		Hangar* hangar = new Hangar(hangar_id, location, capacity, occupied_spaces);

		if (airplane_id != 0)
		{
			AirVehicle* airplane = getAirVehicleById(conn, airplane_id);
			hangar->display();
			airplane->display();
			delete airplane;


		}
		else
		{
			hangar->display();
		}

		delete hangar; // Clean up memory after displaying the hangar details

	}

	mysql_free_result(res);
}
Hangar* Admin::getHangar(int h_id, MYSQL* conn)
{
	string query = "SELECT * FROM hangar WHERE HANGAR_ID = " + to_string(h_id);

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "SELECT failed. Error: " << mysql_error(conn) << endl;
		return nullptr;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "Error storing result: " << mysql_error(conn) << endl;
		return nullptr;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	if (row == nullptr)
	{
		cout << "No hangar found with HANGAR_ID = " << h_id << endl;
		mysql_free_result(res);
		return nullptr;
	}

	int hangar_id = atoi(row[0]);
	string location = row[1];
	int capacity = atoi(row[2]);
	int occupied_spaces = atoi(row[3]);

	Hangar* hangar = new Hangar(hangar_id, location, capacity, occupied_spaces);

	mysql_free_result(res);

	return hangar;
}


