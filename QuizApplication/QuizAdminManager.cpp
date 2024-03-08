#include "QuizAdminManager.h"
#include "Category.h"
#include "DatabaseConnection.h"

void QuizAdminManager::insertCategory(const string& category_name) {
	DatabaseConnection().callInsertCategory(category_name);
}

void QuizAdminManager::insertQuiz(const string& category_id, const string& quiz_title, const string& quiz_description) {
	DatabaseConnection().callInsertQuiz(category_id, quiz_title, quiz_description);
}

void QuizAdminManager::insertQuestion(const string& quiz_id, const string& question_text, const string& question_type) {
	DatabaseConnection().callInsertQuestion(quiz_id, question_text, question_type);
}

void QuizAdminManager::insertOption(const string& question_id, const string& option_text, const bool& isCorrect) {
	DatabaseConnection().callInsertOption(question_id, option_text, isCorrect);
}

void QuizAdminManager::updateCategory(const string& category_id, const string& category_name) {
	DatabaseConnection().callUpdateCategory(category_id, category_name);
}

void QuizAdminManager::updateQuiz(const string& quiz_id, const string& category_id, const string& quiz_title, const string& quiz_description) {
	DatabaseConnection().callUpdateQuiz(quiz_id, category_id, quiz_title, quiz_description);
}

void QuizAdminManager::updateQuestion(const string& question_id, const string& quiz_id, const string& question_text, const string& question_type) {
	DatabaseConnection().callUpdateQuestion(question_id, quiz_id, question_text, question_type);
}

void QuizAdminManager::updateOption(const string& option_id, const string& question_id, const string& option_text, const bool& isCorrect) {
	DatabaseConnection().callUpdateOption(option_id, question_id, option_text, isCorrect);
}

void QuizAdminManager::deleteCategory(const string& category_id) {
	DatabaseConnection().callDeleteCategory(category_id);
}

void QuizAdminManager::deleteQuiz(const string& quiz_id) {
	DatabaseConnection().callDeleteQuiz(quiz_id);
}

void QuizAdminManager::deleteQuestion(const string& question_id) {
	DatabaseConnection().callDeleteQuestion(question_id);
}

void QuizAdminManager::deleteOption(const string& option_id) {
	DatabaseConnection().callDeleteOption(option_id);
}

void QuizAdminManager::startAdminOperation() {
	int choice1;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Welcome ADMIN!" << endl;
	cout << "Do you wish to play quiz (1) " << endl << "OR " << endl << "Modify Our Quiz DB? (2)" << endl;
	cin >> choice1;

	if (choice1 == 1) {
		QuizUserManager::startUserOperation();
	}
	else {
		exit(0);
	}
}
