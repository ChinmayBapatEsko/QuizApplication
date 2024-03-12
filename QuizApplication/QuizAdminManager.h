
/*

The class takes care of handling all the functions of the Admin. 
The AdminManager can let the Admin inside it CREATE, UPDATE or DELETE the Categories, Quizzes, Questions in the Quizzes and also the Options of a particular Question.
The manager can also divert the Admin to play the quiz if he wishes for.

*/

#pragma once
#include "Admin.h"
#include "QuizUserManager.h"

class QuizAdminManager:public QuizUserManager
{
public:
	Admin admin; //
	QuizAdminManager(const Admin a) { admin = a;};
	QuizAdminManager() {};
	//cant ids of any table.
	void insertCategory(const string& category_name);//
	void insertQuiz(const string& category_id, const string& quiz_title, const string& quiz_description);//
	void insertQuestion(const string& quiz_id, const string& question_text, const string& question_type);//
	void insertOption(const string& question_id, const string& option_text, const bool& isCorrect);//

	void updateCategory(const string& category_id, const string& category_name);//
	void updateQuiz(const string& quiz_id, const string& category_id, const string& quiz_title, const string& quiz_description);//
	void updateQuestion(const string& question_id, const string& quiz_id, const string& question_text, const string& question_type); //can only change question text
	void updateOption(const string& option_id, const string& question_id, const string& option_text, const bool& isCorrect); //can only change option text
	
	void deleteCategory(const string& category_id);//
	void deleteQuiz(const string& quiz_id);//
	void deleteQuestion(const string& question_id);//
	void deleteOption(const string& option_id);//

	void startAdminOperation();//
};

