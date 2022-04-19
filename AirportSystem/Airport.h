#pragma once

#include <string>
#include <list>
#include "LandingStrip.h"
#include <fstream>

using namespace std;

class Airport
{
public:
	string ID;
	list<LandingStrip> LandingStrips;

	Airport() {}
	Airport(string id) { ID = id; }
	Airport(string id, string landingStrip) { ID = id; addLandingStrip(landingStrip); }
	Airport(string id, list<string> landingStrips) { ID = id; addLandingStrips(landingStrips); }
	~Airport() {}

	void addLandingStrip(string);
	void addLandingStrips(list<string>);
	void requestLanding(string RequestedAircraft);

};

