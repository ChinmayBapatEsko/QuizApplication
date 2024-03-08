#include "Quiz.h"
#include <iostream>
ostream& operator<<(ostream& os, const Quiz& quiz)
{
	os << "Quiz Title: " << quiz.quiz_title << endl << "Description: " << quiz.quiz_description << endl << endl;
	return os;
}
