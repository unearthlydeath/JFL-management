#ifndef STADIUM_H
#define STADIUM_H

#include <iostream>
#include <string>
using namespace std;

class Stadium
{
private:
    int stadiumID;
    string name;
    string location;
    int seatingCapacity;
    string fieldCondition;
    double ticketPrice;
    int currentOccupancy;

public:
    // Default Constructor
    Stadium()
    {
        stadiumID = 0;
        name = "";
        location = "";
        seatingCapacity = 0;
        fieldCondition = "Unknown";
        ticketPrice = 0.0;
        currentOccupancy = 0;
    }

    // Parameterized Constructor
    Stadium(int id, string n, string loc, int capacity, string condition, double price)
    {
        stadiumID = id;
        name = n;
        location = loc;
        seatingCapacity = capacity;
        fieldCondition = condition;
        ticketPrice = price;
        currentOccupancy = 0;
    };

    // Getters and Setters
    int getStadiumID()
    {
        return stadiumID;
    }

    void setStadiumID(int id)
    {
        if (id > 0)
        {
            stadiumID = id;
        }   
    }

    string getName()
    {
        return name;
    }

    void setName(string n)
    {
        if (!n.empty())
        {
            name = n;
        }    
    }

    string getLocation()
    {
        return location;
    }

    void setLocation(string loc)
    {
        if (!loc.empty())
        {
            location = loc;
        } 
    }

    int getSeatingCapacity()
    {
        return seatingCapacity;
    }

    void setSeatingCapacity(int capacity)
    {
        if (capacity >= currentOccupancy && capacity > 0)
        {
            seatingCapacity = capacity;
        }  
    }

    string getFieldCondition()
    {
        return fieldCondition;
    }

    void setFieldCondition(string condition)
    {
        if (!condition.empty())
        {
            fieldCondition = condition;
        }
    }

    double getTicketPrice()
    {
        return ticketPrice;
    }

    void setTicketPrice(double price)
    {
        if (price >= 0)
        {
            ticketPrice = price;
        }
    }

    int getCurrentOccupancy()
    {
        return currentOccupancy;
    }

    //Display Stadium Information Function
    void displayStadium()
    {
        cout << "\n===== Stadium Information =====" << endl;
        cout << "Stadium ID: " << stadiumID << endl;
        cout << "Name: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Seating Capacity: " << seatingCapacity << endl;
        cout << "Field Condition: " << fieldCondition << endl;
        cout << "Ticket Price: J$" << ticketPrice << endl;
        cout << "Current Occupancy: " << currentOccupancy << endl;
        cout << "================================" << endl;
    }

    // Checking if there are available seats
    bool hasAvailableSeats() {
        return currentOccupancy < seatingCapacity;
    }

    //Funtion to add a Spectator
    void addSpectator() 
    {
        if (hasAvailableSeats()) {
            currentOccupancy++;
            cout << "Spectator added successfully!" << endl;
        }
        else {
            cout << "Stadium is full!" << endl;
        }
    }

    // Function to remove a Spectator
    void removeSpectator() 
    {
        if (currentOccupancy > 0) {
            currentOccupancy--;
            cout << "Spectator removed successfully!" << endl;
        }
        else 
        {
            cout << "Stadium is already empty!" << endl;
        }
    }

};

#endif
