#ifndef MATCHRESULT_H
#define MATCHRESULT_H

#include <iostream>
#include <string>
#include <stdexcept>
#include "Fixture.h"
using namespace std;

class MatchResult
{
private:
    int resultID;
    int homeScore;
    int awayScore;
    string winner;
    bool resultRecorded;
    Fixture* fixture;

public:
    // Defaut Constructor
    MatchResult()
    {
        resultID = 0;
        fixture = nullptr;
        homeScore = 0;
        awayScore = 0;
        winner = "Not Determined";
        resultRecorded = false;
    }

    // Parameterized Constructor
    MatchResult(int id,  Fixture* f, int home, int away)
    {
        resultID = id;
        fixture = f;
        homeScore = 0;
        awayScore = 0;
        winner = "Not Determined";
        resultRecorded = false;
        

        recordResult(home, away);
    }

    // Getters and Setters
    int getResultID(){
        return resultID;
    }

    void setResultID(int id)
    {
        if (id > 0)
        {
            resultID = id;
        }
    }

    Fixture* getFixture(){
        return fixture;
    }

    int getHomeScore(){
        return homeScore;
    }

    int getAwayScore(){
        return awayScore;
    }

    // Will use recordResult instead of seperate setters

    string getWinner(){
        return winner;
    }

    bool isResultRecorded(){
        return resultRecorded;
    }

    // Record macth scores and determine the winner
    void recordResult(int home, int away)
    {
        if (home < 0 || away < 0)
        {
            throw invalid_argument("Match scores cannot be negative!");
        }

        homeScore = home;
        awayScore = away;

        if (homeScore > awayScore)
        {
            winner = "Home Team";
        }
        else if (awayScore > homeScore)
        {
            winner = "Away Team";
        }
        else
        {
            winner = "Draw";
        }
        
        resultRecorded = true;

        fixture->completeFixture(resultRecorded);
    }

    void displayResult()
    {
        cout << "\n===== Match Result =====" << endl;
        cout << "Result ID: " << resultID << endl;

        if (resultRecorded)
        {
            cout << "Home Score: " << homeScore << endl;
            cout << "Away Score: " << awayScore << endl;
            cout << "Winner: " << winner << endl;
        }
        else
        {
            cout << "Result has not been recorded yet." << endl;
        }
        cout << "========================" << endl; 
    }
    
};

#endif
