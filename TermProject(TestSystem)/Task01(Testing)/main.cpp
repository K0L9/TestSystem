#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

#include <conio.h>

using namespace std;
#define CLEAR cin.ignore(cin.rdbuf()->in_avail())

struct QuestAnsw
{
	string question;
	string answers[4];
	int indexCorrect;

	QuestAnsw() = default;

	QuestAnsw(string quest, string* answers, int correct)
		:question(quest), indexCorrect(correct)
	{
		for (size_t i = 0; i < 4; i++)
			this->answers[i] = answers[i];
	}

	void SetQuest(string quest)
	{
		this->question = quest;
	}
	void SetAnswers(string* answers)
	{
		for (size_t i = 0; i < 4; i++)
			this->answers[i] = answers[i];
	}
	void SetInd(int ind)
	{
		this->indexCorrect = ind;
	}
	string GetTrueAnswer()const
	{
		return answers[indexCorrect];
	}

	void ShowQuestAnsw()const
	{
		cout << question << ":\n";

		char tmp = 'A';

		for (int i = 0; i < 4; i++)
			cout << "   " << tmp++ << ". " << answers[i] << endl;
	}

	bool CheckAnsw(char answer) const
	{
		return answer - 49 == indexCorrect;
	}

	friend ifstream& operator>>(ifstream& in, QuestAnsw& cat)
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
	friend ofstream& operator<<(ofstream& out, QuestAnsw& cat)
	{
		out << cat.question << endl;

		for (size_t i = 0; i < 4; i++)
			out << cat.answers[i] << endl;

		int rnd = rand() % 100;
		char indToWr = cat.indexCorrect + rnd;

		out << rnd << " " << indToWr << endl;

		return out;
	}
};

class CurrentTest
{
private:
	string testName;
	vector<QuestAnsw> QA;

public:
	CurrentTest() = default;

	CurrentTest(string testName)
	{
		this->testName = testName;
	}

	void SetName(string testName)
	{
		this->testName = testName;
	}
	string GetName()
	{
		return this->testName;
	}

	friend ifstream& operator>>(ifstream& in, CurrentTest& currTest)
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
	friend ofstream& operator<<(ofstream& out, CurrentTest& currTest)
	{
		out << currTest.QA.size() << endl;
		out << currTest.testName << endl;

		for (auto& i : currTest.QA)
			out << i;

		return out;
	}

	friend class Admin;
	friend class User;
	friend class Shows;
	friend class Founders;
};

class Category
{
private:
	string catName;
	vector<CurrentTest> testsInCat;

	friend class Test;

public:
	Category()
	{

	}

	Category(string catName)
		:catName(catName)
	{

	}

	void SetName(string catName)
	{
		this->catName = catName;
	}
	string GetName() const
	{
		return catName;
	}

	friend class Admin;
	friend class Shows;
	friend class Founders;

	friend ifstream& operator>>(ifstream& in, Category& cat)
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
	friend ofstream& operator<<(ofstream& out, Category& cat)
	{
		out << cat.testsInCat.size() << endl;

		out << cat.catName << endl;

		for (auto& i : cat.testsInCat)
			out << i;

		return out;
	}
};

class Test
{
private:
	vector <Category> categories;
public:

	friend ifstream& operator>>(ifstream& in, Test& test)
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
	friend ofstream& operator<<(ofstream& out, Test& test)
	{
		out << test.categories.size() << endl;

		for (auto& i : test.categories)
			out << i;

		return out;
	}

	friend class Admin;
	friend class Shows;
	friend class Founders;
};

class Shows
{
public:
	static bool ShowAllCategories(const Test& tests)
	{
		if (tests.categories.empty())
			return false;

		int counter = 0;
		for (auto& i : tests.categories)
			cout << "#" << ++counter << " " << i.catName << endl;

		return true;
	}
	static bool ShowCurrentCategorie(const Category* const cat)
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
	static void ShowAllQuest(const Test& tests)
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

	static bool ShowAllTests(const Test& tests)
	{
		if (tests.categories.empty())
		{
			cout << "Ask admin to add categories\n";
			return false;
		}

		int counter, counter1 = 1;

		for (auto& i : tests.categories)
		{
			cout << "#" << counter++ << " " << i.catName << endl;
			counter1 = 1;

			for (auto& j : i.testsInCat)
				cout << "\tTest #" << counter1++ << " " << j.testName << endl;
		}

		return true;
	}
	static bool ShowTestsInCurrentCategorie(const Category* const cat)
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
	static bool ShowCurrentTest(const CurrentTest* const test)
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

};

string GetPassword(string message = "Input password: ")
{
	vector<char> password;

	char c;

	cout << message;
	while ((c = _getch()) != '\r')
	{
		password.push_back(c);
		_putch('*');
	}

	string passStr(password.begin(), password.end());

	cout << endl;

	return passStr;
}
class User;
class Founders
{
public:
	static Category* GetCategoryByName(string catName, Test& tests)
	{
		if (isdigit(catName[0]))
		{
			int index = atoi(catName.c_str()) - 1;

			if (index < 0 || index > tests.categories.size())
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
	static int GetCategIndex(const Test& tests)
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
	static int GetCategIndByName(string categorie, const Test& tests)
	{
		if (isdigit(categorie[0]))
		{
			int index = atoi(categorie.c_str()) - 1;

			if (index < 0 || index > tests.categories.size())
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
	static string GetCategoriesName(const Test& tests)
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

	static int CountRightAnsw(const bool* stat, int size)
	{
		int counter = 0;
		for (size_t i = 0; i < size; i++)
			if (stat[i])
				counter++;

		return counter;
	}
	static bool CheckAndConvertAnswer(char& answer)
	{
		if ((answer < 'a' || answer > 'd') && (answer < 'A' || answer > 'D') && (answer < '1' || answer > '4'))
			return false;

		if (answer >= 'a' && answer <= 'd')
			answer -= 48;

		else if (answer >= 'A' && answer <= 'D')
			answer -= 16;

		return true;
	}
	static int GetQuestIndByQuest(const CurrentTest* test, string quest)
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

	static CurrentTest* GetTestByName(string testName, Category* const cat)
	{
		if (isdigit(testName[0]))
		{
			int index = atoi(testName.c_str()) - 1;

			if (index < 0 || index > cat->testsInCat.size())
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
	static int GetTestIndByName(string testName, const Category& cat)
	{
		if (isdigit(testName[0]))
		{
			int index = atoi(testName.c_str()) - 1;

			if (index < 0 || index > cat.testsInCat.size())
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
	static int GetTestIndByName(string testName, const Category* cat)
	{
		if (isdigit(testName[0]))
		{
			int index = atoi(testName.c_str()) - 1;

			if (index < 0 || index > cat->testsInCat.size())
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

	static string FoundPersonByLogin(string login, vector<User> users);
	static bool CheckPass(string str)
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
	static bool CheckLogin(string str)
	{
		if (str.size() < 3)
			throw logic_error("Your login must have min 3 characters");

		for (size_t i = 0; i < str.size(); i++)
			if (!(str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z' || str[i] >= '0' && str[i] <= '9' || str[i] == '_'))
				throw logic_error("Your login can have only digits, letters and _");
	}
};

class Statistic
{
private:
	bool* fullAnsw;
	string categTitle;
	string currTestTitle;
	string whoLog;
	int rightRes;
	double rightInProc;
	int size;

public:
	Statistic(string categTitle = "", string currTestTitle = "", string whoLog = "", bool* fullAnsw = nullptr, int rightRes = 0, double rightInProc = 0, int size = 0)
		: whoLog(whoLog), categTitle(categTitle), currTestTitle(currTestTitle), fullAnsw(fullAnsw), rightRes(rightRes), rightInProc(rightInProc), size(size)
	{
	}

	friend ofstream& operator<<(ofstream& out, const Statistic& stat)
	{
		out << stat.whoLog << endl << stat.rightRes << " " << stat.rightInProc << " " << stat.size << " " << stat.categTitle << endl << stat.currTestTitle << endl;

		return out;
	}

	friend ifstream& operator>>(ifstream& in, Statistic& stat)
	{
		getline(in, stat.whoLog);
		in >> stat.rightRes;
		in >> stat.rightInProc;
		in >> stat.size;
		getline(in, stat.categTitle);
		getline(in, stat.currTestTitle);

		return in;
	}

	void ShowStat()
	{
		cout << "Correct: " << this->rightRes << " / " << size << endl;
		cout << "Right in proc.: " << rightInProc << "%" << endl;
	}

	void ShowCategTitle()
	{
		cout << "Category name: " << categTitle << endl;
	}
	void ShowTestTitle()
	{
		cout << "Test name: " << currTestTitle << endl;
	}

	friend class User;
	friend class Admin;
};

class User
{
private:
	string fullName = "NoFullName";
	string address = "NoAddress";
	string number = "NoNumber";
	const string pass;
	const string login;

public:
	User()
	{

	}

	User(string ulogin, string upass)
		: login(ulogin), pass(upass)
	{

	}

	User(string fullName, string address, string number)
	{
		SetFullName(fullName);
		SetAddress(address);
		SetNumber(number);
	}

	bool SetFullName(string fullName)
	{
		if (fullName.empty())
			return false;

		this->fullName = fullName;
		return true;
	}
	bool SetAddress(string address)
	{
		if (address.empty())
			return false;

		this->address = address;
		return true;
	}
	bool SetNumber(string number)
	{
		if (number.empty())
			return false;

		this->number = number;
		return true;
	}
	bool SetLogin(string loginU)
	{
		if (loginU.empty())
			return false;

		const_cast<string&>(this->login) = loginU;
		return true;
	}
	bool SetPass(string passU)
	{
		if (passU.empty())
			return false;

		const_cast<string&>(this->pass) = passU;
		return true;
	}

	string GetFullName() const
	{
		return fullName;
	}
	string GetAddress() const
	{
		return address;
	}
	string GetNumber() const
	{
		return number;
	}
	string GetLogin() const
	{
		return this->login;
	}
	string GetPass() const
	{
		return this->pass;
	}

	friend ofstream& operator<<(ofstream& out, const User& user)
	{
		string pass{ user.pass };

		for (size_t i = 0; i < user.pass.size(); i++)
			pass[i] = user.pass[i] + 3;

		out << user.fullName << endl << user.address << endl << user.number << endl << user.login << endl << pass << endl;

		return out;
	}
	friend ostream& operator<<(ostream& out, const User& user)
	{
		out << "Fullname: " << user.fullName << endl;
		out << "\tUser's address: " << user.address << endl;
		out << "\tUser's number: " << user.number << endl;
		out << "\tUser's login: " << user.login << endl;
		out << "\tUser's password: " << user.pass << endl;

		return out;
	}

	friend ifstream& operator>>(ifstream& in, User& user)
	{
		string fullName, address, number, login, pass;

		getline(in, fullName);
		getline(in, address);
		getline(in, number);
		getline(in, login);
		getline(in, pass);

		for (size_t i = 0; i < pass.size(); i++)
			pass[i] -= 3;

		user.SetFullName(fullName);
		user.SetAddress(address);
		user.SetNumber(number);
		user.SetLogin(login);
		user.SetPass(pass);

		return in;
	}
	friend istream& operator>>(istream& in, User& user)
	{
		string fullName, address, number;

		cout << "Input user's fullname: ";
		in.ignore(in.rdbuf()->in_avail());
		getline(in, fullName);

		cout << "Input user's address: ";
		getline(in, address);

		cout << "Input user's number: ";
		getline(in, number);

		user.SetFullName(fullName);
		user.SetAddress(address);
		user.SetNumber(number);

		cout << endl;

		return in;
	}

	User operator=(const User& other)
	{
		this->fullName = other.fullName;
		this->address = other.address;
		this->number = other.number;

		return *this;
	}

	void GoTest(Test& tests)
	{
		if (!Shows::ShowAllCategories(tests))
			return;

		string categoryName;
		CLEAR;
		cout << "Input category: ";
		getline(cin, categoryName);

		Category* cat = Founders::GetCategoryByName(categoryName, tests);

		if (cat == nullptr)
		{
			cout << "Invalid cat title or index\n";
			system("pause");
			return;
		}

		if (!Shows::ShowTestsInCurrentCategorie(cat))
			return;

		string testName;
		CLEAR;
		cout << "Input test title: ";
		getline(cin, testName);

		CurrentTest* currTest = Founders::GetTestByName(testName, cat);

		if (currTest == nullptr)
		{
			cout << "Invalid test title or index\n";
			system("pause");
			return;
		}

		bool isTrue = false;
		char userAnswer;
		int size = currTest->QA.size();
		bool* stat = new bool[size];

		int counter = 0;
		for (auto& i : currTest->QA)
		{
			cout << "Answer #" << counter + 1 << " / " << size << endl;

			do
			{
				i.ShowQuestAnsw();

				cout << "Input your answer digit or number: ";
				cin >> userAnswer;
			} while (!Founders::CheckAndConvertAnswer(userAnswer));

			if (i.CheckAnsw(userAnswer))
				stat[counter] = true;

			else
				stat[counter] = false;

			counter++;
		}

		int nRight = Founders::CountRightAnsw(stat, size);
		double rightInProc = (double)(nRight * 100) / size;

		Statistic fullStat{ cat->GetName(), currTest->GetName(), this->login, stat, nRight, rightInProc, size };

		cout << "RESULTS: \n";

		fullStat.ShowStat();
		system("pause");

		ofstream file("Saves/Statistic.txt", ios_base::app);

		if (!file.good())
		{
			cout << "Error with Saves/Statistic.txt file\n";
			system("pause");
			return;
		}

		int choice;
		do
		{
			system("cls");
			cout << "=============================================\n";
			cout << "|1. Show correct/incorrect                  |\n";
			cout << "|2. Show result of this test by other users |\n";
			cout << "|3. Show older results of this test         |\n";
			cout << "|0. Exit                                    |\n";
			cout << "=============================================\n";
			cout << "Input your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				SeeTrueFalse(stat, size, currTest);
				break;

			case 2:
				SeeResultsByOtherPeople(currTest);
				break;

			case 3:
				SeeOlderByCurrPersonByTest(currTest);
				break;

			case 0:
				file << fullStat;
				return;

			default:
				cout << "Input right value\n";
				break;
			}
			system("pause");
		} while (choice != 0);

	}

	bool ShowPersonStat()
	{
		ifstream file("Saves/Statistic.txt");
		if (!file.good())
		{
			cout << "Error with file\n";
			return false;
		}

		Statistic tmp{};

		bool isOne = false;

		while (file.peek() != ifstream::traits_type::eof())
		{
			file >> tmp;
			if (tmp.whoLog == this->login)
			{
				cout << "-----------\n";
				isOne = true;
				tmp.ShowCategTitle();
				tmp.ShowTestTitle();
				tmp.ShowStat();
			}
		}

		if (!isOne)
		{
			cout << "Not found any your test result\n";
			return false;
		}

		return true;
	}
	void SeeTrueFalse(const bool* const answers, int answerSize, const CurrentTest* const test)
	{
		for (size_t i = 0; i < answerSize; i++)
		{
			cout << "\n" << i + 1 << ") " << test->QA[i].question << " : " << boolalpha << answers[i] << endl;
			if (!answers[i])
				cout << "\tRight answer: " << test->QA[i].GetTrueAnswer() << endl;
		}
	}
	void SeeOlderByCurrPersonByCateg(const Category* const cat)
	{
		ifstream file("Saves/Statistic.txt");
		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}

		Statistic tmp{};

		bool isOne = false;
		bool isFirst = false;

		while (file.peek() != ifstream::traits_type::eof())
		{
			file >> tmp;

			if (tmp.whoLog == this->login && tmp.categTitle == cat->GetName())
			{
				cout << "-----------\n";
				isOne = true;
				tmp.ShowTestTitle();
				tmp.ShowStat();
			}
		}

		if (!isOne)
		{
			cout << "You didn't go this test\n";
			return;
		}
	}
	void SeeOlderByCurrPersonByTest(const CurrentTest* const cat)
	{
		ifstream file("Saves/Statistic.txt");
		if (!file.good())
		{
			cout << "Error with file\n";
			system("pause");
			return;
		}

		Statistic tmp{};

		bool isOne = false;

		while (file.peek() != ifstream::traits_type::eof())
		{
			file >> tmp;

			if (tmp.whoLog == this->login && tmp.currTestTitle == cat->testName)
			{
				cout << "-----------\n";
				isOne = true;
				tmp.ShowStat();
			}
		}

		if (!isOne)
		{
			cout << "You didn't go this test\n";
			return;
		}
	}
	void SeeResultsByOtherPeople(const CurrentTest* const cat)
	{
		ifstream file("Saves/Statistic.txt");
		if (!file.good())
		{
			cout << "Error with file\n";
			system("pause");
			return;
		}

		Statistic tmp{};

		bool isOne = false;

		while (file.peek() != ifstream::traits_type::eof())
		{
			file >> tmp;
			if (tmp.currTestTitle == cat->testName)
			{
				cout << "-----------\n";
				isOne = true;
				tmp.ShowCategTitle();
				tmp.ShowTestTitle();
				tmp.ShowStat();
			}
		}

		if (!isOne)
		{
			cout << "You are first who going this test\n";
			return;
		}
	}

	void MainUserMenu(Test& tests)
	{
		int choice;
		do
		{
			system("cls");
			cout << "====================================\n";
			cout << "|1. Go test                        |\n";
			cout << "|2. Show full person stat          |\n";
			cout << "|3. Show statistic by curent test  |\n";
			cout << "|4. Show statistic by curent categ |\n";
			cout << "|0. Exit                           |\n";
			cout << "====================================\n";
			cout << "Input your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				system("cls");
				GoTest(tests);
				break;

			case 2:
				system("cls");
				ShowPersonStat();
				break;

			case 3:
			{
				system("cls");
				Shows::ShowAllCategories(tests);

				string cat;
				cout << "Input category (that's no all category, you can know more categories): ";
				CLEAR;
				getline(cin, cat);
				Category* catPtr = Founders::GetCategoryByName(cat, tests);

				if (catPtr == nullptr)
				{
					cout << "Invalid category name\n";
					break;
				}

				Shows::ShowTestsInCurrentCategorie(catPtr);

				string test;
				cout << "Input test (this is no all test, you can know more tests): ";
				CLEAR;
				getline(cin, test);

				CurrentTest* testPtr = Founders::GetTestByName(test, catPtr);

				SeeOlderByCurrPersonByTest(testPtr);

				break;
			}

			case 4:
			{
				system("cls");
				Shows::ShowAllCategories(tests);

				string choose;
				cout << "Input category (that's no all category, you can know more categories): ";
				CLEAR;
				getline(cin, choose);
				Category* choosePtr = Founders::GetCategoryByName(choose, tests);

				if (choosePtr == nullptr)
				{
					cout << "Invalid category name\n";
					break;
				}

				SeeOlderByCurrPersonByCateg(choosePtr);

				break;
			}
			case 0:
				return;
			default:
				cout << "Input right choice(0-4)\n";
				break;
			}
			system("pause");
		} while (choice != 0);

	}
};

class Admin
{
private:
	vector <User>& users;
	Test& tests;

public:
	Admin(vector <User>& users, Test& tests)
		:users(users), tests(tests)
	{

	}

	void WriteLogin()
	{
		ofstream file("Saves/ThereAreNoLogin.dat", ios_base::binary || ios::app);

		if (!file.good())
			throw logic_error("Error with file");

		char login[100];
		bool isTrue = false;

		do
		{
			cout << "Input new login: ";
			CLEAR;
			cin.getline(login, 100);

			try
			{
				Founders::CheckLogin(login);
				isTrue = true;
			}

			catch (const logic_error& ex)
			{
				cout << ex.what() << endl;
				system("pause");
				system("cls");
			}

		} while (!isTrue);

		int size = sizeof(login);

		file.write(reinterpret_cast<const char*>(&size), sizeof(int));

		for (size_t i = 0; i < strlen(login); i++)
			login[i] -= 2;

		file.write(reinterpret_cast<const char*>(&login), size);
	}
	string ReadLogin()
	{
		ifstream file("Saves/ThereAreNoLogin.dat", ios_base::binary);

		if (!file.good())
			throw logic_error("Error with file");
		if (file.peek() == ifstream::traits_type::eof())
			throw logic_error("No one admin in system");

		int sizeLogin;
		file.read(reinterpret_cast<char*>(&sizeLogin), sizeof(int));

		char login[100];
		file.read(reinterpret_cast<char*>(&login), sizeLogin);

		for (size_t i = 0; i < strlen(login); i++)
			login[i] += 2;

		return login;
	}

	void WritePass()
	{
		ofstream file("Saves/ThereAreNoPassword.dat", ios_base::binary || ios::app);

		if (!file.good())
			throw logic_error("Error with file");

		bool isTrue = false;
		char pass[100];
		do
		{
			CLEAR;
			string tmpPass = GetPassword("Input new password: ");
			strcpy_s(pass, 100, tmpPass.c_str());

			try
			{
				Founders::CheckPass(pass);
				isTrue = true;
			}

			catch (const logic_error& ex)
			{
				cout << ex.what() << endl;
				system("pause");
				system("cls");
			}

		} while (!isTrue);


		int size = sizeof(pass);

		file.write(reinterpret_cast<const char*>(&size), sizeof(int));

		for (size_t i = 0; i < strlen(pass); i++)
			pass[i] += 3;

		file.write(reinterpret_cast<const char*>(&pass), size);
	}
	string ReadPass()
	{
		ifstream file("Saves/ThereAreNoPassword.dat", ios_base::binary);

		if (!file.good())
			throw logic_error("Error with file");
		if (file.peek() == ifstream::traits_type::eof())
			throw logic_error("No one admin in system");

		int sizePass;
		file.read(reinterpret_cast<char*>(&sizePass), sizeof(int));

		char pass[100];
		file.read(reinterpret_cast<char*>(&pass), sizePass);

		for (size_t i = 0; i < strlen(pass); i++)
			pass[i] -= 3;

		return pass;
	}

	bool IsFirst()
	{
		ifstream fileLog("Saves/ThereAreNoLogin.dat");
		if (fileLog.peek() == ifstream::traits_type::eof())
		{
			fileLog.close();
			return true;
		}

		return false;
	}
	bool EntryAdmin()
	{
		if (IsFirst())
		{
			cout << "You are first admin, go login up\n";
			system("pause");
			system("cls");
			try
			{
				WriteLogin();
				WritePass();
			}
			catch (const logic_error& ex)
			{
				cout << ex.what() << endl;
				system("pause");
				system("cls");
				return false;
			}

			cout << "Admin are succesfully loged\n";
			system("pause");
		}

		system("cls");
		cout << "---Entering-admin---\n";

		string login, pass;
		string loginInSys, passInSys;
		try
		{
			loginInSys = ReadLogin();
			passInSys = ReadPass();
		}
		catch (const logic_error& ex)
		{
			cout << ex.what() << endl;
			system("pause");
			system("cls");
			return false;
		}

		cin.clear();
		bool isTrueLogin = false;;

		while (cin.good())
		{
			cout << "Input login (Input CTRL + Z to go back): ";
			CLEAR;
			getline(cin, login);

			if (login != loginInSys && cin.good())
			{
				cout << "Invalid login\n";
				system("pause");
				system("cls");
			}

			else if(login == loginInSys)
			{
				isTrueLogin = true;
				break;
			}
		}

		cin.clear();

		if (!isTrueLogin)
			return false;

		for (size_t i = 3; i > 0; i--)
		{
			CLEAR;
			pass = GetPassword("Input password, you have " + to_string(i) + " tries more: " );

			if (pass == passInSys)
				return true;

			else
			{
				cout << "Invalid password\n";
				system("pause");
				system("cls");
			}
		}
			return false;
	}

	bool ReadAutoUserLoad()
	{
		ifstream file("Saves/autoLoads.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return 0;
		}

		bool tmp = true;

		file >> tmp;

		return tmp;
	}
	bool ReadAutoQuestLoad()
	{
		ifstream file("Saves/autoLoads.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return 0;
		}

		file.seekg(1);

		bool tmp = true;

		file >> tmp;

		return tmp;
	}
	void SwitchAutoQuestLoad()
	{
		ifstream file("Saves/autoLoads.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}

		bool tmp, tmp1, tmp2, tmp3;

		file >> tmp;
		file >> tmp1;
		file >> tmp2;
		file >> tmp3;

		tmp1 = !tmp1;

		file.close();

		ofstream file1("Saves/autoLoads.txt");

		file1 << tmp << " " << tmp1 << " " << tmp2 << " " << tmp3;
	}
	void SwitchAutoUserLoad()
	{
		ifstream file("Saves/autoLoads.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}

		bool tmp, tmp1, tmp2, tmp3;

		file >> tmp;
		file >> tmp1;
		file >> tmp2;
		file >> tmp3;

		tmp = !tmp;

		file.close();

		ofstream file1("Saves/autoLoads.txt");

		file1 << tmp << " " << tmp1 << " " << tmp2 << " " << tmp3;
	}

	bool ReadAutoUserUpLoad()
	{
		ifstream file("Saves/autoLoads.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return 0;
		}

		file.seekg(3);

		bool tmp = true;

		file >> tmp;

		return tmp;
	}
	bool ReadAutoQuestUpLoad()
	{
		ifstream file("Saves/autoLoads.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return 0;
		}

		file.seekg(5);

		bool tmp = true;

		file >> tmp;

		return tmp;
	}
	void SwitchAutoQuestUpLoad()
	{
		ifstream file("Saves/autoLoads.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}

		bool tmp, tmp1, tmp2, tmp3;

		file.seekg(3);

		file >> tmp;
		file >> tmp1;
		file >> tmp2;
		file >> tmp3;

		tmp3 = !tmp3;

		file.close();

		ofstream file1("Saves/autoLoads.txt");

		file1 << tmp << " " << tmp1 << " " << tmp2 << " " << tmp3;
	}
	void SwitchAutoUserUpLoad()
	{
		ifstream file("Saves/autoLoads.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}

		bool tmp, tmp1, tmp2, tmp3;

		file.seekg(3);

		file >> tmp;
		file >> tmp1;
		file >> tmp2;
		file >> tmp3;

		tmp2 = !tmp2;

		file.close();

		ofstream file1("Saves/autoLoads.txt");

		file1 << tmp << " " << tmp1 << " " << tmp2 << " " << tmp3;
	}

	//users
	bool ShowUsers() const
	{
		if (users.empty())
		{
			cout << "No one user\n";
			return false;
		}

		int counter = 1;

		for (auto& i : users)
			cout << "User #" << counter++ << "\n\t" << i << endl;

		cout << endl;

		return true;
	}
	bool CheckExistLogin(string log)
	{
		for (auto& i : users)
			if (i.GetLogin() == log)
				throw logic_error("This login is exist");
	}
	void AddUser()
	{
		string login, pass;

		bool isTrue = false;

		do
		{
			system("cls");
			cout << "Input login: ";
			CLEAR;
			getline(cin, login);

			try
			{
				CheckExistLogin(login);
				Founders::CheckLogin(login);
				isTrue = true;
			}

			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
				system("pause");
			}

		} while (!isTrue);
		isTrue = false;
		do
		{
			system("cls");
			CLEAR;
			pass = GetPassword();

			try
			{
				Founders::CheckPass(pass);
				isTrue = true;
			}

			catch (const exception& ex)
			{
				cout << ex.what() << endl;
				system("pause");
			}

		} while (!isTrue);

		User user(login, pass);
		system("cls");
		cin >> user;
		users.push_back(user);

		cout << "User are sucesfully added\n";
	}

	void DeleteUser()
	{
		if (!ShowUsers())
			return;

		int index;
		cout << "Input index: ";

		cin >> index;

		users.erase(users.begin() + --index);
	}
	void UserEdit()
	{
		if (!ShowUsers())
			return;

		int index;
		cout << "Input index: ";

		cin >> index;

		UserEditHelper(users[--index]);
	}
	void UserEditHelper(User& user)
	{
		string tmp;
		int choose;
		do
		{
			cout << "===============\n";
			cout << "|1. Full name |\n";
			cout << "|2. Address   |\n";
			cout << "|3. Number    |\n";
			cout << "|0. Exit      |\n";
			cout << "===============\n";
			cin >> choose;

			switch (choose)
			{
			case 1:
				cout << "Input new user full name: ";
				CLEAR;
				getline(cin, tmp);
				user.SetFullName(tmp);
				cout << "Full name are succesfullt edit\n";
				break;

			case 2:
				cout << "Input new user address: ";
				CLEAR;
				getline(cin, tmp);
				user.SetAddress(tmp);
				cout << "Address are succesfullt edit\n";
				break;

			case 3:
				cout << "Input new user number: ";
				CLEAR;
				getline(cin, tmp);
				user.SetNumber(tmp);
				cout << "Number are succesfullt edit\n";
				break;

			case 0:
				return;

			default:
				cout << "Input right digit (1-3)\n";
				break;
			}
			system("pause");

		} while (choose != 0);
	}

	//Questions
	void AddQuestAnsw()
	{
		if (!Shows::ShowAllCategories(tests))
			cout << "No one categories yet\n";

		string categorie;
		cout << "Input category to that you want add new question (you can input new category): ";
		CLEAR;
		getline(cin, categorie);

		int nCategor = -1;
		try
		{
			nCategor = Founders::GetCategIndByName(categorie, tests);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			return;
		}
		if (nCategor == -1)
		{
			cout << "No one category with title " << categorie << " will be create new category " << endl;
			tests.categories.push_back(categorie);
			nCategor = tests.categories.size() - 1;
		}

		if (!Shows::ShowTestsInCurrentCategorie(&tests.categories[nCategor]))
			cout << "No one tests in this categ yet\n";

		string test;
		cout << "Input test to that you want add new question (you can input new test, it will be create): ";
		CLEAR;
		getline(cin, test);

		int nTest = -1;
		try
		{
			nTest = Founders::GetTestIndByName(test, tests.categories[nCategor]);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			return;
		}

		if (nTest == -1)
		{
			cout << "No one test with title " << test << " will be create new test " << endl;
			tests.categories[nCategor].testsInCat.push_back(test);
			nTest = tests.categories[nCategor].testsInCat.size() - 1;
		}


		string quest;
		cout << "Input question: ";
		CLEAR;
		getline(cin, quest);

		string answers[4];

		for (size_t i = 0; i < 4; i++)
		{
			cout << "Input question #" << i + 1 << ": ";
			getline(cin, answers[i]);
		}

		bool isRight;
		int rightAnsw;
		do
		{
			isRight = true;
			cout << "Input index of right question: ";
			cin >> rightAnsw;

			if (rightAnsw < 1 || rightAnsw > 4)
			{
				cout << "Input right index\n";
				isRight = false;
			}

		} while (!isRight);

		tests.categories[nCategor].testsInCat[nTest].QA.push_back(QuestAnsw(quest, answers, rightAnsw - 1));
	}
	void DeleteQuestAnsw()
	{
		Category* catName = Founders::GetCategoryByName(Founders::GetCategoriesName(tests), tests);

		Shows::ShowTestsInCurrentCategorie(catName);

		string test;
		cout << "Input test that quest you want to delete: ";
		CLEAR;
		getline(cin, test);

		CurrentTest* testPtr = Founders::GetTestByName(test, catName);

		if (testPtr == nullptr)
		{
			cout << "Invalid test title\n";
			return;
		}

		if (!Shows::ShowCurrentTest(testPtr))
		{
			cout << "No one quest in test\n";
			return;
		}

		string quest;
		cout << "Input quest: ";
		CLEAR;
		getline(cin, quest);

		int toDel = Founders::GetQuestIndByQuest(testPtr, quest);

		if (toDel == -1)
		{
			cout << "Incorrect question title\n";
			return;
		}

		testPtr->QA.erase(testPtr->QA.begin() + toDel);
	}
	QuestAnsw& ChooseQuestAnsw()
	{
		Category* catName = Founders::GetCategoryByName(Founders::GetCategoriesName(tests), tests);

		system("cls");
		Shows::ShowTestsInCurrentCategorie(catName);

		string test;
		cout << "Input test that quest you want to edit: ";
		CLEAR;
		getline(cin, test);

		CurrentTest* testPtr = Founders::GetTestByName(test, catName);

		system("cls");
		if (!Shows::ShowCurrentTest(testPtr))
			throw "No one quest in test";

		string quest;
		cout << "Input quest: ";
		CLEAR;
		getline(cin, quest);

		int toEdit = Founders::GetQuestIndByQuest(testPtr, quest);

		if (toEdit == -1)
			throw "Incorrect question title";

		return testPtr->QA[toEdit];
	}
	void EditQuest()
	{
		try
		{
			QuestAnsw& quest = ChooseQuestAnsw();
			EditHelper(quest);
		}

		catch (const char* ex)
		{
			cout << ex << endl;
		}

	}
	void EditHelper(QuestAnsw& quest)
	{
		int choice;

		do
		{
			cout << "=====================\n";
			cout << "|1. Edit question   |\n";
			cout << "|2. Edit answers    |\n";
			cout << "|3. Edit right answ |\n";
			cout << "=====================\n";
			cout << "Input what you want to edit: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
			{
				string newQuest;
				cout << "Input new question: ";
				CLEAR;
				getline(cin, newQuest);

				cout << "This test had quest: " << quest.question << endl;
				cout << "And now this is a: " << newQuest << endl;

				quest.question = newQuest;
				break;
			}

			case 2:
			{
				for (size_t i = 0; i < 4; i++)
					cout << "#" << i + 1 << " " << quest.answers[i] << endl;
				int index;
				cout << "Input index that you want to edit: ";
				cin >> index;

				index--;

				string newQuest;
				cout << "Input new answer for this question: ";
				CLEAR;
				getline(cin, newQuest);

				quest.answers[index] = newQuest;
				break;
			}

			case 3:
			{
				for (size_t i = 0; i < 4; i++)
					cout << "#" << i + 1 << " " << quest.answers[i] << endl;
				int newRight;
				cout << "What answer you want to do right: ";
				cin >> newRight;

				newRight--;

				quest.indexCorrect = newRight;
				break;
			}
			default:
				cout << "Input right value (1 - 3)\n";
				break;
			}
		} while (choice < 1 || choice > 3);
	}

	//Test
	void AddNewTest()
	{
		if (!Shows::ShowAllCategories(tests))
			cout << "No one categories yet\n";

		string categorie;
		cout << "Input category to that you want add test (you can input new category): ";
		CLEAR;
		getline(cin, categorie);

		int nCategor = -1;
		try
		{
			nCategor = Founders::GetCategIndByName(categorie, tests);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			return;
		}

		bool isNew = false;

		if (nCategor == -1)
		{
			isNew = true;

			if (isdigit(categorie.front()))
			{
				cout << "Unresolved title (title can't start from digit)\n";
				return;
			}
			cout << "No one category with title " << categorie << " will be create new category " << endl;
			nCategor = tests.categories.size();
		}

		string test;
		cout << "Input new title of test: ";
		CLEAR;
		getline(cin, test);


		if (isdigit(test.front()))
		{
			cout << "Unresolved title (title can't start from digit)\n";
			return;
		}

		if (isNew)
			tests.categories.push_back(categorie);

		tests.categories[nCategor].testsInCat.push_back(test);
	}
	void DeleteTest()
	{
		if (!Shows::ShowAllCategories(tests))
		{
			cout << "No one test yet\n";
			return;
		}

		string cat;
		cout << "Input category title that have your test: ";
		CLEAR;
		getline(cin, cat);

		Category* catPtr = Founders::GetCategoryByName(cat, tests);

		if (catPtr == nullptr)
		{
			cout << "Invalid category name\n";
			system("pause");
			return;
		}

		if (!Shows::ShowTestsInCurrentCategorie(catPtr))
		{
			cout << "This category don't have any test\n";
			system("pause");
			return;
		}

		string test;
		cout << "Input test title: ";
		CLEAR;
		getline(cin, test);

		int nTest = -1;
		try
		{
			nTest = Founders::GetTestIndByName(test, catPtr);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what();
			return;
		}

		if (nTest == -1)
		{
			cout << "Invalid test title\n";
			system("pause");
			return;
		}

		catPtr->testsInCat.erase(catPtr->testsInCat.begin() + nTest);
	}
	void RenameTest()
	{
		if (!Shows::ShowAllCategories(tests))
		{
			cout << "No one test yet\n";
			return;
		}

		string cat;
		cout << "Input category title that have your test: ";
		CLEAR;
		getline(cin, cat);

		Category* catPtr = Founders::GetCategoryByName(cat, tests);

		if (catPtr == nullptr)
		{
			cout << "Invalid category name\n";
			system("pause");
			return;
		}

		if (!Shows::ShowTestsInCurrentCategorie(catPtr))
		{
			cout << "This category don't have any test\n";
			system("pause");
			return;
		}

		string test;
		cout << "Input test title: ";
		CLEAR;
		getline(cin, test);

		CurrentTest* testPtr = Founders::GetTestByName(test, catPtr);

		if (testPtr == nullptr)
		{
			cout << "Invalid test title\n";
			system("pause");
			return;
		}

		string newTitle;
		cout << "Input new test title: ";
		CLEAR;
		getline(cin, newTitle);

		testPtr->SetName(newTitle);
	}

	//Categories
	void AddNewCategorie()
	{
		cout << "Input new category name: ";
		string catName;
		CLEAR;
		getline(cin, catName);

		if (isdigit(catName.front()))
		{
			cout << "Unresolved title (title can't start from digit)\n";
			return;
		}

		try
		{
			if (Founders::GetCategIndByName(catName, tests) != -1)
			{
				cout << "This categ name is exist\n";
				return;
			}
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			return;
		}

		tests.categories.push_back(catName);
	}
	void DeleteCateg()
	{
		if (!Shows::ShowAllCategories(tests))
		{
			cout << "No one categories\n";
			return;
		}

		cout << "Input category name: ";
		string catName;
		CLEAR;
		getline(cin, catName);

		int index;
		try
		{
			index = Founders::GetCategIndByName(catName, tests);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			return;
		}

		if (index == -1)
		{
			cout << "Invalid category name\n";
			return;
		}

		tests.categories.erase(tests.categories.begin() + index);
	}
	void RenameCateg()
	{
		cout << "Input old category name: ";
		string catName;
		CLEAR;
		getline(cin, catName);

		int index;
		try
		{
			index = Founders::GetCategIndByName(catName, tests);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			return;
		}

		if (index == -1)
		{
			cout << "Invalid old category name\n";
			return;
		}

		cout << "Input mews category name: ";
		string newCatName;
		CLEAR;
		getline(cin, newCatName);

		tests.categories[index].catName = newCatName;
	}

	//Statistic
	void ShowStatisticByCurrentPeople()
	{
		ifstream file("Saves/Statistic.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}
		if (file.peek() == fstream::traits_type::eof())
		{
			cout << "File is empty\n";
			return;
		}

		if (!ShowUsers())
			return;
		string fullName;
		cout << "WARNING! This is't all users, you can know user with other fullname\n";
		cout << "What full name in person, which stat. you want to see: ";
		CLEAR;
		getline(cin, fullName);

		Statistic tmp{};
		bool isOne = false;

		while (!file.eof())
		{
			file >> tmp;

			if (Founders::FoundPersonByLogin(tmp.whoLog, users) == fullName)
			{
				tmp.ShowCategTitle();
				tmp.ShowTestTitle();
				tmp.ShowStat();
				cout << endl;
				isOne = true;
			}
		}

		if (!isOne)
			cout << "Invalid user name or this user don't go any test\n";

	}
	void ShowStatisticByCurrentCategory()
	{
		ifstream file("Saves/Statistic.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}
		if (file.peek() == fstream::traits_type::eof())
		{
			cout << "File is empty\n";
			return;
		}

		Shows::ShowAllCategories(tests);

		string category;
		cout << "Input category what you want to see: ";
		CLEAR;
		getline(cin, category);

		Statistic tmp{};
		bool isOne = false;

		while (!file.eof())
		{
			file >> tmp;

			if (tmp.categTitle == category)
			{
				cout << "Who: " << Founders::FoundPersonByLogin(tmp.whoLog, users) << endl;
				tmp.ShowTestTitle();
				tmp.ShowStat();
				cout << endl;
				isOne = true;
			}
		}

		if (!isOne)
			cout << "No one person don't goind this category\n";

	}
	void ShowStatisticByCurrentTest()
	{
		ifstream file("Saves/Statistic.txt");

		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}
		if (file.peek() == fstream::traits_type::eof())
		{
			cout << "File is empty\n";
			return;
		}

		Shows::ShowAllCategories(tests);

		string category;
		cout << "Input category that have your need test (this is not all categories, you can know more): ";
		CLEAR;
		getline(cin, category);

		Category* catPtr = Founders::GetCategoryByName(category, tests);

		Shows::ShowTestsInCurrentCategorie(catPtr);

		string test;
		cout << "Input test that you want to see (this is not all tests, you can know more): ";
		CLEAR;
		getline(cin, test);

		Statistic tmp{};
		bool isOne = false;

		cout << "Test: " << category << endl;
		while (!file.eof())
		{
			file >> tmp;

			if (tmp.currTestTitle == test && tmp.categTitle == category)
			{
				cout << "Who: " << Founders::FoundPersonByLogin(tmp.whoLog, users);
				tmp.ShowStat();
				cout << endl;
				isOne = true;
			}
		}

		if (!isOne)
			cout << "No one person don't goind this test\n";

	}

	//Loads
	void UpLoadAllUsers()
	{
		ifstream file("Saves/Users.txt");

		if (!file.good())
			return;

		if (file.peek() == ifstream::traits_type::eof())
		{
			cout << "WARNING! No one test in file\n";
			system("pause");
			system("cls");
			return;
		}

		User tmp;

		users.clear();

		while (file.peek() != fstream::traits_type::eof())
		{
			file >> tmp;

			users.push_back(tmp);
		}
	}
	void LoadAllUsers()
	{
		ofstream file("Saves/Users.txt");

		if (!file.good())
			return;

		for (auto& i : users)
			file << i;
	}
	void UpLoadAllTest()
	{
		ifstream file("Saves/Questions.txt");

		if (!file.good())
			return;

		if (file.peek() == ifstream::traits_type::eof())
		{
			cout << "WARNING! No one test in file\n";
			system("pause");
			system("cls");
			return;
		}

		tests.categories.clear();

		file >> tests;
	}
	void LoadAllTest()
	{
		ofstream file("Saves/Questions.txt");

		if (!file.good())
			return;

		file << tests;
	}

	void MainAdminMenu()
	{
		// Change login
		// Change password

		// ShowAllUsers
		// add new user
		// dlete user
		// edit user

		// add qustion
		// delete question
		// edit quest

		// add categories
		// del categories
		// rename categories

		// show stat by cur person

		int choice;
		do
		{
			system("cls");
			cout << "================\n";
			cout << "|1. Users      |\n";
			cout << "|2. Quesions   |\n";
			cout << "|3. Test       |\n";
			cout << "|4. Categories |\n";
			cout << "|5. Statistic  |\n";
			cout << "|6. Settings   |\n";
			cout << "|0. Exit       |\n";
			cout << "================\n";
			cout << "Input your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				UsersMenu();
				break;

			case 2:
				QuestionsMenu();
				break;

			case 3:
				TestMenu();
				break;

			case 4:
				CategoriesMenu();
				break;

			case 5:
				StatisticMenu();
				break;

			case 6:
				SettingsMenu();
				break;

			case 0:
				return;

			default:
				cout << "Input right digit (0-5)\n";
				break;
			}

		} while (choice != 0);
	}

	void UsersMenu()
	{
		int choice;
		do
		{
			system("cls");
			cout << "====================\n";
			cout << "|1. Show all users |\n";
			cout << "|2. Add new user   |\n";
			cout << "|3. Delete user    |\n";
			cout << "|4. Edit user      |\n";
			cout << "|0. Go back        |\n";
			cout << "====================\n";
			cout << "Input your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				ShowUsers();
				break;

			case 2:
				AddUser();
				break;

			case 3:
				DeleteUser();
				break;

			case 4:
				UserEdit();
				break;

			case 0:
				return;

			default:
				cout << "Input right digit (0-4)\n";
				break;
			}
			system("pause");

		} while (choice != 0);
	}
	void QuestionsMenu()
	{
		int choice;
		do
		{
			system("cls");
			cout << "========================\n";
			cout << "|1. Show all questions |\n";
			cout << "|2. Add question       |\n";
			cout << "|3. Delete question    |\n";
			cout << "|4. Edit question      |\n";
			cout << "|0. Go back            |\n";
			cout << "========================\n";
			cout << "Input your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				Shows::ShowAllQuest(tests);
				break;

			case 2:
				AddQuestAnsw();
				break;

			case 3:
				DeleteQuestAnsw();
				break;

			case 4:
				EditQuest();
				break;

			case 0:
				return;

			default:
				cout << "Input right digit (0-4)\n";
				break;
			}

			system("pause");

		} while (choice != 0);
	}
	void CategoriesMenu()
	{
		int choice;

		do
		{
			system("cls");
			cout << "=========================\n";
			cout << "|1. Show all categories |\n";
			cout << "|2. Add category        |\n";
			cout << "|3. Delete category     |\n";
			cout << "|4. Rename category     |\n";
			cout << "|0. Go back             |\n";
			cout << "=========================\n";
			cout << "Input your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				Shows::ShowAllCategories(tests);
				break;

			case 2:
				AddNewCategorie();
				break;

			case 3:
				DeleteCateg();
				break;

			case 4:
				RenameCateg();
				break;

			case 0:
				return;

			default:
				cout << "Input right digit (0-4)\n";
				break;
			}

			system("pause");

		} while (choice != 0);

	}
	void TestMenu()
	{
		int choice;

		do
		{
			system("cls");
			cout << "=========================\n";
			cout << "|1. Show all tests      |\n";
			cout << "|2. Add test            |\n";
			cout << "|3. Delete test         |\n";
			cout << "|4. Rename test         |\n";
			cout << "|0. Go back             |\n";
			cout << "=========================\n";
			cout << "Input your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				for (auto& i : tests.categories)
					Shows::ShowTestsInCurrentCategorie(&i);

				break;

			case 2:
				AddNewTest();
				break;

			case 3:
				DeleteTest();
				break;

			case 4:
				RenameTest();
				break;

			case 0:
				return;

			default:
				cout << "Input right digit (0-4)\n";
				break;
			}

			system("pause");

		} while (choice != 0);

	}
	void StatisticMenu()
	{
		int choice;

		do
		{
			system("cls");
			cout << "===================================\n";
			cout << "|1. Show stat by current person   |\n";
			cout << "|2. Show stat by current category |\n";
			cout << "|3. Show stat by current test     |\n";
			cout << "|0. Go back                       |\n";
			cout << "===================================\n";
			cout << "Input your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				ShowStatisticByCurrentPeople();
				break;

			case 2:
				ShowStatisticByCurrentCategory();
				break;

			case 3:
				ShowStatisticByCurrentTest();
				break;

			case 0:
				return;

			default:
				cout << "Input right digit (0-4)\n";
				break;
			}

			system("pause");

		} while (choice != 0);
	}
	void SettingsMenu()
	{
		int choice;
		do
		{
			system("cls");
			cout << "=================================\n";
			cout << "|1. Edit admin entry data       |\n";
			cout << "|2. Load questions              |\n";
			cout << "|3. Upload questions            |\n";
			cout << "|4. Load users                  |\n";
			cout << "|5. Upload users                |\n";
			cout << "|6. Auto load users:      " << std::setw(5) << boolalpha << ReadAutoUserLoad() << noboolalpha << " |\n";
			cout << "|7. Auto load question: " << std::setw(7) << boolalpha << ReadAutoQuestLoad() << noboolalpha << " |\n";
			cout << "|8. Auto upload users: " << std::setw(8) << boolalpha << ReadAutoQuestUpLoad() << noboolalpha << " |\n";
			cout << "|9. Auto upload question: " << std::setw(5) << boolalpha << ReadAutoQuestUpLoad() << noboolalpha << " |\n";
			cout << "|0. Go back                     |\n";
			cout << "=================================\n";
			cout << "Input your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				cout << "To change admin login you input right pass and login\n";
				system("pause");
				system("cls");

				if (EntryAdmin())
					AdminAuthorizeEditMenu();
				else
					cout << "Authorize error\n";

				break;

			case 2:
				LoadAllTest();
				break;

			case 3:
				UpLoadAllTest();
				break;

			case 4:
				LoadAllUsers();
				break;

			case 5:
				UpLoadAllUsers();
				break;

			case 6:
				SwitchAutoUserLoad();
				break;

			case 7:
				SwitchAutoQuestLoad();
				break;

			case 8:
				SwitchAutoUserUpLoad();
				break;

			case 9:
				SwitchAutoQuestUpLoad();
				break;

			case 0:
				return;

			default:
				cout << "Input right digit (0-6)\n";
				break;
			}

			system("pause");

		} while (choice != 0);
	}
	void AdminAuthorizeEditMenu()
	{
		int choice;
		do
		{
			system("cls");
			cout << "==============\n";
			cout << "|1. Login    |\n";
			cout << "|2. Password |\n";
			cout << "|0. Exit     |\n";
			cout << "==============\n";
			cout << "Input what you want to edit: ";
			cin >> choice;

			if (choice == 1)
				WriteLogin();

			else if (choice == 2)
				WritePass();

			else if (choice == 0)
			{
				cout << "Data are succesfully changed\n";
				return;
			}

			else
				cout << "Input right digit (0-2)\n";

			system("pause");

		} while (choice != 0);
	}
};

string Founders::FoundPersonByLogin(string login, vector<User> users)
{
	for (auto& i : users)
		if (i.GetLogin() == login)
			return i.GetFullName();

	return string("");
}
User* EntryAsUser(const vector<User>& users)
{
	system("cls");

	if (users.empty())
		throw logic_error("No one user in system");

	string login, pass;
	User* tmp = nullptr;
	bool isTrueLogin = false;
	cin.clear();
	while (cin.good())
	{
		system("cls");
		cout << "Input login (Input CTRL + Z to go back): ";
		CLEAR;
		getline(cin, login);

		for (auto& i : users)
		{
			if (i.GetLogin() == login)
			{
				tmp = const_cast<User*>(&i);
				isTrueLogin = true;
				break;
			}
		}

		if (!isTrueLogin && cin.good())
		{
			cout << "No one user with this login in system\n";
			system("pause");
		}

		else
			break;
	}
	cin.clear();

	if (!isTrueLogin)
		throw - 1;

	for (size_t i = 3; i > 0; i--)
	{
		CLEAR;
		pass = GetPassword("Input password, you have " + to_string(i) + " tries more: ");

		if (tmp->GetPass() == pass)
		{
			cout << "Login is succesfully\n";
			cout << "Welcome " << tmp->GetFullName() << endl;
			system("pause");
			return tmp;
		}

		cout << "Invalid password\n";
		system("pause");
		system("cls");
	}

	throw  logic_error("Authorization error");

}

void EntryMenu()
{
	vector<User> users;
	Test tests;
	Admin admin(users, tests);

	if (admin.ReadAutoUserUpLoad())
		admin.UpLoadAllUsers();
	if (admin.ReadAutoQuestUpLoad())
		admin.UpLoadAllTest();

	int choice;
	do
	{
		system("cls");
		cout << "===================\n";
		cout << "|1. Sign up user  |\n";
		cout << "|2. Sign in user  |\n";
		cout << "|3. Sign in admin |\n";
		cout << "|0. Exit          |\n";
		cout << "===================\n";
		cout << "Input your choose: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			admin.AddUser();
			system("pause");
			break;

		case 2:
			try
			{
				User* user = EntryAsUser(users);
				user->MainUserMenu(tests);
			}

			catch (const logic_error& ex)
			{
				cout << ex.what() << endl;
				system("pause");
				break;
			}
			catch (...)
			{
				break;
			}
			break;

		case 3:
			if (admin.EntryAdmin())
				admin.MainAdminMenu();

			else
				cout << "Authtification error\n";

			system("pause");
			break;

		case 0:
			cout << "Good bye\n";
			break;

		default:
			cout << "Input right choice (0-3)\n";
			break;
		}

	} while (choice != 0);

	if (admin.ReadAutoUserLoad())
		admin.LoadAllUsers();
	if (admin.ReadAutoQuestLoad())
		admin.LoadAllTest();
}

int main()
{
	srand(time(nullptr));

	EntryMenu();

	return 0;
}