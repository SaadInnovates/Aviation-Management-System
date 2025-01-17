#pragma warning(disable : 4996)
#include <iostream>
#include <sstream>
#include <sapi.h>
#include <sphelper.h>

using namespace std;
#include "Pilot.h"
#include "Flight.h"

Pilot::Pilot() : Pilot(0, "", "", 0) {}

Pilot::Pilot(int id, string p_name, string p_license, int years) : pilot_id(id), name(p_name), licenseNumber(p_license), experience_years(years) {}

void Pilot::setID(int id) {
    pilot_id = id;
}

void Pilot::setName(string name) {
    this->name = name;
}

void Pilot::setLicense(string lic) {
    licenseNumber = lic;
}

void Pilot::setExperienceYears(int y) {
    experience_years = y;
}

void Pilot::displayPilot() const {
    cout << "Pilot ID : " << pilot_id << endl;
    cout << "Pilot Name : " << name << endl;
    cout << "Pilot License Number : " << licenseNumber << endl;
    cout << "Experience Years : " << experience_years << endl;
}

void Pilot::Speak(ISpVoice* pVoice, const wchar_t* statement, long rate) {
    pVoice->SetRate(rate);
    pVoice->SetVolume(100);
    pVoice->Speak(statement, SPF_IS_XML, NULL);
}

void Pilot::takeOffFlight(Flight* flight) {
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) return;

    ISpVoice* pVoice = NULL;
    hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (FAILED(hr)) {
        CoUninitialize();
        return;
    }

    IEnumSpObjectTokens* pEnum = NULL;
    hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &pEnum);
    if (FAILED(hr)) {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    ISpObjectToken* pMaleVoiceToken = NULL;

    while (SUCCEEDED(pEnum->Next(1, &pMaleVoiceToken, NULL))) {
        WCHAR* pName = NULL;
        hr = SpGetDescription(pMaleVoiceToken, &pName);
        if (SUCCEEDED(hr) && wcsstr(pName, L"Microsoft David") != NULL) {
            break;
        }
        CoTaskMemFree(pName);
        pMaleVoiceToken->Release();
        pMaleVoiceToken = NULL;
    }

    pEnum->Release();

    if (pMaleVoiceToken == NULL) {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    pVoice->SetVoice(pMaleVoiceToken);
    pVoice->SetVolume(100);

    string flightSource = flight->getSource();
    int flightID = flight->getId();

    wstringstream msgStream;
    msgStream << L"Roger. "
        << wstring(flightSource.begin(), flightSource.end())
        << L", this is Flight "
        << to_wstring(flightID)
        << L" ready for take-off.";

    wstring msg = msgStream.str();
    Speak(pVoice, msg.c_str(), 0);

    pMaleVoiceToken->Release();
    pVoice->Release();
    CoUninitialize();
}

void Pilot::landFlight(Flight* flight) {
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) return;

    ISpVoice* pVoice = NULL;
    hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (FAILED(hr)) {
        CoUninitialize();
        return;
    }

    IEnumSpObjectTokens* pEnum = NULL;
    hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &pEnum);
    if (FAILED(hr)) {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    ISpObjectToken* pMaleVoiceToken = NULL;

    while (SUCCEEDED(pEnum->Next(1, &pMaleVoiceToken, NULL))) {
        WCHAR* pName = NULL;
        hr = SpGetDescription(pMaleVoiceToken, &pName);
        if (SUCCEEDED(hr) && wcsstr(pName, L"Microsoft David") != NULL) {
            break;
        }
        CoTaskMemFree(pName);
        pMaleVoiceToken->Release();
        pMaleVoiceToken = NULL;
    }

    pEnum->Release();

    if (pMaleVoiceToken == NULL) {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    pVoice->SetVoice(pMaleVoiceToken);
    pVoice->SetVolume(100);

    string flightSource = flight->getSource();
    int flightID = flight->getId();

    wstringstream msgStream;
    msgStream << L"Destination, this is Flight "
        << wstring(flightSource.begin(), flightSource.end())
        << L", it's now level 3000 feet. Request for landing. Over";

    wstring msg = msgStream.str();
    Speak(pVoice, msg.c_str(), 0);

    pMaleVoiceToken->Release();
    pVoice->Release();
    CoUninitialize();
}

void Pilot::assignFlight(Flight* flight) {
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) return;

    ISpVoice* pVoice = NULL;
    hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (FAILED(hr)) {
        CoUninitialize();
        return;
    }

    IEnumSpObjectTokens* pEnum = NULL;
    hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &pEnum);
    if (FAILED(hr)) {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    ISpObjectToken* pMaleVoiceToken = NULL;

    while (SUCCEEDED(pEnum->Next(1, &pMaleVoiceToken, NULL))) {
        WCHAR* pName = NULL;
        hr = SpGetDescription(pMaleVoiceToken, &pName);
        if (SUCCEEDED(hr) && wcsstr(pName, L"Microsoft David") != NULL) {
            break;
        }
        CoTaskMemFree(pName);
        pMaleVoiceToken->Release();
        pMaleVoiceToken = NULL;
    }

    pEnum->Release();

    if (pMaleVoiceToken == NULL) {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    pVoice->SetVoice(pMaleVoiceToken);
    pVoice->SetVolume(100);

    flight->setPilot(this);

    wstring msg = L"Pilot " + wstring(name.begin(), name.end()) +
        L" is now assigned to flight " + to_wstring(flight->getId()) + L".";
    Speak(pVoice, msg.c_str(), 1);

    pMaleVoiceToken->Release();
    pVoice->Release();
    CoUninitialize();
}

void Pilot::updateStatus(Flight* flight) {
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) return;

    ISpVoice* pVoice = NULL;
    hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (FAILED(hr)) {
        CoUninitialize();
        return;
    }

    IEnumSpObjectTokens* pEnum = NULL;
    hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &pEnum);
    if (FAILED(hr)) {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    ISpObjectToken* pMaleVoiceToken = NULL;

    while (SUCCEEDED(pEnum->Next(1, &pMaleVoiceToken, NULL))) {
        WCHAR* pName = NULL;
        hr = SpGetDescription(pMaleVoiceToken, &pName);
        if (SUCCEEDED(hr) && wcsstr(pName, L"Microsoft David") != NULL) {
            break;
        }
        CoTaskMemFree(pName);
        pMaleVoiceToken->Release();
        pMaleVoiceToken = NULL;
    }

    pEnum->Release();

    if (pMaleVoiceToken == NULL) 
    {
        pVoice->Release();
        CoUninitialize();
        return;
    }

    pVoice->SetVoice(pMaleVoiceToken);
    pVoice->SetVolume(100);

    string flightSource = flight->getSource();
    int flightID = flight->getId();

    int randomAltitude = rand() % (35000 - 5000 + 1) + 5000;

    wstringstream msgStream;
    msgStream << L" "
        << wstring(flightSource.begin(), flightSource.end())
        << L", Flight "
        << to_wstring(flightID)
        << L" has reached an altitude of "
        << to_wstring(randomAltitude)
        << L" feet and is proceeding towards its destination.";

    wstring msg = msgStream.str();
    Speak(pVoice, msg.c_str(), 1);

    pMaleVoiceToken->Release();
    pVoice->Release();
    CoUninitialize();
}
