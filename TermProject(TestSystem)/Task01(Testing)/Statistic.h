#pragma once
#include "Helpers.h";

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
	int grade;

public:
	Statistic(string categTitle = "", string currTestTitle = "", string whoLog = "", bool* fullAnsw = nullptr, int rightRes = 0, double rightInProc = 0, int size = 0, int grade = 0)
		: whoLog(whoLog), categTitle(categTitle), currTestTitle(currTestTitle), fullAnsw(fullAnsw), rightRes(rightRes), rightInProc(rightInProc), size(size), grade(grade)
	{
	}

	friend ofstream& operator<<(ofstream& out, const Statistic& stat)
	{
		out << stat.whoLog << endl << stat.rightRes << " " << stat.rightInProc << " " << stat.size << " " << stat.grade << " " << stat.categTitle << endl << stat.currTestTitle << endl;

		return out;
	}

	friend ifstream& operator>>(ifstream& in, Statistic& stat);

	void ShowStat();
	void ShowCategTitle();
	void ShowTestTitle();

	friend class User;
	friend class Admin;
};