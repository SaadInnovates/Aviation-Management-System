#ifndef CONTROL_TOWER_H
#define CONTROL_TOWER_H

#include<string>
#pragma warning(disable : 4996)  // Disable deprecated warning
#include <sapi.h>  // Include the SAPI header file
#include <sphelper.h>  // For COM initialization and cleanup


using namespace std;
#include "Flight.h"
class ControlTower
{
private:
	int towerID;
	string loc;
	string runwayID;

public:
	ControlTower();
	ControlTower(int, string, string);
	void setTowerID(int);
	void setLoc(string);
	void setAirportID(string);
	int getTowerID() const { return towerID; }
	string getLoc() const { return loc; }
	string getAirportID() const{ return runwayID; }
	void scheduleFlight(Flight*);
	void track_flight_status(Flight*);
	void landFlight(Flight *);
	void Speak(ISpVoice* pVoice, const wchar_t* statement, long rate);

};
#endif

