/*
 * Spectator.h
 *
 *  Created on: 10 Nov 2026
 *      Author: tiata
 */

#ifndef SRC_SPECTATOR_H_
#define SRC_SPECTATOR_H_
#include "Person.h"

class Spectator : public Person{
private:
	int ticketsPurchased;
	double totalSpent;

public:
	Spectator(string id, string name, int age, char gender) : Person(id, name, age, gender){
		ticketsPurchased = 0;
		totalSpent = 0.0;
	}

	int getTicketsPurchased() const {
		return ticketsPurchased;
	}

	void setTicketsPurchased(int ticketsPurchased) {
		this->ticketsPurchased = ticketsPurchased;
	}

	double getTotalSpent() const {
		return totalSpent;
	}

	void setTotalSpent(double totalSpent) {
		this->totalSpent = totalSpent;
	}

	void recordPurchase(int tickets, double amount){
		if(tickets < 0 || amount < 0){
			throw invalid_argument("Quantity and amount cannot be negative.");
		}
		ticketsPurchased += tickets;
		totalSpent += amount;
	}

	string displayRole() override{
		return "Spectator";
	}

	void display() override{
		Person::display();
		cout << "Tickets: " << ticketsPurchased << endl;
		cout << "Total Spent: $" << totalSpent << endl;
	}
};



#endif /* SRC_SPECTATOR_H_ */
