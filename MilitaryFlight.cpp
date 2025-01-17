#include<iostream>
#include<string>
#include<mysql.h>
using namespace std;
#include "MilitaryFlight.h"
MilitaryFlight::MilitaryFlight():MilitaryFlight(0,"","","","",0,"","",' ',nullptr)
{

}
MilitaryFlight::MilitaryFlight(int f_id, string src, string dest, string arriveTime, string departTime, int f_bookedSeats, string st,string mission,char restrict,Pilot *ptr) :Flight(f_id, src, dest, arriveTime, departTime, f_bookedSeats, st,ptr), restrictedStatus(restrict), missionType(mission)
{

}
void MilitaryFlight::setMission(string mission)
{
	missionType = mission;
}
void MilitaryFlight::setRestriction(char st)
{
	restrictedStatus = st;
}
string MilitaryFlight::getMission() const
{
	return missionType;
}
char MilitaryFlight::getRestrictStatus() const
{
	return restrictedStatus;
}
void MilitaryFlight::display() const
{
	Flight::display();
	cout << "Mission Type : " << missionType << endl;
	if (restrictedStatus == 'T' || restrictedStatus == 't')
	{
		cout << "Restricted Status : TRUE " << endl;
	}
	else
	{
		cout << "Restricted Status : FALSE " << endl;

	}
}

void  MilitaryFlight::scheduleMission(MYSQL* conn)
{
    
    cout << "Enter the Mission Type (e.g., Recon, Air Strike, etc.): ";
    getline(cin, this->missionType);

    cout << "Is this mission restricted? (Y/N): ";
    cin >> restrictedStatus;
    
    while (restrictedStatus != 'Y' && restrictedStatus != 'N')
    {
        cout << "ERROR!!\a\n";
        cout << "Is this mission restricted? (Y/N): ";
        cin >> this->restrictedStatus;

    }

    string query = "INSERT INTO military_flight (MFLIGHT_ID, MISSION_TYPE, RESTRICTED) "
        "VALUES (" + to_string(flightID) + ", '" + missionType + "', '" + restrictedStatus + "');";

    if (mysql_query(conn, query.c_str())) 
    {
        cerr << "MySQL query failed: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Mission scheduled successfully!" << endl;
    }
}
