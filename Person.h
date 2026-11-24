/*
 * Person.h
 *
 *  Created on: 7 Nov 2026
 *      Author: tiata
 */

#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_
#include <iostream>
#include <string>
using namespace std;


class Person{

private:
	string id, name;
	int age;
	char gender;

public:
	Person(string id, string name, int age, char gender){
		if (gender != 'M' && gender != 'F') throw invalid_argument("Gender must be 'F' or 'M'");
		this->id = id;
		this->name = name;
		this->age = age;
		this->gender = gender;
	}

	virtual ~Person(){}

	string getId(){
		return id;
	}

	string getName(){
		return name;
	}

	int getAge(){
		return age;
	}

	char getGender(){
		return gender;
	}

	virtual string displayRole() = 0;

	virtual void display(){
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout <<"Gender: " << gender << endl;
	}
};


#endif /* SRC_PERSON_H_ */
