#pragma once
#include <string>
using namespace std;
class User
{
public:
	string user_id;
	string username;
	string password;
	int quizAttempts;
	double accuracy;
	User(string id, string username, string password, int quizAttempts, double accuracy);
	User() {};

	//getters and setters
	string getUsername() const;
	string getUserId() const;
	string getPassword() const;
	int getQuizAttempts() const;
	double getAccuracy() const;
	void setUsername(const string &u);
	void setUserId(const string &ui);
	void setPassword(const string &p);
	void setQuizAttempts(const int &qa);
	void setAccuracy(const double &a);
};

