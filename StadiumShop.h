/*
 * StadiumShop.h
 *
 *  Created on: 30 Oct 2026
 *      Author: tijau
 */

#ifndef DOMAIN_STADIUMSHOP_H_
#define DOMAIN_STADIUMSHOP_H_

#define MAX_PRODUCTS 100

class StadiumShop {
private:
	double tax;

public:
	Product *products[MAX_PRODUCTS] {};

	StadiumShop() {
		this->tax = 15;
	}

	double getTax() {
		return tax;
	}

	void setTax(double tax) {
		this->tax = tax;
	}

	bool findProduct(string itemName) {
		for (int i = 0; i < (Product::productId + 1); i++) {
			if (itemName == products[i]->getItemName()) {
				return true;
			}
		}
		return false;
	}

	void addProduct(Product *p) {
		products[Product::productId] = p;
	}

	void displayFoodItems(string itemType) {
		string itemName;
		int index = 1;

		cout << "Here is the list of " << itemType << "s:" << endl << endl;
		for (int i = 0; i < (Product::productId + 1); i++) {
			if (itemType == products[i]->getItemType()) {
				cout << index << ". ";
				products[i]->printMenuView();
				index++;
			}
		}
	}

	string displayMerchandise() {
		int opt;
		string itemName;

		cout << "What type of merchandise would you like to buy?" << endl << endl;
		cout << "1. Flag" << endl;
		cout << "2. Jersey" << endl;
		cout << "3. Key chain" << endl;
		cout << "4. Arm band" << endl;

		do {
			cout << endl << "Enter your option: ";
			cin >> opt;

			switch (opt) {
			case 1:
				return "Flag";
			case 2:
				return "Jersey";
			case 3:
				return "Key chain";
			case 4:
				return "Arm band";
			default:
				cout << "Invalid option. Please an option from the list." << endl;
			}

		} while (opt <= 1 && opt >= 4);
	}

	void finalizePurchase(string *itemList, int *amountList, int listIndex) {
		double total = 0;

		cout << "Item\t\t\t\t\tPrice" << endl;
		for (int i = 0; i < listIndex; i++) {
			for (int p = 0; p < (Product::productId + 1); p++) {
				if (itemList[i] == products[p]->getItemName()) {
					cout << products[p]->getItemName() << "\t\tx" << amountList[i] << "\t\t\t$" << products[p]->getPrice() * amountList[i] << endl;
					total += products[p]->getPrice() * amountList[i];
				}
			}
		}
		cout << "\t\t\t\t" << "Total:  $" << total << endl;
	}

	void printProducts() {
		cout << "List of all products: " << endl;

		for (int i = 0; i < (Product::productId + 1); i++) {
			products[i]->printProductInfo();
		}
	}

	void printItemMenu() {
		for (int i = 0; i < (Product::productId + 1); i++) {
			products[i]->printMenuView();
		}
	}

	void manageInv() {
		string itemName;
		int inventory;

		cout << "Enter Item ID: ";
		cin >> itemName;

		for (int i = 0; i < (Product::productId + 1); i++) {
			if (itemName == products[i]->getItemName()) {
				cout << "Item Name: " << products[i]->getItemName() << endl;
				cout << "Inventory: " << products[i]->getInventory() << endl;

				cout << "Enter new inventory: ";
				cin >> inventory;

				products[i]->setInventory(inventory);
				cout << "Inventory updated successfully." << endl;
				return;
			}
		}

		cout << "Item with ID: " << itemName << " not found." << endl;
	}

	void calcTax(Product *p) {
		double totalTax = 0;

		for (int i = 0; i < 10; i++) {
			totalTax += p->getPrice() * 15/115;
		}
	}
};


#endif /* DOMAIN_STADIUMSHOP_H_ */
