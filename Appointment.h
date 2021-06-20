#pragma once
#include <string>
using namespace std;

class Appointment
{
public:
	Appointment(void);
	Appointment(int start, int duration, string topic);
	~Appointment(void);

	int GetStartTime();
	int GetDuration();
	string GetTopic();

	void SetStartTime(int t);
	void SetDuration(int d);
	void SetTopic(string s);

	string Description();

private:
	int m_Id;			// Identifier for easy reference
	int m_StartTime;	// Minutes since midnight
	int m_Duration;		// Minutes
	string m_Topic;

	string FormatDuration();

};
