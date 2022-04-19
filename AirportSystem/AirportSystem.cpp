// AirportSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include "Airport.h"
#include <thread>

list<Airport> Airports;
bool update = true;

void requestLanding(string RequestedAircraft, string RequestedAirport)
{
    bool Valid = false;
    //loop through to request the landing at the correct airport and strip
    for (auto& Airport : Airports)
    {
       if (Airport.ID == RequestedAirport)
       {
            Airport.requestLanding(RequestedAircraft);
            Valid = true;
       }
    }
    //print to the console if the input was correct
    if (Valid)
        cout << "Flight Requested.\n";
    else
        cout << "User input did not match the an aircraft and/or airport, please ensure the casing is correct.\n";
}

void StripQueue()
{
    //check waiting planes indefinitely until ended. Alternatively a sleep function could be use to make this be done on an interval
    while (update == true)
    {
        //loop through all landing strips at each airport
        for (auto& Airport : Airports)
        {
            for  (auto& strip : Airport.LandingStrips)
            {
                //if there is a plane waiting 
                if (!strip.WaitingPlanes.empty())
                {
                    strip.freeRunway(Airport.ID);
                }
            }
        }
    }
}

void UserInput()
{
    string input;
    bool exit = false;

    while (exit == false)
    {

        string RequestedAircraft;
        string RequestedAirport;

        //get user input from line
        getline(cin, input);
        istringstream iss(input);
        
        //loop through and extract the first and second word
        int c = 0;
        do
        {
            c++;
            string word;
            iss >> word;
            if (c == 1)
                RequestedAircraft = word;
            else
                RequestedAirport = word;
        } while (c < 2);

        c = 0;

        //if requested exit loop to exit program
        if (RequestedAircraft == "Exit")
            exit = true;
        else
        {
            //request landing from aircraft and airport
            requestLanding(RequestedAircraft, RequestedAirport);
        }
    }
}

void main()
{
    //initialise a list of default strip sizes for the airport
    list<string> Runways({ "Big", "Light" });
    
    //add three new airports to the list
    Airports.push_front(Airport("LGW", Runways));
    Airports.push_front(Airport("EMA", Runways));
    Airports.push_front(Airport("MAN", Runways));

    //thread the checking of the waiting airplanes so that user input can be taken simultaneously
    thread t(StripQueue);

    cout << "Please enter type of aircraft to land and the airport e.g (Light LGW) or to terminate (Exit).\n";

    //call user input loop
    UserInput();

    //exit update loops
    update = false;
    //close thread
    t.join();

    return;
}
