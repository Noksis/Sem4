#pragma once
#include <iostream>
#include <cstring>



class Human {
protected:
	int age;
	std::string name;
public:
	Human(std::string Name, int Age) {
		age = Age;
		name = Name;
	}

	void get_age() {
		std::cout << name << " His age is " << age << std::endl;
	}

	int set_age(int Age) {
		age = Age;
	}

	void get_name() {
		std::cout << "My name is" << name;
	}

	void set_name(std::string Name) {
		name = Name;
	}
};

class Student: public Human {
protected:
	int score;
public:
	Student(std::string Name, int Age, int Score) : Human(Name, Age) {
		score = Score;
	}
	void get_score() {
		std::cout << name << " His score is " << score << std::endl;
	}
	void set_score(int Score) {
		score = Score;
	}
}; 

class Teacher : public Human {
protected:
	int salary;
public:
	Teacher(std::string Name, int Age, int Salary) : Human(Name, Age) {
		salary = Salary;
	}

	void get_salary() {
		std::cout << name << " His salary is " << salary << std::endl;
	}
	void set_salary(int Salary) {
		salary = Salary;
	}
};