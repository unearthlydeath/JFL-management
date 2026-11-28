
#ifndef FIXTURE_H
#define FIXTURE_H

#include <iostream>
#include <string>
#include "Stadium.h"
using namespace std;

class FootballTeam;

class Fixture 
{
private:
    int fixtureID;
    FootballTeam* homeTeam;
    FootballTeam* awayTeam;
    Stadium* stadium;
    string date;
    string time;
    string status;

public:
    // Default constructor
    Fixture() 
    {
        fixtureID = 0;
        homeTeam = nullptr;
        awayTeam = nullptr;
        stadium = nullptr;
        date = "";
        time = "";
        status = "Not Scheduled";
    }

    // Parameterized constructor
    Fixture(int id, FootballTeam* home, FootballTeam* away, Stadium* venue, string d, string t) 
    {
        fixtureID = id;
        homeTeam = home;
        awayTeam = away;
        stadium = venue;
        date = d;
        time = t;
        status = "Not Scheduled";
    }

    // Getters and Setters
    int getFixtureID()
    {
        return fixtureID;
    }

    void setFixtureID(int id)
    {
        if (id > 0)
        {
            fixtureID = id;
        }    
    }

    FootballTeam* getHomeTeam(){
        return homeTeam;
    }

    void setHomeTeam(FootballTeam* home)
    {
        if (home != nullptr && home != awayTeam)
        {
            homeTeam = home;
        }  
    }

    FootballTeam* getAwayTeam(){
        return awayTeam;
    }

    void setAwayTeam(FootballTeam* away)
    {
        if (away != nullptr && away != homeTeam)
        {
            awayTeam = away;
        }
    }

    Stadium* getStadium(){
        return stadium;
    }

    void setStadium(Stadium* venue)
    {
        if (venue != nullptr)
        {
            stadium = venue;
        }  
    }

    string getDate(){
        return date;
    }

    void setDate(string d)
    {
        if (!d.empty())
        {
            date = d;
        }
    }

    string getTime(){
        return time;
    }

    void setTime(string t)
    {
        if (!t.empty())
        {
            time = t;
        }
    }

    string getStatus(){
        return status;
    }

    void setStatus(string s)
    {
        if (s == "Not Scheduled" ||
            s == "Scheduled" ||
            s == "In Progress")
        {
            status = s;
        }   
    }


    // Display fixture information
    void displayFixture() 
    {
        cout << "\n===== Fixture Information =====" << endl;
        cout << "Fixture ID: " << fixtureID << endl;

        if (homeTeam != nullptr) {
            cout << "Home Team: Assigned" << endl;  //Implement home team pointer here
        }
        else {
            cout << "Home Team: Not Assigned" << endl;
        }

        if (awayTeam != nullptr) {
            cout << "Away Team: Assigned" << endl;  //Implement away team pointer here
        }
        else {
            cout << "Away Team: Not Assigned" << endl;
        }

        if (stadium != nullptr) 
        {
            cout << "Stadium: " << stadium->getName() << endl;
        }
        else 
        {
            cout << "Stadium: Not Assigned" << endl;
        }

        cout << "Date: " << date << endl;
        cout << "Time: " << time << endl;
        cout << "Status: " << status << endl;
        cout << "===============================" << endl;
    }


    // Check if fixture has its required information
    bool isReady() 
    {
        return fixtureID > 0 &&
               homeTeam != nullptr &&
               awayTeam != nullptr &&
               homeTeam != awayTeam &&
               stadium != nullptr &&
               !date.empty() &&
               !time.empty();
    }
    // All the conditions must be true for isReady() to return true

    
    // Schedule fixture
    void scheduleFixture() 
    {
        if (isReady()) 
        {
            status = "Scheduled";
            cout << "Fixture scheduled successfully!" << endl;
        }
        else 
        {
            cout << "Cannot schedule fixture, missing or invalid information!" << endl;
        }
    }

    void completeFixture(bool validResult)
    {
        if (!validResult)
        {
            cout << "Fixture cannot be completed without a valid result!" << endl;
            return;
        }

        if (status != "In Progress")
        {
            cout << "Fixture must be in progress before completion!" << endl;
            return;
        }

        status = "Completed";
        cout << "Fixture completed successfully!" << endl; 
    }

};

#endif
