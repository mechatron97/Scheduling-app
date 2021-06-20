#include <sstream>
#include "Appointment.h"

Appointment::Appointment(void)
{
 m_StartTime = 0;
 m_Duration = 60;
 m_Topic = "";
}

Appointment::Appointment(int start, int duration, string topic)
{
	m_StartTime = start;
	m_Duration = duration;
	m_Topic = topic;
}

Appointment::~Appointment(void)
{
}

int Appointment::GetStartTime()
{
	return m_StartTime;
}

int Appointment::GetDuration()
{
	return m_Duration;
}

string Appointment::GetTopic()
{
	return m_Topic;
}

void Appointment::SetStartTime(int t)
{
	m_StartTime = t;
}

void Appointment::SetDuration(int d)
{
	m_Duration = d;
}

void Appointment::SetTopic(string s)
{
	m_Topic = s;
}

string Appointment::Description()
{
	return m_Topic + " (" + FormatDuration() + ")";
}

string Appointment::FormatDuration()
{
	stringstream ss;
	int hrs = m_Duration / 60;
	int mins = m_Duration % 60;
	if (hrs >= 1)
	{
		ss << hrs << " hour" << (hrs > 1 ? "s" : "") << (mins != 0 ? ", " : "");
	}
	if (mins != 0)
	{
		ss << mins << (mins > 1 ? " minutes" : " minute");
	}
	return ss.str();
}


