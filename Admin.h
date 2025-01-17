#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
#include "AirVehicle.h"
#include "Pilot.h"
#include "UtilityVehicle.h"
#include "Hangar.h"
class Admin :public User
{
private:




public:
	Admin();
	Admin(int, string, string, string);
	AirVehicle* getAirVehicleById(MYSQL*, int);
	void setAdminID(int);
	int getAdminID() const;
	void display() const override;
	void addFlight(MYSQL*);
	void updateFlight(MYSQL*, int);
	void viewAllBookings(MYSQL*);
	void viewAllPassengers(MYSQL*);
	void deletePassenger(MYSQL*, int);
	void findPassenger(MYSQL*, int);
	void viewAllFlights(MYSQL*);
	void updateFlightPilot(MYSQL*, Flight*, Pilot*);
	void updateFlightCredentials(MYSQL*, int, string);
	void deleteFlight(MYSQL*, int);
	void viewAllUtilityVehicles(MYSQL*);
	void updateUtilityVehicleProps(MYSQL*, UtilityVehicle*);
	void updateUtilityVehicleAirVehicle(MYSQL*, UtilityVehicle*, AirVehicle*);
	void viewAllAirVehicles(MYSQL*);
	void viewAllAdmins(MYSQL* conn);
	void addAirVehicle(MYSQL*);
	Flight* getFlightById(MYSQL* conn, int flight_id);
	Pilot* getPilotByFlightId(MYSQL* conn, int flight_id);
	Pilot* getPilotById(MYSQL* conn, int pilot_id);
	void deleteAirVehicle(MYSQL*, int);
	void updateAirVehicle(MYSQL*, int);
	void addCargo(MYSQL*);
	void updateCargo(MYSQL*, int);
	void deleteCargo(MYSQL*, int);
	void viewAllCargo(MYSQL*);
	void addEngineer(MYSQL*);
	void updateEngineer(MYSQL*, int);
	void deleteEngineer(MYSQL*, int);
	void viewAllEngineers(MYSQL*);
	void addPilot(MYSQL*);
	void updatePilot(MYSQL*, int);
	void deletePilot(MYSQL*, int);
	void viewAllPilots(MYSQL*);
	void viewMissionsMilitary(MYSQL*);
	void updateMissions(MYSQL*, int);
	void deleteMissions(MYSQL*, int);
	void deleteAdmin(MYSQL*, int);
	void addUtilityVehicle(MYSQL*, UtilityVehicle*);
	void deleteUtilityVehicle(MYSQL*, int);
	void findEngineer(MYSQL*, int);
	void viewSpecificCargo(MYSQL*, int);
	bool MilflightExists(MYSQL*, int);
	UtilityVehicle* findUtiltyVehicle(MYSQL*, int);
	void createMilitaryFlight(MYSQL* cnn);
	void viewAllHangars(MYSQL* conn);
	Hangar* getHangar(int, MYSQL*);



};
#endif

