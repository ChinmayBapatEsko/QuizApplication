#include "QuizUserManager.h"
#include "DatabaseConnection.h"
#include "vector"
#include <utility>
#include <chrono>
#include <thread>

QuizUserManager::QuizUserManager(const User u){
	user = u;
};

void QuizUserManager::changeUser(const User u) {
	user = u;
}

void QuizUserManager::getAllCategories() {
	currentCategories.clear();
	currentCategories = DatabaseConnection().callGetAllCategories();
}

void QuizUserManager::getAllQuizes(const string& category_id) {
	quizzesInThisCategory.clear();
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
	QuestionList.clear();
	vector<Question> temp;
	 temp = DatabaseConnection().callSetMap(quiz_id);
	 //QuestionList = DatabaseConnection().callSetOptionsInMap(temp);
	 for (auto& q : temp) {
		 QuestionList.push_back({q , DatabaseConnection().callGetOptionByQuestion(q.question_id) });
	 }
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

void QuizUserManager::insertUserAnswer(const string& attempt_id, vector<pair<Question, Option>> userAnswered) {
	for (auto& qa : userAnswered) {
		DatabaseConnection().callInsertUserAnswer(attempt_id, qa.first.question_id, qa.second.option_id);
	}
}

void QuizUserManager::takeAnotherQuiz() {
	int choice1, choice2;
	try {

		int choice;
		cout << "Select your choice: " << endl;
		cout << "1) Play Quiz" << endl << "2) View all previous quiz scores" << endl << "3) View User Accuracy" << endl << "4) Exit" << endl;
		cin >> choice;

		if (choice == 1) {
			cout << "Do you want to play another quiz?" << endl;
			cin >> choice1;
			if (choice1 == 0) {
				cout << "THANKYOU!!!" << endl;
				exit(0);
			}
			else {
				cout << "Do you want to take quiz of the same category?" << endl << "Press 1 for Yes and 0 for No: " << endl;
				cin >> choice1;
				if (choice1 == 1) {
					cout << "Do you want to retake the same quiz?" << endl << "Press 1 for Yes and 0 for No: " << endl;
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
		else if (choice == 2) {
			viewPreviousScores(user.getUserId());
			startUserOperation();
		}
		else if (choice == 3) {
			cout << "Accuracy: " << viewUserAccuracy(user.getUserId()) << endl;
			startUserOperation();
		}
		else if (choice == 4) {
			cout << "Thankyou!!!" << endl;
			exit(0);
		}
		else {
			cout << "Invalid Input" << endl;
			exit(0);
		}

	}
	catch(std::exception& e) {
		cout << e.what() << endl;
		cout << "CMON! Give proper Input!!!" << endl;
		cout << "Restart Now, as your punishment  >_<   " << endl;
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

	//need to give user option to see his current accuracy.(wrt all quizzes) AND to see all his attempts

	try
	{
		int choice;
		cout << "Select your choice: " << endl;
		cout << "1) Play Quiz" << endl << "2) View all previous quiz scores" << endl << "3) View User Accuracy" << endl << "4) Exit" << endl;
		cin >> choice;

		if (choice == 1) {

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
		else if (choice == 2) {
			viewPreviousScores(user_id);
			startUserOperation();
		}
		else if (choice == 3) {
			cout << "Accuracy: " << viewUserAccuracy(user_id) << endl;
			startUserOperation();
		}
		else if (choice == 4) {
			cout << "Thankyou!!!" << endl;
			exit(0);
		}
		else {
			cout << "Invalid Input" << endl;
			exit(0);
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		cout << "CMON! Give proper Input!!!" << endl;
		cout << "Restart Now, as your punishment  >_<   " << endl;
		exit(0);
	}
}

void QuizUserManager::decideCategory() {
	try
	{
		int choice;
		getAllCategories();
		cout << "---------------------------------------------------------------------------------------------" << endl;
		cout << "Lets hop onto the the game, User!" << "  " << "Choose wisely, we are keeping your track record!!" << endl;
		cout << "NOTE: While Choosing anything including options, quizzes, categories, input of the integer n is expected where your choice is the nth value in the shown list" << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl << endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		cout << "These are the quiz categories that we currently have." << endl << endl;
		int count = 0;
		for (auto& category : currentCategories) {
			count++;
			cout << count << ") " << category << endl;
		}
		cout << endl;
		cout << "----------------------------------------------------------------------------------------------" << endl;
		cout << "Make a choice!" << endl;
		cin >> choice;
		if (choice > currentCategories.size()) { cout << "CATEGORY YOU WANT, IS NOT SERVED HERE, PLS INPUT PROPERLY!" << endl; exit(0); }
		cout << "Ok, choosing category " << count << ") " << currentCategories[choice - 1] << endl << endl;
		cat = currentCategories[choice - 1];
		cout << "----------------------------------------------------------------------------------------------" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		cout << "CMON! Give proper Input!!!" << endl;
		cout << "Restart Now, as your punishment  >_<   " << endl;
		exit(0);
	}
}

void QuizUserManager::decideQuiz() {
	
	int choice;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	cout << "Showing all the quizzes in the chosen category. Choose which quiz you want to attempt:  " << endl << endl;
	getAllQuizes(cat.category_id);
	int count = 0;
	for (auto& quiz : quizzesInThisCategory) {
		count++;
		cout << count << ") " << quiz << endl;
	}
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	cout << "Make a choice!" << endl;
	try
	{
		cin >> choice;
		if (choice > quizzesInThisCategory.size()) {
			throw new exception;
		}
		cout << "Ok, choosing quiz with title: " << count << ") " << quizzesInThisCategory[choice - 1].quiz_title << endl << endl;
		quiz = quizzesInThisCategory[choice - 1];
		cout << "------------------------------------------------------------------------------------------------" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		cout << "CMON! Give proper Input!!!" << endl;
		cout << "Restart Now, as your punishment  >_<   " << endl;
		exit(0);
	}
}

vector<pair<Question, Option>> QuizUserManager::startQuiz(const string& user_id) {
	try
	{
		insertUserAttempt(user_id, quiz.quiz_id); //create user attempt
		increaseUserAttempts(user_id); // increase number of attempts in User Table
		attempt_id = getLatestAttemptId(user.user_id);

		cout << "Great! Now that you have selected the quiz you want to attempt, LETS START!" << endl;
		cout << "Loading questions and options for you!" << endl << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << "------------------------------------------------------------------------------------------------" << endl;
		setMap(quiz.quiz_id);

		cout << "STARTING THE QUIZ! ANSWER WISELY..." << endl << endl;

		for (int i = 5; i >= 1; i--) {
			cout << i << endl;
			this_thread::sleep_for(chrono::seconds(1));
		}
		vector<pair<Question, Option>> userAnswered;

		int qCount = 0;
		for (auto& question : QuestionList) {
			int optionChoice;
			qCount++;
			cout << "Q" << qCount << ") " << question.first << endl;
			cout << "OPTIONS ARE: " << endl;
			int oCount = 0;
			for (auto& option : question.second) {
				oCount++;
				cout << oCount << ") " << option << endl;
			}
			cout << endl;
			cout << "Your answer will be: " << endl;
			cin >> optionChoice;
			Option userChoiceOption = question.second[optionChoice - 1];
			//append in the user answered.
			userAnswered.push_back({ question.first, question.second[optionChoice - 1] });
		}
		cout << "---------------------------------------------------------------------------------" << endl;
		return userAnswered;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		cout << "CMON! Give proper Input!!!" << endl;
		cout << "Restart Now, as your punishment  >_<   " << endl;
		exit(0);
	}
}

void QuizUserManager::postQuizShow(const string& user_id, const string & attempt_id, vector<pair<Question, Option>> userAnswered) {
	cout << "Congratulations!! You have completed you attempt!" << endl;
	cout << "Hold on, let me sync your attempt with the DB..." << endl;
	
	insertUserAnswer(attempt_id,userAnswered);

	cout << "Done! Now lets get your quiz score.." << endl;
	cout << "Following are the details of your Quiz Attempt." << endl << endl;
	getLatestAttemptDetails(user_id);
	cout << "Your score (%) is: " << getLatestQuizScore(quiz.quiz_id, user_id) << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
}