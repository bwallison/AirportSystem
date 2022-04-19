#include "LandingStrip.h"

void LandingStrip::freeRunway(string ID)
{
    PlaneLanding = true;
    //check what type of runway
    if (Size == "Light")
    {
        //check if light runway is still occupied
        if (time(0) - LastLanding >= 30)
        {
            //store newest landing time and remove from queue
            LastLanding = time(0);
            WaitingPlanes.pop();

            //log this landing event
            logEvent("Aircraft landed on the Light runway at " + ID + "\n");
        }
    }
    else if (Size == "Big")
    {
        //check if big runway is still occupied
        if (time(0) - LastLanding >= 60)
        {
            //store newest landing time and remove from queue
            LastLanding = time(0);
            WaitingPlanes.pop();

            //log this landing event
            logEvent("Aircraft landed on the Big runway at " + ID + "\n");
        }
    }
    PlaneLanding = false;
}

void LandingStrip::delayLanding(string ID, int QueueSize)
{
    //add time of waiting aircraft to queue
    time_t CurrentTime = time(0);
    WaitingPlanes.push(CurrentTime);

    int WaitingTime = 0;

    //calculate its waiting time till it can land for its landing strip size
    if (Size == "Light")
    {
        WaitingTime = 30 - (WaitingPlanes.front() - LastLanding) + (QueueSize * 30);
    }
    else if (Size == "Big")
    {
        WaitingTime = 60 - (WaitingPlanes.front() - LastLanding) + (QueueSize * 60);
    }

    //log the waiting time for this aircraft
    logEvent("Aircraft waiting for the " + Size + " runway at " + ID + " and must wait " + to_string(WaitingTime) + " Seconds\n");
}

void LandingStrip::acceptLanding(string ID)
{
    //determine what type of strip it is landing at
    if (Size == "Light")
    {
        //store the time of the last landed aircraft
        time_t CurrentTime = time(0);
        LastLanding = CurrentTime;

        //log the time of this aircraft landing
        logEvent("Confirmed landing on " + Size + " runway at " + ID + "\n");
    }
    else if (Size == "Big")
    {
        //store the time of the last landed aircraft
        time_t CurrentTime = time(0);
        LastLanding = CurrentTime;

        //log the time of this aircraft landing
        logEvent("Confirmed landing on " + Size + " runway at " + ID + "\n");
    }
}

void LandingStrip::logEvent(string LogText)
{
    bool IsFileAlreadyOpen = true;

    //ofstream only allows a file to be open once it set a failbit if not. Therefor due to threading it is best to check encase a log is logged at the same time e.g. plane is requested at the same time a waiting plane lands
    while (IsFileAlreadyOpen)
    {
        try
        {
            ofstream log;
            log.open("flightLog.txt", fstream::app);
            log << LogText;
            log.close();

            //if the log sucessfully wrote exit
            IsFileAlreadyOpen = false;
        }
        catch (ofstream::failure e)
        {
            //if the file is already open by another thread to prevent the missing of a log event keep trying
            IsFileAlreadyOpen = true;
        }
    }
}

