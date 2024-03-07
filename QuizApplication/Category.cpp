#include "Category.h"
#include<iostream>

ostream& operator<<(ostream& os, const Category& category)
{
	os << "Category Name: " << category.category_name << endl;
	return os;
}
