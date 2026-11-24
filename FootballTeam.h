#ifndef FOOTBALLTEAM_H
#define FOOTBALLTEAM_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Player.h"
#include "Coach.h"
#include "KPFLExceptions.h"
using namespace std;

class FootballTeam
{
private:
    string teamName;
    string parish;
    string registrationNumber;
    int maxSquadSize;
    string leagueStatus;   // Pending, Registered, Suspended

    // Composition: the team owns its players and coaches and deletes them
    vector<Player*> players;
    vector<Coach*> coaches;

    int matchesPlayed;
    int wins;
    int draws;
    int losses;
    int goalsFor;
    int goalsAgainst;

public:
    static const int WIN_POINTS = 3;
    static const int DRAW_POINTS = 1;
    static const int LOSS_POINTS = 0;

    // Parameterized Constructor
    FootballTeam(string teamName, string parish, string registrationNumber, int maxSquadSize)
    {
        if (teamName.empty())
        {
            throw invalid_argument("Team name cannot be empty!");
        }
        if (parish.empty())
        {
            throw invalid_argument("Parish cannot be empty!");
        }
        if (registrationNumber.empty())
        {
            throw invalid_argument("Registration number cannot be empty!");
        }
        if (maxSquadSize < 11)
        {
            throw invalid_argument("Squad size must allow at least 11 players!");
        }

        this->teamName = teamName;
        this->parish = parish;
        this->registrationNumber = registrationNumber;
        this->maxSquadSize = maxSquadSize;
        leagueStatus = "Pending";
        matchesPlayed = 0;
        wins = 0;
        draws = 0;
        losses = 0;
        goalsFor = 0;
        goalsAgainst = 0;
    }

    // Destructor: deletes the players and coaches the team owns
    ~FootballTeam()
    {
        for (int playerIndex = 0; playerIndex < (int)players.size(); playerIndex++)
        {
            Player* player = players[playerIndex];
            delete player;
        }
        for (int coachIndex = 0; coachIndex < (int)coaches.size(); coachIndex++)
        {
            Coach* coach = coaches[coachIndex];
            delete coach;
        }
    }

    // Getters and Setters
    string getTeamName()
    {
        return teamName;
    }

    void setTeamName(string teamName)
    {
        if (teamName.empty())
        {
            throw invalid_argument("Team name cannot be empty!");
        }
        this->teamName = teamName;

        // Keep each coach's team assignment up to date
        for (int coachIndex = 0; coachIndex < (int)coaches.size(); coachIndex++)
        {
            Coach* coach = coaches[coachIndex];
            coach->setTeamName(teamName);
        }
    }

    string getParish()
    {
        return parish;
    }

    void setParish(string parish)
    {
        if (parish.empty())
        {
            throw invalid_argument("Parish cannot be empty!");
        }
        this->parish = parish;
    }

    string getRegistrationNumber()
    {
        return registrationNumber;
    }

    int getMaxSquadSize()
    {
        return maxSquadSize;
    }

    void setMaxSquadSize(int maxSquadSize)
    {
        if (maxSquadSize < 11)
        {
            throw invalid_argument("Squad size must allow at least 11 players!");
        }
        if (maxSquadSize < getSquadSize())
        {
            throw invalid_argument("Squad size cannot be less than the number of players already on the team!");
        }
        this->maxSquadSize = maxSquadSize;
    }

    int getSquadSize()
    {
        return players.size();
    }

    string getLeagueStatus()
    {
        return leagueStatus;
    }

    void setLeagueStatus(string leagueStatus)
    {
        if (leagueStatus != "Pending" && leagueStatus != "Registered" && leagueStatus != "Suspended")
        {
            throw invalid_argument("League status must be Pending, Registered or Suspended!");
        }
        this->leagueStatus = leagueStatus;
    }

    vector<Player*> getPlayers()
    {
        return players;
    }

    vector<Coach*> getCoaches()
    {
        return coaches;
    }

    int getMatchesPlayed()
    {
        return matchesPlayed;
    }

    int getWins()
    {
        return wins;
    }

    int getDraws()
    {
        return draws;
    }

    int getLosses()
    {
        return losses;
    }

    int getGoalsFor()
    {
        return goalsFor;
    }

    int getGoalsAgainst()
    {
        return goalsAgainst;
    }

    int getGoalDifference()
    {
        return goalsFor - goalsAgainst;
    }

    // Win = 3, draw = 1, loss = 0
    int getPoints()
    {
        return wins * WIN_POINTS + draws * DRAW_POINTS + losses * LOSS_POINTS;
    }

    // Only registered teams can be assigned to fixtures
    bool isEligibleForFixture()
    {
        return leagueStatus == "Registered";
    }

    // Player functions
    void addPlayer(Player* player)
    {
        if (player == nullptr)
        {
            throw invalid_argument("Cannot add an empty player!");
        }
        if (getSquadSize() >= maxSquadSize)
        {
            throw SquadFullException(teamName + " already has the maximum of " +
                                     to_string(maxSquadSize) + " players.");
        }
        for (int currentIndex = 0; currentIndex < (int)players.size(); currentIndex++)
        {
            Player* current = players[currentIndex];
            if (current->getId() == player->getId())
            {
                throw DuplicateEntryException("Player " + player->getId() +
                                              " is already on " + teamName + ".");
            }
            if (current->getJerseyNum() == player->getJerseyNum())
            {
                throw DuplicateEntryException("Jersey number " + to_string(player->getJerseyNum()) +
                                              " is already taken on " + teamName + ".");
            }
        }
        players.push_back(player);
    }

    void removePlayer(string playerId)
    {
        for (int index = 0; index < (int)players.size(); index++)
        {
            if (players[index]->getId() == playerId)
            {
                delete players[index];
                players.erase(players.begin() + index);
                return;
            }
        }
        throw EntityNotFoundException("No player with ID " + playerId + " on " + teamName + ".");
    }

    Player* findPlayer(string playerId)
    {
        for (int playerIndex = 0; playerIndex < (int)players.size(); playerIndex++)
        {
            Player* player = players[playerIndex];
            if (player->getId() == playerId)
            {
                return player;
            }
        }
        return nullptr;
    }

    // Coach functions
    void addCoach(Coach* coach)
    {
        if (coach == nullptr)
        {
            throw invalid_argument("Cannot add an empty coach!");
        }
        if (findCoach(coach->getId()) != nullptr)
        {
            throw DuplicateEntryException("Coach " + coach->getId() +
                                          " is already on " + teamName + ".");
        }
        coach->setTeamName(teamName);
        coaches.push_back(coach);
    }

    void removeCoach(string coachId)
    {
        for (int index = 0; index < (int)coaches.size(); index++)
        {
            if (coaches[index]->getId() == coachId)
            {
                delete coaches[index];
                coaches.erase(coaches.begin() + index);
                return;
            }
        }
        throw EntityNotFoundException("No coach with ID " + coachId + " on " + teamName + ".");
    }

    Coach* findCoach(string coachId)
    {
        for (int coachIndex = 0; coachIndex < (int)coaches.size(); coachIndex++)
        {
            Coach* coach = coaches[coachIndex];
            if (coach->getId() == coachId)
            {
                return coach;
            }
        }
        return nullptr;
    }

    // Updates the team's record after a match
    void recordMatch(int goalsScored, int goalsConceded)
    {
        if (goalsScored < 0 || goalsConceded < 0)
        {
            throw NegativeValueException("Match scores cannot be negative.");
        }

        matchesPlayed++;
        goalsFor += goalsScored;
        goalsAgainst += goalsConceded;

        if (goalsScored > goalsConceded)
        {
            wins++;
        }
        else if (goalsScored == goalsConceded)
        {
            draws++;
        }
        else
        {
            losses++;
        }
    }

    // Display functions
    void displayTeam()
    {
        cout << "\nTeam: " << teamName << endl;
        cout << "Registration Number: " << registrationNumber << endl;
        cout << "Parish: " << parish << endl;
        cout << "League Status: " << leagueStatus << endl;
        cout << "Squad: " << getSquadSize() << " / " << maxSquadSize << " players" << endl;
        cout << "Coaching Staff: " << coaches.size() << endl;
        cout << "Record (W-D-L): " << wins << "-" << draws << "-" << losses << endl;
        cout << "Points: " << getPoints() << endl;
    }

    void displayPlayers()
    {
        cout << "\nPlayers for " << teamName << ":" << endl;
        if (players.empty())
        {
            cout << "No players registered." << endl;
            return;
        }
        for (int playerIndex = 0; playerIndex < (int)players.size(); playerIndex++)
        {
            Player* player = players[playerIndex];
            player->display();
            cout << endl;
        }
    }

    void displayCoaches()
    {
        cout << "\nCoaching staff for " << teamName << ":" << endl;
        if (coaches.empty())
        {
            cout << "No coaches registered." << endl;
            return;
        }
        for (int coachIndex = 0; coachIndex < (int)coaches.size(); coachIndex++)
        {
            Coach* coach = coaches[coachIndex];
            coach->display();
            cout << endl;
        }
    }
};

#endif
