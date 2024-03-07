#pragma once
#include <string>
using namespace std;


class Question
{
public:
	string question_id;
	string quiz_id;
	string question_text;
	string question_type;
	Question(string id1, string id2, string t, string ty) :question_id(id1), quiz_id(id2), question_text(t), question_type(ty) {};
	Question() {};

	friend ostream& operator<<(ostream& os, const Question& q);
};

