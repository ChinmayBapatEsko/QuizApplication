/*

The AuthenticationManager class is responsible for authentication of the User that is about to play the quiz. If the user is not present in the database, it will register the 
user by taking his credentials. The primary method that runs in the class is the init method that is called by the Main class.
Thus, the class's server is: Main class.
The class further doesnt create any instance of any class, however provides the responce to the InstanceManager class as a pair <isAdmin (boolean), user_id (string)>

*/


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

