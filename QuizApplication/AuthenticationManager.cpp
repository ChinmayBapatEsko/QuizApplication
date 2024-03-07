#include "AuthenticationManager.h"
#include <iostream>
#include "DatabaseConnection.h"
using namespace std;

static Connection* conn = DatabaseConnection().getConnection();

pair<bool, string> AuthenticationManager::init() {
	pair<bool, string> response;
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
	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL AuthenticateUser(?, ?)");
		stmt->setString(1, username);
		stmt->setString(2, password);
		ResultSet* res = stmt->executeQuery();

		if (res->next()) {
			//User found
			user_id = res->getString("user_id");
			isAdmin = res->getBoolean("isAdmin");
			cout << "Login Successful!" << endl;
			return make_pair(isAdmin, user_id);
		}
		else {
			//user not found
			cout << "Invalid credentials or User not found! Retry!" << endl;
			return make_pair(false, "");
		}

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}

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

	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL InsertUser(?, ?, ?)");
		stmt->setString(1, tempUsername);
		stmt->setString(2, tempPass);
		stmt->setBoolean(3, tempFlag);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}

}