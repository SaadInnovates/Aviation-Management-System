#ifndef FUNCTION_H
#define FUNCTION_H


#include<mysql.h>
using namespace std;
#include "Passenger.h"
#include "Admin.h"

void setColor(int);
void displayMainMenu();
void displayTitle();
int optionMainMenu();
void displayMenu(string);
int displaySignupLoginMenu(string);
int getNextUserId(MYSQL*);
void signUpAdmin(MYSQL*);
void signUpPassenger(MYSQL*);
void loginAdmin(MYSQL*);
void loginPassenger(MYSQL*);
bool flightExists(MYSQL*, int);
bool isFlightAssignedToPilot(MYSQL*, int);
bool isCargoAssignedToVehicle(MYSQL*, int);
void passengerAdminOptionsDisplay(MYSQL*, Admin);
void adminMenu(MYSQL*, Admin);
void PassengerMenu(MYSQL*, Passenger);
void PassengerOptionsMenu(MYSQL*, Passenger);
void adminOptionsMenu(MYSQL*, Admin);
void flightMenu(MYSQL*, Admin);
void pilotMenu(MYSQL* , Admin );
void engineerMenu(MYSQL* , Admin );
void cargoMenu(MYSQL* , Admin );
void airVehicleMenu(MYSQL*, Admin);
void missionsMenu(MYSQL* , Admin );
void maintenanceMenu(MYSQL* conn, Admin obj);
void utilityVehicleMenu(MYSQL* , Admin );
void passengersMenu(MYSQL*, Admin);
void adminFlightOptions(MYSQL* conn, Admin obj);
void adminPilotOptions(MYSQL* conn, Admin obj);
bool engineerExists(MYSQL* conn, int engineer_id);
void adminEngineerOptions(MYSQL* conn, Admin obj);
void adminCargoOptions(MYSQL* conn, Admin obj);
bool cargoExists(MYSQL* conn, int cargo_id);
void adminAirVehicleOptions(MYSQL* conn, Admin obj);
void adminMissionsOptions(MYSQL* conn, Admin obj);
void adminUtilityVehiclesMenu(MYSQL* conn, Admin obj);
void adminPassengerMenu(MYSQL*, Admin obj);
int getNextEngineerId(MYSQL* conn);
int getNextAirVehicleId(MYSQL* conn);
int gtNextUtilityVehicleID(MYSQL* conn);
int getNextPilotId(MYSQL* conn);
int getNextCargoId(MYSQL* conn);
int getNextHangarId(MYSQL* conn);
int getNextFlightId(MYSQL* conn);
void adminCargoOptions(MYSQL* conn, Admin obj);
void adminHangarOptions(MYSQL* conn, Admin obj);






#endif