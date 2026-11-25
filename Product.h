/*
 * Product.h
 *
 *  Created on: 30 Oct 2026
 *      Author: tijau
 */

#ifndef DOMAIN_PRODUCT_H_
#define DOMAIN_PRODUCT_H_


class Product {
protected:
	string itemName;
	string itemType;
	double price;
	int inventory;

public:
	static int productId;

	Product() {
		this->itemName = "";
		this->itemType = "";
		this->price = 0.0;
		this->inventory = 0;
		productId++;
	}

	string getItemName() const {
		return itemName;
	}

	string getItemType() const {
		return itemType;
	}

	double getPrice() {
		return price;
	}

	int getInventory() const {
		return inventory;
	}

	void setInventory(int inventory) {
		this->inventory = inventory;
	}

	virtual void printProductInfo() = 0;

	virtual void printMenuView() = 0;

	virtual ~Product() {}
};

int Product::productId = -1;

#endif /* DOMAIN_PRODUCT_H_ */
