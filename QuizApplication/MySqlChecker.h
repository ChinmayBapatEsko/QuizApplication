/*

The MySQLChecker class is responsible for checking if MySQL is installed on the device. Uses a connection to test if the connection returns a response.
Server for the class is the Main class. 

*/

#pragma once
#include <string>
using namespace std;
class MySqlChecker
{
public:
	MySqlChecker(const string& server, const string& username, const string& password);
	bool checkConnection() const;
	string server;
	string username;
	string pass;
};
