#include "QuizUserManager.h"
#include "DatabaseConnection.h"
#include "vector"
#include <utility>

static Connection* conn = DatabaseConnection().getConnection();

QuizUserManager::QuizUserManager(const User u){
	user = u;
};

void QuizUserManager::changeUser(const User u) {
	user = u;
}

void QuizUserManager::getAllCategories() {
	vector<Category> ans;
	try {
		conn->setSchema("quizapplication");
		Statement* stmt = conn->createStatement();
		ResultSet* res = stmt->executeQuery("CALL GetAllCategories()");

		while (res->next()) {
			string id = res->getString("category_id");
			string name = res->getString("category_name");
			Category category(id, name);
			ans.push_back(category);
		}
		delete res;
		delete stmt;

	}
	catch(SQLException& e){
		cout << "MySQL Error: " << e.what() << endl;
	}

	currentCategories = ans;
}


void QuizUserManager::getAllQuizes(const string& category_id) {
	vector<Quiz> ans;
	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL GetQuizzesByCategory(?)");
		stmt->setString(1, category_id);
		ResultSet* res = stmt->executeQuery();

		while (res->next()) {
			string quiz_id = res->getString("quiz_id");
			string category_id = res->getString("category_id");
			string quiz_title = res->getString("quiz_title");
			string quiz_description = res->getString("quiz_description");
			Quiz quiz(quiz_id, category_id, quiz_title, quiz_description);
			ans.push_back(quiz);
		}
		delete res;
		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}

	quizzesInThisCategory = ans;
}

void QuizUserManager::setCategory(const Category& c) {
	cat = c;
}

void QuizUserManager::setQuiz(const Quiz& q) {
	quiz = q;
}

vector<Option> QuizUserManager::getOptionByQuestion(const string& question_id) {
	vector<Option> ans;

	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL GetOptionsByQuestion(?)");
		stmt->setString(1, question_id);
		ResultSet* res = stmt->executeQuery();

		while (res->next()) {
			string option_id = res->getString("option_id");
			string question_id = res->getString("question_id");
			string option_text = res->getString("option_text");
			bool isCorrect = res->getBoolean("is_correct");
			Option option(option_id, question_id, option_text, isCorrect);
			ans.push_back(option);
		}
		delete res;
		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}

	return ans;
}

void QuizUserManager::setMap(const string& quiz_id) {
	vector<Question> qList;

	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL GetQuestionsByQuiz(?)");
		stmt->setString(1, quiz_id);
		ResultSet* res = stmt->executeQuery();

		while (res->next()) {
			string question_id = res->getString("question_id");
			string quiz_id = res->getString("quiz_id");
			string question_text = res->getString("question_text");
			string question_type = res->getString("question_type");
			Question question(question_id, quiz_id, question_text, question_type);
			qList.push_back(question);
		}
		delete res;
		delete stmt;

		try {
			for (auto& q : qList) {
				vector<Option> opts = getOptionByQuestion(q.question_id);
				QuestionList.push_back({ q , opts });
			}
		}
		catch (SQLException& e) {
			cout << "MySQL Error: " << e.what() << endl;
		}

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

double QuizUserManager::getLatestQuizScore(const string& quiz_id, const string& user_id) {
	
	double score;
	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL getLatestQuizScore(?, ?)");
		stmt->setString(1, quiz_id);
		stmt->setString(2, user_id);
		ResultSet* res = stmt->executeQuery();

		while (res->next()) {
			score = res->getDouble("score");
		}

		delete res;
		delete stmt;
	}
	catch(SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}

	return score;
}

void QuizUserManager::getLatestAttemptDetails(const string& user_id) {
	//vector<string, pair<string, string>> ans;

	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL GetLatestAttemptDetails(?)");
		stmt->setString(1, user_id);
		ResultSet* res = stmt->executeQuery();

		while (res->next()) {
			string questionText = res->getString("question_text");
			string user_answer_text = res->getString("user_answer_text");
			string correct_answer_text = res->getString("correct_answer_text");
			//ans[questionText] = make_pair(user_answer_text, correct_answer_text);

			cout << "Question: " << questionText << endl;
			cout << "User answered this: " << user_answer_text << endl;
			cout << "Actual answer is: " << correct_answer_text << endl;
		}
		delete res;
		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}

}

void QuizUserManager::insertUserAttempt(const string& user_id, const string& quiz_id) {
	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL InsertUserAttempt(?, ?)");
		stmt->setString(1, user_id);
		stmt->setString(2, quiz_id);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

string QuizUserManager::getLatestAttemptId(const string& user_id) {
	string ans;

	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL getLatestAttemptId(?)");
		stmt->setString(1, user_id);
		ResultSet* res = stmt->executeQuery();

		while (res->next()) {
			ans = res->getString("latestAttemptID");
		}

		delete res;
		delete stmt;
	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}

	return ans;
}

void QuizUserManager::insertUserAnswer(const string& attempt_id, const string& question_id, const string& option_id) {
	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL InsertUserAttempt(?, ?)");
		stmt->setString(1, attempt_id);
		stmt->setString(2, question_id);
		stmt->setString(3, option_id);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizUserManager::takeAnotherQuiz() {
	int choice1, choice2;
	try {
		cout << "Do you want to play another quiz?" << endl;
		cin >> choice1;
		if (choice1 == 0) {
			exit(0);
		}
		else {
			cout << "Do you want to take quiz of the same category?" << endl << "Press 1 for Yes and 0 for No" << endl;
			cin >> choice1;
			if (choice1 == 1) {
				cout << "Do you want to retake the same quiz?" << endl << "Press 1 for Yes and 0 for No" << endl;
				cin >> choice2;
				if (choice2 == 1) {
					//start quiz
					startQuiz(user.getUserId());
				}
				else if (choice2 == 0) {
					//decide quiz in same category
					decideQuiz();
					//start quiz
					startQuiz(user.getUserId());
				}
				else {
					throw new exception;
				}
			}

			else if (choice1 == 0) {
				//need to reselect all the categories and redo everything == startUserOperation functionality
				startUserOperation();
			}

			else {
				throw new exception;
			}
		}
	}
	catch(invalid_argument& e) {
		cout << "Invalid input, please retry!"<<endl;
		cout << e.what() << endl;
		exit(0);
	}
}

double QuizUserManager::viewUserAccuracy(const string& user_id) {
	double accuracy;

	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("select Accuracy from User u where u.user_id = (?)");
		stmt->setString(1, user_id);
		ResultSet* res = stmt->executeQuery();

		while (res->next()) {
			accuracy = res->getDouble("Accuracy");
		}

		delete res;
		delete stmt;
	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}

	return accuracy;
}

void QuizUserManager::viewPreviousScores(const string& user_id) {
	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL GetAllUserAttemptsWScores(?)");
		stmt->setString(1, user_id);
		ResultSet* res = stmt->executeQuery();

		cout << "Printing the history of the User with Quiz and its Scores: " << endl;

		while (res->next()) {
			string Score = res->getString("Score");
			string quiz_title = res->getString("quiz_title");

			cout << "Quiz Title: " << quiz_title << "and Score is: " << Score << endl;
		}
		delete res;
		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizUserManager::increaseUserAttempts(const string& user_id) {
	try {
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL IncrementQuizAttempts(?)");
		stmt->setString(1, user_id);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizUserManager::startUserOperation() {

	string user_id = user.getUserId();

	//fixing which category the user would like to choose
	decideCategory();
	
	//fixing which Quiz user would like to take
	decideQuiz();

	//startQuiz
	vector<pair<Question, Option>> userAnswered = startQuiz(user_id);

	//postQuizShow
	postQuizShow(user_id, attempt_id, userAnswered);

	//take another quiz
	takeAnotherQuiz();

}

void QuizUserManager::decideCategory() {
	int choice;
	getAllCategories();
	cout << "Lets hop onto the the game, User!" << "\t" << "Choose wisely, we are keeping your track record!!" << endl;
	cout << "NOTE: While Choosing anything including options, quizzes, categories, input of the integer n is expected where your choice is the nth value in the shown list" << endl;
	cout << "These are the quiz categories that we currently have." << endl;

	for (auto& category : currentCategories) {
		cout << category << endl;
	}
	cout << "Make a choice!" << endl;
	cin >> choice;
	cout << "Ok, choosing category: " << currentCategories[choice - 1] << endl;
	cat = currentCategories[choice - 1];
}

void QuizUserManager::decideQuiz() {
	int choice;
	cout << "Showing all the quizzes in the chosen category. Choose which quiz you want to attempt:  " << endl;
	getAllQuizes(cat.category_id);
	for (auto& quiz : quizzesInThisCategory) {
		cout << quiz << endl;
	}
	cout << "Make a choice!" << endl;
	cin >> choice;
	cout << "Ok, choosing quiz with title: " << quizzesInThisCategory[choice - 1].quiz_title << endl;
	quiz = quizzesInThisCategory[choice - 1];
}

vector<pair<Question, Option>> QuizUserManager::startQuiz(const string& user_id) {
	insertUserAttempt(user_id, quiz.quiz_id); //create user attempt
	increaseUserAttempts(user_id); // increase number of attempts in User Table
	attempt_id = getLatestAttemptId(user_id);

	cout << "Great! Now that you have selected the quiz you want to attempt, LETS START!" << endl;
	cout << "Loading questions and options for you!" << endl;

	setMap(quiz.quiz_id);

	cout << "STARTING THE QUIZ! ANSWER WISELY..." << endl;
	vector<pair<Question, Option>> userAnswered;

	for (auto& question : QuestionList) {
		int optionChoice;
		cout << question.first << endl;
		cout << "OPTIONS ARE: " << endl;
		for (auto& option : question.second) {
			cout << option << endl;
		}
		cout << "Your answer will be: " << endl;
		cin >> optionChoice;
		Option userChoiceOption = question.second[optionChoice - 1];
		//append in the user answered.
		userAnswered.push_back({ question.first, question.second[optionChoice - 1] });
	}
	return userAnswered;
}

void QuizUserManager::postQuizShow(const string& user_id, const string & attempt_id, vector<pair<Question, Option>> userAnswered) {
	cout << "Congratulations!! You have completed you attempt!" << endl;
	cout << "Hold on, let me sync your attempt with the DB..." << endl;

	for (auto& qa : userAnswered) {
		insertUserAnswer(attempt_id, qa.first.question_id, qa.second.option_id);
	}

	cout << "Done! Now lets get your quiz score.." << endl;
	cout << "Following are the details of your Quiz Attempt." << endl;
	getLatestAttemptDetails(user_id);
	cout << "Your score (%) is: " << getLatestQuizScore(quiz.quiz_id, user_id);
}
