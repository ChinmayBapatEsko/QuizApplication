#include "User.h"

User::User(string id, string username, string password, int quizAttempts, double accuracy) :
	user_id(id), username(username), password(password), quizAttempts(quizAttempts), accuracy(accuracy) {}

std::string User::getUsername() const {
    return username;
}

void User::setUsername(const string& u) {
    username = u;
}

std::string User::getPassword() const {
    return password;
}

void User::setPassword(const std::string& p) {
    password = p;
}

int User::getQuizAttempts() const {
    return quizAttempts;
}

void User::setQuizAttempts(const int &qa) {
    quizAttempts = qa;
}

double User::getAccuracy() const {
    return accuracy;
}

void User::setAccuracy(const double &a) {
    accuracy = a;
}

string User::getUserId() const {
    return user_id;
}