#pragma once
#include "TestComponent.h"

class Shows
{
public:
	static bool ShowAllCategories(const Test& tests);
	static bool ShowCurrentCategorie(const Category* const cat);

	static void ShowAllQuest(const Test& tests);

	static bool ShowAllTests(const Test& tests);
	static bool ShowTestsInCurrentCategorie(const Category* const cat);
	static bool ShowCurrentTest(const CurrentTest* const test);

};

class User;
class Founders
{
public:
	static Category* GetCategoryByName(string catName, Test& tests);
	static int GetCategIndex(const Test& tests);
	static int GetCategIndByName(string categorie, const Test& tests);
	static string GetCategoriesName(const Test& tests);

	static int CountRightAnsw(const bool* stat, int size);
	static bool CheckAndConvertAnswer(char& answer);
	static int GetQuestIndByQuest(const CurrentTest* test, string quest);

	static CurrentTest* GetTestByName(string testName, Category* const cat);
	static int GetTestIndByName(string testName, const Category& cat);
	static int GetTestIndByName(string testName, const Category* cat);

	static string FoundPersonByLogin(string login, vector<User> users);
	static bool CheckPass(string str);
	static bool CheckLogin(string str);
};

