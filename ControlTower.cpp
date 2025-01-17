#include<iostream>
#include<sstream>
#pragma warning(disable : 4996)  // Disable deprecated warning
#include <sapi.h>  // Include the SAPI header file
#include <sphelper.h>  // For COM initialization and cleanup
using namespace std;
#include "ControlTower.h"
#include "Flight.h"



enum RunwayName 
{
    Runway_090,  
    Runway_27L,  
    Runway_27R,  
    Runway_36,   
    Runway_18L,  
    Runway_18R   
};

string runwayNameToString(RunwayName runway) 
{
    switch (runway) 
    {
    case Runway_090: return "090";
    case Runway_27L: return "27L";
    case Runway_27R: return "27R";
    case Runway_36: return "36";
    case Runway_18L: return "18L";
    case Runway_18R: return "18R";
    default: return "Unknown Runway";
    }
}

RunwayName getRandomRunway() 
{
    srand(time(nullptr));
    int randomInt = rand() % 6;
    return static_cast<RunwayName>(randomInt); 
}

ControlTower::ControlTower():ControlTower(0,"","")
{

}
ControlTower::ControlTower(int c_id, string location, string a_id):towerID(c_id),loc(location), runwayID(a_id)
{

}
void ControlTower::setTowerID(int id)
{
	towerID = id;
}
void ControlTower::setLoc(string l)
{
	loc = l;
}
void ControlTower::setAirportID(string id)
{
    runwayID = id;
}
void ControlTower::Speak(ISpVoice* pVoice, const wchar_t* statement, long rate)
{
    pVoice->SetRate(rate);  // Adjust the rate for different voices
    pVoice->SetVolume(100); // Set maximum volume
    pVoice->Speak(statement, SPF_IS_XML, NULL);  // Speak the statement
}

void ControlTower::scheduleFlight(Flight* flight) {
    // Initialize COM
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        std::wcerr << L"Error: COM initialization failed with HRESULT " << hr << std::endl;
        return;
    }

    // Create a voice object
    ISpVoice* pVoice = NULL;
    hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (FAILED(hr)) {
        std::wcerr << L"Error: Failed to create voice instance with HRESULT " << hr << std::endl;
        CoUninitialize();
        return;
    }

    // Enumerate available voices and find a female voice
    IEnumSpObjectTokens* pEnum = NULL;
    hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &pEnum);
    if (FAILED(hr)) {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    ISpObjectToken* pFemaleVoiceToken = NULL;

    // Loop through available voices to find a female voice
    while (SUCCEEDED(pEnum->Next(1, &pFemaleVoiceToken, NULL))) {
        WCHAR* pName = NULL;
        hr = SpGetDescription(pFemaleVoiceToken, &pName);
        if (SUCCEEDED(hr)) {
            // Look for a female voice, such as "Microsoft Zira"
            if (wcsstr(pName, L"Microsoft Zira") != NULL) {
                break;  // We found the female voice, so break out of the loop
            }
            CoTaskMemFree(pName);
        }
        pFemaleVoiceToken->Release();
        pFemaleVoiceToken = NULL; // Reset the token before continuing
    }

    // Clean up the enumerator
    pEnum->Release();

    // Ensure we found a female voice
    if (pFemaleVoiceToken == NULL) {
        pVoice->Release();
        CoUninitialize();
        std::wcerr << L"Error: No female voice found." << std::endl;
        return;  // Return an error if no female voice was found
    }

    // Set the voice to the female voice
    pVoice->SetVoice(pFemaleVoiceToken);

    // Set volume
    pVoice->SetVolume(100);

    // Get a random runway name
    RunwayName runway = getRandomRunway();
    std::string runwayStr = runwayNameToString(runway);

    // Create the message
    std::wstringstream msgStream;
    msgStream << L"Panam Flight "
        << std::to_wstring(flight->getId())  // Flight ID
        << L", taxi on runway "
        << std::wstring(runwayStr.begin(), runwayStr.end())  // Runway name
        << L" and report takeoff point. Over";

    // Convert the stream to a wide string
    std::wstring msg = msgStream.str();

    // Speak the message
    Speak(pVoice, msg.c_str(), 1);

    // Set the flight status to "Scheduled"
    flight->setStatus("Scheduled");

    // Clean up
    pFemaleVoiceToken->Release();
    pVoice->Release();
    CoUninitialize();
    
}


void ControlTower::track_flight_status(Flight* flight)
{
    // Initialize COM
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        std::wcerr << L"Error: COM initialization failed with HRESULT " << hr << std::endl;
        return;
    }

    // Create a voice object
    ISpVoice* pVoice = NULL;
    hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (FAILED(hr)) {
        std::wcerr << L"Error: Failed to create voice instance with HRESULT " << hr << std::endl;
        CoUninitialize();
        return;
    }

    // Enumerate available voices and find a female voice
    IEnumSpObjectTokens* pEnum = NULL;
    hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &pEnum);
    if (FAILED(hr)) {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    ISpObjectToken* pFemaleVoiceToken = NULL;

    // Loop through available voices to find a female voice
    while (SUCCEEDED(pEnum->Next(1, &pFemaleVoiceToken, NULL))) {
        WCHAR* pName = NULL;
        hr = SpGetDescription(pFemaleVoiceToken, &pName);
        if (SUCCEEDED(hr)) {
            // Look for a female voice, such as "Microsoft Zira"
            if (wcsstr(pName, L"Microsoft Zira") != NULL) {
                break;  // We found the female voice, so break out of the loop
            }
            CoTaskMemFree(pName);
        }
        pFemaleVoiceToken->Release();
        pFemaleVoiceToken = NULL; // Reset the token before continuing
    }

    // Clean up the enumerator
    pEnum->Release();

    // Ensure we found a female voice
    if (pFemaleVoiceToken == NULL) {
        pVoice->Release();
        CoUninitialize();
        std::wcerr << L"Error: No female voice found." << std::endl;
        return;  // Return an error if no female voice was found
    }

    // Set the voice to the female voice
    pVoice->SetVoice(pFemaleVoiceToken);

    // Set volume
    pVoice->SetVolume(100);

    // Get the current status of the flight
    std::string status = flight->getStatus();  // Assuming Flight class has this method
    std::wstring statusWStr = std::wstring(status.begin(), status.end());

    // Create the message for the flight status
    std::wstringstream msgStream;
    msgStream << L"Current status of Panam Flight " << std::to_wstring(flight->getId()) << L": " << statusWStr << L".";

    // Convert the stream to a wide string
    std::wstring msg = msgStream.str();

    // Speak the message
    Speak(pVoice, msg.c_str(), 1);

    // Clean up
    pFemaleVoiceToken->Release();
    pVoice->Release();
    CoUninitialize();
}
void ControlTower::landFlight(Flight* flight)
{
    // Initialize COM
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        std::wcerr << L"Error: COM initialization failed with HRESULT " << hr << std::endl;
        return;
    }

    // Create a voice object
    ISpVoice* pVoice = NULL;
    hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (FAILED(hr)) {
        std::wcerr << L"Error: Failed to create voice instance with HRESULT " << hr << std::endl;
        CoUninitialize();
        return;
    }

    // Enumerate available voices and find a female voice
    IEnumSpObjectTokens* pEnum = NULL;
    hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &pEnum);
    if (FAILED(hr)) {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    ISpObjectToken* pFemaleVoiceToken = NULL;

    // Loop through available voices to find a female voice
    while (SUCCEEDED(pEnum->Next(1, &pFemaleVoiceToken, NULL))) {
        WCHAR* pName = NULL;
        hr = SpGetDescription(pFemaleVoiceToken, &pName);
        if (SUCCEEDED(hr)) {
            // Look for a female voice, such as "Microsoft Zira"
            if (wcsstr(pName, L"Microsoft Zira") != NULL) {
                break;  // We found the female voice, so break out of the loop
            }
            CoTaskMemFree(pName);
        }
        pFemaleVoiceToken->Release();
        pFemaleVoiceToken = NULL; // Reset the token before continuing
    }

    // Clean up the enumerator
    pEnum->Release();

    // Ensure we found a female voice
    if (pFemaleVoiceToken == NULL) {
        pVoice->Release();
        CoUninitialize();
        std::wcerr << L"Error: No female voice found." << std::endl;
        return;  // Return an error if no female voice was found
    }

    // Set the voice to the female voice
    pVoice->SetVoice(pFemaleVoiceToken);

    // Set volume
    pVoice->SetVolume(100);

    // Get the final runway and its name
    RunwayName runway = getRandomRunway();  // This function gets a random runway name
    std::string runwayStr = runwayNameToString(runway);  // Convert the enum to a string

    // Create the message for landing
    std::wstringstream msgStream;
    msgStream << L"Descend to minima. Recheck gear down and lock. C3 Greens. Report final runway Over."
        << std::wstring(runwayStr.begin(), runwayStr.end())  // Runway name
        << L".";  // Ending the sentence with a period

    // Convert the stream to a wide string
    std::wstring msg = msgStream.str();

    // Speak the message
    Speak(pVoice, msg.c_str(), 1);

    // Set the flight status to "Landing"
    flight->setStatus("Landing");

    // Clean up
    pFemaleVoiceToken->Release();
    pVoice->Release();
    CoUninitialize();
}
