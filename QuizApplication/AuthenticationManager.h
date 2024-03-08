#pragma once
#include <string>
#include "User.h"
using namespace std;

static pair<bool, string> response;

class AuthenticationManager
{
private:
	string username;
	string password;
	string user_id;
	bool isAdmin=false;

public:
	AuthenticationManager() {};
	pair<bool, string> init();
	pair<bool, string> Login();
	void Register();
};

