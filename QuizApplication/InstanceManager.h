#pragma once
#include<string>
#include <utility>
#include "QuizUserManager.h"
#include "QuizAdminManager.h"

using namespace std;
class InstanceManager
{
public:
	QuizUserManager userManager; //
	QuizAdminManager adminManager; //
	InstanceManager() {};
	InstanceManager(pair<bool, string> creds);
};

