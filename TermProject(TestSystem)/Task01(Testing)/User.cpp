#include "User.h"

//Ctors
User::User(string ulogin, string upass)
	: login(ulogin), pass(upass)
{

}
User::User(string fullName, string address, string number)
{
	SetFullName(fullName);
	SetAddress(address);
	SetNumber(number);
}

//Setters
bool User::SetFullName(string fullName)
{
	if (fullName.empty())
		return false;

	this->fullName = fullName;
	return true;
}
bool User::SetAddress(string address)
{
	if (address.empty())
		return false;

	this->address = address;
	return true;
}
bool User::SetNumber(string number)
{
	if (number.empty())
		return false;

	this->number = number;
	return true;
}
bool User::SetLogin(string loginU)
{
	if (loginU.empty())
		return false;

	const_cast<string&>(this->login) = loginU;
	return true;
}
bool User::SetPass(string passU)
{
	if (passU.empty())
		return false;

	const_cast<string&>(this->pass) = passU;
	return true;
}

//Getters
string User::GetFullName() const
{
	return fullName;
}
string User::GetAddress() const
{
	return address;
}
string User::GetNumber() const
{
	return number;
}
string User::GetLogin() const
{
	return this->login;
}
string User::GetPass() const
{
	return this->pass;
}

//RunTest
bool User::IsPause()
{
	ifstream filePause("Saves/Pause/" + this->login + ".txt");

	if (!filePause.good())
		return false;

	if (filePause.peek() == ifstream::traits_type::eof())
		return false;

	return true;

	filePause.close();
}
void User::LoadTest(Test& tests)
{
	ifstream filePause("Saves/Pause/" + this->login + ".txt");

	if (!filePause.good())
	{
		cout << "Error with file\n";
		return;
	}
	string cat, test;
	int ind;

	getline(filePause, test);
	getline(filePause, cat);
	filePause >> ind;


	Category* catPtr = Founders::GetCategoryByName(cat, tests);
	CurrentTest* testPtr = Founders::GetTestByName(test, catPtr);

	bool* stat = new bool[testPtr->QA.size()];
	for (size_t i = 0; i < ind; i++)
		filePause >> stat[i];

	filePause.close();

	GoTestHelper(testPtr, catPtr, ind, stat);

}
void User::GoTest(Test& tests)
{
	cout << "   TEST RUNNING\n";
	if (!Shows::ShowAllCategories(tests))
		return;

	string categoryName;
	CLEAR;
	cout << "Input category title or index: ";
	getline(cin, categoryName);

	Category* cat = Founders::GetCategoryByName(categoryName, tests);

	if (cat == nullptr)
	{
		cout << "Invalid cat title or index\n";
		return;
	}

	system("cls");
	if (!Shows::ShowTestsInCurrentCategorie(cat))
		return;

	string testName;
	CLEAR;
	cout << "Input test title or index: ";
	getline(cin, testName);

	CurrentTest* currTest = Founders::GetTestByName(testName, cat);

	if (currTest == nullptr)
	{
		cout << "Invalid test title or index\n";
		return;
	}

	bool* stat = new bool[currTest->QA.size()];
	GoTestHelper(currTest, cat, 0, stat);
}
void User::GoTestHelper(CurrentTest* currTest, Category* cat, int currTestInd, bool* stat)
{
	bool isTrue = false;
	char userAnswer;
	int size = currTest->QA.size();

	int counter = currTestInd;
	bool isTrueAnswer = false, isPause = false;
	for (int i = currTestInd; i < size; i++)
	{

		do
		{
			system("cls");
			cout << "Answer #" << counter + 1 << " / " << size << endl;
			currTest->QA[i].ShowQuestAnsw();

			cout << "Input your answer digit or number (Input CTRL + Z  or  P to stay on pause): ";
			cin >> userAnswer;

			if (userAnswer == 'P' || !cin.good())
			{
				isPause = true;
				cin.clear();
				break;
			}

			isTrueAnswer = Founders::CheckAndConvertAnswer(userAnswer);

			if (!isTrueAnswer)
			{
				cout << "Input right answer index or digit (1-4; a-d; A-D; P; CTRL + Z)\n";
				system("pause");
			}

		} while (!isTrueAnswer);

		if (isPause)
		{
			ofstream filePause("Saves/Pause/" + this->login + ".txt");

			filePause << currTest->GetName() << endl << cat->GetName() << endl << i << endl;
			for (size_t j = 0; j < counter; j++)
				filePause << stat[j] << " ";
			filePause << endl;
			filePause.close();
			return;
		}

		if (currTest->QA[i].CheckAnsw(userAnswer))
			stat[counter] = true;

		else
			stat[counter] = false;

		counter++;
	}

	int nRight = Founders::CountRightAnsw(stat, size);
	double rightInProc = (double)(nRight * 100) / size;
	int grade = (12 / size) * nRight;

	Statistic fullStat{ cat->GetName(), currTest->GetName(), this->login, stat, nRight, rightInProc, size, grade };

	cout << "RESULTS: \n";

	fullStat.ShowStat();
	system("pause");

	ofstream file("Saves/Statistic.txt", ios_base::app);

	if (!file.good())
	{
		cout << "Error with Saves/Statistic.txt file\n";
		return;
	}

	remove(string("Saves/Pause/" + this->login + ".txt").c_str());

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
			system("pause");
			break;

		case 2:
			SeeResultsByOtherPeople(currTest);
			system("pause");
			break;

		case 3:
			SeeOlderByCurrPersonByTest(currTest);
			system("pause");
			break;

		case 0:
			file << fullStat;
			return;

		default:
			cout << "Input right value\n";
			system("pause");
			break;
		}
	} while (choice != 0);

}

//Stat
bool User::ShowPersonStat()
{
	ifstream file("Saves/Statistic.txt");
	if (!file.good())
	{
		cout << "Error with file\n";
		return false;
	}

	Statistic tmp{};

	bool isOne = false;

	system("cls");
	cout << "Full Person Stat: \n\n";

	while (file.peek() != ifstream::traits_type::eof())
	{
		file >> tmp;
		if (tmp.whoLog == this->login)
		{
			isOne = true;
			tmp.ShowCategTitle();
			tmp.ShowTestTitle();
			tmp.ShowStat();
			cout << "===============\n";
		}
	}

	if (!isOne)
	{
		cout << "Not found any your test result\n";
		return false;
	}

	return true;
}
void User::SeeTrueFalse(const bool* const answers, int answerSize, const CurrentTest* const test)
{
	system("cls");
	for (size_t i = 0; i < answerSize; i++)
	{
		cout << "\n" << i + 1 << ") " << test->QA[i].question << " : " << boolalpha << answers[i] << endl;
		if (!answers[i])
			cout << "\tRight answer: " << test->QA[i].GetTrueAnswer() << endl;
	}
}
void User::SeeOlderByCurrPersonByCateg(const Category* const cat)
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

	system("cls");
	cout << "Older your result by this category: \n\n";
	while (file.peek() != ifstream::traits_type::eof())
	{
		file >> tmp;

		if (tmp.whoLog == this->login && tmp.categTitle == cat->GetName())
		{
			isOne = true;
			tmp.ShowTestTitle();
			tmp.ShowStat();
			cout << "===============\n";
		}
	}

	if (!isOne)
	{
		cout << "You didn't go this test\n";
		return;
	}
}
void User::SeeOlderByCurrPersonByTest(const CurrentTest* const cat)
{
	ifstream file("Saves/Statistic.txt");
	if (!file.good())
	{
		cout << "Error with file\n";
		return;
	}

	Statistic tmp{};

	bool isOne = false;

	system("cls");
	cout << "Older your result by this test: \n\n";
	while (file.peek() != ifstream::traits_type::eof())
	{
		file >> tmp;

		if (tmp.whoLog == this->login && tmp.currTestTitle == cat->testName)
		{
			isOne = true;
			tmp.ShowStat();
			cout << "===============\n";
		}
	}

	if (!isOne)
	{
		cout << "You didn't go this test\n";
		return;
	}
}
void User::SeeResultsByOtherPeople(const CurrentTest* const cat)
{
	ifstream file("Saves/Statistic.txt");
	if (!file.good())
	{
		cout << "Error with file\n";
		return;
	}

	Statistic tmp{};

	bool isOne = false;

	system("cls");
	cout << "Result of this test by other people: \n\n";

	while (file.peek() != ifstream::traits_type::eof())
	{
		file >> tmp;
		if (tmp.currTestTitle == cat->testName)
		{
			isOne = true;
			tmp.ShowCategTitle();
			tmp.ShowTestTitle();
			tmp.ShowStat();
			cout << "===============\n";
		}
	}

	if (!isOne)
	{
		cout << "You are first who going this test\n";
		return;
	}
}

//Menu
void User::MainUserMenu(Test& tests)
{
	if (IsPause())
	{
		int choice;
		system("cls");
		cout << "            USER MENU\n";
		cout << "=====================================\n";
		cout << "|1. Going old test from pause       |\n";
		cout << "|2. Start new test                  |\n";
		cout << "|3. Show full person stat           |\n";
		cout << "|4. Show statistic by curent test   |\n";
		cout << "|5. Show statistic by curent categ. |\n";
		cout << "|0. Log Out                         |\n";
		cout << "=====================================\n";
		cout << "Input your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			system("cls");
			LoadTest(tests);
			break;

		case 2:
			system("cls");
			GoTest(tests);
			break;

		case 3:
			system("cls");
			ShowPersonStat();
			break;

		case 4:
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

		case 5:
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
		MainUserMenu(tests);
	}
	else
	{
		int choice;
		system("cls");
		cout << "            USER MENU\n";
		cout << "=====================================\n";
		cout << "|1. Start test                      |\n";
		cout << "|2. Show full person stat           |\n";
		cout << "|3. Show statistic by curent test   |\n";
		cout << "|4. Show statistic by curent categ. |\n";
		cout << "|0. Log Out                         |\n";
		cout << "=====================================\n";
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
		MainUserMenu(tests);
		system("pause");
	}

}

//Operators
User User::operator=(const User& other)
{
	this->fullName = other.fullName;
	this->address = other.address;
	this->number = other.number;

	return *this;
}
ofstream& operator<<(ofstream& out, const User& user)
{
	string pass{ user.pass };
	string login{ user.login };

	for (size_t i = 0; i < user.pass.size(); i++)
		pass[i] += 3;

	for (size_t i = 0; i < user.login.size(); i++)
		login[i] -= 5;

	out << user.fullName << endl << user.address << endl << user.number << endl << login << endl << pass << endl;

	return out;
}
ostream& operator<<(ostream& out, const User& user)
{
	out << "Fullname: " << user.fullName << endl;
	out << "\tUser's address: " << user.address << endl;
	out << "\tUser's number: " << user.number << endl;
	out << "\tUser's login: " << user.login << endl;
	out << "\tUser's password: " << user.pass << endl;

	return out;
}
ifstream& operator>>(ifstream& in, User& user)
{
	string fullName, address, number, login, pass;

	getline(in, fullName);
	getline(in, address);
	getline(in, number);
	getline(in, login);
	getline(in, pass);

	for (size_t i = 0; i < pass.size(); i++)
		pass[i] -= 3;

	for (size_t i = 0; i < login.size(); i++)
		login[i] += 5;

	user.SetFullName(fullName);
	user.SetAddress(address);
	user.SetNumber(number);
	user.SetLogin(login);
	user.SetPass(pass);

	return in;
}
istream& operator>>(istream& in, User& user)
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