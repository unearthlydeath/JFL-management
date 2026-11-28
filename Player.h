/*
 * Player.h
 *
 *  Created on: 10 Nov 2026
 *      Author: tiata
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include "Person.h"

class Player : public Person{
private:
	string position, status;
	int jerseyNum, goals;

public:
	static const int Min_Age = 18; //league minimum age to play

	Player(string id, string name, int age, char gender, string position, int jerseyNum, string status = "Active") : Person(id, name, age, gender){
		if (age < Min_Age) throw invalid_argument("Player is below the league's minimum age.");
		setPosition(position);
		setJerseyNum(jerseyNum);
		setStatus(status);
		goals = 0;
	}

	string getPosition(){
		return position;
	}

	int getJerseyNum(){
		return jerseyNum;
	}

	int getGoals(){
		return goals;
	}

	string getStatus(){
		return status;
	}

	 void setPosition(string p) {
	        if (p.empty()) throw invalid_argument("Position cannot be empty.");
	        position = p;
	    }
	void setJerseyNum(int n) {
	    if (n < 1 || n > 99) throw invalid_argument("Jersey number must be 1-99.");
	    jerseyNum = n;
	}
	void setStatus(string s) {
	    if (s != "Active" && s != "Injured" && s != "Suspended")
	        throw invalid_argument("Status must be Active, Injured or Suspended.");
	        status = s;
	}
	void addGoals(int g) {
	    if (g < 0) throw invalid_argument("Goals cannot be negative.");
	    goals += g;
	}

	string displayRole() override { return "Player"; }

	void display() override {
		Person::display();
		cout << "Position: " << position << endl;
		cout << "Jersey: " << jerseyNum << endl;
		cout << "Goals: " << goals << endl;
		cout << "Status: " << status << endl;
	}
};



#endif /* SRC_PLAYER_H_ */
