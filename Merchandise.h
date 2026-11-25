/*
 * Merchandise.h
 *
 *  Created on: 30 Oct 2026
 *      Author: tijau
 */

#ifndef DOMAIN_MERCHANDISE_H_
#define DOMAIN_MERCHANDISE_H_


class Merchandise : public Product {
private:
	string team;

public:
	Merchandise() { // Default Constructor
		this->itemName = "";
		this->itemType = "";
		this->team = "";
		this->price = 0.0;
		this->inventory = 0;
	}

	Merchandise(string itemName, string itemType, string team, double price, int inventory) { // Primary Constructor
		this->itemName = itemName;
		this->itemType = itemType;
		this->team = team;
		this->price = price;
		this->inventory = inventory;
	}

	Merchandise(Merchandise &m) { // Copy Constructor
		this->itemName = m.itemName;
		this->itemType = m.itemType;
		this->team = m.team;
		this->price = m.price;
		this->inventory = m.inventory;
	}

	// Getters & Setters
	string getItemName() {
		return itemName;
	}

	void setItemName(string itemName) {
		this->itemName = itemName;
	}

	string getItemType() {
		return itemType;
	}

	void setItemType(string itemType) {
		this->itemType = itemType;
	}

	string getTeam() {
		return team;
	}

	void setTeam(string team) {
		this->team = team;
	}

	double getPrice() {
		return price;
	}

	void setPrice(double price) {
		this->price = price;
	}

	int getInventory() {
		return inventory;
	}

	void setInventory(int inventory) {
		this->inventory = inventory;
	}

	void printProductInfo() override {
		cout << itemName << "\t" << itemType << "\t" << team << "\t$" << price << "\t" << inventory << endl;
	}

	void printMenuView() override {
		cout << team << "\t$" << price << endl;
	}
};


#endif /* DOMAIN_MERCHANDISE_H_ */
