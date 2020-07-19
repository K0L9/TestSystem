#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

vector <Category> categories;

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
		out << user.fullName << " " << user.address << " " << user.number << endl;

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

		in >> fullName;
		in >> address;
		in >> number;

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
};

struct QuestAnsw
{
	string question;
	string answers[4];
	int indexCorrect;

	QuestAnsw(string quest, string a1, string a2, string a3, string a4, int correct)
		:question(quest), indexCorrect(correct)
	{
		answers[0] = a1;
		answers[1] = a2;
		answers[2] = a3;
		answers[3] = a4;
	}

	string GetTrueAnswer()
	{
		return answers[indexCorrect];
	}

	void ShowQuestAnsw()
	{
		cout << question << ":\n";

		char tmp = 'A';

		for (int i = 0; i < 4; i++)
			cout << "\t" << tmp++ << ". " << answers[i] << endl;
	}
	friend class Admin;

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

	friend class Admin;
};

class Test
{
public:
	Test()
	{
		int userCateg = GetUserCateg();

		for (size_t i = 0; i < categories[userCateg].QA.size(); i++)
			categories[--userCateg].QA[i].ShowQuestAnsw();

	}

	static bool ShowCategories()
	{
		if (categories.empty())
		{
			cout << "Ask admin to add categories\n";
			return false;
		}

		int counter = 1;

		for (auto& i : categories)
			cout << "#" << counter++ << i.catName << endl;

		return true;
	}

	int GetUserCateg()
	{
		if (!ShowCategories())
			return -1;

		int userCateg;

		cout << "Input categories index: ";
		cin >> userCateg;

		if (userCateg < 0 || userCateg > categories.size())
		{
			cout << "Input right index\n";
			return -1;
		}

		return --userCateg;
	}

	static int FoundCategories(string categorie)
	{
		for (size_t i = 0; i < categories.size(); i++)
			if (categories[i].catName == categorie)
				return i;

		return -1;
	}

	friend class Admin;
};

class Admin
{
private:
	vector <User> users;

public:
	void Entry()
	{

	}

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

	void AddQuestAnsw()
	{
		string categorie;
		cout << "Input categorie: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, categorie);

		bool isNew = false;

		int nCategor = Test::FoundCategories(categorie);
		if (nCategor == -1)
		{
			isNew = true;
			cout << "No one categorie with title " << categorie << " will be create new categorie " << endl;
			categories.push_back(categorie);
		}

		string quest;
		cout << "Input question: ";
		cin >> quest;

		string answer1, answer2, answer3, answer4;

		cout << "Input 4 answers yet: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, answer1);

		cout << "Input 3 answers yet: ";
		getline(cin, answer2);

		cout << "Input 2 answers yet: ";
		getline(cin, answer3);

		cout << "Input 1 answer yet: ";
		getline(cin, answer4);

		int rightAnsw;
		cout << "Input index of right question: ";
		cin >> rightAnsw;

		if (isNew || categorie.size() == 0)
			categories[categorie.size() - 1].Category::QA.push_back(QuestAnsw(quest, answer1, answer2, answer3, answer4, rightAnsw));

		else
			categories[nCategor].Category::QA.push_back(QuestAnsw(quest, answer1, answer2, answer3, answer4, rightAnsw));
	}
};


int main()
{
	srand(time(nullptr));
	Admin kolya;

	kolya.AddQuestAnsw();
	Test test;
	//kolya.AddUser();
	//kolya.AddUser();
	//kolya.ShowUsers();
	//kolya.UserEdit();
	//kolya.ShowUsers();



	return 0;
}