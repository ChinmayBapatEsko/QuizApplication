#include "AuthenticationManager.h"
#include <iostream>
#include "DatabaseConnection.h"

using namespace std;

pair<bool, string> AuthenticationManager::init() {
	//pair<bool, string> response;
	response = Login();
	/*cout << "InitMethod" << endl;
	cout << response.first;
	cout << response.second;*/
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
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	
	return DatabaseConnection().callLoginFunction(username, password);
}

void AuthenticationManager::Register() {
	string tempUsername;
	string tempPass;
	bool tempFlag;
	int choice;
	cout << "Please enter Username and Password: " << endl;
	cout << "Username: ";
	cin >> tempUsername;
	cout << "Password: ";
	cin >>  tempPass;
	cout << "Are you an admin? Type 0 for No and 1 for Yes: " << endl;
	cin >> choice;
	if (choice == 1) {
		tempFlag = true;
	}
	else {
		tempFlag = false;
	}

	DatabaseConnection().callRegisterFunction(tempUsername, tempPass, tempFlag);

	cout << "Lets Retry logging in now: " << endl;
	cout << "-------------------------------------------------------------" << endl;

}