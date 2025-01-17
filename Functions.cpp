#include<iostream>
#include<string>
#include<windows.h>
using namespace std;
#include "User.h"
#include "Passenger.h"
#include "Functions.h"
#include "Hangar.h"
#include "Admin.h"
#include "Flight.h"
#include "MilitaryFlight.h"
#include "Pilot.h"
#include "ControlTower.h"


void setColor(int color)
{
	cout << "\033[" << color << "m";
}
void displayTitle()
{
	setColor(93);
	cout << "                                        ";
	cout << "<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>";
	setColor(30);
	cout << endl;
	setColor(93);

	cout << "                                        ";
	cout << "|";
	cout << "     AVIATION MANAGEMENT SYSTEM";
	cout << "     |";
	setColor(30);
	cout << endl;
	cout << "                                        ";
	setColor(93);
	cout << "<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>";




}
void displayMainMenu()
{
	cout << endl << endl << endl;
	cout << "                                   ";
	setColor(92);
	cout << "-------------------";
	cout << " MAIN MENU ";
	cout << "-------------------";
	cout << endl << endl << endl;


	cout << "Select any one of the given options (1-3) " << endl << endl << endl;
	cout << "----------------------------------------------\n";
	cout << "1-Signup         2-Login         3-Exit" << endl;
	cout << "----------------------------------------------\n";
	cout << endl << endl;
	setColor(93);
	cout << "Enter : ";

}
int optionMainMenu()
{
	displayTitle();
	displayMainMenu();
	string choice;
	setColor(97);
	cin >> choice;
	while (choice[0] < '1' || choice[0] > '3' || choice.length() != 1)
	{
		system("cls");
		displayTitle();
		setColor(91);
		cout << endl << "ERROR!!!!\a\n";
		displayMainMenu();
		setColor(97);
		cin >> choice;

	}
	system("cls");
	displayTitle();

	int option = choice[0] - '0';
	if (option == 3)
	{
		system("cls");
		displayTitle();
		cout << endl << endl << endl;
		setColor(96);
		cout << "Thank You for using this Application. Hope you enjoyed it!!!\n";
		terminate;
	}
	return option;
}
void displayMenu(string purpose)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	cout << "                                   ";
	setColor(92);
	cout << "-------------------";
	cout << " " << purpose << " ";
	cout << "-------------------";
	cout << endl << endl << endl;


	cout << "Select any one of the given options (1-3) " << endl << endl << endl;
	cout << "----------------------------------------------\n";
	cout << "1-Admin         2-Passenger         3-Exit" << endl;
	cout << "----------------------------------------------\n";
	cout << endl << endl;
	setColor(93);
	cout << "Enter : ";

}
int displaySignupLoginMenu(string purpose)
{
	displayTitle();
	displayMenu(purpose);
	string choice;
	setColor(97);
	cin >> choice;
	while (choice[0] < '1' || choice[0] > '3' || choice.length() != 1)
	{
		system("cls");
		displayTitle();
		setColor(91);
		cout << endl << "ERROR!!!!\a\n";
		displayMenu(purpose);
		setColor(97);
		cin >> choice;

	}
	system("cls");
	displayTitle();

	int option = choice[0] - '0';
	if (option == 3)
	{
		system("cls");
		displayTitle();
		cout << endl << endl << endl;
		setColor(96);
		cout << "Thank You for using this Application. Hope you enjoyed it!!!\n";
		terminate;
	}
	return option;
}
int getNextUserId(MYSQL* conn)
{
	string query = "SELECT MAX(user_id) FROM user;";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == NULL)
	{
		cerr << "Failed to retrieve result: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	int next_user_id = 1;

	if (row[0] != NULL)
	{
		next_user_id = atoi(row[0]) + 1;
	}

	mysql_free_result(res);

	return next_user_id;
}
int getNextEngineerId(MYSQL* conn)
{
	string query = "SELECT MAX(engineer_id) FROM engineer;";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == NULL)
	{
		cerr << "Failed to retrieve result: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	int next_user_id = 1;

	if (row[0] != NULL)
	{
		next_user_id = atoi(row[0]) + 1;
	}

	mysql_free_result(res);

	return next_user_id;
}
int getNextAirVehicleId(MYSQL* conn)
{
	string query = "SELECT MAX(vehicle_id) FROM airvehicle;";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == NULL)
	{
		cerr << "Failed to retrieve result: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	int next_user_id = 1;

	if (row[0] != NULL)
	{
		next_user_id = atoi(row[0]) + 1;
	}

	mysql_free_result(res);

	return next_user_id;
}
int getNextFlightId(MYSQL* conn)
{
	string query = "SELECT MAX(flight_id) FROM flight;";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == NULL)
	{
		cerr << "Failed to retrieve result: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	int next_user_id = 1;

	if (row[0] != NULL)
	{
		next_user_id = atoi(row[0]) + 1;
	}

	mysql_free_result(res);

	return next_user_id;
}
int gtNextUtilityVehicleID(MYSQL* conn)
{
	string query = "SELECT MAX(vehicle_id) FROM utility_vehicle;";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == NULL)
	{
		cerr << "Failed to retrieve result: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	int next_user_id = 1;

	if (row[0] != NULL)
	{
		next_user_id = atoi(row[0]) + 1;
	}

	mysql_free_result(res);

	return next_user_id;
}
int getNextPilotId(MYSQL* conn)
{
	string query = "SELECT MAX(pilot_id) FROM pilot;";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == NULL)
	{
		cerr << "Failed to retrieve result: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	int next_user_id = 1;

	if (row[0] != NULL)
	{
		next_user_id = atoi(row[0]) + 1;
	}

	mysql_free_result(res);

	return next_user_id;
}
int getNextCargoId(MYSQL* conn)
{
	string query = "SELECT MAX(cargo_id) FROM cargo;";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == NULL)
	{
		cerr << "Failed to retrieve result: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	int next_user_id = 1;

	if (row[0] != NULL)
	{
		next_user_id = atoi(row[0]) + 1;
	}

	mysql_free_result(res);

	return next_user_id;
}
int getNextHangarId(MYSQL* conn)
{
	string query = "SELECT MAX(hangar_id) FROM hangar;";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == NULL)
	{
		cerr << "Failed to retrieve result: " << mysql_error(conn) << endl;
		return -1;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	int next_user_id = 1;

	if (row[0] != NULL)
	{
		next_user_id = atoi(row[0]) + 1;
	}

	mysql_free_result(res);

	return next_user_id;
}
void signUpAdmin(MYSQL* conn)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;

	int user_id = getNextUserId(conn);
	string name;
	string email;
	string phone;
	string password;

	cin.ignore();
	setColor(92);
	cout << "Enter Name: ";
	setColor(97);
	getline(cin, name);
	setColor(92);
	cout << "Enter Email: ";
	setColor(97);
	getline(cin, email);
	setColor(92);
	cout << "Enter Phone in format +92-300-1234567: ";
	setColor(97);
	getline(cin, phone);

	while (phone.length() != 15)
	{
		setColor(92);
		cout << "Re-enter Phone in correct format +92-300-1234567: ";
		setColor(97);
		getline(cin, phone);
	}

	setColor(92);
	cout << "Enter Password upto 10 characters : ";
	setColor(97);
	getline(cin, password);
	while (password.length() > 10)
	{
		setColor(92);
		cout << "\aRe-enter Password upto 10 characters : ";
		setColor(97);
		getline(cin, password);
	}

	string query = "INSERT INTO user (user_id, name, email, phone) VALUES (" + to_string(user_id) + ", '" + name + "', '" + email + "', '" + phone + "');";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL insert into user table failed: " << mysql_error(conn) << endl;
		return;
	}

	query = "INSERT INTO admin (admin_id) VALUES (" + to_string(user_id) + ");";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL insert into admin table failed: " << mysql_error(conn) << endl;
		return;
	}

	query = "INSERT INTO user_passwords (user_id, password) VALUES (" + to_string(user_id) + ", '" + password + "');";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL insert into user_passwords table failed: " << mysql_error(conn) << endl;
		return;
	}

	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	cout << "Admin signed up successfully with user_id: " << user_id << endl;

	cout << "DETAILS :- " << endl;
	User* ptr = new Admin(user_id, name, email, phone);
	setColor(97);
	ptr->display();
	delete ptr;
	ptr = nullptr;

	cout << endl << endl;
	setColor(93);
	cout << "Press ENTER To Continue: ";
	cin.get();
	system("cls");
	displayTitle();
}


void signUpPassenger(MYSQL* conn)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;

	int user_id = getNextUserId(conn);
	string name;
	string email;
	string phone;
	string password;
	float wallet_balance;

	cin.ignore();
	setColor(92);
	cout << "Enter Name: ";
	setColor(97);
	getline(cin, name);
	setColor(92);
	cout << "Enter Email: ";
	setColor(97);
	getline(cin, email);
	setColor(92);
	cout << "Enter Phone in format +92-300-1234567: ";
	setColor(97);
	getline(cin, phone);

	while (phone.length() != 15)
	{
		setColor(92);
		cout << "\aRe-enter Phone in correct format +92-300-1234567: ";
		setColor(97);
		getline(cin, phone);
	}

	setColor(92);
	cout << "Enter Initial Wallet Balance (minimum 50000 PKR): PKR ";
	setColor(97);
	cin >> wallet_balance;
	while (wallet_balance < 50000)
	{
		cout << "\aRe-enter Initial Wallet Balance minimum (50000 PKR): PKR ";
		setColor(97);
		cin >> wallet_balance;
	}

	cin.ignore();
	setColor(92);
	cout << "Enter Password upto 10 characters : ";
	setColor(97);
	getline(cin, password);
	while (password.length() > 10)
	{
		setColor(92);
		cout << "\aRe-enter Password upto 10 characters : ";
		setColor(97);
		getline(cin, password);
	}

	string query = "INSERT INTO user (user_id, name, email, phone) VALUES (" + to_string(user_id) + ", '" + name + "', '" + email + "', '" + phone + "');";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL insert into user table failed: " << mysql_error(conn) << endl;
		return;
	}

	query = "INSERT INTO passenger (passenger_id, wallet_balance) VALUES (" + to_string(user_id) + ", " + to_string(wallet_balance) + ");";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL insert into passenger table failed: " << mysql_error(conn) << endl;
		return;
	}

	query = "INSERT INTO user_passwords (user_id, password) VALUES (" + to_string(user_id) + ", '" + password + "');";
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL insert into user_passwords table failed: " << mysql_error(conn) << endl;
		return;
	}

	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	cout << "Passenger signed up successfully with user_id: " << user_id << endl;

	cout << "DETAILS :- " << endl;
	User* ptr = new Passenger(user_id, name, email, phone, wallet_balance);
	setColor(97);
	ptr->display();
	delete ptr;
	ptr = nullptr;

	cout << endl << endl;
	setColor(93);
	cout << "Press ENTER To Continue: ";
	cin.get();
	system("cls");
	displayTitle();
}



void loginAdmin(MYSQL* conn)
{
	cout << endl << endl << endl;
	int user_id;
	setColor(35);

	cout << "Enter the User ID: ";
	setColor(97);

	cin >> user_id;
	cin.ignore(); // To clear the leftover newline from entering the user ID.

	// Query to check if the user exists
	string query = "SELECT user_id FROM user WHERE user_id = " + to_string(user_id) + ";";
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
		setColor(31);
		cout << "\aNo Admin found with user_id: " << user_id << endl;
		mysql_free_result(res);
		return;
	}

	// Query to check if the user is an admin and fetch user details
	query = "SELECT u.user_id, u.name, u.email, u.phone FROM user u "
		"JOIN admin a ON u.user_id = a.admin_id WHERE u.user_id = " + to_string(user_id) + ";";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		mysql_free_result(res);
		return;
	}

	MYSQL_RES* res_admin = mysql_store_result(conn);
	if (res_admin == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		mysql_free_result(res);
		return;
	}

	num_rows = mysql_num_rows(res_admin);
	if (num_rows == 0)
	{
		setColor(31);
		cout << "\aAccess Denied. You are not an Admin." << endl;
		mysql_free_result(res);
		mysql_free_result(res_admin);
		return;
	}

	// Fetch admin details from the result
	MYSQL_ROW row = mysql_fetch_row(res_admin);
	int admin_id = stoi(row[0]);
	string name = row[1] ? row[1] : "";
	string email = row[2] ? row[2] : "";
	string phone = row[3] ? row[3] : "";

	// Create Admin object with the details
	Admin admin(admin_id, name, email, phone);

	// Free the result set after using it
	mysql_free_result(res);
	mysql_free_result(res_admin);

	// Step 2: Password check loop
	string password;
	bool password_correct = false;

	while (!password_correct)
	{
		setColor(35);
		cout << "Enter Password: ";
		setColor(97);

		getline(cin, password);

		query = "SELECT password FROM user_passwords WHERE user_id = " + to_string(user_id) + ";";
		if (mysql_query(conn, query.c_str()))
		{
			cerr << "MySQL query failed: " << mysql_error(conn) << endl;
			return;
		}

		MYSQL_RES* res_password = mysql_store_result(conn);
		if (res_password == nullptr)
		{
			cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
			return;
		}

		num_rows = mysql_num_rows(res_password);
		if (num_rows == 0)
		{
			setColor(31);
			cout << "\aNo password found for user_id: " << user_id << endl;
			mysql_free_result(res_password);
			return;
		}

		MYSQL_ROW row_password = mysql_fetch_row(res_password);
		string stored_password = row_password[0];

		if (password == stored_password)
		{
			cout << "Login successful!" << endl;
			password_correct = true;
		}
		else
		{
			setColor(31);
			cout << "\aIncorrect password. Please try again." << endl;
		}

		mysql_free_result(res_password);
	}

	displayTitle();
	cout << endl << endl << endl;
	setColor(37);
	cout << "Welcome Admin!" << endl;
	admin.display(); // Display the admin details after login
	cout << "Press ENTER TO CONTINUE : ";
	cin.get();


	// Optionally, you can proceed to the Admin options menu
	adminOptionsMenu(conn, admin);
}


void loginPassenger(MYSQL* conn)
{
	cout << endl << endl << endl;
	int user_id;
	setColor(35);

	cout << "Enter the User ID: ";
	setColor(97);

	cin >> user_id;
	cin.ignore();

	// Step 1: Check if the user exists by joining the 'user' and 'passenger' tables
	string query = "SELECT u.user_id, u.name, u.email, u.phone, p.wallet_balance "
		"FROM user u "
		"JOIN passenger p ON u.user_id = p.passenger_id "
		"WHERE u.user_id = " + to_string(user_id) + ";";

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
		setColor(31);
		cout << "No Passenger found with user_id: " << user_id << endl;
		mysql_free_result(res);
		return;
	}

	MYSQL_ROW row = mysql_fetch_row(res);

	// Extracting user and passenger details
	int passenger_id = stoi(row[0]);
	string name = row[1] ? row[1] : "";
	string email = row[2] ? row[2] : "";
	string phone = row[3] ? row[3] : "";
	float wallet_balance = row[4] ? stof(row[4]) : 0.0f;

	Passenger passenger(passenger_id, name, email, phone, wallet_balance); // Create Passenger object

	mysql_free_result(res); // Free the result set after using it

	// Step 2: Password check loop
	string password;
	bool password_correct = false;

	while (!password_correct)
	{
		setColor(35);
		cout << "Enter Password: ";
		setColor(97);

		getline(cin, password);

		query = "SELECT password FROM user_passwords WHERE user_id = " + to_string(user_id) + ";";
		if (mysql_query(conn, query.c_str()))
		{
			cerr << "MySQL query failed: " << mysql_error(conn) << endl;
			return;
		}

		MYSQL_RES* res_password = mysql_store_result(conn);
		if (res_password == nullptr)
		{
			cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
			return;
		}

		num_rows = mysql_num_rows(res_password);
		if (num_rows == 0)
		{
			setColor(31);
			cout << "No password found for user_id: " << user_id << endl;
			mysql_free_result(res_password);
			return;
		}

		MYSQL_ROW row_password = mysql_fetch_row(res_password);
		string stored_password = row_password[0];

		if (password == stored_password)
		{
			cout << "Login successful!" << endl;
			password_correct = true;
		}
		else
		{
			setColor(31);
			cout << "Incorrect password. Please try again." << endl;
		}

		mysql_free_result(res_password);
	}

	cout << "Welcome Passenger!" << endl;
	passenger.display();
	cout << "Press ENTER TO continue : ";
	cin.get();


	PassengerOptionsMenu(conn, passenger);
}


bool flightExists(MYSQL* conn, int flight_id)
{
	string query = "SELECT FLIGHT_ID FROM flight WHERE FLIGHT_ID = " + to_string(flight_id) + ";";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return false;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		return false;
	}

	int num_rows = mysql_num_rows(res);
	mysql_free_result(res);

	return num_rows > 0;
}
bool engineerExists(MYSQL* conn, int engineer_id)
{
	// Construct the SQL query to check for the existence of the engineer.
	string query = "SELECT ENGINEER_ID FROM engineer WHERE ENGINEER_ID = " + to_string(engineer_id) + ";";

	// Execute the query.
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return false; // Return false if the query execution fails.
	}

	// Store the result of the query.
	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		return false; // Return false if storing the result fails.
	}

	// Get the number of rows returned.
	int num_rows = mysql_num_rows(res);

	// Free the result memory.
	mysql_free_result(res);

	// Return true if one or more rows were found, indicating the engineer exists.
	return num_rows > 0;
}
bool pilotExists(MYSQL* conn, int pilot_id)
{
	string query = "SELECT PILOT_ID FROM pilot WHERE PILOT_ID = " + to_string(pilot_id) + ";";

	// Execute the query
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return false;
	}

	// Store the result of the query
	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		return false;
	}

	// Check if a pilot exists with the provided ID
	int num_rows = mysql_num_rows(res);
	mysql_free_result(res);

	// Return true if a row exists, indicating the pilot exists
	return num_rows > 0;
}
bool cargoExists(MYSQL* conn, int cargo_id)
{
	string query = "SELECT CARGO_ID FROM cargo WHERE CARGO_ID = " + to_string(cargo_id) + ";";

	// Execute the query
	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return false;
	}

	// Store the result of the query
	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		return false;
	}

	// Check if a cargo exists with the provided ID
	int num_rows = mysql_num_rows(res);
	mysql_free_result(res);

	// Return true if a row exists, indicating the cargo exists
	return num_rows > 0;
}


bool isFlightAssignedToPilot(MYSQL* conn, int flight_id)
{
	string query = "SELECT flight_id FROM pilot WHERE flight_id = " + to_string(flight_id) + ";";

	if (mysql_query(conn, query.c_str()))
	{
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return false;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		return false;
	}

	int num_rows = mysql_num_rows(res);
	mysql_free_result(res);

	return num_rows > 0;
}
bool isCargoAssignedToVehicle(MYSQL* conn, int cargo_id)
{
	string query = "SELECT AIR_VEHICLE_ID FROM cargo WHERE CARGO_ID = " + to_string(cargo_id) + ";";
	if (mysql_query(conn, query.c_str())) {
		cerr << "MySQL query failed: " << mysql_error(conn) << endl;
		return false;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res == nullptr)
	{
		cerr << "MySQL store result failed: " << mysql_error(conn) << endl;
		return false;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	mysql_free_result(res);

	if (row != nullptr && row[0] != nullptr)
	{
		return true;
	}
	return false;
}
void PassengerMenu(MYSQL* conn, Passenger obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-Search Flight            2-Book Ticket\n";
	cout << "3-Cancel Booking           4-Add Balance\n";
	cout << "5-Display Your Info        6-Search Your Booking \n";
	cout << "Enter : ";



}
void PassengerOptionsMenu(MYSQL* conn, Passenger obj)
{
	char play;
	do
	{
		PassengerMenu(conn, obj);
		string input;
		setColor(97);
		getline(cin, input);
		while (input.length() != 1 || input[0] < '1' || input[0] > '6')
		{
			cout << "ERROR!!\a\n";
			PassengerMenu(conn, obj);
			setColor(97);
			getline(cin, input);
		}
		int option = input[0] - '0';
		string src, dest;

		switch (option)
		{
		case 1:
			cout << "Enter the Source : ";
			getline(cin, src);
			cout << "Enter the Destination : ";
			getline(cin, dest);
			obj.searchFlight(src, dest);
			break;
		case 2:
			int flightID, seats;
			cout << "Enter the Flight ID : ";
			cin >> flightID;
			while (flightExists(conn, flightID) == false)
			{
				cout << "\aRe-enter the flight ID : ";
				cin >> flightID;
			}
			cout << "Enter the seats : ";
			cin >> seats;
			while (seats <= 0)
			{
				cout << "ERROR!!\a\n";
				cout << "Enter the seats : ";
				cin >> seats;
			}
			obj.bookTicket(flightID, seats, conn);
			break;
		case 3:
			int bookingId;
			cout << "Enter the Booking ID : ";
			cin >> bookingId;
			obj.cancelBooking(bookingId, conn);
			break;
		case 4:
			obj.addBalance(conn);
		case 5:
			obj.display();
			break;
		case 6:
			int bookingID;
			cout << "Enter the Booking ID : ";
			cin >> bookingID;
			obj.findTheBooking(conn, bookingID);
			break;



		}
		cout << "Press Y/y to Continue : ";
		cin >> play;
		cin.ignore();

	} while (play == 'y' || play == 'Y');
}
void adminMenu(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "A-Manage Flights            B-Manage Pilots\n";
	cout << "C-Manage Engineers          D-Manage Cargo\n";
	cout << "E-Manage Air-Vehicles       F-Manage Military Missions \n";
	cout << "G-Manage Utility Vehicles   H-Manage Passengers        \n";
	cout << "I-View All Bookings         J-Delete Admin\n";
	cout << "K-Takeoff Flights           L-Land Flights\n";
	cout << "M-View All Admins           N-Manage Hangars\n";

	cout << "\nENTER : ";

}
void adminOptionsMenu(MYSQL* conn, Admin obj)
{
	char play;
	do
	{
		adminMenu(conn, obj);
		string input;
		setColor(97);
		getline(cin, input);
		while (input.length() != 1 || input[0] < 'A' || input[0] > 'N' && input[0] < 'a' || input[0] > 'n')
		{
			cout << "ERROR!!\a\n";
			adminMenu(conn, obj);
			setColor(97);
			getline(cin, input);
		}
		char option = input[0];
		Flight* ptr;
		Pilot* ptr2;
		int flightId;
		int adminId;
		switch (option)
		{
		case 'a':
		case 'A':
			adminFlightOptions(conn, obj);

			break;

		case 'b':
		case 'B':
			adminPilotOptions(conn, obj);
			break;

		case 'c':
		case 'C':
			adminEngineerOptions(conn, obj);
			break;

		case 'd':
		case 'D':
			adminCargoOptions(conn, obj);
			break;

		case 'e':
		case 'E':
			adminAirVehicleOptions(conn, obj);
			break;

		case 'f':
		case 'F':
			adminMissionsOptions(conn, obj);
			break;

		case 'g':
		case 'G':
			adminUtilityVehiclesMenu(conn, obj);
			break;

		case 'h':
		case 'H':
			adminPassengerMenu(conn, obj);

			break;

		case 'i':
		case 'I':

			obj.viewAllBookings(conn);

			break;

		case 'j':
		case 'J':

			cout << "Enter the Admin ID : ";
			cin >> adminId;
			obj.deleteAdmin(conn, adminId);
			break;
		case 'k':
		case 'K':

		{
			cout << "Enter the Flight ID : ";
			cin >> flightId;
			while (flightExists(conn, flightId) == false)
			{
				cout << "ERROR!!\a\n";
				cout << "Enter the Flight ID : ";
				cin >> flightId;
			}
			ptr = obj.getFlightById(conn, flightId);
			ptr2 = obj.getPilotByFlightId(conn, flightId);
			if (ptr2 != nullptr)
			{
				ptr->setPilot(ptr2);
				ControlTower tower(1, "Francis International Airport", "Random");
				tower.scheduleFlight(ptr);
				ptr2->takeOffFlight(ptr);
				delete ptr;
				ptr = nullptr;
				delete ptr2;
				ptr2 = nullptr;
			}
			else
			{
				delete ptr;
				ptr = nullptr;
			}

		}
		break;
		case 'l':
		case 'L':
		{
			cout << "Enter the Flight ID : ";
			cin >> flightId;
			while (flightExists(conn, flightId) == false)
			{
				cout << "ERROR!!\a\n";
				cout << "Enter the Flight ID : ";
				cin >> flightId;
			}
			ptr = obj.getFlightById(conn, flightId);
			ptr2 = obj.getPilotByFlightId(conn, flightId);
			if (ptr2 != nullptr)
			{
				ptr->setPilot(ptr2);
				ControlTower tower(1, "Francis International Airport", "Random");
				ptr2->landFlight(ptr);
				tower.landFlight(ptr);
				delete ptr;
				ptr = nullptr;
				delete ptr2;
				ptr2 = nullptr;
			}
			else
			{
				delete ptr;
				ptr = nullptr;

			}
		}
		break;
		case 'M':
		case 'm':
			obj.viewAllAdmins(conn);
			break;
		case 'N':
		case 'n':
			adminHangarOptions(conn, obj);
			break;



		}
		setColor(92);
		cout << "Press Y/y to continue : ";
		setColor(97);
        cin >> play;
		cin.ignore();

	} while (play == 'Y' || play == 'y');

	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(96);
	cout << "Thank You for using this Application. Hope you enjoyed it!!!\n";
	terminate;
}
void flightMenu(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-Add Flight                2-Update Flight\n";
	cout << "3-View All Flights          4-Update Flight Pilot\n";
	cout << "5-Update Credentials        6-Delete Flight \n";
	cout << "7-Search Flight\n";

	cout << "\nENTER : ";
}
void pilotMenu(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-Add Pilot                2-Update Pilot\n";
	cout << "3-Delete Pilot             4-View All Pilots\n";
	cout << "5-Search Pilot\n";


	cout << "\nENTER : ";
}
void engineerMenu(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-Add Engineer                2-Update Engineer\n";
	cout << "3-Delete Engineer             4-View All Engineers\n";
	cout << "5-Find Engineer\n";

	cout << "\nENTER : ";
}
void cargoMenu(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-Add Cargo                2-Update Cargo\n";
	cout << "3-Delete Cargo             4-View All Cargos\n";
	cout << "5-Find Cargo\n";

	cout << "\nENTER : ";
}
void airVehicleMenu(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-Add Air-Vehicle                2-Update Air-Vehicle\n";
	cout << "3-Delete Air-Vehicle             4-View All Air-Vehicles\n";
	cout << "5-Find Air-Vehicle               6-Set the Flight\n";

	cout << "\nENTER : ";
}
void missionsMenu(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-View Missions                2-Update Mission\n";
	cout << "3-Delete Mission               4-Create Mission\n";

	cout << "\nENTER : ";
}
void maintenanceMenu(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-View All Maintenances                2-Delete Mainternance\n";

	cout << "\nENTER : ";
}
void utilityVehicleMenu(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-View All Utility Vehicles        2-Update Props\n";
	cout << "3-Update Assigned Air-Vehicle      4-Delete Utility Vehicle\n";
	cout << "5-Add Utility Vehicle\n";


	cout << "\nENTER : ";
}
void passengersMenu(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-View All Passengers        2-Delete Passenger\n";
	cout << "3-Find Passenger\n";


	cout << "\nENTER : ";
}


void adminFlightOptions(MYSQL* conn, Admin obj)
{
	flightMenu(conn, obj);
	string input;
	setColor(97);
	getline(cin, input);
	while (input.length() != 1 || input[0] < '1' || input[0] > '7')
	{
		cout << "ERROR!!\a\n";
		flightMenu(conn, obj);
		setColor(97);
		getline(cin, input);
	}
	int option = input[0] - '0';
	string newStatus;
	int flightId, pilotId;
	Flight* ptr1;
	Pilot* ptr2;
	switch (option)
	{
	case 1:
		obj.addFlight(conn);
		break;
	case 2:
		cout << "Enter the Flight ID : ";
		cin >> flightId;
		while (flightExists(conn, flightId) == false)
		{
			cout << "ERROR!!\a\n";
			cout << "Enter the Flight ID : ";
			cin >> flightId;
		}
		obj.updateFlight(conn, flightId);

		break;
	case 3:
		obj.viewAllFlights(conn);
		break;
	case 4:
		cout << "Enter the Flight ID : ";
		cin >> flightId;
		while (flightExists(conn, flightId) == false)
		{
			cout << "Error!!\a\n";
			cout << "Enter the Flight ID : ";
			cin >> flightId;
		}
		ptr1 = obj.getFlightById(conn, flightId);
		cout << "Enter the Pilot ID : ";
		cin >> pilotId;
		while (pilotExists(conn, pilotId) == false)
		{
			cout << "Error!!\a\n";
			cout << "Enter the Pilot ID : ";
			cin >> pilotId;
		}
		ptr2 = obj.getPilotById(conn, pilotId);
		obj.updateFlightPilot(conn, ptr1, ptr2);
		delete ptr1;
		delete ptr2;
		ptr1 = nullptr;
		ptr2 = nullptr;



		break;
	case 5:
		cout << "Enter the Flight ID : ";
		cin >> flightId;
		while (flightExists(conn, flightId) == false)
		{
			cout << "Error!!\a\n";
			cout << "Enter the Flight ID : ";
			cin >> flightId;
		}

		cin.ignore();
		cout << "Enter the New Status : ";
		getline(cin, newStatus);
		obj.updateFlightCredentials(conn, flightId, newStatus);

		break;
	case 6:
		cout << "Enter the Flight ID : ";
		cin >> flightId;
		while (flightExists(conn, flightId) == false)
		{
			cout << "Error!!\a\n";
			cout << "Enter the Flight ID : ";
			cin >> flightId;
		}
		obj.deleteFlight(conn, flightId);


		break;
	case 7:
		cout << "Enter the Flight ID : ";
		cin >> flightId;
		if (flightExists(conn, flightId) == false)
		{
			cout << "No Such Flight exist!!!\a\n";
		}
		else
		{
			ptr1 = obj.getFlightById(conn, flightId);
			ptr1->display();
			delete ptr1;
			ptr1 = nullptr;

		}

		break;
	}
}
void adminPilotOptions(MYSQL* conn, Admin obj)
{
	pilotMenu(conn, obj);
	string input;
	setColor(97);
	getline(cin, input);
	while (input.length() != 1 || input[0] < '1' || input[0] > '5')
	{
		cout << "ERROR!!\a\n";
		flightMenu(conn, obj);
		setColor(97);
		getline(cin, input);
	}
	int option = input[0] - '0';
	int pilotid;
	Pilot* ptr;
	switch (option)
	{
	case 1:
		obj.addPilot(conn);
		break;
	case 2:
		cout << "Enter the Pilot ID : ";
		cin >> pilotid;
		while (pilotExists(conn, pilotid) == false)
		{
			cout << "ERROR!!\a\n";
			cout << "Enter the Pilot ID : ";
			cin >> pilotid;
		}
		obj.updatePilot(conn, pilotid);

		break;
	case 3:
		cout << "Enter the Pilot ID : ";
		cin >> pilotid;
		if (pilotExists(conn, pilotid) == false)
		{
			cout << "Pilot does not exists!!\a\n" << endl;

		}
		else
		{
			obj.deletePilot(conn, pilotid);
		}
		break;
	case 4:
		obj.viewAllPilots(conn);



		break;
	case 5:
		cout << "Enter the Pilot ID : ";
		cin >> pilotid;
		if (pilotExists(conn, pilotid) == false)
		{
			cout << "Pilot does not exists!!\a\n" << endl;

		}
		else
		{
			ptr = obj.getPilotById(conn, pilotid);
			ptr->displayPilot();
			delete ptr;
			ptr = nullptr;
		}
		

		break;

	}
}
void adminEngineerOptions(MYSQL* conn, Admin obj)
{
	engineerMenu(conn, obj);
	string input;
	setColor(97);
	getline(cin, input);
	while (input.length() != 1 || input[0] < '1' || input[0] > '5')
	{
		cout << "ERROR!!\a\n";
		engineerMenu(conn, obj);
		setColor(97);
		getline(cin, input);
	}
	int option = input[0] - '0';
	int engineerId;
	switch (option)
	{
	case 1:
		obj.addEngineer(conn);
		break;
	case 2:
		cout << "Enter the Engineer ID : ";
		cin >> engineerId;
		if (engineerExists(conn, engineerId) == false)
		{
			cout << "Engineer does no Exists!!\a\n";

		}
		else
		{
			obj.updateEngineer(conn, engineerId);

		}

		break;
	case 3:
		cout << "Enter the Engineer ID : ";
		cin >> engineerId;
		if (engineerExists(conn, engineerId) == false)
		{
			cout << "Engineer Does not Exists!!\a\n";
		}
		else
		{
			obj.deleteEngineer(conn, engineerId);
		}
		break;
	case 4:
		obj.viewAllEngineers(conn);

		break;
	case 5:
		int engineerId;
		cout << "Enter the Engineer ID : ";
		cin >> engineerId;
		obj.findEngineer(conn, engineerId);
		break;
	}
}
void adminCargoOptions(MYSQL* conn, Admin obj)
{
	cargoMenu(conn, obj);
	string input;
	setColor(97);
	getline(cin, input);
	while (input.length() != 1 || input[0] < '1' || input[0] > '5')
	{
		cout << "ERROR!!\a\n";
		cargoMenu(conn, obj);
		setColor(97);
		getline(cin, input);
	}
	int option = input[0] - '0';
	int cargoId;
	switch (option)
	{
	case 1:
		obj.addCargo(conn);
		break;
	case 2:
		cout << "Enter the Cargo ID : ";
		cin >> cargoId;
		if (cargoExists(conn, cargoId) == false)
		{
			cout << "Cargo does no Exists!!\a\n";

		}
		else
		{
			obj.updateCargo(conn, cargoId);

		}

		break;
	case 3:
		cout << "Enter the Cargo ID : ";
		cin >> cargoId;
		if (cargoExists(conn, cargoId) == false)
		{
			cout << "Cargo Does not Exists!!\a\n";
		}
		else
		{
			obj.deleteCargo(conn, cargoId);
		}
		break;
	case 4:
		obj.viewAllCargo(conn);

		break;
	case 5:
		int cargoId;
		cout << "Enter the Cargo ID : ";
		cin >> cargoId;
		obj.viewSpecificCargo(conn, cargoId);
		break;
	}
}
void adminAirVehicleOptions(MYSQL* conn, Admin obj)
{
	airVehicleMenu(conn, obj);
	string input;
	setColor(97);
	getline(cin, input);
	while (input.length() != 1 || input[0] < '1' || input[0] > '6')
	{
		cout << "ERROR!!\a\n";
		airVehicleMenu(conn, obj);
		setColor(97);
		getline(cin, input);
	}
	int option = input[0] - '0';
	int vID;
	int fId;
	AirVehicle* ptr;
	switch (option)
	{
	case 1:
		obj.addAirVehicle(conn);

		break;
	case 2:
		cout << "Enter the Air-Vehicle ID : ";
		cin >> vID;
		ptr = obj.getAirVehicleById(conn, vID);

		if (ptr == nullptr)
		{
			cout << "Air-Vehicle does not Exists!!\a\n";

		}
		else
		{
			obj.updateAirVehicle(conn, vID);
			delete ptr;
			ptr = nullptr;

		}

		break;
	case 3:
		cout << "Enter the Air-Vehicle ID : ";
		cin >> vID;
		ptr = obj.getAirVehicleById(conn, vID);

		if (ptr == nullptr)
		{
			cout << "Air-Vehicle does not Exists!!\a\n";

		}
		else
		{
			obj.deleteAirVehicle(conn, vID);
		}
		break;
	case 4:
		obj.viewAllAirVehicles(conn);

		break;
	case 5:
		cout << "Enter the Air-Vehicle ID : ";
		cin >> vID;
		ptr = obj.getAirVehicleById(conn, vID);
		if (ptr == nullptr)
		{
			cout << "No Such Air Vehicle exists!!\a\n";
		}
		else
		{
			ptr->display();
			delete ptr;
			ptr = nullptr;
		}
		break;
	case 6:
		cout << "Enter the Air-Vehicle ID : ";
		cin >> vID;
		ptr = obj.getAirVehicleById(conn, vID);
		if (ptr == nullptr)
		{
			cout << "No Such Air Vehicle exists!!\a\n";
		}
		else if (ptr->isAssignedOrNot() == true)
		{
			cout << "Sorry This Air Vehicle is already assigned to a flight.\a\n";

		}
		else
		{
			cout << "Enter the Flight ID : ";
			cin >> fId;
			if (flightExists(conn, fId) == false)
			{
				cout << "No Such flight exists!!\a\n";
				

			}
			else
			{
				ptr->setFlight(conn,fId);

				
			}
		}
		break;

	}
}
void adminMissionsOptions(MYSQL* conn, Admin obj)
{
	missionsMenu(conn, obj);
	string input;
	setColor(97);
	getline(cin, input);
	while (input.length() != 1 || input[0] < '1' || input[0] > '4')
	{
		cout << "ERROR!!\a\n";
		missionsMenu(conn, obj);
		setColor(97);
		getline(cin, input);
	}
	int option = input[0] - '0';
	int flightId;

	switch (option)
	{
	case 1:
		obj.viewMissionsMilitary(conn);
		break;
	case 2:

		cout << "Enter the Flight ID : ";
		cin >> flightId;
		obj.updateMissions(conn, flightId);
		break;
	case 3:
		cout << "Enter the Flight ID : ";
		cin >> flightId;
		obj.deleteMissions(conn, flightId);
		break;
	case 4:
		obj.createMilitaryFlight(conn);
		break;



	}
}
void adminUtilityVehiclesMenu(MYSQL* conn, Admin obj)
{
	utilityVehicleMenu(conn, obj);
	string input;
	setColor(97);
	getline(cin, input);
	while (input.length() != 1 || input[0] < '1' || input[0] > '5')
	{
		cout << "ERROR!!\a\n";
		missionsMenu(conn, obj);
		setColor(97);
		getline(cin, input);
	}
	int option = input[0] - '0';
	int vid, airvehicleID;
	AirVehicle* ptr;
	UtilityVehicle* ptr2;
	string purpose, vstatus;

	switch (option)
	{
	case 1:
		obj.viewAllUtilityVehicles(conn);
		break;
	case 2:
		cout << "Enter the Vehicle ID : ";
		cin >> vid;
		ptr2 = obj.findUtiltyVehicle(conn, vid);
		if (ptr2 == nullptr)
		{
			cout << "No Such Utility Vehicle found!!\a\n";
		}
		else
		{
			obj.updateUtilityVehicleProps(conn, ptr2);
			delete ptr2;
			ptr2 = nullptr;
		}
		break;
	case 3:
		cout << "Enter the AirVehicle ID : ";
		cin >> airvehicleID;
		ptr = obj.getAirVehicleById(conn, airvehicleID);
		cout << "Enter the Vehicle ID : ";
		cin >> vid;
		ptr2 = obj.findUtiltyVehicle(conn, vid);
		if (ptr == nullptr || ptr2 == nullptr)
		{
			if (ptr == nullptr)
			{
				cout << "No Such Air Vehicle found!!\a\n";
			}
			else
			{
				cout << "No Such Utility Vehicle found!!\a\n";

			}
		}
		else
		{
			obj.updateUtilityVehicleAirVehicle(conn, ptr2, ptr);
			delete ptr2;
			delete ptr;
			ptr2 = nullptr;
			ptr = nullptr;
		}
		break;
	case 4:
		cout << "Enter the Vehicle ID : ";
		cin >> vid;
		ptr2 = obj.findUtiltyVehicle(conn, vid);
		if (ptr2 == nullptr)
		{
			cout << "No Such Utility Vehicle found!!\a\n";

		}
		else
		{
			delete ptr2;
			ptr2 = nullptr;
			obj.deleteUtilityVehicle(conn, vid);
		}
		break;
	case 5:
		vid = gtNextUtilityVehicleID(conn);

		cout << "Enter the Purpose : ";
		cin >> purpose;
		cout << "Enter the Status : ";
		cin >> vstatus;
		cout << "Enter the Assigned Airvehicle ID : ";
		cin >> airvehicleID;
		ptr = obj.getAirVehicleById(conn, airvehicleID);
		while (ptr == nullptr)
		{
			cout << "ERROR!!\a\n";
			cout << "Re-enter the Assigned Airvehicle ID : ";
			cin >> airvehicleID;
			ptr = obj.getAirVehicleById(conn, airvehicleID);
		}

		ptr2 = new UtilityVehicle(vid, purpose, vstatus, ptr);



		obj.addUtilityVehicle(conn, ptr2);
		delete ptr;
		delete ptr2;
		ptr = nullptr;
		ptr2 = nullptr;
		break;
	case 6:
		cout << "Enter the Vehicle ID : ";
		cin >> vid;
		ptr2 = obj.findUtiltyVehicle(conn, vid);
		if (ptr2 == nullptr)
		{
			cout << "No Such Utility Vehicle found!!\a\n";

		}
		else
		{
			ptr2->display();
			delete ptr2;
			ptr2 = nullptr;
		}




	}
}
void passengerAdminOptionsDisplay(MYSQL* conn, Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-View All Passengers      2-Delete Passenger\n";
	cout << "3-Find Passenger\n";
	cout << "Enter : ";

}
void adminPassengerMenu(MYSQL* conn, Admin obj)
{
	
	passengerAdminOptionsDisplay(conn, obj);
	string input;
	setColor(97);
	getline(cin, input);
	while (input.length() != 1 || input[0] < '1' || input[0] > '3')
	{
		cout << "ERROR!!\a\n";
		passengerAdminOptionsDisplay(conn, obj);
		setColor(97);
		getline(cin, input);
	}
	int option = input[0] - '0';
	int passengerId;


	switch (option)
	{
	case 1:

		obj.viewAllPassengers(conn);
		break;
	case 2:
		int passengerId;
		cout << "Enter the passenger ID : ";
		cin >> passengerId;
		obj.deletePassenger(conn, passengerId);
		break;
	case 3:
		cout << "Enter the passenger ID : ";
		cin >> passengerId;
		obj.findPassenger(conn, passengerId);
		break;



	}
}
void adminHangarMenu(MYSQL*conn,Admin obj)
{
	system("cls");
	displayTitle();
	cout << endl << endl << endl;
	setColor(92);
	cout << "Select any one of the options given below :- \n\n";
	cout << "1-View All Hangars             2-Park Airplane in Hangar\n";
	cout << "3-Free Hangar\n";

	cout << "\nENTER : ";
}
void adminHangarOptions(MYSQL* conn, Admin obj)
{
	adminHangarMenu(conn, obj);
	string input;
	setColor(97);
	getline(cin, input);
	while (input.length() != 1 || input[0] < '1' || input[0] > '3')
	{
		cout << "ERROR!!\a\n";
		adminHangarMenu(conn, obj);
		setColor(97);
		getline(cin, input);
	}
	int option = input[0] - '0';
	int hangarId;
	Hangar* ptr;
	int airVehicleId;
	AirVehicle* ptr2;

	switch (option)
	{
	case 1:
		obj.viewAllHangars(conn);
		break;
	case 2:
		cout << "Enter the Hangar ID : ";
		cin >> hangarId;
		ptr = obj.getHangar(hangarId, conn);
		if (ptr == nullptr)
		{
			cout << "No Such Hangar Found!!\a\n";

		}
		else
		{
			cout << "Enter the Airplane ID : ";
			cin >> airVehicleId;
			ptr2 = obj.getAirVehicleById(conn,airVehicleId);
			if (ptr2 == nullptr)
			{
				cout << "\aNo Such Airplane Found!!\n";
			}
			else
			{
				ptr->addAirplane(conn, ptr2);
				ptr->display();
				delete ptr;
				delete ptr2;
				ptr = nullptr;
				ptr2 = nullptr;
			}
		}
		break;
	case 3:
		cout << "Enter the Hangar ID : ";
		cin >> hangarId;
		ptr = obj.getHangar(hangarId, conn);
		if (ptr == nullptr)
		{
			cout << "No Such Hangar Found!!\a\n";

		}
		else
		{
			cout << "Enter the Airplane ID : ";
			cin >> airVehicleId;
			{
				ptr->freeSpace(conn, airVehicleId);
			}
		}
		break;
	}
}