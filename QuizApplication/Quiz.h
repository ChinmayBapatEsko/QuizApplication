#pragma once
#include <string>
using namespace std;


class Quiz
{
public:
	string quiz_id;
	string category_id;
	string quiz_title;
	string quiz_description;
	Quiz(string id1, string id2, string t, string d) :quiz_id(id1), category_id(id2), quiz_title(t), quiz_description(d) {};
	Quiz() {};

	friend ostream& operator<<(ostream& os, const Quiz& quiz);
};

