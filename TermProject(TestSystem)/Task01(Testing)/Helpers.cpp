#include "Helpers.h"

//Shows
bool Shows::ShowAllCategories(const Test& tests)
{
	if (tests.categories.empty())
		return false;

	int counter = 0;
	for (auto& i : tests.categories)
		cout << "#" << ++counter << " " << i.catName << endl;

	return true;
}
bool Shows::ShowCurrentCategorie(const Category* const cat)
{
	if (cat == nullptr)
	{
		cout << "No one category with this name\n";
		return false;
	}

	if (cat->testsInCat.empty())
	{
		cout << "This category not have any tests\n";
		return false;
	}

	cout << "Category: " << cat->catName << endl;

	int counter = 1;

	for (auto& i : cat->testsInCat)
	{
		cout << "Test #" << counter++ << " :" << i.testName << endl;
		for (auto& j : i.QA)
		{
			cout << "\t Question: " << j.question << endl;

			for (size_t k = 0; k < 4; k++)
				cout << "\t\tAnswer #" << k + 1 << ": " << j.answers[k] << endl;

			cout << "\t\t\tRight answer: " << j.GetTrueAnswer() << endl;
		}
	}
	return true;
}
void Shows::ShowAllQuest(const Test& tests)

{
	int counter = 0, counter1 = 0;
	for (auto& i : tests.categories)
	{
		cout << "Category #" << ++counter << " " << i.catName << "\t( ";
		cout << "This category have: " << i.testsInCat.size() << " tests )\n";
		counter1 = 0;
		for (auto& j : i.testsInCat)
		{
			cout << "\tTest # " << ++counter1 << " :" << j.testName << "\t( ";
			cout << "This test have: " << j.QA.size() << " questions )\n";
			for (auto& l : j.QA)
			{
				cout << "\t\t Question: " << l.question << endl;
				for (size_t k = 0; k < 4; k++)
					cout << "\t\t\tAnswer #" << k + 1 << ": " << l.answers[k] << endl;

				cout << "\t\t\t\tRight answer: " << l.GetTrueAnswer() << endl;
			}
		}
	}
}
bool Shows::ShowAllTests(const Test& tests)
{
	if (tests.categories.empty())
	{
		cout << "Ask admin to add categories\n";
		return false;
	}

	int counter = 1, counter1 = 1;

	for (auto& i : tests.categories)
	{
		cout << "#" << counter++ << " " << i.catName << endl;
		counter1 = 1;

		for (auto& j : i.testsInCat)
			cout << "\tTest #" << counter1++ << " " << j.testName << endl;
	}

	return true;
}
bool Shows::ShowTestsInCurrentCategorie(const Category* const cat)
{
	if (cat == nullptr)
	{
		cout << "No one category with this name\n";
		return false;
	}

	if (cat->testsInCat.empty())
	{
		cout << "This category not have any tests\n";
		return false;
	}

	int counter = 1;

	cout << "Category: " << cat->catName << endl;

	for (auto& i : cat->testsInCat)
		cout << "\tTest " << "#" << counter++ << " :" << i.testName << endl;

	cout << endl;

	return true;
}
bool Shows::ShowCurrentTest(const CurrentTest* const test)
{
	if (test->QA.empty())
		return false;

	for (auto& i : test->QA)
	{
		cout << "\tQuestion: " << i.question << endl;

		for (size_t k = 0; k < 4; k++)
			cout << "\t\tAnswer #" << k + 1 << ": " << i.answers[k] << endl;

		cout << "\t\t\tRight answer: " << i.GetTrueAnswer() << endl;
	}

	return true;
}

//Founders
class User;
Category* Founders::GetCategoryByName(string catName, Test& tests)
{
	if (isdigit(catName[0]))
	{
		int index = atoi(catName.c_str()) - 1;

		if (index < 0 || index > tests.categories.size() - 1)
			return nullptr;

		return &tests.categories[index];
	}
	else
	{

		for (auto& i : tests.categories)
			if (i.catName == catName)
				return &i;

		return nullptr;
	}
}
int Founders::GetCategIndex(const Test& tests)
{
	if (!Shows::ShowAllCategories(tests))
		return -1;

	int userCateg;

	cout << "Input categories index: ";
	cin >> userCateg;

	if (userCateg < 0 || userCateg > tests.categories.size())
	{
		cout << "Input right index\n";
		return -1;
	}

	return --userCateg;
}
int Founders::GetCategIndByName(string categorie, const Test& tests)
{
	if (isdigit(categorie[0]))
	{
		int index = atoi(categorie.c_str()) - 1;

		if (index < 0 || index > tests.categories.size() -1)
			throw logic_error("Invalid index or unresolved new title");

		return index;
	}

	else
	{
		for (size_t i = 0; i < tests.categories.size(); i++)
			if (tests.categories[i].catName == categorie)
				return i;

		return -1;
	}
}
string Founders::GetCategoriesName(const Test& tests)
{
	string catName;

	if (!Shows::ShowAllCategories(tests))
	{
		cout << "No one category\n";
		return "";
	}

	cout << "Input category: ";
	CLEAR;
	getline(cin, catName);

	return catName;
}

int Founders::CountRightAnsw(const bool* stat, int size)
{
	int counter = 0;
	for (size_t i = 0; i < size; i++)
		if (stat[i])
			counter++;

	return counter;
}
bool Founders::CheckAndConvertAnswer(char& answer)
{
	if ((answer < 'a' || answer > 'd') && (answer < 'A' || answer > 'D') && (answer < '1' || answer > '4'))
		return false;

	if (answer >= 'a' && answer <= 'd')
		answer -= 48;

	else if (answer >= 'A' && answer <= 'D')
		answer -= 16;

	return true;
}
int Founders::GetQuestIndByQuest(const CurrentTest* test, string quest)
{
	int counter = 0;
	for (auto& i : test->QA)
	{
		if (i.question == quest)
			return counter;

		counter++;
	}

	return -1;
}

CurrentTest* Founders::GetTestByName(string testName, Category* const cat)
{
	if (isdigit(testName[0]))
	{
		int index = atoi(testName.c_str()) - 1;

		if (index < 0 || index > cat->testsInCat.size() - 1)
			return nullptr;

		return &cat->testsInCat[index];
	}

	else
	{
		for (auto& i : cat->testsInCat)
			if (testName == i.testName)
				return &i;

		return nullptr;
	}
}
int Founders::GetTestIndByName(string testName, const Category& cat)
{
	if (isdigit(testName[0]))
	{
		int index = atoi(testName.c_str()) - 1;

		if (index < 0 || index > cat.testsInCat.size() -1)
			throw logic_error("Invalid index or unresolved new title");

		return index;
	}

	else
	{
		for (size_t i = 0; i < cat.testsInCat.size(); i++)
			if (cat.testsInCat[i].testName == testName)
				return i;

		return -1;
	}
}
int Founders::GetTestIndByName(string testName, const Category* cat)
{
	if (isdigit(testName[0]))
	{
		int index = atoi(testName.c_str()) - 1;

		if (index < 0 || index > cat->testsInCat.size() -1)
			throw logic_error("Invalid index or unresolved new title");

		return index;
	}

	else
	{
		for (size_t i = 0; i < cat->testsInCat.size(); i++)
			if (cat->testsInCat[i].testName == testName)
				return i;

		return -1;
	}
}

bool Founders::CheckPass(string str)
{
	if (str.size() < 8)
		throw logic_error("Your pass must have min 8 characters");

	bool isOneBig, isOneSmall, isOneDigit;
	isOneBig = isOneDigit = isOneSmall = false;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			isOneSmall = true;

		else if (str[i] >= 'A' && str[i] <= 'Z')
			isOneBig = true;

		else if (str[i] >= '0' && str[i] <= '9')
			isOneDigit = true;
	}

	if (!isOneBig)
		throw logic_error("Your pass must have min 1 BIG letter");
	if (!isOneSmall)
		throw logic_error("Your pass must have min 1 small letter");
	if (!isOneDigit)
		throw logic_error("Your pass must have min 1 digit");

}
bool Founders::CheckLogin(string str)
{
	if (str.size() < 3)
		throw logic_error("Your login must have min 3 characters");

	for (size_t i = 0; i < str.size(); i++)
		if (!(str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z' || str[i] >= '0' && str[i] <= '9' || str[i] == '_'))
			throw logic_error("Your login can have only digits, letters and _");
}


