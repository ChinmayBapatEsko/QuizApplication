#include "Option.h"
#include<iostream>

ostream& operator<<(ostream& os, const Option& option) {
	os << option.option_text << endl;
	return os;
}
