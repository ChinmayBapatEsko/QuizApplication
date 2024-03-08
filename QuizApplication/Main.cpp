#include "Main.h"
#include <string>
#include <iostream>
using namespace std;
void Main::start() {
	pair<bool, string> userCreds = authManager.init();

	instManager = InstanceManager(userCreds);
}

int main() {
	cout << "WELCOME To my Quiz Application." << "\t" << "Without any further ado, lets start!" << endl << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	Main application = Main();
	application.start();

	//DatabaseConnection().getAllCategoriesWorking();
	//QuizUserManager().getAllQuizes("C_1");
}