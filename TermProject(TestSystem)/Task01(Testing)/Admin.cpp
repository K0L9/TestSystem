//#include "Admin.h"
//
//void Admin::FirstEntry()
//{
//	WriteLogin();
//}
//
//void Admin::WriteLogin() const
//{
//	ofstream file("ThereAreNoLogin.dat", ios_base::binary || ios::app);
//
//	if (!file.good())
//	{
//		cout << "Error with file\n";
//		return;
//	}
//
//	char login[100];
//	cout << "Input login: ";
//	cin.getline(login, 100);
//
//	int size = sizeof(login);
//
//	file.write(reinterpret_cast<const char*>(&size), sizeof(int));
//
//	for (size_t i = 0; i < strlen(login); i++)
//		login[i] -= 2;
//
//	file.write(reinterpret_cast<const char*>(&login), size);
//}
//
//string Admin::ReadLogin() const
//{
//	ifstream file("ThereAreNoLogin.dat", ios_base::binary);
//
//	if (!file.good())
//	{
//		throw "Error with file";
//	}
//	if (file.peek() == ifstream::traits_type::eof())
//	{
//		throw "No one admin in system";
//	}
//
//	int sizeLogin;
//	file.read(reinterpret_cast<char*>(&sizeLogin), sizeof(int));
//
//	char login[100];
//	file.read(reinterpret_cast<char*>(&login), sizeLogin);
//
//	for (size_t i = 0; i < strlen(login); i++)
//		login[i] += 2;
//
//	return login;
//}
//
//void Admin::WritePass() const
//{
//	ofstream file("ThereAreNoPassword.dat", ios_base::binary || ios::app);
//
//	if (!file.good())
//	{
//		throw "Error with file";
//	}
//
//	char pass[100];
//	cout << "Input password: ";
//	cin.getline(pass, 100);
//
//	int size = sizeof(pass);
//
//	file.write(reinterpret_cast<const char*>(&size), sizeof(int));
//
//	for (size_t i = 0; i < strlen(pass); i++)
//		pass[i] += 3;
//
//	file.write(reinterpret_cast<const char*>(&pass), size);
//}
//
//string Admin::ReadPass() const
//{
//	ifstream file("ThereAreNoPassword.dat", ios_base::binary);
//
//	if (!file.good())
//	{
//		throw "Error with file";
//	}
//	if (file.peek() == ifstream::traits_type::eof())
//	{
//		throw "No one admin in system";
//	}
//
//	int sizePass;
//	file.read(reinterpret_cast<char*>(&sizePass), sizeof(int));
//
//	char pass[100];
//	file.read(reinterpret_cast<char*>(&pass), sizePass);
//
//	for (size_t i = 0; i < strlen(pass); i++)
//		pass[i] -= 3;
//
//	return pass;
//}
//
//void Admin::Entry() const
//{}
//
//bool Admin::ShowUsers() const
//{
//	if (users.empty())
//	{
//		cout << "No one user\n";
//		return false;
//	}
//
//	int counter = 1;
//
//	for (auto& i : users)
//		cout << "User #" << counter++ << "\n\t" << i << endl;
//
//	cout << endl;
//
//	return true;
//}
//
//void Admin::AddUser()
//{
//	User tmpUser;
//	cin >> tmpUser;
//
//	users.push_back(tmpUser);
//}
//
//void Admin::DeleteUser()
//{
//	if (!ShowUsers())
//		return;
//
//	int index;
//	cout << "Input index: ";
//
//	cin >> index;
//
//	users.erase(users.begin() + --index);
//}
//
//void Admin::UserEdit()
//{
//	if (!ShowUsers())
//		return;
//
//	int index;
//	cout << "Input index: ";
//
//	cin >> index;
//
//	UserEditHelper(users[--index]);
//}
//
//void Admin::UserEditHelper(User& user)
//{
//	string tmp;
//	int choose;
//	do
//	{
//		cout << "===============\n";
//		cout << "|1. Full name |\n";
//		cout << "|2. Address   |\n";
//		cout << "|3. Number    |\n";
//		cout << "===============\n";
//		cout << "Input what you want to edit: ";
//		cin >> choose;
//
//		if (choose < 1 || choose > 3)
//			cout << "Input right value (1-3)";
//
//	} while (choose < 1 || choose > 3);
//
//	switch (choose)
//	{
//	case 1:
//		cout << "Input new user full name: ";
//		cin.ignore(cin.rdbuf()->in_avail());
//		getline(cin, tmp);
//		user.SetFullName(tmp);
//		break;
//
//	case 2:
//		cout << "Input new user address: ";
//		cin.ignore(cin.rdbuf()->in_avail());
//		getline(cin, tmp);
//		user.SetAddress(tmp);
//		break;
//
//	case 3:
//		cout << "Input new user number: ";
//		cin.ignore(cin.rdbuf()->in_avail());
//		getline(cin, tmp);
//		user.SetNumber(tmp);
//		break;
//
//	default:
//		break;
//	}
//}
//
//void Admin::AddQuestAnsw() const
//{
//	Shows::ShowAllCategories();
//
//	string categorie;
//	cout << "Input category: ";
//	cin.ignore(cin.rdbuf()->in_avail());
//	getline(cin, categorie);
//
//	bool isNew = false;
//
//	int nCategor = Founders::GetCategIndByName(categorie);
//	if (nCategor == -1)
//	{
//		isNew = true;
//		cout << "No one category with title " << categorie << " will be create new category " << endl;
//		Shows::test.categories.push_back(categorie);
//	}
//
//	//if (Shows::test.categories[nCategor].QA.size() > 12)
//	//{
//	//	cout << "This category have 12 answers yet\n";
//	//	return;
//	//}
//
//	string quest;
//	cout << "Input question: ";
//	cin.ignore(cin.rdbuf()->in_avail());
//	getline(cin, quest);
//
//	string answers[4];
//
//	for (size_t i = 0; i < 4; i++)
//	{
//		cout << "Input question #" << i + 1 << ": ";
//		getline(cin, answers[i]);
//	}
//
//	bool isRight;
//	int rightAnsw;
//	do
//	{
//		isRight = true;
//		cout << "Input index of right question: ";
//		cin >> rightAnsw;
//
//		if (rightAnsw < 1 || rightAnsw > 4)
//		{
//			cout << "Input right index\n";
//			isRight = false;
//		}
//
//	} while (!isRight);
//
//	if (isNew || categorie.size() == 0)
//		Shows::test.categories.back().Category::QA.push_back(QuestAnsw(quest, answers, rightAnsw - 1));
//
//	else
//		Shows::test.categories[nCategor].Category::QA.push_back(QuestAnsw(quest, answers, rightAnsw - 1));
//}
//
//void Admin::DeleteQuestAnsw() const
//{
//	Category* catName = Founders::GetCategoryByName(Founders::GetCategoriesName());
//
//	Shows::ShowCurrentCategorie(catName);
//
//	string quest;
//	cout << "Input quest that you want to delete: ";
//	cin.ignore(cin.rdbuf()->in_avail());
//	getline(cin, quest);
//
//	int toDel = Founders::GetQuestIndByQuest(catName, quest);
//
//	if (toDel == -1)
//	{
//		cout << "Incorrect answer name\n";
//		return;
//	}
//
//	catName->QA.erase(catName->QA.begin() + toDel);
//}
//
//void Admin::EditQuest() const
//{
//	Category* catName = Founders::GetCategoryByName(Founders::GetCategoriesName());
//
//	Shows::ShowCurrentCategorie(catName);
//
//	string quest;
//	cout << "Input quest that you want to delete: ";
//	cin.ignore(cin.rdbuf()->in_avail());
//	getline(cin, quest);
//
//	int toDel = Founders::GetQuestIndByQuest(catName, quest);
//
//	if (toDel == -1)
//	{
//		cout << "Incorrect answer name\n";
//		return;
//	}
//
//	EditHelper(catName->QA[toDel]);
//}
//
//void Admin::EditHelper(QuestAnsw& quest) const
//{
//	int choice;
//
//	do
//	{
//		cout << "=====================\n";
//		cout << "|1. Edit question   |\n";
//		cout << "|2. Edit answers    |\n";
//		cout << "|3. Edit right answ |\n";
//		cout << "=====================\n";
//		cout << "Input what you want to edit: ";
//		cin >> choice;
//
//		switch (choice)
//		{
//		case 1:
//		{
//			string newQuest;
//			cout << "Input new question: ";
//			cin.ignore(cin.rdbuf()->in_avail());
//			getline(cin, newQuest);
//
//			cout << "This Shows::test had quest: " << quest.question << endl;
//			cout << "And now this is a: " << newQuest << endl;
//
//			quest.question = newQuest;
//			break;
//		}
//
//		case 2:
//		{
//			for (size_t i = 0; i < 4; i++)
//				cout << "#" << i + 1 << " " << quest.answers[i] << endl;
//			int index;
//			cout << "Input index that you want to edit: ";
//			cin >> index;
//
//			index--;
//
//			string newQuest;
//			cout << "Input new answer for this question: ";
//			cin.ignore(cin.rdbuf()->in_avail());
//			getline(cin, newQuest);
//
//			quest.answers[index] = newQuest;
//			break;
//		}
//
//		case 3:
//		{
//			for (size_t i = 0; i < 4; i++)
//				cout << "#" << i + 1 << " " << quest.answers[i] << endl;
//			int newRight;
//			cout << "What answer you want to do right: ";
//			cin >> newRight;
//
//			newRight--;
//
//			quest.indexCorrect = newRight;
//			break;
//		}
//		default:
//			cout << "Input right value (1 - 3)\n";
//			break;
//		}
//	} while (choice < 1 || choice > 3);
//}
//
//void Admin::DelQuestAnsw() const
//{
//	if (Founders::GetCategIndByName(Founders::Founders::GetCategoriesName()) == -1)
//	{
//		cout << "Incorrect category name\n";
//		return;
//	}
//
//}
//
//void Admin::AddNewCategorie() const
//{
//	cout << "Input new category name: ";
//	string catName;
//	cin.ignore(cin.rdbuf()->in_avail());
//	getline(cin, catName);
//
//	if (Founders::GetCategIndByName(catName) != -1)
//	{
//		cout << "This categ name is exist\n";
//		return;
//	}
//
//	Shows::test.categories.push_back(catName);
//}
//
//void Admin::DeleteCateg() const
//{
//	cout << "Input category name: ";
//	string catName;
//	cin.ignore(cin.rdbuf()->in_avail());
//	getline(cin, catName);
//
//	int index = Founders::GetCategIndByName(catName);
//
//	if (index == -1)
//	{
//		cout << "Invalid category name\n";
//		return;
//	}
//
//	Shows::test.categories.erase(Shows::test.categories.begin() + index);
//}
//
//void Admin::RenameCateg() const
//{
//	cout << "Input old category name: ";
//	string catName;
//	cin.ignore(cin.rdbuf()->in_avail());
//	getline(cin, catName);
//
//	int index = Founders::GetCategIndByName(catName);
//
//	if (index == -1)
//	{
//		cout << "Invalid old category name\n";
//		return;
//	}
//
//	cout << "Input mews category name: ";
//	string newCatName;
//	cin.ignore(cin.rdbuf()->in_avail());
//	getline(cin, newCatName);
//
//	Shows::Shows::test.categories[index].catName = newCatName;
//}