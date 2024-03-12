#include "MySqlChecker.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <iostream>

using namespace sql;
using namespace std;

MySqlChecker::MySqlChecker(const string& server, const string& username, const string& password) : server(server), username(username), pass(password) {}

bool MySqlChecker::checkConnection() const {
	try
	{
		mysql::MySQL_Driver* driver;
		unique_ptr<Connection> con;

		driver = mysql::get_driver_instance();
		con.reset(driver->connect(server, username, pass));

		cout << "MySQL is installed!" << endl;
		return true;
	}
	catch (const sql::SQLException& e)
	{
		std::cerr << "SQLException caught: " << e.what() << std::endl;
		std::cerr << "With MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLStateCStr() << std::endl;

		std::cerr << "Basically, Check if you have done all these steps: " << endl << "1) Installation of MYSQL on your device" << endl << "2) Input correct username and passwords." << endl << "Connector to MySQL not found or is unsupported." << endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	return false;
}
