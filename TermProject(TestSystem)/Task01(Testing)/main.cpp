#include "Admin.h"

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
string GetPassword(string message)
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
		cout << "    MAIN MENU\n";
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
string Founders::FoundPersonByLogin(string login, vector<User> users)
{
	for (auto& i : users)
		if (i.GetLogin() == login)
			return i.GetFullName();

	return "";
}

int main()
{
	srand(time(nullptr));

	EntryMenu();

	return 0;
}

