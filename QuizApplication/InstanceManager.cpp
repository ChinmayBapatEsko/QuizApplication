#include "InstanceManager.h"
#include "DatabaseConnection.h"

InstanceManager::InstanceManager(pair<bool, string> creds) {
	/*cout << "InstanceConstructor" << endl;
	cout << creds.first;
	cout << creds.second;*/

	string user_id = creds.second;
	bool isAdmin = creds.first;

	cout << "-----------------------------------------------------------------------" << endl;
	cout << "Setting up User Profile, please hold on.." << endl;

	User temp = DatabaseConnection().callInstanceManagerUtility(user_id);

	if (isAdmin == true) {
		//isAdmin
		// //create Admin
		//QuizAdminManager
		cout << "I see that you are a Admin, setting your profile.." << endl;
		adminManager = QuizAdminManager(Admin(user_id, temp.username, temp.password, temp.quizAttempts, temp.accuracy));
		adminManager.startAdminOperation();
	}
	else {
		//notAdmin
		//create User
		//QuizUserManager
		cout << "I see that you are a User, hope you enjoy the game :)" << endl;
		userManager = QuizUserManager(User(user_id, temp.username, temp.password, temp.quizAttempts, temp.accuracy));
		userManager.startUserOperation();
	}
}