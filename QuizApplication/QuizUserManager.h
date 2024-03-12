
/*

QuizUserManager class is responsible to create and maintain the state of the entire game for a User. The state of game includes the Category of quiz that is being played, 
the quiz itself and the list of questions with their options inside the quiz. The manager will also keep track of the options that the user has answered

The class can also show the user's accuracy. Can also show the scores that the user scored in his various attempts.

The class also handles the option if user wants to take another quiz (of different / same category, retake same quiz / different quiz)

*/


#pragma once
#include "User.h"
#include "Category.h"
#include "Quiz.h"
#include "Question.h"
#include "Option.h"
#include<string>
#include<unordered_map>
#include<vector>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace sql;

static string attempt_id;

class QuizUserManager
{
public:

	QuizUserManager(const User u);
	QuizUserManager() {};

	User user; //
	Category cat;//
	Quiz quiz;//
	vector<pair<Question, vector<Option>>> QuestionList;//
	vector<Category> currentCategories;//
	vector<Quiz> quizzesInThisCategory;//

	void getAllCategories();//
	void getAllQuizes(const string &category_id);//
	
	void changeUser(const User u);//
	void setCategory(const Category &c);//
	void setQuiz(const Quiz &q);//
	
	vector<Option> getOptionByQuestion(const string& option_id);//
	void setMap(const string& quiz_id);//
	double getLatestQuizScore(const string &quiz_id, const string& user_id);//
	void getLatestAttemptDetails(const string& user_id);//

	void insertUserAttempt(const string& user_id, const string& quiz_id);//
	string getLatestAttemptId(const string& user_id);//
	void insertUserAnswer(const string& attempt_id, vector<pair<Question, Option>> userAnswered);//
	
	void startUserOperation();//
	void takeAnotherQuiz();//
	double viewUserAccuracy(const string& user_id);//
	void viewPreviousScores(const string& user_id);//
	void increaseUserAttempts(const string& user_id);//

	void decideCategory();//
	void decideQuiz();//
	vector<pair<Question, Option>> startQuiz(const string& user_id);//
	void postQuizShow(const string& user_id, const string& attempt_id, vector<pair<Question, Option>> userAnswered);//
};

