#pragma once
#include<string>
#include <utility>
#include "QuizUserManager.h"
#include "QuizAdminManager.h"

using namespace std;
static QuizUserManager userManager; //
static QuizAdminManager adminManager; //

class InstanceManager
{
public:
	InstanceManager() {};
	InstanceManager(pair<bool, string> creds);
};

