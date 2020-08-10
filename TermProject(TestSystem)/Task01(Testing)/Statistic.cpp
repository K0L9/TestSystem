#include "Statistic.h"

void Statistic::ShowStat()
{
	cout << "Correct: " << this->rightRes << " / " << size << endl;
	cout << "Right in proc.: " << rightInProc << "%" << endl;
	cout << "Grade: " << this->grade << " / 12\n";
}

void Statistic::ShowCategTitle()
{
		cout << "Category name: " << categTitle << endl;
}

void Statistic::ShowTestTitle()
{
	cout << "Test name: " << currTestTitle << endl;
}

ifstream& operator>>(ifstream& in, Statistic& stat)
{
	string categTitleTmp, currTestTitleTmp;

	getline(in, stat.whoLog);
	in >> stat.rightRes;
	in >> stat.rightInProc;
	in >> stat.size;
	in >> stat.grade;
	getline(in, categTitleTmp);
	getline(in, currTestTitleTmp);

	if (categTitleTmp[0] == ' ')
		categTitleTmp.erase(0, 1);
	if (currTestTitleTmp[0] == ' ')
		currTestTitleTmp.erase(0, 1);

	stat.categTitle = categTitleTmp;
	stat.currTestTitle = currTestTitleTmp;

	return in;
}
