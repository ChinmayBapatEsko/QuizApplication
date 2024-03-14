#include "AuthenticationManager.h"
#include <iostream>
#include "DatabaseConnection.h"

using namespace std;

pair<bool, string> AuthenticationManager::init() {
	response = Login();
	if (response.second == "") {
		//no user found
		Register();
		return Login();
	}
	else {
		//user found
		//reponse goes to InstanceManager that will decide to start the QuizUserManager or the QuizAdminManager.
		return response;
	}
}

pair<bool, string> AuthenticationManager::Login() {
	try
	{
		cout << "Please enter Username and Password: " << endl;
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;
		return DatabaseConnection().callLoginFunction(username, password);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		cout << "CMON! Give proper Input!!!" << endl;
		cout << "Restart Now, as your punishment  >_<   " << endl;
		exit(0);
	}
	
}

void AuthenticationManager::Register() {
	try
	{
		string tempUsername;
		string tempPass;
		bool tempFlag;
		int choice;
		cout << "Please enter Username and Password: " << endl;
		cout << "Username: ";
		cin >> tempUsername;
		cout << "Password: ";
		cin >> tempPass;
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
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		cout << "CMON! Give proper Input!!!" << endl;
		cout << "Restart Now, as your punishment  >_<   " << endl;
		exit(0);
	}

	cout << "Lets Retry logging in now: " << endl;
	cout << "-------------------------------------------------------------" << endl;

}