#include "Quiz.h"
#include <iostream>
ostream& operator<<(ostream& os, const Quiz& quiz)
{
	os << "Quiz Title: " << quiz.quiz_title << ", Description: " << quiz.quiz_description << endl;
	return os;
}
