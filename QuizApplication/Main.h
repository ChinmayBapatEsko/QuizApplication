/*

 > Main header file. Contains the main method. Maintains a static object of AuthenticationManager and InstanceManager in memory till completion of execution.

 > start() method in the Main class, creates a instance of the SqlChecker class that checks if MySQL is installed on the device.

 > Also stores the server url, username and password of MySQL of that device. (Connection essentials).

  > Clients of this class are: AuthenticationManager and InstanceManager class objects.

*/



#pragma once
#include <string>
#include "AuthenticationManager.h"
#include "InstanceManager.h"
#include "DatabaseConnection.h"
using namespace std;


static AuthenticationManager authManager;
static InstanceManager instManager;

class Main
{
public:
	Main() {};
	void start();
	bool checkConfigFile();
	void checkMySQLInstallation();
	void setLocalDatabase();
};

