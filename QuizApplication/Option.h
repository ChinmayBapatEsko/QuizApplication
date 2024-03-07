#pragma once
#include <string>
using namespace std;


class Option
{
public:
	string option_id;
	string question_id;
	string option_text;
	bool isCorrect=false;

	Option(string id1, string id2, string t, bool c) :question_id(id2), option_id(id1), option_text(t), isCorrect(c) {};
	Option() {};

	friend ostream& operator<<(ostream& os, const Option& option);
};

