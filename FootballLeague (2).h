#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include "FootballTeam.h"
#include "Commissioner.h"
#include "Official.h"
#include "Stadium.h"
#include "Fixture.h"
#include "MatchResult.h"
#include "KPFLExceptions.h"
using namespace std;

class FootballLeague
{
private:
    string leagueName;
    string season;

    // Composition: everything added to the league must be created with new,
    // and the league deletes it in the destructor
    Commissioner* commissioner;
    vector<FootballTeam*> teams;
    vector<Stadium*> stadiums;
    vector<Official*> officials;
    vector<Fixture*> fixtures;
    vector<MatchResult*> results;

    // Which official is assigned to which fixture (same index in both vectors)
    vector<Official*> assignedOfficials;
    vector<Fixture*> assignedFixtures;

    // Returns the text in lowercase so searches ignore capital letters
    string toLowerCase(string text)
    {
        for (int index = 0; index < (int)text.length(); index++)
        {
            text[index] = tolower(text[index]);
        }
        return text;
    }

    // Returns true if the first team should be placed below the second team in the standings
    bool ranksBelow(FootballTeam* first, FootballTeam* second)
    {
        if (first->getPoints() != second->getPoints())
        {
            return first->getPoints() < second->getPoints();
        }
        if (first->getGoalDifference() != second->getGoalDifference())
        {
            return first->getGoalDifference() < second->getGoalDifference();
        }
        if (first->getGoalsFor() != second->getGoalsFor())
        {
            return first->getGoalsFor() < second->getGoalsFor();
        }
        return first->getTeamName() > second->getTeamName();
    }

    bool containsFixture(Fixture* fixture)
    {
        for (int currentIndex = 0; currentIndex < (int)fixtures.size(); currentIndex++)
        {
            Fixture* current = fixtures[currentIndex];
            if (current == fixture)
            {
                return true;
            }
        }
        return false;
    }

public:
    // Parameterized Constructor
    FootballLeague(string leagueName, string season)
    {
        if (leagueName.empty() || season.empty())
        {
            throw invalid_argument("League name and season cannot be empty!");
        }
        this->leagueName = leagueName;
        this->season = season;
        commissioner = nullptr;
    }

    // Destructor: deletes everything the league owns
    ~FootballLeague()
    {
        delete commissioner;
        for (int stadiumIndex = 0; stadiumIndex < (int)stadiums.size(); stadiumIndex++)
        {
            delete stadiums[stadiumIndex];
        }
        for (int officialIndex = 0; officialIndex < (int)officials.size(); officialIndex++)
        {
            delete officials[officialIndex];
        }
        for (int fixtureIndex = 0; fixtureIndex < (int)fixtures.size(); fixtureIndex++)
        {
            delete fixtures[fixtureIndex];
        }
        for (int teamIndex = 0; teamIndex < (int)teams.size(); teamIndex++)
        {
            FootballTeam* team = teams[teamIndex];
            delete team;
        }
        for (int resultIndex = 0; resultIndex < (int)results.size(); resultIndex++)
        {
            MatchResult* result = results[resultIndex];
            delete result;
        }
    }

    // Getters and Setters
    string getLeagueName()
    {
        return leagueName;
    }

    string getSeason()
    {
        return season;
    }

    Commissioner* getCommissioner()
    {
        return commissioner;
    }

    void setCommissioner(Commissioner* commissioner)
    {
        if (commissioner == nullptr)
        {
            throw invalid_argument("Commissioner cannot be empty!");
        }
        if (this->commissioner != commissioner)
        {
            delete this->commissioner;   // the old commissioner is replaced
        }
        this->commissioner = commissioner;
    }

    vector<FootballTeam*> getTeams()
    {
        return teams;
    }

    vector<Stadium*> getStadiums()
    {
        return stadiums;
    }

    vector<Fixture*> getFixtures()
    {
        return fixtures;
    }

    vector<Official*> getOfficials()
    {
        return officials;
    }

    vector<MatchResult*> getResults()
    {
        return results;
    }

    // Team functions
    void registerTeam(FootballTeam* team)
    {
        if (team == nullptr)
        {
            throw invalid_argument("Cannot register an empty team!");
        }
        if (findTeam(team->getRegistrationNumber()) != nullptr)
        {
            throw DuplicateEntryException("A team with registration number " +
                                          team->getRegistrationNumber() + " already exists.");
        }
        teams.push_back(team);
    }

    void removeTeam(string registrationNumber)
    {
        for (int index = 0; index < (int)teams.size(); index++)
        {
            FootballTeam* team = teams[index];
            if (team->getRegistrationNumber() != registrationNumber)
            {
                continue;
            }
            for (int fixtureIndex = 0; fixtureIndex < (int)fixtures.size(); fixtureIndex++)
            {
                Fixture* fixture = fixtures[fixtureIndex];
                if (fixture->getHomeTeam() == team || fixture->getAwayTeam() == team)
                {
                    throw invalid_argument("Cannot remove " + team->getTeamName() +
                                           " because it has scheduled fixtures!");
                }
            }
            delete team;
            teams.erase(teams.begin() + index);
            return;
        }
        throw EntityNotFoundException("No team with registration number " + registrationNumber + ".");
    }

    FootballTeam* findTeam(string registrationNumber)
    {
        for (int teamIndex = 0; teamIndex < (int)teams.size(); teamIndex++)
        {
            FootballTeam* team = teams[teamIndex];
            if (team->getRegistrationNumber() == registrationNumber)
            {
                return team;
            }
        }
        return nullptr;
    }

    vector<FootballTeam*> searchTeamsByName(string searchText)
    {
        vector<FootballTeam*> matches;
        string lowerSearchText = toLowerCase(searchText);

        for (int teamIndex = 0; teamIndex < (int)teams.size(); teamIndex++)
        {
            FootballTeam* team = teams[teamIndex];
            if (toLowerCase(team->getTeamName()).find(lowerSearchText) != string::npos)
            {
                matches.push_back(team);
            }
        }
        return matches;
    }

    void approveTeam(string registrationNumber)
    {
        if (commissioner == nullptr)
        {
            throw invalid_argument("A league commissioner must be set before teams can be approved!");
        }
        FootballTeam* team = findTeam(registrationNumber);
        if (team == nullptr)
        {
            throw EntityNotFoundException("No team with registration number " + registrationNumber + ".");
        }
        if (team->getLeagueStatus() == "Registered")
        {
            throw DuplicateEntryException(team->getTeamName() + " is already registered.");
        }
        team->setLeagueStatus("Registered");
        commissioner->approveTeam(team->getTeamName());
    }

    void suspendTeam(string registrationNumber)
    {
        if (commissioner == nullptr)
        {
            throw invalid_argument("A league commissioner must be set before teams can be suspended!");
        }
        FootballTeam* team = findTeam(registrationNumber);
        if (team == nullptr)
        {
            throw EntityNotFoundException("No team with registration number " + registrationNumber + ".");
        }
        team->setLeagueStatus("Suspended");
        cout << commissioner->getName() << " suspended " << team->getTeamName() << "." << endl;
    }

    void displayAllTeams()
    {
        cout << "\n" << leagueName << " " << season << " - Registered Teams" << endl;
        if (teams.empty())
        {
            cout << "No teams in the league." << endl;
            return;
        }
        for (int teamIndex = 0; teamIndex < (int)teams.size(); teamIndex++)
        {
            FootballTeam* team = teams[teamIndex];
            team->displayTeam();
        }
    }

    // Stadium and official functions
    void addStadium(Stadium* stadium)
    {
        if (stadium == nullptr)
        {
            throw invalid_argument("Cannot add an empty stadium!");
        }
        for (int currentIndex = 0; currentIndex < (int)stadiums.size(); currentIndex++)
        {
            Stadium* current = stadiums[currentIndex];
            if (current == stadium)
            {
                throw DuplicateEntryException("This stadium is already in the league.");
            }
        }
        stadiums.push_back(stadium);
    }

    void addOfficial(Official* official)
    {
        if (official == nullptr)
        {
            throw invalid_argument("Cannot add an empty match official!");
        }
        if (findOfficial(official->getId()) != nullptr)
        {
            throw DuplicateEntryException("Match official " + official->getId() +
                                          " is already registered.");
        }
        officials.push_back(official);
    }

    Stadium* findStadium(int stadiumId)
    {
        for (int stadiumIndex = 0; stadiumIndex < (int)stadiums.size(); stadiumIndex++)
        {
            if (stadiums[stadiumIndex]->getStadiumID() == stadiumId)
            {
                return stadiums[stadiumIndex];
            }
        }
        return nullptr;
    }

    Fixture* findFixture(int fixtureId)
    {
        for (int fixtureIndex = 0; fixtureIndex < (int)fixtures.size(); fixtureIndex++)
        {
            if (fixtures[fixtureIndex]->getFixtureID() == fixtureId)
            {
                return fixtures[fixtureIndex];
            }
        }
        return nullptr;
    }

    Official* findOfficial(string officialId)
    {
        for (int officialIndex = 0; officialIndex < (int)officials.size(); officialIndex++)
        {
            Official* official = officials[officialIndex];
            if (official->getId() == officialId)
            {
                return official;
            }
        }
        return nullptr;
    }

    // Fixture functions
    // Business rules: only registered teams can be scheduled, and a team
    // cannot play two fixtures on the same day and time
    void scheduleFixture(Fixture* fixture)
    {
        if (fixture == nullptr)
        {
            throw invalid_argument("Cannot schedule an empty fixture!");
        }
        if (containsFixture(fixture))
        {
            throw DuplicateEntryException("This fixture is already scheduled.");
        }

        FootballTeam* homeTeam = fixture->getHomeTeam();
        FootballTeam* awayTeam = fixture->getAwayTeam();

        if (homeTeam == nullptr || awayTeam == nullptr)
        {
            throw invalid_argument("A fixture needs both a home team and an away team!");
        }
        if (homeTeam == awayTeam)
        {
            throw invalid_argument("A team cannot play against itself!");
        }
        if (findTeam(homeTeam->getRegistrationNumber()) == nullptr ||
            findTeam(awayTeam->getRegistrationNumber()) == nullptr)
        {
            throw TeamNotEligibleException("Both teams must belong to the " + leagueName + ".");
        }
        if (!homeTeam->isEligibleForFixture())
        {
            throw TeamNotEligibleException(homeTeam->getTeamName() + " is " +
                                           homeTeam->getLeagueStatus() + " and cannot be assigned to a fixture.");
        }
        if (!awayTeam->isEligibleForFixture())
        {
            throw TeamNotEligibleException(awayTeam->getTeamName() + " is " +
                                           awayTeam->getLeagueStatus() + " and cannot be assigned to a fixture.");
        }

        for (int existingIndex = 0; existingIndex < (int)fixtures.size(); existingIndex++)
        {
            Fixture* existing = fixtures[existingIndex];
            if (existing->getDate() != fixture->getDate() || existing->getTime() != fixture->getTime())
            {
                continue;
            }
            if (existing->getHomeTeam() == homeTeam || existing->getAwayTeam() == homeTeam)
            {
                throw SchedulingConflictException(homeTeam->getTeamName() + " already has a fixture on " +
                                                  fixture->getDate() + " at " + fixture->getTime() + ".");
            }
            if (existing->getHomeTeam() == awayTeam || existing->getAwayTeam() == awayTeam)
            {
                throw SchedulingConflictException(awayTeam->getTeamName() + " already has a fixture on " +
                                                  fixture->getDate() + " at " + fixture->getTime() + ".");
            }
        }

        fixture->scheduleFixture();
        if (fixture->getStatus() != "Scheduled")
        {
            throw invalid_argument("Fixture is missing its ID, stadium, date or time!");
        }
        fixtures.push_back(fixture);
    }

    // Business rule: a match official cannot be assigned to conflicting fixtures
    void assignOfficial(Fixture* fixture, Official* official)
    {
        if (fixture == nullptr || official == nullptr)
        {
            throw invalid_argument("Fixture and match official are both required!");
        }
        if (!containsFixture(fixture))
        {
            throw EntityNotFoundException("The fixture must be scheduled before officials are assigned.");
        }
        if (findOfficial(official->getId()) == nullptr)
        {
            throw EntityNotFoundException("Match official " + official->getId() +
                                          " is not registered with the league.");
        }
        if (!official->isAvailable())
        {
            throw SchedulingConflictException(official->getName() + " is not available to officiate.");
        }

        for (int index = 0; index < (int)assignedOfficials.size(); index++)
        {
            if (assignedOfficials[index] != official)
            {
                continue;
            }
            Fixture* existing = assignedFixtures[index];
            if (existing == fixture)
            {
                throw DuplicateEntryException(official->getName() + " is already assigned to this fixture.");
            }
            if (existing->getDate() == fixture->getDate() && existing->getTime() == fixture->getTime())
            {
                throw SchedulingConflictException(official->getName() + " is already assigned to a fixture on " +
                                                  fixture->getDate() + " at " + fixture->getTime() + ".");
            }
        }

        assignedOfficials.push_back(official);
        assignedFixtures.push_back(fixture);
    }

    vector<Official*> getAssignedOfficials()
    {
        return assignedOfficials;
    }

    vector<Fixture*> getAssignedFixtures()
    {
        return assignedFixtures;
    }

    vector<Official*> getOfficialsForFixture(Fixture* fixture)
    {
        vector<Official*> matches;
        for (int index = 0; index < (int)assignedFixtures.size(); index++)
        {
            if (assignedFixtures[index] == fixture)
            {
                matches.push_back(assignedOfficials[index]);
            }
        }
        return matches;
    }

    // Creates the MatchResult (which completes the fixture), then updates both teams
    // Business rule: a fixture cannot be completed until a valid result has been recorded
    void recordResult(Fixture* fixture, int resultId, int homeScore, int awayScore)
    {
        if (fixture == nullptr)
        {
            throw invalid_argument("Fixture is required!");
        }
        if (!containsFixture(fixture))
        {
            throw EntityNotFoundException("This fixture is not scheduled in the league.");
        }
        if (homeScore < 0 || awayScore < 0)
        {
            throw NegativeValueException("Match scores cannot be negative.");
        }
        if (fixture->getStatus() == "Completed")
        {
            throw DuplicateEntryException("A result has already been recorded for this fixture.");
        }
        if (fixture->getStatus() != "In Progress")
        {
            throw invalid_argument("The fixture must be In Progress before a result can be recorded!");
        }

        results.push_back(new MatchResult(resultId, fixture, homeScore, awayScore));
        fixture->getHomeTeam()->recordMatch(homeScore, awayScore);
        fixture->getAwayTeam()->recordMatch(awayScore, homeScore);
    }

    // Restore functions: used only by FileManager when loading saved data.
    // They skip the scheduling checks because the data was already checked
    // when it was first entered.
    void restoreFixture(Fixture* fixture, string status, int resultId, int homeScore, int awayScore)
    {
        if (fixture == nullptr || fixture->getHomeTeam() == nullptr || fixture->getAwayTeam() == nullptr)
        {
            throw invalid_argument("Saved fixture is missing its teams!");
        }
        fixture->scheduleFixture();
        fixtures.push_back(fixture);

        if (status == "In Progress" || status == "Completed")
        {
            fixture->setStatus("In Progress");
        }
        if (status == "Completed")
        {
            results.push_back(new MatchResult(resultId, fixture, homeScore, awayScore));
            fixture->getHomeTeam()->recordMatch(homeScore, awayScore);
            fixture->getAwayTeam()->recordMatch(awayScore, homeScore);
        }
    }

    void restoreOfficialAssignment(Official* official, Fixture* fixture)
    {
        if (official == nullptr || fixture == nullptr)
        {
            throw invalid_argument("Saved assignment is missing its official or fixture!");
        }
        assignedOfficials.push_back(official);
        assignedFixtures.push_back(fixture);
    }

    // Standings functions
    // Sorted by points, then goal difference, then goals scored, then name
    vector<FootballTeam*> getStandings()
    {
        vector<FootballTeam*> standings = teams;

        // Bubble sort: swap neighbouring teams that are in the wrong order
        for (int pass = 0; pass < (int)standings.size() - 1; pass++)
        {
            for (int index = 0; index < (int)standings.size() - 1 - pass; index++)
            {
                if (ranksBelow(standings[index], standings[index + 1]))
                {
                    FootballTeam* temp = standings[index];
                    standings[index] = standings[index + 1];
                    standings[index + 1] = temp;
                }
            }
        }

        return standings;
    }

    void displayStandings()
    {
        vector<FootballTeam*> standings = getStandings();

        cout << "\n" << leagueName << " " << season << " - League Standings" << endl;
        cout << left << setw(5) << "Pos" << setw(25) << "Team"
             << right << setw(4) << "P" << setw(4) << "W" << setw(4) << "D" << setw(4) << "L"
             << setw(5) << "GF" << setw(5) << "GA" << setw(5) << "GD" << setw(6) << "Pts" << endl;

        int position = 1;
        for (int teamIndex = 0; teamIndex < (int)standings.size(); teamIndex++)
        {
            FootballTeam* team = standings[teamIndex];
            cout << left << setw(5) << position << setw(25) << team->getTeamName()
                 << right << setw(4) << team->getMatchesPlayed()
                 << setw(4) << team->getWins() << setw(4) << team->getDraws() << setw(4) << team->getLosses()
                 << setw(5) << team->getGoalsFor() << setw(5) << team->getGoalsAgainst()
                 << setw(5) << team->getGoalDifference() << setw(6) << team->getPoints() << endl;
            position++;
        }
    }
};

#endif
