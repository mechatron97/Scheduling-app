#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <list>
#include "Appointment.h"
#include "Calendar.h"

using namespace std;

Calendar::Calendar(void)
{
	m_DisplayStart = ToMinutes("0800");
	m_DisplayEnd = ToMinutes("2000");
	m_DisplayGran = ToMinutes("15");
}

Calendar::~Calendar(void)
{
}

void Calendar::Run()
{
	string input = " ";
	while (input[0] != '9')
	{
		system("cls");
		ShowMenu();
		getline(cin, input, '\n');
		if (input.length() == 0) continue;
		switch (input[0])
		{
		case '1':
			Display();
			break;
		case '2':
			CreateAppointment();
			break;
		case '3':
			ModifyAppointment();
			break;
		case '4':
			DeleteAppointment();
			break;
		case '5':
			SetOptions();
			break;
		default: 
			continue;
		}
	}

}

void Calendar::ShowMenu()
{
	cout << endl << "Please choose one of the following options:" << endl;
	cout << "1 - Display Calendar" << endl;
	cout << "2 - Create Appointment" << endl;
	cout << "3 - Modify Appointment" << endl;
	cout << "4 - Delete Appointment" << endl;
	cout << "5 - Set Display Options" << endl;
	cout << "9 - Quit" << endl;
}

void Calendar::Display()
{
	for(int t=m_DisplayStart; t<=m_DisplayEnd; t += m_DisplayGran)
	{
		string appDesc = "";
		Appointment * app = GetAppointmentAt(t);
		if (NULL != app)
		{
			appDesc = app->Description();
		}
		cout << ToString(t, false) << " : " << setw(60) << setfill('_') << left << appDesc << endl;
	}
	string junk;
	getline(cin, junk, '\n');
}

Appointment * Calendar::GetAppointmentAt(int t)
{
	list<Appointment>::iterator itr;
	for(itr = m_AppList.begin(); itr != m_AppList.end(); ++itr)
	{
		if (t == itr->GetStartTime())
		{
			return &*itr;
		}
	}
	return NULL;
}

void Calendar::CreateAppointment()
{
	Appointment *pNewApp = new Appointment();
	bool ok = false;
	do
	{
		EditAppointment(pNewApp);
		ok = ValidateAppointment(pNewApp);
	} while (!ok);
	m_AppList.insert(m_AppList.end(), *pNewApp);


}

bool Calendar::ValidateAppointment(Appointment *pApp)
{
	// Check for overlap with existing appointments.
	list<Appointment>::iterator itr;
	int ts0,ts1,te0,te1;
	ts0 = pApp->GetStartTime();
	te0 = ts0 + pApp->GetDuration();
	for(itr = m_AppList.begin(); itr != m_AppList.end(); ++itr)
	{
		if (pApp == (&*itr)) 
			continue;
		// *itr is the appointment to compare for overlap
		ts1 = itr->GetStartTime();
		te1 = ts1 + itr->GetDuration();
		if (
			(ts0 >= ts1 && ts0 < te1)	// pApp starts during other app, or
			|| (te0 > ts1 && te0 <= te1)// pApp ends during other app
			)
		{
			cout << endl << "Appointment conflicts with an existing appointment" << endl << endl;
			return false;
		}
	}

	return true;
}

void Calendar::EditAppointment(Appointment *pApp)
{
	string input;

	cout << "Topic: [" << pApp->GetTopic() << "] ";
	getline(cin, input, '\n');
	if (input.length() > 0)
	{
		pApp->SetTopic(input);
	}

	cout << "Start Time: [" << ToString(pApp->GetStartTime(),true) << "] ";
	getline(cin, input, '\n');
	if (input.length() > 0)
	{
		pApp->SetStartTime(ToMinutes(input));
	}

	cout << "Duration: [" << pApp->GetDuration() << "] ";
	getline(cin, input, '\n');
	if (input.length() > 0)
	{
		pApp->SetDuration(ToMinutes(input));
	}
}

Appointment * Calendar::FindAppointment(string prompt)
{
	string input;
	cout << prompt;
	getline(cin, input, '\n');
	if (input.length() == 0) return NULL;
	int t = ToMinutes(input);
	Appointment *pApp = GetAppointmentAt(t);
	if (NULL == pApp)
	{
		cout << "Error: Appointment not found" << endl;
		getline(cin, input, '\n');
		return NULL;
	}
	else
	{
		return pApp;
	}
}

void Calendar::ModifyAppointment()
{
	Appointment *pApp = FindAppointment("Start time of appointment to modify: ");
	if (NULL == pApp) return;

	bool ok = false;
	do
	{
		EditAppointment(pApp);
		ok = ValidateAppointment(pApp);
	} while (!ok);

}

void Calendar::DeleteAppointment()
{
	Appointment *pApp = FindAppointment("Start time of appointment to delete: ");
	if (NULL == pApp) return;

	list<Appointment>::iterator itr;
	for(itr = m_AppList.begin(); itr != m_AppList.end(); ++itr)
	{
		if (pApp == (&*itr)) 
		{
			m_AppList.erase(itr);
			break;
		}
	}	

}

void Calendar::SetOptions()
{
	string in;
	cout << "Display Start: [" << ToString(m_DisplayStart,true) << "] ";
	getline(cin,in,'\n');
	if (in.length() > 0)
	{
		m_DisplayStart = ToMinutes(in);
	}

	cout << "Display End: [" << ToString(m_DisplayEnd,true) << "] ";
	getline(cin,in,'\n');
	if (in.length() > 0)
	{
		m_DisplayEnd = ToMinutes(in);
	}

	bool ok = false;
	while (!ok)
	{
		cout << "Granularity: [" << ToString(m_DisplayGran,true) << "] ";
		getline(cin,in,'\n');
		int i = m_DisplayGran;
		if (in.length() > 0)
		{
			i = ToMinutes(in);
		}
		if (i != 15 && i != 30 && i != 60)
		{
			cout << "Granularity must be 15, 30 or 60" << endl;
		}
		else
		{

			m_DisplayGran = i;
			ok = true;
		}
	}

}

int Calendar::ToMinutes(string s)
{
	if (s.length() < 2) return -1;
	int result;
	int hrs=0,mins=0;
	string sMins = s.substr(s.length()-2,2);
	stringstream ss;
	ss << sMins;
	ss >> mins;
	if (s.length() > 2)
	{
		string sHrs = s.substr(0,s.length()-2);
		ss.clear();
		ss << sHrs;
		ss >> hrs;
	}
	result = hrs*60 + mins;
	return result;
}

string Calendar::ToString(int minutes, bool military)
{
	int hrs = minutes/60;
	int mins = minutes % 60;
	stringstream ss;
	if (military)
	{
		ss << setw(2) << setfill('0') << hrs << setw(2) << setfill('0') << mins;
	}
	else
	{	string suffix = "AM";
		if (hrs == 0) hrs = 12;
		if (hrs > 12) 
		{
			hrs -= 12;
			suffix = "PM";
		}
		ss << right << setw(2) << hrs << ":" << setw(2) << setfill('0') << mins << " " << suffix;
	}
	return ss.str();
}

