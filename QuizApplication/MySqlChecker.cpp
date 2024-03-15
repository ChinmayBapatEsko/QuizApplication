#include "MySqlChecker.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/stringbuffer.h"

using namespace sql;
using namespace std;
using namespace rapidjson;

MySqlChecker::MySqlChecker(const string& server, const string& username, const string& password) : server(server), username(username), pass(password) {}

bool MySqlChecker::checkConnection() const {
	try
	{
		mysql::MySQL_Driver* driver;
		unique_ptr<Connection> con;

		driver = mysql::get_driver_instance();
		con.reset(driver->connect(server, username, pass));

		cout << "MySQL is installed!" << endl;

		// set the credentials in the config.json file.


		const char* tempUName = username.c_str();
		const char* tempPass = pass.c_str();
		const char* tempSer = server.c_str();


		ifstream inputFile("creds.json");
		if (!inputFile.is_open()) {
			cerr << "Failed to open config.json file. Make sure its present in the directory." << endl;
			exit(0);
		}
		stringstream buffer;
		buffer << inputFile.rdbuf();
		string jsonText = buffer.str();
		inputFile.close();

		//Parse the Doc
		Document doc;
		doc.Parse(jsonText.c_str());

		//update values
		if (doc.HasMember("username")) {
			//doc["username"] = username;
			doc["username"].SetString(tempUName, strlen(tempUName), doc.GetAllocator());
		}
		if (doc.HasMember("password")) {
			//doc["password"] = pass;
			doc["password"].SetString(tempPass, strlen(tempPass), doc.GetAllocator());
		}
		if (doc.HasMember("server")) {
			//doc["server"] = server;
			doc["server"].SetString(tempSer, strlen(tempSer), doc.GetAllocator());
		}

		//write to json file
		FILE* fp;
		if (fopen_s(&fp, "creds.json", "w") != 0 || !fp) {
			cerr << "Failed to open config.json for writing" << endl;
			exit(0);
		}

		char writeBuffer[65536];  // 64 KB buffer
		FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		PrettyWriter<FileWriteStream> writer(os);
		doc.Accept(writer);
		fflush(fp);
		fclose(fp);

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
