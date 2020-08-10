#pragma once
#include "Statistic.h"

string GetPassword(string message = "Input password: ");
class User
{
private:
	string fullName = "NoFullName";
	string address = "NoAddress";
	string number = "NoNumber";
	const string pass;
	const string login;

public:
	//Ctors
	User() = default;
	User(string ulogin, string upass);
	User(string fullName, string address, string number);

	//Setters
	bool SetFullName(string fullName);
	bool SetAddress(string address);
	bool SetNumber(string number);
	bool SetLogin(string loginU);
	bool SetPass(string passU);

	//Getters
	string GetFullName() const;
	string GetAddress() const;
	string GetNumber() const;
	string GetLogin() const;
	string GetPass() const;

	friend ofstream& operator<<(ofstream& out, const User& user);
	friend ostream& operator<<(ostream& out, const User& user);

	friend ifstream& operator>>(ifstream& in, User& user);
	friend istream& operator>>(istream& in, User& user);

	User operator=(const User& other);

	void GoTest(Test& tests);

	bool ShowPersonStat();
	void SeeTrueFalse(const bool* const answers, int answerSize, const CurrentTest* const test);
	void SeeOlderByCurrPersonByCateg(const Category* const cat);
	void SeeOlderByCurrPersonByTest(const CurrentTest* const cat);
	void SeeResultsByOtherPeople(const CurrentTest* const cat);

	void MainUserMenu(Test& tests);
};