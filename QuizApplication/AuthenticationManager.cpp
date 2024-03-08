#include "AuthenticationManager.h"
#include <iostream>
#include "DatabaseConnection.h"

using namespace std;

pair<bool, string> AuthenticationManager::init() {
	//pair<bool, string> response;
	response = Login();
	if (response.second == "") {
		//no user found
		Register();
		init();
	}
	else {
		//user found
		//reponse goes to InstanceManager that will decide to start the QuizUserManager or the QuizAdminManager.
		return response;
	}
}

pair<bool, string> AuthenticationManager::Login() {
	cout << "Please enter Username and Password: " << endl;
	cin >> username >> password;
	
	return DatabaseConnection().callLoginFunction(username, password);
}

void AuthenticationManager::Register() {
	string tempUsername;
	string tempPass;
	bool tempFlag;
	int choice;
	cout << "Please enter Username and Password: " << endl;
	cin >> tempUsername >> tempPass;
	cout << "Are you an admin? Type 0 for No and 1 for Yes: " << endl;
	cin >> choice;
	if (choice == 1) {
		tempFlag = true;
	}
	else {
		tempFlag = false;
	}

	DatabaseConnection().callRegisterFunction(tempUsername, tempPass, tempFlag);

}