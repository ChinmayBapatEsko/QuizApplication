#include "Question.h"
#include <iostream>

ostream& operator<<(ostream& os, const Question& q){
	os << "Question is: " << q.question_text << ", please answer this question in " << q.question_type << " format" << endl << endl;
	return os;
}
