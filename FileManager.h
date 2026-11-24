#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "FootballLeague.h"
#include "Spectator.h"
#include "Ticket.h"
#include "Product.h"
#include "Merchandise.h"
#include "FoodItem.h"
using namespace std;

// Saves and loads all system data using sequential access text files.
// Each record is one line, with its fields separated by '|'.
class FileManager
{
private:
    FootballLeague* league;
    vector<Spectator*>* spectators;
    vector<Ticket*>* tickets;
    vector<Product*>* products;

    // Splits one line of a file into its fields using '|' as the separator
    vector<string> splitLine(string line)
    {
        vector<string> fields;
        string field = "";

        for (int index = 0; index < (int)line.length(); index++)
        {
            if (line[index] == '|')
            {
                fields.push_back(field);
                field = "";
            }
            else
            {
                field += line[index];
            }
        }
        fields.push_back(field);
        return fields;
    }

    // Opens a file for writing and throws an exception if it cannot be opened
    void openForWriting(ofstream& outFile, string fileName)
    {
        outFile.open(fileName);
        if (!outFile)
        {
            throw runtime_error("Could not open " + fileName + " for saving!");
        }
    }

    // Finds the result recorded for a fixture, or nullptr if it has none
    MatchResult* findResult(Fixture* fixture)
    {
        vector<MatchResult*> results = league->getResults();
        for (int resultIndex = 0; resultIndex < (int)results.size(); resultIndex++)
        {
            if (results[resultIndex]->getFixture() == fixture)
            {
                return results[resultIndex];
            }
        }
        return nullptr;
    }

    // Save functions

    void saveCommissioner()
    {
        ofstream outFile;
        openForWriting(outFile, "commissioner.txt");

        Commissioner* commissioner = league->getCommissioner();
        if (commissioner != nullptr)
        {
            outFile << commissioner->getId() << "|" << commissioner->getName() << "|"
                    << commissioner->getAge() << "|" << commissioner->getGender() << "|"
                    << commissioner->getTitle() << endl;
        }
        outFile.close();
    }

    void saveStadiums()
    {
        ofstream outFile;
        openForWriting(outFile, "stadiums.txt");

        vector<Stadium*> stadiums = league->getStadiums();
        for (int stadiumIndex = 0; stadiumIndex < (int)stadiums.size(); stadiumIndex++)
        {
            Stadium* stadium = stadiums[stadiumIndex];
            outFile << stadium->getStadiumID() << "|" << stadium->getName() << "|"
                    << stadium->getLocation() << "|" << stadium->getSeatingCapacity() << "|"
                    << stadium->getFieldCondition() << "|" << stadium->getTicketPrice() << endl;
        }
        outFile.close();
    }

    void saveOfficials()
    {
        ofstream outFile;
        openForWriting(outFile, "officials.txt");

        vector<Official*> officials = league->getOfficials();
        for (int officialIndex = 0; officialIndex < (int)officials.size(); officialIndex++)
        {
            Official* official = officials[officialIndex];
            outFile << official->getId() << "|" << official->getName() << "|"
                    << official->getAge() << "|" << official->getGender() << "|"
                    << official->getOfficiatingRole() << "|" << official->getRank() << "|"
                    << official->isAvailable() << endl;
        }
        outFile.close();
    }

    // Saves teams, plus their players and coaches in separate files
    void saveTeams()
    {
        ofstream teamFile, playerFile, coachFile;
        openForWriting(teamFile, "teams.txt");
        openForWriting(playerFile, "players.txt");
        openForWriting(coachFile, "coaches.txt");

        vector<FootballTeam*> teams = league->getTeams();
        for (int teamIndex = 0; teamIndex < (int)teams.size(); teamIndex++)
        {
            FootballTeam* team = teams[teamIndex];
            teamFile << team->getRegistrationNumber() << "|" << team->getTeamName() << "|"
                     << team->getParish() << "|" << team->getMaxSquadSize() << "|"
                     << team->getLeagueStatus() << endl;

            vector<Player*> players = team->getPlayers();
            for (int playerIndex = 0; playerIndex < (int)players.size(); playerIndex++)
            {
                Player* player = players[playerIndex];
                playerFile << team->getRegistrationNumber() << "|" << player->getId() << "|"
                           << player->getName() << "|" << player->getAge() << "|"
                           << player->getGender() << "|" << player->getPosition() << "|"
                           << player->getJerseyNum() << "|" << player->getGoals() << "|"
                           << player->getStatus() << endl;
            }

            vector<Coach*> coaches = team->getCoaches();
            for (int coachIndex = 0; coachIndex < (int)coaches.size(); coachIndex++)
            {
                Coach* coach = coaches[coachIndex];
                coachFile << team->getRegistrationNumber() << "|" << coach->getId() << "|"
                          << coach->getName() << "|" << coach->getAge() << "|"
                          << coach->getGender() << "|" << coach->getQualification() << "|"
                          << coach->getRole() << endl;
            }
        }
        teamFile.close();
        playerFile.close();
        coachFile.close();
    }

    // Saves fixtures with their results, plus which officials are assigned to them
    void saveFixtures()
    {
        ofstream fixtureFile, assignmentFile;
        openForWriting(fixtureFile, "fixtures.txt");
        openForWriting(assignmentFile, "assignments.txt");

        vector<Fixture*> fixtures = league->getFixtures();
        for (int fixtureIndex = 0; fixtureIndex < (int)fixtures.size(); fixtureIndex++)
        {
            Fixture* fixture = fixtures[fixtureIndex];
            MatchResult* result = findResult(fixture);

            int resultId = 0, homeScore = 0, awayScore = 0;
            if (result != nullptr)
            {
                resultId = result->getResultID();
                homeScore = result->getHomeScore();
                awayScore = result->getAwayScore();
            }

            fixtureFile << fixture->getFixtureID() << "|"
                        << fixture->getHomeTeam()->getRegistrationNumber() << "|"
                        << fixture->getAwayTeam()->getRegistrationNumber() << "|"
                        << fixture->getStadium()->getStadiumID() << "|"
                        << fixture->getDate() << "|" << fixture->getTime() << "|"
                        << fixture->getStatus() << "|" << resultId << "|"
                        << homeScore << "|" << awayScore << endl;
        }

        vector<Official*> assignedOfficials = league->getAssignedOfficials();
        vector<Fixture*> assignedFixtures = league->getAssignedFixtures();
        for (int index = 0; index < (int)assignedOfficials.size(); index++)
        {
            assignmentFile << assignedOfficials[index]->getId() << "|"
                           << assignedFixtures[index]->getFixtureID() << endl;
        }
        fixtureFile.close();
        assignmentFile.close();
    }

    void saveSpectators()
    {
        ofstream outFile;
        openForWriting(outFile, "spectators.txt");

        for (int spectatorIndex = 0; spectatorIndex < (int)spectators->size(); spectatorIndex++)
        {
            Spectator* spectator = (*spectators)[spectatorIndex];
            outFile << spectator->getId() << "|" << spectator->getName() << "|"
                    << spectator->getAge() << "|" << spectator->getGender() << "|"
                    << spectator->getTicketsPurchased() << "|" << spectator->getTotalSpent() << endl;
        }
        outFile.close();
    }

    void saveTickets()
    {
        ofstream outFile;
        openForWriting(outFile, "tickets.txt");

        for (int ticketIndex = 0; ticketIndex < (int)tickets->size(); ticketIndex++)
        {
            Ticket* ticket = (*tickets)[ticketIndex];
            int fixtureId = 0;
            if (ticket->getFixture() != nullptr)
            {
                fixtureId = ticket->getFixture()->getFixtureID();
            }
            outFile << ticket->getTicketID() << "|" << fixtureId << "|"
                    << ticket->getCategory() << "|" << ticket->getPrice() << "|"
                    << ticket->isSold() << endl;
        }
        outFile.close();
    }

    // Merchandise lines start with M and food lines start with F,
    // so the loader knows which class to create
    void saveProducts()
    {
        ofstream outFile;
        openForWriting(outFile, "products.txt");

        for (int productIndex = 0; productIndex < (int)products->size(); productIndex++)
        {
            Product* product = (*products)[productIndex];
            Merchandise* merchandise = dynamic_cast<Merchandise*>(product);
            FoodItem* foodItem = dynamic_cast<FoodItem*>(product);

            if (merchandise != nullptr)
            {
                outFile << "M|" << merchandise->getItemId() << "|" << merchandise->getItemName() << "|"
                        << merchandise->getItemType() << "|" << merchandise->getTeam() << "|"
                        << merchandise->getPrice() << "|" << merchandise->getInventory() << endl;
            }
            else if (foodItem != nullptr)
            {
                outFile << "F|" << foodItem->getItemId() << "|" << foodItem->getItemName() << "|"
                        << foodItem->getItemType() << "||"
                        << foodItem->getPrice() << "|" << foodItem->getInventory() << endl;
            }
        }
        outFile.close();
    }

    // Load functions
    // A missing file is not an error: it just means nothing was saved yet.
    // A damaged line is skipped with a warning so the rest of the file still loads.

    void loadCommissioner()
    {
        ifstream inFile("commissioner.txt");
        string line;
        if (inFile && getline(inFile, line) && !line.empty())
        {
            vector<string> fields = splitLine(line);
            if (fields.size() == 5)
            {
                league->setCommissioner(new Commissioner(fields[0], fields[1], stoi(fields[2]),
                                                         fields[3][0], fields[4]));
            }
        }
        inFile.close();
    }

    void loadStadiums()
    {
        ifstream inFile("stadiums.txt");
        string line;
        while (getline(inFile, line))
        {
            try
            {
                vector<string> fields = splitLine(line);
                if (fields.size() != 6)
                {
                    throw runtime_error("wrong number of fields");
                }
                league->addStadium(new Stadium(stoi(fields[0]), fields[1], fields[2],
                                               stoi(fields[3]), fields[4], stod(fields[5])));
            }
            catch (exception& e)
            {
                cout << "Skipped a stadium record: " << e.what() << endl;
            }
        }
        inFile.close();
    }

    void loadOfficials()
    {
        ifstream inFile("officials.txt");
        string line;
        while (getline(inFile, line))
        {
            try
            {
                vector<string> fields = splitLine(line);
                if (fields.size() != 7)
                {
                    throw runtime_error("wrong number of fields");
                }
                Official* official = new Official(fields[0], fields[1], stoi(fields[2]),
                                                  fields[3][0], fields[4], fields[5]);
                official->setAvailable(fields[6] == "1");
                league->addOfficial(official);
            }
            catch (exception& e)
            {
                cout << "Skipped an official record: " << e.what() << endl;
            }
        }
        inFile.close();
    }

    void loadTeams()
    {
        ifstream inFile("teams.txt");
        string line;
        while (getline(inFile, line))
        {
            try
            {
                vector<string> fields = splitLine(line);
                if (fields.size() != 5)
                {
                    throw runtime_error("wrong number of fields");
                }
                FootballTeam* team = new FootballTeam(fields[1], fields[2], fields[0], stoi(fields[3]));
                team->setLeagueStatus(fields[4]);
                league->registerTeam(team);
            }
            catch (exception& e)
            {
                cout << "Skipped a team record: " << e.what() << endl;
            }
        }
        inFile.close();
    }

    void loadPlayers()
    {
        ifstream inFile("players.txt");
        string line;
        while (getline(inFile, line))
        {
            try
            {
                vector<string> fields = splitLine(line);
                if (fields.size() != 9)
                {
                    throw runtime_error("wrong number of fields");
                }
                FootballTeam* team = league->findTeam(fields[0]);
                if (team == nullptr)
                {
                    throw runtime_error("team " + fields[0] + " not found");
                }
                Player* player = new Player(fields[1], fields[2], stoi(fields[3]), fields[4][0],
                                            fields[5], stoi(fields[6]), fields[8]);
                player->addGoals(stoi(fields[7]));
                team->addPlayer(player);
            }
            catch (exception& e)
            {
                cout << "Skipped a player record: " << e.what() << endl;
            }
        }
        inFile.close();
    }

    void loadCoaches()
    {
        ifstream inFile("coaches.txt");
        string line;
        while (getline(inFile, line))
        {
            try
            {
                vector<string> fields = splitLine(line);
                if (fields.size() != 7)
                {
                    throw runtime_error("wrong number of fields");
                }
                FootballTeam* team = league->findTeam(fields[0]);
                if (team == nullptr)
                {
                    throw runtime_error("team " + fields[0] + " not found");
                }
                team->addCoach(new Coach(fields[1], fields[2], stoi(fields[3]), fields[4][0],
                                         fields[5], fields[6]));
            }
            catch (exception& e)
            {
                cout << "Skipped a coach record: " << e.what() << endl;
            }
        }
        inFile.close();
    }

    void loadFixtures()
    {
        ifstream inFile("fixtures.txt");
        string line;
        while (getline(inFile, line))
        {
            try
            {
                vector<string> fields = splitLine(line);
                if (fields.size() != 10)
                {
                    throw runtime_error("wrong number of fields");
                }
                FootballTeam* homeTeam = league->findTeam(fields[1]);
                FootballTeam* awayTeam = league->findTeam(fields[2]);
                Stadium* stadium = league->findStadium(stoi(fields[3]));
                if (homeTeam == nullptr || awayTeam == nullptr || stadium == nullptr)
                {
                    throw runtime_error("team or stadium not found");
                }
                Fixture* fixture = new Fixture(stoi(fields[0]), homeTeam, awayTeam, stadium,
                                               fields[4], fields[5]);
                league->restoreFixture(fixture, fields[6], stoi(fields[7]),
                                       stoi(fields[8]), stoi(fields[9]));
            }
            catch (exception& e)
            {
                cout << "Skipped a fixture record: " << e.what() << endl;
            }
        }
        inFile.close();
    }

    void loadAssignments()
    {
        ifstream inFile("assignments.txt");
        string line;
        while (getline(inFile, line))
        {
            try
            {
                vector<string> fields = splitLine(line);
                if (fields.size() != 2)
                {
                    throw runtime_error("wrong number of fields");
                }
                league->restoreOfficialAssignment(league->findOfficial(fields[0]),
                                                  league->findFixture(stoi(fields[1])));
            }
            catch (exception& e)
            {
                cout << "Skipped an official assignment: " << e.what() << endl;
            }
        }
        inFile.close();
    }

    void loadSpectators()
    {
        ifstream inFile("spectators.txt");
        string line;
        while (getline(inFile, line))
        {
            try
            {
                vector<string> fields = splitLine(line);
                if (fields.size() != 6)
                {
                    throw runtime_error("wrong number of fields");
                }
                Spectator* spectator = new Spectator(fields[0], fields[1], stoi(fields[2]), fields[3][0]);
                spectator->recordPurchase(stoi(fields[4]), stod(fields[5]));
                spectators->push_back(spectator);
            }
            catch (exception& e)
            {
                cout << "Skipped a spectator record: " << e.what() << endl;
            }
        }
        inFile.close();
    }

    // Selling a saved sold ticket again also puts its seat back in the stadium's occupancy
    void loadTickets()
    {
        ifstream inFile("tickets.txt");
        string line;
        while (getline(inFile, line))
        {
            try
            {
                vector<string> fields = splitLine(line);
                if (fields.size() != 5)
                {
                    throw runtime_error("wrong number of fields");
                }
                Fixture* fixture = league->findFixture(stoi(fields[1]));
                Ticket* ticket = new Ticket(stoi(fields[0]), fixture, fields[2], stod(fields[3]));
                if (fields[4] == "1")
                {
                    ticket->sellTicket();
                }
                tickets->push_back(ticket);
            }
            catch (exception& e)
            {
                cout << "Skipped a ticket record: " << e.what() << endl;
            }
        }
        inFile.close();
    }

    void loadProducts()
    {
        ifstream inFile("products.txt");
        string line;
        while (getline(inFile, line))
        {
            try
            {
                vector<string> fields = splitLine(line);
                if (fields.size() != 7)
                {
                    throw runtime_error("wrong number of fields");
                }
                if (fields[0] == "M")
                {
                    products->push_back(new Merchandise(fields[1], fields[2], fields[3], fields[4],
                                                        stod(fields[5]), stoi(fields[6])));
                }
                else if (fields[0] == "F")
                {
                    products->push_back(new FoodItem(fields[1], fields[2], fields[3],
                                                     stod(fields[5]), stoi(fields[6])));
                }
                else
                {
                    throw runtime_error("unknown product type " + fields[0]);
                }
            }
            catch (exception& e)
            {
                cout << "Skipped a product record: " << e.what() << endl;
            }
        }
        inFile.close();
    }

public:
    // Parameterized Constructor
    // The menu keeps the spectator, ticket and product lists; the FileManager only fills and reads them
    FileManager(FootballLeague* league, vector<Spectator*>* spectators,
                vector<Ticket*>* tickets, vector<Product*>* products)
    {
        if (league == nullptr || spectators == nullptr || tickets == nullptr || products == nullptr)
        {
            throw invalid_argument("FileManager needs the league and all three lists!");
        }
        this->league = league;
        this->spectators = spectators;
        this->tickets = tickets;
        this->products = products;
    }

    // Writes every record to its file. Call this before the program exits.
    void saveAll()
    {
        saveCommissioner();
        saveStadiums();
        saveOfficials();
        saveTeams();
        saveFixtures();
        saveSpectators();
        saveTickets();
        saveProducts();
        cout << "All data saved." << endl;
    }

    // Reads every file back into the system. Call this once when the program starts.
    // The order matters: teams and stadiums must exist before the fixtures that use them,
    // and fixtures must exist before tickets and official assignments.
    void loadAll()
    {
        if (!league->getTeams().empty())
        {
            throw runtime_error("Data can only be loaded into an empty league!");
        }
        loadCommissioner();
        loadStadiums();
        loadOfficials();
        loadTeams();
        loadPlayers();
        loadCoaches();
        loadFixtures();
        loadAssignments();
        loadSpectators();
        loadTickets();
        loadProducts();
        cout << "All data loaded." << endl;
    }
};

#endif
