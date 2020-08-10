#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;
#define CLEAR cin.ignore(cin.rdbuf()->in_avail())

struct QuestAnsw
{
	string question = "NoQuestion";
	string answers[4] = { "NoAnswer1", "NoAnswer2", "NoAnswer3", "NoAnswer4" };
	int indexCorrect = INT_MIN;

	QuestAnsw() = default;

	QuestAnsw(string quest, string* answers, int correct);

	void SetQuest(string quest);
	void SetAnswers(string* answers);
	bool SetInd(int ind);

	string GetTrueAnswer() const;

	void ShowQuestAnsw() const;

	bool CheckAnsw(char answer) const;

	friend ifstream& operator>>(ifstream& in, QuestAnsw& cat);
	friend ofstream& operator<<(ofstream& out, QuestAnsw& cat);
};

class CurrentTest
{
private:
	string testName = "NoTestName";
	vector<QuestAnsw> QA;

public:
	CurrentTest() = default;

	CurrentTest(string testName);

	void SetName(string testName);
	string GetName();

	friend ifstream& operator>>(ifstream& in, CurrentTest& currTest);
	friend ofstream& operator<<(ofstream& out, CurrentTest& currTest);

	friend class Admin;
	friend class User;
	friend class Shows;
	friend class Founders;
};

class Category
{
private:
	string catName = "NoCategoryName";
	vector<CurrentTest> testsInCat;

	friend class Test;

public:
	Category() = default;

	Category(string catName)
		:catName(catName) {}

	void SetName(string catName);

	string GetName() const;

	friend class Admin;
	friend class Shows;
	friend class Founders;

	friend ifstream& operator>>(ifstream& in, Category& cat);
	friend ofstream& operator<<(ofstream& out, Category& cat);
};

class Test
{
private:
	vector <Category> categories;
public:

	friend ifstream& operator>>(ifstream& in, Test& test);
	friend ofstream& operator<<(ofstream& out, Test& test);


	friend class Admin;
	friend class Shows;
	friend class Founders;
};