#ifndef PILOT_H
#define PILOT_H
#include<string>
#pragma warning(disable : 4996)  // Disable deprecated warning
#include <sapi.h>  // Include the SAPI header file
#include <sphelper.h>  // For COM initialization and cleanup

using namespace std;


class Flight;

class Pilot
{
private:
	int pilot_id;
	string name;
	string licenseNumber;
	int experience_years;




public:

	Pilot();
	Pilot(int, string, string, int);
	void setID(int);
	void setName(string);
	void setLicense(string);
	void setExperienceYears(int);
	int getId() const { return pilot_id; }
	string getName() const { return name; }
	string getLicense() const { return licenseNumber; }
	int getExperienceYears() const { return experience_years; }
	void displayPilot() const;
	void Speak(ISpVoice* pVoice, const wchar_t* statement, long rate);
	void landFlight(Flight*);
	void takeOffFlight(Flight*);
	void assignFlight(Flight*);
	void updateStatus(Flight*);






};
#endif
