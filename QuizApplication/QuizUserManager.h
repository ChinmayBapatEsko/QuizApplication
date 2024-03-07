#pragma once
#include "User.h"
#include "Category.h"
#include "Quiz.h"
#include "Question.h"
#include "Option.h"
#include<string>
#include<unordered_map>
#include<vector>

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
	string attempt_id;//

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
	void insertUserAnswer(const string& attempt_id, const string& question_id, const string& option_id);//
	
	void takeAnotherQuiz();//
	double viewUserAccuracy(const string& user_id);//
	void viewPreviousScores(const string& user_id);//
	void increaseUserAttempts(const string& user_id);//

	void startUserOperation();//
	void decideCategory();//
	void decideQuiz();//
	vector<pair<Question, Option>> startQuiz(const string& user_id);//
	void postQuizShow(const string& user_id, const string& attempt_id, vector<pair<Question, Option>> userAnswered);//
};

