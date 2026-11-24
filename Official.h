/*
 * Official.h
 *
 *  Created on: 10 Nov 2026
 *      Author: tiata
 */

#ifndef SRC_OFFICIAL_H_
#define SRC_OFFICIAL_H_
#include "Person.h"

class Official : public Person{
private:

	string officiatingRole; //so this is referee, assisstant, var etc etc
	string rank;
	bool available;

public:
	Official(string id, string name, int age, char gender, string officiatingRole, string rank) : Person(id, name, age, gender){
		setOfficiatingRole(officiatingRole);
		setRank(rank);
		available = true;
	}

	bool isAvailable() const {
		return available;
	}

	void setAvailable(bool available) {
		this->available = available;
	}

	const string& getOfficiatingRole() const {
		return officiatingRole;
	}

	void setOfficiatingRole(const string &officiatingRole) {
		this->officiatingRole = officiatingRole;
	}

	const string& getRank() const {
		return rank;
	}

	void setRank(const string &rank) {
		this->rank = rank;
	}

	string displayRole() override{
		return "Match Official";
	}

	void display() override{
		Person::display();
		cout << "Role: " << officiatingRole	<< endl;
		cout << "Rank : " << rank << endl;
		cout << "Available: " << (available ? "Yes" : "No") << endl;
	}
};



#endif /* SRC_OFFICIAL_H_ */
