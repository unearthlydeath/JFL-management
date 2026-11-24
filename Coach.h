/*
 * Coach.h
 *
 *  Created on: 10 Nov 2026
 *      Author: tiata
 */

#ifndef SRC_COACH_H_
#define SRC_COACH_H_
#include "Person.h"

class Coach : public Person{
private:
	string qualification, role, teamName;

public:
	Coach(string id, string name, int age, char gender, string qualification, string role, string teamName = "Unassigned") :
		Person(id, name, age, gender){
		setQualification(qualification);
		setRole(role);
		setTeamName(teamName);
	}

	string getQualification(){
		return qualification;
	}

	void setQualification(string q) {
		if (q.empty()) throw invalid_argument("Qualification cannot be empty.");
		qualification = q;
	}

	string getRole(){
		return role;
	}

	void setRole(string r) {
		if (r.empty()) throw invalid_argument("Coaching role cannot be empty.");
	    	role = r;
	}

	string getTeamName(){
		return teamName;
	}

	void setTeamName(string t) {
		if (t.empty()) throw invalid_argument("Team name cannot be empty.");
	    	teamName = t;
	}

	string displayRole() override{
		return "Coach";
	}

	void display() override{
		Person::display();
		cout << "Qualification: " << qualification << endl;
		cout << "Role: " << role << endl;
		cout << "Team: " << teamName << endl;
	}
};




#endif /* SRC_COACH_H_ */
