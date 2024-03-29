#include "DatabaseConnection.h"

vector<Category> DatabaseConnection::callGetAllCategories() {
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
    catch (SQLException& e) {
        cout << "MySQL Error: " << e.what() << endl;
    }
    return ans;

}

vector<Quiz> DatabaseConnection::callgetAllQuizzes(const string& category_id) {
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

    return ans;
}

vector<Option> DatabaseConnection::callGetOptionByQuestion(const string& question_id) {
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

vector<Question> DatabaseConnection::callSetMap(const string& quiz_id) {
    vector<Question> qList;
    vector<pair<Question, vector<Option>>> QuestionList;
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
    }
    catch (SQLException& e) {
        cout << "MySQL Error: " << e.what() << endl;
    }

    return qList;
}

vector<pair<Question, vector<Option>>> DatabaseConnection::callSetOptionsInMap(vector<Question> qList) {
    vector<pair<Question, vector<Option>>> QuestionList;
    try {
        for (auto& q : qList) {
            vector<Option> opts = callGetOptionByQuestion(q.question_id);
            QuestionList.push_back({ q , opts });
        }
    }
    catch (SQLException& e) {
        cout << "MySQL Error: " << e.what() << endl;
    }

    return QuestionList;
}

double DatabaseConnection::callGetLatestQuizScore(const string& quiz_id, const string& user_id) {
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
    catch (SQLException& e) {
        cout << "MySQL Error: " << e.what() << endl;
    }

    return score;
}

void DatabaseConnection::callGetLatestAttemptDetails(const string& user_id) {
    try {
        conn->setSchema("quizapplication");
        PreparedStatement* stmt = conn->prepareStatement("CALL GetLatestAttemptDetails(?)");
        stmt->setString(1, user_id);
        ResultSet* res = stmt->executeQuery();

        while (res->next()) {
            string questionText = res->getString("question_text");
            string user_answer_text = res->getString("user_answer_text");
            string correct_answer_text = res->getString("correct_answer_text");

            cout << "Question: " << questionText << endl;
            cout << "User answered this: " << user_answer_text << endl;
            cout << "Actual answer is: " << correct_answer_text << endl << endl;
        }
        delete res;
        delete stmt;

    }
    catch (SQLException& e) {
        cout << "MySQL Error: " << e.what() << endl;
    }
}

void DatabaseConnection::callInsertUserAttempt(const string& user_id, const string& quiz_id) {
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

string DatabaseConnection::callGetLatestAttemptId(const string& user_id) {
    string ans;

    try {
        conn->setSchema("quizapplication");
        PreparedStatement* stmt = conn->prepareStatement("CALL getLatestAttemptId(?)");
        stmt->setString(1, user_id);
        ResultSet* res = stmt->executeQuery();

        if (res->next()) {
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

void DatabaseConnection::callInsertUserAnswer(const string& attempt_id, const string& question_id, const string& option_id) {
    try {
        conn->setSchema("quizapplication");
        PreparedStatement* stmt = conn->prepareStatement("CALL InsertUserAnswer(?, ?, ?)");
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

double DatabaseConnection::callViewUserAccuracy(const string& user_id) {
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

void DatabaseConnection::callViewPreviousScores(const string& user_id) {
    try {
        conn->setSchema("quizapplication");
        PreparedStatement* stmt = conn->prepareStatement("CALL GetAllUserAttemptsWScoresAndTitles(?)");
        stmt->setString(1, user_id);
        ResultSet* res = stmt->executeQuery();

        cout << "Printing the history of the User with Quiz and its Scores: " << endl << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;

        while (res->next()) {
            double Score = res->getDouble("Score");
            string quiz_title = res->getString("quiz_title");

            cout << "Quiz Title: " << quiz_title << " and Score is: " << Score << endl;
        }
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        delete res;
        delete stmt;

    }
    catch (SQLException& e) {
        cout << "MySQL Error: " << e.what() << endl;
    }
}

void DatabaseConnection::callIncreaseUserAttempts(const string& user_id) {
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

User DatabaseConnection::callInstanceManagerUtility(const string& user_id) {

    User temp;
    try {
        conn->setSchema("quizapplication");
        PreparedStatement* stmt = conn->prepareStatement("SELECT username, password, QuizAttempts, Accuracy FROM User where User.user_id = (?)");
        stmt->setString(1, user_id);
        ResultSet* res = stmt->executeQuery();

        while (res->next()) {
            temp.username = res->getString("username");
            temp.password = res->getString("password");
            temp.quizAttempts = res->getInt("QuizAttempts");
            temp.accuracy = res->getDouble("Accuracy");
        }
        delete res;
        delete stmt;

    }
    catch (SQLException& e) {
        cout << "MySQL Error: " << e.what() << endl;
    }

    return temp;
}

pair<bool, string> DatabaseConnection::callLoginFunction(const string& username, const string& password) {
    try {
        conn->setSchema("quizapplication");
        PreparedStatement* stmt = conn->prepareStatement("CALL AuthenticateUser(?, ?)");
        stmt->setString(1, username);
        stmt->setString(2, password);
        ResultSet* res = stmt->executeQuery();

        if (res->next()) {
            //User found
            string user_id = res->getString("user_id");
            bool isAdmin = res->getBoolean("isAdmin");
            cout << "Login Successful!" << endl;
            return make_pair(isAdmin, user_id);
        }
        else {
            //user not found
            cout << "Invalid credentials or User not found!" << endl;
            return make_pair(false, "");
        }

        delete stmt;

    }
    catch (SQLException& e) {
        cout << "MySQL Error: " << e.what() << endl;
    }
}

void DatabaseConnection::callRegisterFunction(const string& tempUsername, const string& tempPass, const bool& tempFlag) {
    try {
        conn->setSchema("quizapplication");
        PreparedStatement* stmt = conn->prepareStatement("CALL InsertUser(?, ?, ?)");
        stmt->setString(1, tempUsername);
        stmt->setString(2, tempPass);
        stmt->setBoolean(3, tempFlag);
        stmt->executeUpdate();

        delete stmt;

    }
    catch (SQLException& e) {
        cout << "MySQL Error: " << e.what() << endl;
    }
}

void DatabaseConnection::callInsertCategory(const string& category_name) {
    try {
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

void DatabaseConnection::callInsertQuiz(const string& category_id, const string& quiz_title, const string& quiz_description) {
    try {
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

void DatabaseConnection::callInsertQuestion(const string& quiz_id, const string& question_text, const string& question_type) {
    try {
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

void DatabaseConnection::callInsertOption(const string& question_id, const string& option_text, const bool& isCorrect) {
    try {
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

void DatabaseConnection::callUpdateCategory(const string& category_id, const string& category_name) {
    try {
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

void DatabaseConnection::callUpdateQuiz(const string& quiz_id, const string& category_id, const string& quiz_title, const string& quiz_description) {
    try {
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

void DatabaseConnection::callUpdateQuestion(const string& question_id, const string& quiz_id, const string& question_text, const string& question_type) {
    try {
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

void DatabaseConnection::callUpdateOption(const string& option_id, const string& question_id, const string& option_text, const bool& isCorrect) {
    try {
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

void DatabaseConnection::callDeleteCategory(const string& category_id) {
    try {
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

void DatabaseConnection::callDeleteQuiz(const string& quiz_id) {
    try {
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

void DatabaseConnection::callDeleteQuestion(const string& question_id) {
    try {
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

void DatabaseConnection::callDeleteOption(const string& option_id) {
    try {
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
