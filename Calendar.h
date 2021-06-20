#pragma once
#include <list>
using namespace std;

#include "Appointment.h"

class Calendar
{
public:
	Calendar(void);
	~Calendar(void);

	void Run();

private:
	list<Appointment> m_AppList;
	int m_DisplayStart;	// Minutes since midnight
	int m_DisplayEnd;	// Minutes since midnight
	int m_DisplayGran;	// Minutes

	void ShowMenu();
	void Display();
	void CreateAppointment();
	void ModifyAppointment();
	void DeleteAppointment();
	void SetOptions();
	
	Appointment * GetAppointmentAt(int t);
	void EditAppointment(Appointment *pApp);
	bool ValidateAppointment(Appointment *pApp);
	Appointment * FindAppointment(string prompt);
	int ToMinutes(string s);
	string ToString(int minutes, bool military);
};
