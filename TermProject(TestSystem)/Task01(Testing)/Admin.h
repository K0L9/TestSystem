#pragma once
#include <iomanip>
#include "User.h";

class Admin
{
private:
	vector <User>& users;
	Test& tests;

public:
	//Ctor
	Admin(vector <User>& users, Test& tests)
		:users(users), tests(tests)
	{

	}

	//Admin authorize data
	void WriteLogin(string message = "");
	string ReadLogin();

	void WritePass();
	string ReadPass();

	bool IsFirst();
	bool EntryAdmin();

	//Load data
	bool ReadAutoUserLoad();
	bool ReadAutoQuestLoad();
	void SwitchAutoQuestLoad();
	void SwitchAutoUserLoad();

	bool ReadAutoUserUpLoad();
	bool ReadAutoQuestUpLoad();
	void SwitchAutoQuestUpLoad();
	void SwitchAutoUserUpLoad();

	//users
	bool ShowUsers() const;
	bool CheckExistLogin(string log);
	void AddUser();

	void DeleteUser();
	void UserEdit();
	bool UserEditHelper(User& user);

	User* GetUserByIndex(int index);

	//Questions
	void AddQuestAnsw();
	void DeleteQuestAnsw();
	QuestAnsw& ChooseQuestAnsw();
	void EditQuest();
	void EditHelper(QuestAnsw& quest);

	//Test
	void AddNewTest();
	void DeleteTest();
	void RenameTest();

	//Categories
	void AddNewCategorie();
	void DeleteCateg();
	void RenameCateg();

	//Statistic
	void ShowStatisticByCurrentPeople();
	void ShowStatisticByCurrentCategory();
	void ShowStatisticByCurrentTest();

	//Loads
	void UpLoadAllUsers();
	void LoadAllUsers();
	void UpLoadAllTest();
	void LoadAllTest();

	//Menu's
	void MainAdminMenu();

	void UsersMenu();
	void QuestionsMenu();
	void CategoriesMenu();
	void TestMenu();
	void StatisticMenu();
	void SettingsMenu();
	void AdminAuthorizeEditMenu();
};