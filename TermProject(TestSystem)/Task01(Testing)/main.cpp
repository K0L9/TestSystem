#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

struct QuestAnsw
{
	string question;
	string answers[4];
	int indexCorrect;

	QuestAnsw(string quest, string* answers, int correct)
		:question(quest), indexCorrect(correct)
	{
		for (size_t i = 0; i < 4; i++)
			this->answers[i] = answers[i];
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

	friend class Admin;
	friend class User;
	friend class Shows;
	friend class Founders;
};

class Category
{
private:
	string catName;
	vector<QuestAnsw> QA;

	friend class Test;

public:
	Category()
	{

	}

	Category(string catName)
		:catName(catName)
	{

	}

	string GetName() const
	{
		return catName;
	}

	friend class Admin;
	friend class User;
	friend class Shows;
	friend class Founders;
	friend class Statistic;

	friend ifstream& operator>>(ifstream& in, Category& cat)
	{
		getline(in, cat.catName);

		if (cat.catName[0] == ' ')
			cat.catName.erase(0, 1);

		return in;
	}

};

class Test
{
private:
	vector <Category> categories;
public:

	friend class Admin;
	friend class User;
	friend class Shows;
	friend class Founders;

};

Test test;

class Shows 
{
public:
	static bool ShowCategories()
	{
		if (test.categories.empty())
		{
			cout << "Ask admin to add categories\n";
			return false;
		}

		int counter = 1;

		for (auto& i : test.categories)
			cout << "#" << counter++ << " " << i.catName << endl;

		return true;
	}

	static bool ShowAllCategories()
	{
		if (test.categories.empty())
			return false;

		int counter = 0;
		for (auto& i : test.categories)
			cout << "#" << ++counter << " " << i.catName << endl;
	}
	static bool ShowCurrentCategorie(Category* cat)
	{
		if (cat == nullptr)
		{
			cout << "No one category with this name\n";
			return false;
		}

		if (cat->QA.empty())
		{
			cout << "This category not have any quest\n";
			return false;
		}

		cout << "Category: " << cat->catName << endl;

		for (auto& i : cat->QA)
		{
			cout << "\t Question: " << i.question << endl;

			for (size_t k = 0; k < 4; k++)
				cout << "\t\tAnswer #" << k + 1 << ": " << i.answers[k] << endl;

			cout << "\t\t\tRight answer: " << i.GetTrueAnswer() << endl;
		}
		return true;
	}
	static void ShowAllQuest()
	{
		int counter = 0;
		for (auto& i : test.categories)
		{
			cout << "Category #" << ++counter << " " << i.catName << endl;
			for (auto& j : i.QA)
			{
				cout << "\t Question: " << j.question << endl;
				for (size_t k = 0; k < 4; k++)
				{
					cout << "\t\tAnswer #" << k + 1 << ": " << j.answers[k] << endl;
				}
				cout << "\t\t\tRight answer: " << j.GetTrueAnswer() << endl;
			}
		}
	}
};

class Founders
{
public:
	static Category* GetCategoryByName(string catName)
	{
		for (auto& i : test.categories)
			if (i.catName == catName)
				return &i;

		return nullptr;
	}
	static int GetCategIndex()
	{
		if (!Shows::ShowCategories())
			return -1;

		int userCateg;

		cout << "Input categories index: ";
		cin >> userCateg;

		if (userCateg < 0 || userCateg > test.categories.size())
		{
			cout << "Input right index\n";
			return -1;
		}

		return --userCateg;
	}
	static int GetCategIndByName(string categorie)
	{
		for (size_t i = 0; i < test.categories.size(); i++)
			if (test.categories[i].catName == categorie)
				return i;

		return -1;
	}
	static string GetCategoriesName()
	{
		string catName;

		if (!Shows::ShowAllCategories())
		{
			cout << "No one category\n";
			return "";
		}

		cout << "Input category: ";
		cin.ignore(cin.rdbuf()->in_avail());
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
	static int GetQuestIndByQuest(const Category* cat, string quest)
	{
		int counter = 0;
		for (auto& i : cat->QA)
		{
			if (i.question == quest)
				return counter;

			counter++;
		}

		return -1;
	}
};

class User;
class Statistic
{
public:
	bool* fullAnsw;
	Category* categ;
	User* who;
	int rightRes;
	double rightInProc;
	int size;

public:
	Statistic(User* who = nullptr, Category* categ = nullptr, bool* fullAnsw = nullptr, int rightRes = 0, double rightInProc = 0, int size = 0)
		:who(who), categ(categ), fullAnsw(fullAnsw), rightRes(rightRes), rightInProc(rightInProc), size(size)
	{
	}

	friend ofstream& operator<<(ofstream& out, const Statistic& stat);

	friend ifstream& operator>>(ifstream& in, Statistic& stat);

	friend ostream& operator<<(ostream& out, const Statistic& stat)
	{}

	void ShowStatWithoutName()
	{
		cout << "Correct: " << this->rightRes  << " / " << size << endl;
		cout << "Right in proc.: " << rightInProc << "%" << endl;
	}

	void ShowStatWithCategory()
	{
		cout << "Category name: " << categ->catName << endl;
		cout << "Correct: " << this->rightRes << " / " << size << endl;
		cout << "Right in proc.: " << rightInProc << "%" << endl;
	}

	friend class User;
};

class User
{
private:
	string fullName = "NoFullName";
	string address = "NoAddress";
	string number = "NoNumber";

public:
	

	User()
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

	friend ofstream& operator<<(ofstream& out, const User& user)
	{
		out << user.fullName << endl << user.address << endl << user.number << endl;

		return out;
	}
	friend ostream& operator<<(ostream& out, const User& user)
	{
		out << "Fullname: " << user.fullName << endl;
		out << "\tUser's address: " << user.address << endl;
		out << "\tUser's number: " << user.number << endl;

		return out;
	}

	friend ifstream& operator>>(ifstream& in, User& user)
	{
		string fullName, address, number;

		getline(in, fullName);
		getline(in, address);
		getline(in, number);

		user.SetFullName(fullName);
		user.SetAddress(address);
		user.SetNumber(number);

		return in;
	}
	friend istream& operator>>(istream& in, User& user)
	{
		string fullName, address, number;

		cout << "Input user's fullname: ";
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

	void GoTest()
	{
		if (!Shows::ShowCategories())
			return;

		string categoryName;
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Input category: ";
		getline(cin, categoryName);

		Category* cat = Founders::GetCategoryByName(categoryName);

		if (cat == nullptr)
		{
			cout << "Invalid cat name\n";
			return;
		}

		bool isTrue = false;
		char userAnswer;
		int size = cat->QA.size();
		bool* stat = new bool[size];

		int counter = 0;
		for (auto& i : cat->QA)
		{
			cout << "Answer #" << counter + 1 << " / " << size << endl;

			do
			{
				i.ShowQuestAnsw();

				cout << "Input your answer: ";
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

		Statistic fullStat{ this, cat, stat, nRight, rightInProc, size };

		cout << "RESULTS: \n";

		fullStat.ShowStatWithoutName();
		system("pause");

		ofstream file("Statistic.txt", ios_base::app);

		if (!file.good())
		{
			cout << "Error with statistic.txt file\n";
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
			cout << "|4. Exit                                    |\n";
			cout << "=============================================\n";
			cout << "Input your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				SeeTrueFalse(stat, size, cat);
				break;

			case 2:
				SeeResultsByOtherPeople(cat);
				break;

			case 3:
				SeeOlderByCurrPerson(cat);
				break;

			case 4:
				break;

			default:
				cout << "Input right value\n";
				break;
			}
			system("pause");
		} while (choice != 4);

		file << fullStat;
	}

	bool ShowPersonStat()
	{
		ifstream file("Statistic.txt");
		if (!file.good())
		{
			cout << "Error with file\n";
			return false;
		}

		Statistic tmp{ &User(), &Category() };

		bool isOne = false;

		while (file.peek() != ifstream::traits_type::eof())
		{
			file >> tmp;
			if (tmp.who->fullName == this->fullName)
			{
				isOne = true;
				tmp.ShowStatWithCategory();
			}
		}

		if (!isOne)
		{
			cout << "Not found any your test result\n";
			return false;
		}

		return true;
	}

	void SeeTrueFalse(const bool* const answers, int answerSize, const Category* const cat)
	{
		for (size_t i = 0; i < answerSize; i++)
		{
			cout << "\n" << i + 1 << ") " << cat->QA[i].question << " : " << boolalpha << answers[i] << endl;
			if (!answers[i])
				cout << "\tRight answer: " << cat->QA[i].GetTrueAnswer() << endl;
		}
	}

	void SeeOlderByCurrPerson(const Category* const cat)
	{
		ifstream file("Statistic.txt");
		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}

		Statistic tmp{ &User(), &Category() };

		bool isOne = false;


		while (file.peek() != ifstream::traits_type::eof())
		{
			file >> tmp;
			if (tmp.who->fullName == this->fullName && tmp.categ->catName == cat->catName)
			{
				isOne = true;
				tmp.ShowStatWithoutName();
				cout << endl;
			}
		}

		if (!isOne)
		{
			cout << "You didn't go this test\n";
			return;
		}
	}

	void SeeResultsByOtherPeople(const Category* const cat)
	{
		ifstream file("Statistic.txt");
		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}

		Statistic tmp{ &User(), &Category() };

		bool isOne = false;


		while (file.peek() != ifstream::traits_type::eof())
		{
			file >> tmp;
			if (tmp.categ->catName == cat->catName)
			{
				cout << "Who: " << tmp.who->fullName << endl;
				isOne = true;
				tmp.ShowStatWithoutName();
				cout << endl;
			}
		}

		if (!isOne)
		{
			cout << "You are first who going this test\n";
			return;
		}
	}
};

ifstream& operator>>(ifstream& in, Statistic& stat)
{
	in >> *stat.who;
	in >> stat.rightRes;
	in >> stat.rightInProc;
	in >> stat.size;
	in >> *stat.categ;

	return in;
}
ofstream& operator<<(ofstream& out, const Statistic& stat)
{
	out << *(stat.who) << stat.rightRes << " " << stat.rightInProc << " " << stat.size << " " << stat.categ->GetName() << endl;

	return out;
}

class Admin
{
private:
	vector <User> users;

public:
	void FirstEntry()
	{
		WriteLogin();
	}

	void WriteLogin()
	{
		ofstream file("ThereAreNoLogin.dat", ios_base::binary || ios::app);

		if (!file.good())
		{
			cout << "Error with file\n";
			return;
		}

		char login[100];
		cout << "Input login: ";
		cin.getline(login, 100);

		int size = sizeof(login);

		file.write(reinterpret_cast<const char*>(&size), sizeof(int));

		for (size_t i = 0; i < strlen(login); i++)
			login[i] -= 2;

		file.write(reinterpret_cast<const char*>(&login), size);
	}
	string ReadLogin()
	{
		ifstream file("ThereAreNoLogin.dat", ios_base::binary);

		if (!file.good())
		{
			throw "Error with file";
		}
		if (file.peek() == ifstream::traits_type::eof())
		{
			throw "No one admin in system";
		}

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
		ofstream file("ThereAreNoPassword.dat", ios_base::binary || ios::app);

		if (!file.good())
		{
			throw "Error with file";
		}

		char pass[100];
		cout << "Input password: ";
		cin.getline(pass, 100);

		int size = sizeof(pass);

		file.write(reinterpret_cast<const char*>(&size), sizeof(int));

		for (size_t i = 0; i < strlen(pass); i++)
			pass[i] += 3;

		file.write(reinterpret_cast<const char*>(&pass), size);
	}
	string ReadPass()
	{
		ifstream file("ThereAreNoPassword.dat", ios_base::binary);

		if (!file.good())
		{
			throw "Error with file";
		}
		if (file.peek() == ifstream::traits_type::eof())
		{
			throw "No one admin in system";
		}

		int sizePass;
		file.read(reinterpret_cast<char*>(&sizePass), sizeof(int));

		char pass[100];
		file.read(reinterpret_cast<char*>(&pass), sizePass);

		for (size_t i = 0; i < strlen(pass); i++)
			pass[i] -= 3;

		return pass;
	}

	void Entry()
	{

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
	void AddUser()
	{
		User tmpUser;
		cin >> tmpUser;

		users.push_back(tmpUser);
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
			cout << "===============\n";
			cout << "Input what you want to edit: ";
			cin >> choose;

			if (choose < 1 || choose > 3)
				cout << "Input right value (1-3)";

		} while (choose < 1 || choose > 3);

		switch (choose)
		{
		case 1:
			cout << "Input new user full name: ";
			cin.ignore(cin.rdbuf()->in_avail());
			getline(cin, tmp);
			user.SetFullName(tmp);
			break;

		case 2:
			cout << "Input new user address: ";
			cin.ignore(cin.rdbuf()->in_avail());
			getline(cin, tmp);
			user.SetAddress(tmp);
			break;

		case 3:
			cout << "Input new user number: ";
			cin.ignore(cin.rdbuf()->in_avail());
			getline(cin, tmp);
			user.SetNumber(tmp);
			break;

		default:
			break;
		}
	}

	//Questions
	void AddQuestAnsw()
	{
		if (!Shows::ShowAllCategories())
			cout << "No one categories yet\n";

		string categorie;
		cout << "Input category: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, categorie);

		bool isNew = false;

		int nCategor = Founders::GetCategIndByName(categorie);
		if (nCategor == -1)
		{
			isNew = true;
			cout << "No one category with title " << categorie << " will be create new category " << endl;
			test.categories.push_back(categorie);
		}

		//if (test.categories[nCategor].QA.size() > 12)
		//{
		//	cout << "This category have 12 answers yet\n";
		//	return;
		//}

		string quest;
		cout << "Input question: ";
		cin.ignore(cin.rdbuf()->in_avail());
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

		if (isNew || categorie.size() == 0)
			test.categories.back().Category::QA.push_back(QuestAnsw(quest, answers, rightAnsw - 1));

		else
			test.categories[nCategor].Category::QA.push_back(QuestAnsw(quest, answers, rightAnsw - 1));
	}
	void DeleteQuestAnsw()
	{
		Category* catName = Founders::GetCategoryByName(Founders::GetCategoriesName());

		Shows::ShowCurrentCategorie(catName);

		string quest;
		cout << "Input quest that you want to delete: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, quest);

		int toDel = Founders::GetQuestIndByQuest(catName, quest);

		if (toDel == -1)
		{
			cout << "Incorrect answer name\n";
			return;
		}

		catName->QA.erase(catName->QA.begin() + toDel);
	}
	void EditQuest()
	{
		Category* catName = Founders::GetCategoryByName(Founders::GetCategoriesName());

		Shows::ShowCurrentCategorie(catName);

		string quest;
		cout << "Input quest that you want to delete: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, quest);

		int toDel = Founders::GetQuestIndByQuest(catName, quest);

		if (toDel == -1)
		{
			cout << "Incorrect answer name\n";
			return;
		}

		EditHelper(catName->QA[toDel]);
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
				cin.ignore(cin.rdbuf()->in_avail());
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
				cin.ignore(cin.rdbuf()->in_avail());
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
	void DelQuestAnsw()
	{
		if (Founders::GetCategIndByName(Founders::Founders::GetCategoriesName()) == -1)
		{
			cout << "Incorrect category name\n";
			return;
		}

	}

	//Categories
	void AddNewCategorie()
	{
		cout << "Input new category name: ";
		string catName;
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, catName);

		if (Founders::GetCategIndByName(catName) != -1)
		{
			cout << "This categ name is exist\n";
			return;
		}

		test.categories.push_back(catName);
	}
	void DeleteCateg()
	{
		cout << "Input category name: ";
		string catName;
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, catName);

		int index = Founders::GetCategIndByName(catName);

		if (index == -1)
		{
			cout << "Invalid category name\n";
			return;
		}

		test.categories.erase(test.categories.begin() + index);
	}
	void RenameCateg()
	{
		cout << "Input old category name: ";
		string catName;
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, catName);

		int index = Founders::GetCategIndByName(catName);

		if (index == -1)
		{
			cout << "Invalid old category name\n";
			return;
		}

		cout << "Input mews category name: ";
		string newCatName;
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, newCatName);

		test.categories[index].catName = newCatName;
	}

	//Statistic
	void ShowStatisticByCurrentPeople()
	{
		ifstream file("Statistic.txt");

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

		string fullName;
		cout << "What full name in person, which stat. you want to see: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, fullName);

		Statistic tmp(&User(), &Category());
		bool isOne = false;

		while (!file.eof())
		{
			file >> tmp;

			if (tmp.who->GetFullName() == fullName)
			{
				tmp.ShowStatWithCategory();
				cout << endl;
				isOne = true;
			}
		}

		if (!isOne)
			cout << "Invalid user name or this user don't go any test\n";

	}

	void ShowMenu()
	{
		cout << "=================\n";
		cout << "| 1. Users      | \n";
		cout << "| 2. Questions  |\n";
		cout << "| 3. Categories |\n";
		cout << "=================\n";
	}

	/*void GoTest()
	{
		if (!Shows::ShowCategories())
			return;

		string categoryName;
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Input category: ";
		getline(cin, categoryName);

		Category* cat = Founders::GetCategoryByName(categoryName);

		if (cat == nullptr)
		{
			cout << "Invalid cat name\n";
			return;
		}

		bool isTrue = false;
		char userAnswer;
		int size = cat->QA.size();
		bool* stat = new bool[size];

		int counter = 0;
		for (auto& i : cat->QA)
		{
			cout << "Answer #" << counter + 1 << " / " << size << endl;

			do
			{
				i.ShowQuestAnsw();

				cout << "Input your answer: ";
				cin >> userAnswer;
			} while (!Founders::CheckAndConvertAnswer(userAnswer));

			if (i.CheckAnsw(userAnswer))
				stat[counter] = true;

			else
				stat[counter] = false;

			counter++;
		}

		int nRight = Founders::CountRightAnsw(stat, size);
		int rightInProc = (nRight * 100) / size;
		cout << "RESULTS: \n";

		cout << "Correct: " << nRight << endl;
		cout << "Right in proc.: " << rightInProc << "%" << endl;
	};*/


};

int main()
{
	srand(time(nullptr));

	Admin kolya;
	kolya.AddQuestAnsw();
	
	User user;
	user.GoTest();

	kolya.ShowStatisticByCurrentPeople();

	return 0;
}