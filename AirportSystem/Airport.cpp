#include "Airport.h"

void Airport::addLandingStrip(string x)
{
	//constructor to add an additional landing strip to the airport
	LandingStrip strip(x);
	LandingStrips.push_front(strip);
}

void Airport::addLandingStrips(list<string> x)
{
	//constructor to add additional landing strips from list of landing strips to the airport
	for (const auto& size : x)
	{
		LandingStrip strip(size);
		LandingStrips.push_front(strip);
	}
}

void Airport::requestLanding(string RequestedAircraft)
{
	//loop through the landing strips at the airport
	for (auto& strip : LandingStrips)
	{
		//if this strip is the one requested to land at
		if (strip.Size == RequestedAircraft)
		{
			//condition if its the first ever plane landing to let it land
			if (strip.LastLanding == 0)
			{
				strip.acceptLanding(ID);
			}
			//check if it is a light strip has it been 30 seconds since the lase landing and if so proceed to land. In addition check if a waiting plane has started a landing as to not have two flights land at the same time.
			else if (RequestedAircraft == "Light" && time(0) - strip.LastLanding >= 30 && strip.PlaneLanding == false)
			{
				strip.acceptLanding(ID);
			}
			//check if it is a big strip has it been 60 seconds since the lase landing and if so proceed to land. In addition check if a waiting plane has started a landing as to not have two flights land at the same time.
			else if (RequestedAircraft == "Big" && time(0) - strip.LastLanding >= 60 && strip.PlaneLanding == false)
			{
				strip.acceptLanding(ID);
			}
			//if it cannot land on these strips delay the landing and call the delayLanding function to add it to the landing request queue
			else
				strip.delayLanding(ID, strip.WaitingPlanes.size());
		}
	}
}