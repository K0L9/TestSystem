#include "TestComponent.h"

ifstream& operator>>(ifstream& in, QuestAnsw& cat)
{
	string quest;
	string* answers = new string[4];
	int rnd;
	char index;

	getline(in, quest);

	for (size_t i = 0; i < 4; i++)
		getline(in, answers[i]);

	in >> rnd;
	in >> index;

	in.ignore();

	cat.SetQuest(quest);
	cat.SetInd(index - rnd);
	cat.SetAnswers(answers);

	delete[] answers;

	return in;
}

ofstream& operator<<(ofstream& out, QuestAnsw& cat)
{
	out << cat.question << endl;

	for (size_t i = 0; i < 4; i++)
		out << cat.answers[i] << endl;

	int rnd = rand() % 100;
	char indToWr = cat.indexCorrect + rnd;

	out << rnd << " " << indToWr << endl;

	return out;
}

ifstream& operator>>(ifstream& in, CurrentTest& currTest)
{
	int count;
	in >> count;

	string testName;

	in.ignore();
	getline(in, testName);

	currTest.SetName(testName);


	for (size_t i = 0; i < count; i++)
	{
		QuestAnsw tmp;
		in >> tmp;
		currTest.QA.push_back(tmp);
	}

	return in;
}

ofstream& operator<<(ofstream& out, CurrentTest& currTest)
{
	out << currTest.QA.size() << endl;
	out << currTest.testName << endl;

	for (auto& i : currTest.QA)
		out << i;

	return out;
}

ifstream& operator>>(ifstream& in, Category& cat)
{
	int count;
	in >> count;

	string catName;

	in.ignore();
	getline(in, catName);
	cat.SetName(catName);


	for (size_t i = 0; i < count; i++)
	{
		CurrentTest tmp;
		in >> tmp;
		cat.testsInCat.push_back(tmp);
	}

	return in;
}

ofstream& operator<<(ofstream& out, Category& cat)
{
	out << cat.testsInCat.size() << endl;

	out << cat.catName << endl;

	for (auto& i : cat.testsInCat)
		out << i;

	return out;
}

ifstream& operator>>(ifstream& in, Test& test)
{
	int count;
	in >> count;


	for (size_t i = 0; i < count; i++)
	{
		Category tmp;
		in >> tmp;
		test.categories.push_back(tmp);
	}

	return in;
}

ofstream& operator<<(ofstream& out, Test& test)
{
	out << test.categories.size() << endl;

	for (auto& i : test.categories)
		out << i;

	return out;
}

QuestAnsw::QuestAnsw(string quest, string* answers, int correct)
	:question(quest), indexCorrect(correct)
{
	for (size_t i = 0; i < 4; i++)
		this->answers[i] = answers[i];
}

void QuestAnsw::SetQuest(string quest)
{
	this->question = quest;
}

void QuestAnsw::SetAnswers(string* answers)
{
	for (size_t i = 0; i < 4; i++)
		this->answers[i] = answers[i];
}

bool QuestAnsw::SetInd(int ind)
{
	if (ind < 0 || ind > 3)
		return false;

	this->indexCorrect = ind;

	return true;
}

string QuestAnsw::GetTrueAnswer() const
{
	return answers[indexCorrect];
}

void QuestAnsw::ShowQuestAnsw() const
{
	cout << question << ":\n";

	char tmp = 'A';

	for (int i = 0; i < 4; i++)
		cout << "   " << tmp++ << ". " << answers[i] << endl;
}

bool QuestAnsw::CheckAnsw(char answer) const
{
	return answer - 49 == indexCorrect;
}

CurrentTest::CurrentTest(string testName)
{
	this->testName = testName;
}

void CurrentTest::SetName(string testName)
{
	this->testName = testName;
}

string CurrentTest::GetName()
{
	return this->testName;
}

void Category::SetName(string catName)
{
	this->catName = catName;
}

string Category::GetName() const
{
	return catName;
}
