
/*

DatabaseConnection class is the class that is responsible for all the functionalities related to the Database. Contains all the methods including methods that only Admin can do
and also the methods that the user can do. 
Clients to this class: QuizUserManager and QuizAdminManager.

*/

#pragma once
#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Category.h"
#include "Quiz.h"
#include "Question.h"
#include "Option.h"
#include "vector"
#include <utility>
#include "User.h"
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace sql;
using namespace rapidjson;

class DatabaseConnection {
private:
    string server;
    string username;
    string password;

public:
    Connection* conn;
    Driver* driver;
    DatabaseConnection() {
        if (server.empty() && username.empty() && password.empty()) {
            updateCredentials();
        }
        try {
            driver = get_driver_instance();
            conn = driver->connect(server, username, password);
        }
        catch (SQLException e) {
            cerr << "Could not connect to server. Error message: " << e.what() << endl;
            exit(1);
        }
    }

    ~DatabaseConnection() {
        delete conn;
    }

    Connection* getConnection() {
        return conn;
    }

    void updateCredentials() {
        ifstream configFile("creds.json");
        if (!configFile.is_open()) {
            cerr << "Failed to open config.json" << endl;
            exit(1);
        }

        stringstream buffer;
        buffer << configFile.rdbuf();
        string jsonText = buffer.str();
        configFile.close();

        Document doc;
        doc.Parse(jsonText.c_str());

        // Set server, username, and password from JSON
        server = doc["server"].GetString();
        username = doc["username"].GetString();
        password = doc["password"].GetString();
    }

    /////////////////////////////////////////////////USER////////////////////////////////////////////

    vector<Category> callGetAllCategories();

    vector<Quiz> callgetAllQuizzes(const string& category_id);

    vector<Option> callGetOptionByQuestion(const string& question_id);

    vector<Question> callSetMap(const string& quiz_id);

    vector<pair<Question, vector<Option>>> callSetOptionsInMap(vector<Question> qList);

    double callGetLatestQuizScore(const string& quiz_id, const string& user_id);

    void callGetLatestAttemptDetails(const string& user_id);

    void callInsertUserAttempt(const string& user_id, const string& quiz_id);

    string callGetLatestAttemptId(const string& user_id);

    void callInsertUserAnswer(const string& attempt_id, const string& question_id, const string& option_id);

    double callViewUserAccuracy(const string& user_id);

    void callViewPreviousScores(const string& user_id);

    void callIncreaseUserAttempts(const string& user_id);

    User callInstanceManagerUtility(const string& user_id);

    pair<bool, string> callLoginFunction(const string& username, const string& password);

    void callRegisterFunction(const string& tempUsername, const string& tempPass, const bool& tempFlag);

    //////////////////////////////////////////ADMIN///////////////////////////////////////////////////////

    void callInsertCategory(const string& category_name);

    void callInsertQuiz(const string& category_id, const string& quiz_title, const string& quiz_description);

    void callInsertQuestion(const string& quiz_id, const string& question_text, const string& question_type);

    void callInsertOption(const string& question_id, const string& option_text, const bool& isCorrect);

    void callUpdateCategory(const string& category_id, const string& category_name);

    void callUpdateQuiz(const string& quiz_id, const string& category_id, const string& quiz_title, const string& quiz_description);

    void callUpdateQuestion(const string& question_id, const string& quiz_id, const string& question_text, const string& question_type);

    void callUpdateOption(const string& option_id, const string& question_id, const string& option_text, const bool& isCorrect);

    void callDeleteCategory(const string& category_id);

    void callDeleteQuiz(const string& quiz_id);

    void callDeleteQuestion(const string& question_id);

    void callDeleteOption(const string& option_id);
};