#include <mysql.h>
#include <iostream>
#include <string>
#pragma warning(disable : 4996)  


using namespace std;


MYSQL* conn = nullptr;
#include "Functions.h"
#include "User.h"
#include "Admin.h"
#include "Passenger.h"
#include "ControlTower.h"
#include "Pilot.h"
#include "Flight.h"
#include "Engineer.h"
#include "AirVehicle.h"
#include "AirPlane.h"
#include "Booking.h"
#include "UtilityVehicle.h"
#include "Engineer.h"
#include "Cargo.h"
#include "MilitaryFlight.h"
#include "Hangar.h"
int main()
{
	
	MYSQL_RES* res = nullptr; 
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "saad2004", "test_db", 3306, NULL, 0);
	if (!conn)
	{
		cout << "Connection failed: " << mysql_error(conn) << endl;
	}
	else
	{
		char play;
		do
		{
			system("cls");
			int option = optionMainMenu();
			int option2;
			system("cls");
			switch (option)
			{
			case 1:
				option2 = displaySignupLoginMenu("SIGNUP");
				if (option2 == 1)
				{
					signUpAdmin(conn);

				}
				else if (option2 == 2)
				{
					signUpPassenger(conn);

				}
				else
				{
					return 0;
				}

				break;
			case 2:
				option2 = displaySignupLoginMenu("LOGIN");
				if (option2 == 1)
				{
					loginAdmin(conn);
				}
				else if (option2 == 2)
				{
					loginPassenger(conn);

				}
				else
				{
					return 0;
				}


				break;
			case 3:

				displayTitle();
				cout << endl << endl << endl;
				setColor(96);
				cout << "Thank You for using this Application. Hope you enjoyed it!!!\n";
				return 0;
			}
			cout << endl << endl << endl;
			setColor(93);

			cout << "Press Y/y to Continue to Main Menu : ";
			setColor(37);

			cin >> play;

		} while (play == 'y' || play == 'Y');
		













	}
	mysql_close(conn);
	



	return 0;
}
