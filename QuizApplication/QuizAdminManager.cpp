#include "QuizAdminManager.h"
#include "Category.h"
#include "DatabaseConnection.h"
//#include "DatabaseSingleton.h"

static Connection* conn = DatabaseConnection().getConnection();

void QuizAdminManager::insertCategory(const string& category_name) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL InsertCategory(?)");
		stmt->setString(1, category_name);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::insertQuiz(const string& category_id, const string& quiz_title, const string& quiz_description) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL InsertQuiz(?, ?, ?)");
		stmt->setString(1, category_id);
		stmt->setString(2, quiz_title);
		stmt->setString(3, quiz_description);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::insertQuestion(const string& quiz_id, const string& question_text, const string& question_type) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL InsertQuestion(?, ?, ?)");
		stmt->setString(1, quiz_id);
		stmt->setString(2, question_text);
		stmt->setString(3, question_type);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::insertOption(const string& question_id, const string& option_text, const bool& isCorrect) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL InsertOption(?, ?, ?)");
		stmt->setString(1, question_id);
		stmt->setString(2, option_text);
		stmt->setBoolean(3, isCorrect);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::updateCategory(const string& category_id, const string& category_name) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL UpdateCategory(?, ?)");
		stmt->setString(1, category_id);
		stmt->setString(2, category_name);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::updateQuiz(const string& quiz_id, const string& category_id, const string& quiz_title, const string& quiz_description) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL UpdateQuiz(?, ?, ?, ?)");
		stmt->setString(1, quiz_id);
		stmt->setString(2, category_id);
		stmt->setString(3, quiz_title);
		stmt->setString(4, quiz_description);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::updateQuestion(const string& question_id, const string& quiz_id, const string& question_text, const string& question_type) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL UpdateQuestion(?, ?, ?, ?)");
		stmt->setString(1, question_id);
		stmt->setString(2, quiz_id);
		stmt->setString(3, question_text);
		stmt->setString(4, question_type);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::updateOption(const string& option_id, const string& question_id, const string& option_text, const bool& isCorrect) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL UpdateOption(?, ?, ?, ?)");
		stmt->setString(1, option_id);
		stmt->setString(2, question_id);
		stmt->setString(3, option_text);
		stmt->setBoolean(4, isCorrect);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::deleteCategory(const string& category_id) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL DeleteCategory(?)");
		stmt->setString(1, category_id);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::deleteQuiz(const string& quiz_id) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL DeleteQuiz(?)");
		stmt->setString(1, quiz_id);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::deleteQuestion(const string& question_id) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL DeleteQuestion(?)");
		stmt->setString(1, question_id);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::deleteOption(const string& option_id) {
	try {
		//Connection* conn = DatabaseSingleton::getConnection();
		conn->setSchema("quizapplication");
		PreparedStatement* stmt = conn->prepareStatement("CALL DeleteOption(?)");
		stmt->setString(1, option_id);
		stmt->executeUpdate();

		delete stmt;

	}
	catch (SQLException& e) {
		cout << "MySQL Error: " << e.what() << endl;
	}
}

void QuizAdminManager::startAdminOperation() {

}
