#include "QuizUserManager.h"
#include "DatabaseConnection.h"
#include "vector"
#include <utility>

QuizUserManager::QuizUserManager(const User u){
	user = u;
};

void QuizUserManager::changeUser(const User u) {
	user = u;
}

void QuizUserManager::getAllCategories() {

	currentCategories = DatabaseConnection().callGetAllCategories();
}

void QuizUserManager::getAllQuizes(const string& category_id) {
	quizzesInThisCategory = DatabaseConnection().callgetAllQuizzes(category_id);
}

void QuizUserManager::setCategory(const Category& c) {
	cat = c;
}

void QuizUserManager::setQuiz(const Quiz& q) {
	quiz = q;
}

vector<Option> QuizUserManager::getOptionByQuestion(const string& question_id) {
	return DatabaseConnection().callGetOptionByQuestion(question_id);
}

void QuizUserManager::setMap(const string& quiz_id) {
	QuestionList = DatabaseConnection().callSetMap(quiz_id);
}

double QuizUserManager::getLatestQuizScore(const string& quiz_id, const string& user_id) {
	return DatabaseConnection().callGetLatestQuizScore(quiz_id, user_id);
}

void QuizUserManager::getLatestAttemptDetails(const string& user_id) {
	DatabaseConnection().callGetLatestAttemptDetails(user_id);
}

void QuizUserManager::insertUserAttempt(const string& user_id, const string& quiz_id) {
	DatabaseConnection().callInsertUserAttempt(user_id, quiz_id);
}

string QuizUserManager::getLatestAttemptId(const string& user_id) {
	return DatabaseConnection().callGetLatestAttemptId(user_id);
}

void QuizUserManager::insertUserAnswer(const string& attempt_id, const string& question_id, const string& option_id) {
	DatabaseConnection().callInsertUserAnswer(attempt_id, question_id, option_id);
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
	return DatabaseConnection().callViewUserAccuracy(user_id);
}

void QuizUserManager::viewPreviousScores(const string& user_id) {
	DatabaseConnection().callViewPreviousScores(user_id);
}

void QuizUserManager::increaseUserAttempts(const string& user_id) {
	DatabaseConnection().callIncreaseUserAttempts(user_id);
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
	attempt_id = getLatestAttemptId(user.user_id);

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