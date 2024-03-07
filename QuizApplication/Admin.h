#pragma once
#include "User.h"
class Admin :
    public User
{
public:
	Admin(string id, string username, string password, int quizAttempts, double accuracy) :
		User(id, username, password, quizAttempts, accuracy) {};
	Admin() {};
};

