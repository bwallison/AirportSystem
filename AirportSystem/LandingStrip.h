#pragma once
#include <ctime>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

class LandingStrip
{
public:
	time_t LastLanding;
	string Size;
	queue<time_t> WaitingPlanes;
	bool PlaneLanding;

	LandingStrip() { LastLanding = 0; PlaneLanding = false; }
	LandingStrip(string s) { Size = s; LastLanding = 0; PlaneLanding = false;}
	~LandingStrip() {}

	void freeRunway(string ID);
	void delayLanding(string ID, int QueueSize);
	void acceptLanding(string ID);
	void logEvent(string LogText);
};

