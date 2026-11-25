/*
 * FoodItem.h
 *
 *  Created on: 30 Oct 2026
 *      Author: tijau
 */

#ifndef DOMAIN_FOODITEM_H_
#define DOMAIN_FOODITEM_H_

class FoodItem: public Product {
public:
	FoodItem() { // Default Constructor
		this->itemName = "";
		this->itemType = "";
		this->price = 0.0;
		this->inventory = 0;
	}

	FoodItem(string itemName, string itemType, double price, int inventory) { // Primary Constructor
		this->itemName = itemName;
		this->itemType = itemType;
		this->price = price;
		this->inventory = inventory;
	}

	FoodItem(FoodItem &f) { // Copy Constructor
		this->itemName = f.itemName;
		this->itemType = f.itemType;
		this->price = f.price;
		this->inventory = f.inventory;
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
		cout << itemName << "\t" << itemType << "\t$" << price << "\t" << inventory << endl;
	}

	void printMenuView() override {
		cout << itemName << "\t$" << price << endl;
	}
};

#endif /* DOMAIN_FOODITEM_H_ */
