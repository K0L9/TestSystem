#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

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

vector <User> users;

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

	string GetTrueAnswer()
	{
		return answers[indexCorrect];
	}

	void ShowQuestAnsw()
	{
		cout << question << ":\n";

		char tmp = 'A';

		for (int i = 0; i < 4; i++)
			cout << "   " << tmp++ << ". " << answers[i] << endl;
	}

	bool CheckAnsw(char answer)
	{
		return answer - 49 == indexCorrect;
	}

	friend class Admin;
	friend class GoTestSystem;


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
	friend class GoTestSystem;

};

class Test
{
private:
	vector <Category> categories;
public:
	Test()
	{
		//int userCateg = GetCategIndex();
		//if (userCateg == -1)
		//{
		//	cout << "No one categories\n";
		//	return;
		//}
		//
		//for (size_t i = 0; i < categories[userCateg].QA.size(); i++)
		//	categories[--userCateg].QA[i].ShowQuestAnsw();

	}

	friend class Admin;
	friend class GoTestSystem;
};

Test test;

class Admin
{
public:
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
		string categorie;
		cout << "Input category: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, categorie);

		bool isNew = false;

		int nCategor = GetCategIndByName(categorie);
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
		Category* catName = GetCategoryByName(GetCategoriesName());

		ShowCurrentCategorie(catName);

		string quest;
		cout << "Input quest that you want to delete: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, quest);

		int toDel = GetQuestIndByQuest(catName, quest);

		if (toDel == -1)
		{
			cout << "Incorrect answer name\n";
			return;
		}

		catName->QA.erase(catName->QA.begin() + toDel);
	}
	void EditQuest()
	{
		Category* catName = GetCategoryByName(GetCategoriesName());

		ShowCurrentCategorie(catName);

		string quest;
		cout << "Input quest that you want to delete: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, quest);

		int toDel = GetQuestIndByQuest(catName, quest);

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
	int GetQuestIndByQuest(const Category* cat, string quest)
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
	void DelQuestAnsw()
	{
		if (GetCategIndByName(GetCategoriesName()) == -1)
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

		if (GetCategIndByName(catName) != -1)
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

		int index = GetCategIndByName(catName);

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

		int index = GetCategIndByName(catName);

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
	int GetCategIndex()
	{
		if (!ShowCategories())
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
	int GetCategIndByName(string categorie)
	{
		for (size_t i = 0; i < test.categories.size(); i++)
			if (test.categories[i].catName == categorie)
				return i;

		return -1;
	}
	string GetCategoriesName()
	{
		string catName;

		if (!ShowAllCategories())
		{
			cout << "No one category\n";
			return "";
		}

		cout << "Input category: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, catName);

		return catName;
	}
	Category* GetCategoryByName(string catName)
	{
		for (auto& i : test.categories)
			if (i.catName == catName)
				return &i;

		return nullptr;
	}

	//Shows
	bool ShowCategories()
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
	bool ShowAllCategories()
	{
		if (test.categories.empty())
			return false;

		int counter = 0;
		for (auto& i : test.categories)
			cout << "#" << ++counter << " " << i.catName << endl;
	}
	bool ShowCurrentCategorie(Category* cat)
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
	void ShowAllQuest()
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

	void GoTest()
	{
		if (!ShowCategories())
			return;

		string categoryName;
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Input category: ";
		getline(cin, categoryName);

		Category* cat = GetCategoryByName(categoryName);

		if (cat == nullptr)
		{
			cout << "Invalid cat name\n";
			return;
		}

		bool isTrue = false;
		char userAnswer;
		int size = cat->QA.size();
		int* stat = new int[size];

		int counter = 0;
		for (auto& i : cat->QA)
		{
			cout << "Answer #" << counter + 1 << " / " << size << endl;

			do
			{
				i.ShowQuestAnsw();

				cout << "Input your answer: ";
				cin >> userAnswer;
			} while (!CheckAndConvertAnswer(userAnswer));

			if (i.CheckAnsw(userAnswer))
				stat[counter] = 1;

			else
				stat[counter] = 0;

			counter++;
		}

		int nRight = CountRightAnsw(stat, size);
		int rightInProc = (nRight * 100) / size;
		cout << "RESULTS: \n";

		cout << "Correct: " << nRight << endl;
		cout << "Right in proc.: " << rightInProc << "%" << endl;
	};

	int CountRightAnsw(const int* stat, int size)
	{
		int counter = 0;
		for (size_t i = 0; i < size; i++)
			if (stat[i] == 1)
				counter++;

		return counter;
	}

	bool CheckAndConvertAnswer(char& answer)
	{
		if ((answer < 'a' || answer > 'd') && (answer < 'A' || answer > 'D') && (answer < '1' || answer > '4'))
			return false;

		if (answer >= 'a' && answer <= 'd')
			answer -= 48;

		else if (answer >= 'A' && answer <= 'D')
			answer -= 16;

		return true;
	}
};


int main()
{
	srand(time(nullptr));

	Admin kolya;
	kolya.AddNewCategorie();
	kolya.AddQuestAnsw();
//	kolya.AddQuestAnsw();
	//kolya.AddQuestAnsw();

	//kolya.AddQuestAnsw();
	//kolya.AddQuestAnsw();
	//kolya.ShowCurrentCategorie(kolya.GetCategoryByName(kolya.GetCategoriesName()));
	//kolya.EditQuest();
	//kolya.ShowAllQuest();
	kolya.GoTest();

	//Test test;
	//kolya.AddUser();
	//kolya.AddUser();
	//kolya.ShowUsers();
	//kolya.UserEdit();
	//kolya.ShowUsers();



	return 0;
}