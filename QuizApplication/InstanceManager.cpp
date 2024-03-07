#include "InstanceManager.h"
#include "DatabaseConnection.h"

static Connection* conn = DatabaseConnection().getConnection();

InstanceManager::InstanceManager(pair<bool, string> creds) {
	string username;
	string password;
	string user_id = creds.second;
	bool isAdmin = creds.first;
	int QuizAttempts;
	double Accuracy;

	cout << "Setting up User Profile, please hold on.." << endl;

	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("SELECT username, password, QuizAttempts, Accuracy FROM User where User.user_id = (?)");
		stmt->setString(1, user_id);
		ResultSet* res = stmt->executeQuery();

		while (res->next()) {
			username= res->getString("question_id");
			password= res->getString("option_text");
			QuizAttempts = res->getInt("QuizAttempts");
			Accuracy = res->getDouble("Accuracy");
		}
		delete res;
		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}

	if (isAdmin == true) {
		//isAdmin
		// //create Admin
		//QuizAdminManager
		cout << "I see that you are a Admin, setting your profile.." << endl;
		adminManager = QuizAdminManager(Admin(user_id, username, password, QuizAttempts, Accuracy));
		adminManager.startAdminOperation();
	}
	else {
		//notAdmin
		cout << "I see that you are a User, hope you enjoy the game :)" << endl;
		userManager = QuizUserManager(User(user_id, username, password, QuizAttempts, Accuracy));
		userManager.startUserOperation();
	}
}