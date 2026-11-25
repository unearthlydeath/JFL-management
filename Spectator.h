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

	void purchaseItems(StadiumShop *shop) {
		int opt;
		char yn;
		string itemName;
		int amount;
		string itemList[MAX_PURCHASES];
		int amountList[MAX_PURCHASES];
		int listIndex = 0;
		int index = 1;
		string team;

		do {
			cout << "What type of item would you like to buy?" << endl << endl;
			cout << "1. Food" << endl;
			cout << "2. Beverage" << endl;
			cout << "3. Merchandise" << endl;
			cout << "4. Cancel" << endl;
			cout << endl << "Enter your option: ";
			cin >> opt;

			switch (opt) {
			case 1:
				shop->displayFoodItems("Food");

				cout << "Enter the name of the item you want: ";
				cin >> itemName;

				cout << "Enter the amount you want: ";
				cin >> amount;

				itemList[listIndex] = itemName;
				amountList[listIndex] = amount;
				listIndex++;

				break;
			case 2:
				shop->displayFoodItems("Beverage");

				cout << "Enter the name of the item you want: ";
				cin >> itemName;

				cout << "Enter the amount you want: ";
				cin >> amount;

				itemList[listIndex] = itemName;
				amountList[listIndex] = amount;
				listIndex++;

				break;
			case 3:
				index = 1;
				itemName = shop->displayMerchandise();
				cout << "Select a team: " << endl;

				for (int i = 0; i < (Product::productId + 1); i++) {
					if (itemName == shop->products[i]->getItemName()) {
						cout << index << ". ";
						shop->products[i]->printMenuView();
						cout << endl;
						index++;
					}
				}

				cout << "Enter your option: ";
				cin >> team;

				cout << "Team selected." << endl;

				cout << "Enter the amount you want: ";
				cin >> amount;

				itemList[listIndex] = itemName;
				amountList[listIndex] = amount;
				listIndex++;

				break;
			case 4:
				cout << "Purchase canceled." << endl;
				return;
			default:
				cout << "Invalid option. Please an option from the list." << endl;
			}

			cout << endl << "Would you like to purchase another item? (Y/N): ";
			cin >> yn;

			do {
				if (yn == 'Y' || yn == 'y') {
					break;
				} else if (yn == 'N' || yn == 'n') {
					shop->finalizePurchase(itemList, amountList, listIndex);
					return;
				} else {
					cout << "Invalid option. Enter 'Y' or 'N': ";
					cin >> yn;
				}
			} while (yn != 'Y' || yn != 'y');

		} while (opt <= 1 || opt >= 4);
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
