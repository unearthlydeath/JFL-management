#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <string>
#include "Fixture.h"

using namespace std;

class Ticket
{
private:
    int ticketID;
    Fixture* fixture;
    string category;
    double price;
    bool sold;      // Will help determine whether an individual ticket has already been sold.

public:
    // Default Constructor
    Ticket()
    {
        ticketID = 0;
        fixture = nullptr;
        category = "";
        price = 0.0;
        sold = false;
    }

    Ticket(int id, Fixture* f, string cat, double p)
    {
        ticketID = id;
        fixture = f;
        category = cat;
        price = p;
        sold = false;
    }

    // Getters and Setters
    int getTicketID(){
        return ticketID;
    }

    void setTicketID(int id)
    {
        if (id > 0)
        {
            ticketID = id;
        }    
    }

    Fixture* getFixture(){
        return fixture;
    }

    void setFixture(Fixture* f)
    {
        if (f != nullptr)
        {
            fixture = f;
        }      
    }

    string getCategory(){
        return category;
    }
    
    void setCategory(string cat)
    {
        if (!cat.empty())
        {
            category = cat;
        } 
    }

    double getPrice(){
        return price;
    }

    void setPrice(double p)
    {
        if (p >= 0)
        {
            price = p;
        }  
    }

    // Getter for sold
    bool isSold(){
        return sold;
    }

    // Display Ticket Function
    void displayTicket()
    {
        cout << "\n===== Ticket Information =====" << endl;
        cout << "Ticket ID: " << ticketID << endl;

        if (fixture != nullptr)
        {
            cout << "Fixture ID: " << fixture->getFixtureID() << endl;
        }
        else
        {
            cout << "Ficture Not Assigned" << endl;
        }

        cout << "Category: " << category << endl;
        cout << "Price (Including GCT): J$" << price << endl;
        cout << "==============================" << endl;

        if (sold) 
        {
            cout << "Status: Sold" << endl;
        }
        else 
        {
            cout << "Status: Available" << endl;
        }
    }

    void sellTicket()
    {
        if (sold)
        {
            cout << "This ticket has already been sold" << endl;
            return;
        }
        
        if (fixture == nullptr)
        {
            cout << "Cannot sell ticket. No fixture assigned!" << endl;
            return;
        }

        Stadium* stadium = fixture->getStadium();

        if (stadium == nullptr)
        {
            cout << "Cannot sell ticket. No stadium assigned" << endl;
            return;
        }
        
        if (stadium->hasAvailableSeats())
        {
            stadium->addSpectator();
            sold = true;
            cout << "Ticket sold successfully!" << endl;
        }
        else
        {
            cout << "Ticket sale failed. Stadium is full!" << endl;
        }   
    }
};

#endif
