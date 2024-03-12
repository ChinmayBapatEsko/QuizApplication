/*

InstanceManager class takes a pair as input from the AuthenticationManager. The InstanceManager class is responsible to create object of the Managers that
will take care of all services to provide to the User/Admin. The pair will contain a boolean => is user a admin? 
and a string => user_id of the Authenticated User that will help us retrive all the data of the User. 
If the user is a Admin, Instance Manager will create an instance of QuizUserManager class
if user is Admin, will create an object of the class QuizAdminManager. 

Clients of the class are: QuizUserManager or QuizAdminManager.
Server for the class is: Main class.

*/


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

