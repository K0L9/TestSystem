#include "Admin.h"

//Admin authorize data
string Admin::ReadLogin()
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
void Admin::WriteLogin(string message)
{
	ofstream file("Saves/ThereAreNoLogin.dat", ios_base::binary || ios::app);

	if (!file.good())
		throw logic_error("Error with file");

	char login[100];
	bool isTrue = false;

	cout << message;
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

void Admin::WritePass()
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
string Admin::ReadPass()
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

bool Admin::IsFirst()
{
	ifstream fileLog("Saves/ThereAreNoLogin.dat");
	if (fileLog.peek() == ifstream::traits_type::eof())
	{
		fileLog.close();
		return true;
	}

	return false;
}
bool Admin::EntryAdmin()
{
	if (IsFirst())
	{
		cout << "You are first admin, go login up\n";
		system("pause");
		system("cls");
		try
		{
			WriteLogin("REGISTER ADMIN");
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
	cout << "ADMIN AUTHORIZE\n";

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

		else if (login == loginInSys)
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
		pass = GetPassword("Input password, you have " + to_string(i) + " tries more: ");

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

//Load data
bool Admin::ReadAutoUserLoad()
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
bool Admin::ReadAutoQuestLoad()
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

void Admin::SwitchAutoQuestLoad()
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
void Admin::SwitchAutoUserLoad()
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

bool Admin::ReadAutoUserUpLoad()
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
bool Admin::ReadAutoQuestUpLoad()
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

void Admin::SwitchAutoQuestUpLoad()
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

	tmp3 = !tmp3;

	file.close();

	ofstream file1("Saves/autoLoads.txt");

	file1 << tmp << " " << tmp1 << " " << tmp2 << " " << tmp3;
}
void Admin::SwitchAutoUserUpLoad()
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

	tmp2 = !tmp2;

	file.close();

	ofstream file1("Saves/autoLoads.txt");

	file1 << tmp << " " << tmp1 << " " << tmp2 << " " << tmp3;
}

// Users
bool Admin::ShowUsers() const
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
bool Admin::CheckExistLogin(string log)
{
	for (auto& i : users)
		if (i.GetLogin() == log)
			throw logic_error("This login is exist");
}

void Admin::AddUser()
{
	string login, pass;

	bool isTrue = false;

	do
	{
		system("cls");
	cout << "    REGISTERING\n";
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
void Admin::DeleteUser()
{
	if (!ShowUsers())
		return;

	int index;
	cout << "Input index: ";

	cin >> index;

	users.erase(users.begin() + --index);
}

void Admin::UserEdit()
{
	if (!ShowUsers())
		return;

	int index;
	cout << "Input index: ";

	cin >> index;

	UserEditHelper(users[--index]);
}
void Admin::UserEditHelper(User& user)
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
void Admin::AddQuestAnsw()
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
void Admin::DeleteQuestAnsw()
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

QuestAnsw& Admin::ChooseQuestAnsw()
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

void Admin::EditQuest()
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
void Admin::EditHelper(QuestAnsw& quest)
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
void Admin::AddNewTest()
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
void Admin::DeleteTest()
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
void Admin::RenameTest()
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
void Admin::AddNewCategorie()
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
void Admin::DeleteCateg()
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
void Admin::RenameCateg()
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
void Admin::ShowStatisticByCurrentPeople()
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
void Admin::ShowStatisticByCurrentCategory()
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
void Admin::ShowStatisticByCurrentTest()
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
void Admin::UpLoadAllUsers()
{
	ifstream file("Saves/Users.txt");

	if (!file.good())
		return;

	if (file.peek() == ifstream::traits_type::eof())
	{
		cout << "WARNING! No one user in file\n";
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
void Admin::LoadAllUsers()
{
	ofstream file("Saves/Users.txt");

	if (!file.good())
		return;

	for (auto& i : users)
		file << i;
}

void Admin::UpLoadAllTest()
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
void Admin::LoadAllTest()
{
	ofstream file("Saves/Questions.txt");

	if (!file.good())
		return;

	file << tests;
}

//Menu's
void Admin::MainAdminMenu()
{
	int choice;
	do
	{
		system("cls");
		cout << "   ADMIN MENU\n";
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

void Admin::UsersMenu()
{
	int choice;
	do
	{
		system("cls");
		cout << "    USER MENU\n";
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
void Admin::QuestionsMenu()
{
	int choice;
	do
	{
		system("cls");
		cout << "     QUESTION MENU\n";
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
void Admin::CategoriesMenu()
{
	int choice;

	do
	{
		system("cls");
		cout << "     CATEGORY MENU\n";
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
void Admin::TestMenu()
{
	int choice;

	do
	{
		system("cls");
		cout << "       TEST MENU\n";
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
void Admin::StatisticMenu()
{
	int choice;

	do
	{
		system("cls");
		cout << "         STATISTIC MENU\n";
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
void Admin::SettingsMenu()
{
	int choice;
	do
	{
		system("cls");
		cout << "           Settings\n";
		cout << "=================================\n";
		cout << "|1. Edit admin entry data       |\n";
		cout << "|2. Load questions              |\n";
		cout << "|3. Upload questions            |\n";
		cout << "|4. Load users                  |\n";
		cout << "|5. Upload users                |\n";
		cout << "|6. Auto load users:      " << std::setw(5) << boolalpha << ReadAutoUserLoad() << noboolalpha << " |\n";
		cout << "|7. Auto load question: " << std::setw(7) << boolalpha << ReadAutoQuestLoad() << noboolalpha << " |\n";
		cout << "|8. Auto upload users: " << std::setw(8) << boolalpha << ReadAutoUserUpLoad() << noboolalpha << " |\n";
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
void Admin::AdminAuthorizeEditMenu()
{
	int choice;
	do
	{
		system("cls");
		cout << "ADMIN AUTH. MENU\n";
		cout << " ==============\n";
		cout << " |1. Login    |\n";
		cout << " |2. Password |\n";
		cout << " |0. Exit     |\n";
		cout << " ==============\n";
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
