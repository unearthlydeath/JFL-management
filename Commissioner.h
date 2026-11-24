/*
 * Commisioner.h
 *
 *  Created on: 10 Nov 2026
 *      Author: tiata
 */

#ifndef SRC_COMMISSIONER_H_
#define SRC_COMMISSIONER_H_
#include "Person.h"

class Commissioner : public Person{
private:
	string title;

public:
	Commissioner(string id, string name, int age, char gender, string title = "League Commissioner") : Person(id, name, age, gender){
		setTitle(title);
	}

	string getTitle(){
		return title;
	}
	void setTitle(string t){
		if(t.empty()) throw invalid_argument("Title cannot be empty");
		title = t;
	}

	//placeholder for after football team was developed

	void approveTeam(string teamName){
		cout << getName()<< " approved the registration of " << teamName << "." << endl;
	}

	string displayRole() override{
		return "League Commissioner";
	}

	void display() override{
		Person :: display();
		cout << "Title: " << title << endl;
	}
};


#endif /* SRC_COMMISSIONER_H_ */
