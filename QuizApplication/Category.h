#pragma once
#include <string>
using namespace std;
class Category
{
public:
	string category_id;
	string category_name;
	Category(string id, string name) :category_id(id), category_name(name) {};
	Category() {};

	friend ostream& operator<<(ostream& os, const Category& category);
};

