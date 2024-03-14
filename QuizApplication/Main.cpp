#include "Main.h"
#include "MySqlChecker.h"
#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
//dll file
#include "PrestartPrints.h"


using namespace std;
using namespace rapidjson;

void Main::start() {


	if (!checkConfigFile()) {
		cerr << "Some error occured during reading config file and setting your environment." << endl;
		exit(0);
	}

	pair<bool, string> userCreds = authManager.init();

	instManager = InstanceManager(userCreds);
}

void Main::checkMySQLInstallation() {

	string server = "tcp://127.0.0.1:";
	string tempUsername;
	string tempPass;
	string tempPort;

	cout << "LETS CHECK IF YOU HAVE MYSQL PROPERLY INSTALLED INTO YOUR DEVICE" << endl;
	cout << "Please enter the port number your MySQL server is hosted on localhost (Default is 3306. If you haven't changed, please input 3306.) : ";
	cin >> tempPort;
	cout << "\nPlease enter the username and password to your MySQL: ";
	cin >> tempUsername >> tempPass;

	MySqlChecker checker(server + tempPort, tempUsername, tempPass);
	if (!checker.checkConnection()) {
		cerr << "Failed to establish connection" << endl;
		exit(0);
	}
	userServer = server + tempPort;
	userUsername = tempUsername;
	userPassword = tempPass;
}


void Main::setLocalDatabase() {
	string dbName = "quizapplication";
	string sqlFilePath = "./quizapplication.sql";
	string resultFile = "/.schema_check_result.txt";
	string importCommand = "mysql -h " + userServer+ " -u " + userUsername + " -p " + userPassword + " " + dbName + " < " + sqlFilePath;
	string checkSchemaCommand = "mysql -u "+ userUsername + " -p" + userPassword + " -e \"SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '" + dbName + "'\" > " + resultFile;
	//execute the command

	system(checkSchemaCommand.c_str());

	ifstream inFile(resultFile);
	string line;
	bool schemaExists = false;
	while (getline(inFile, line)) {
		if (!line.empty()) {
			schemaExists = true;
			break;
		}
	}
	inFile.close();
	// Optionally delete the temporary file here
	remove(resultFile.c_str());


	if (!schemaExists) {
		cout << "Database does not exist...Attempting to import...." << endl;
		int importCheck = system(importCommand.c_str());
		if (importCheck == 0)
		{
			cout << "Database imported successfully" << endl;
		}
		else {
			cout << "Failed to import Database" << endl;
			cout << "Try again. Check the file name (must be quizDB.sql) or check the file path (must be same directory as the .exe file)" << endl;
			exit(0);
		}
	}
	else {
		cout << "Database Already Exists, no need to import. Moving onto further process...." << endl;
		cout << "----------------------------------------------------------------------------------" << endl;
	}
}

bool Main::checkConfigFile() {

	bool flag1 = false;
	bool flag2 = false;
	ifstream inputFile("config.json");
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

	if (doc.HasMember("mySqlInstalled")) {
		if (doc["mySqlInstalled"] == true) {
			flag1 = true;
		}
		else {
			checkMySQLInstallation();
			flag1 = true;
			doc["mySqlInstalled"] = true;
			FILE* fp;
			if (fopen_s(&fp, "config.json", "w") != 0 || !fp){
				cerr << "Failed to open config.json for writing" << endl;
				exit(0);
			}

			char writeBuffer[65536];  // 64 KB buffer
				FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
				PrettyWriter<FileWriteStream> writer(os);
				doc.Accept(writer);

				fclose(fp);
		}
	}
	else {
		cerr << "Config File has been modified! ERROR: Key (mySqlInstalled) has been changed / not present" << endl;
		exit(0);
	}

	if (doc.HasMember("schemaPresent")) {
		if (doc["schemaPresent"] == true) {
			flag2 = true;
		}
		else {
			setLocalDatabase();
			flag2 = true;
			doc["schemaPresent"] = true;
			FILE* fp;
			if (fopen_s(&fp, "config.json", "w") != 0 || !fp){
				cerr << "Failed to open config.json for writing" << endl;
				exit(0);
			}

			char writeBuffer[65536];  // 64 KB buffer
			FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
			PrettyWriter<FileWriteStream> writer(os);
			doc.Accept(writer);

			fclose(fp);
		}
	}
	else {
		cerr << "Config File has been modified! ERROR: Key (schemaPresent) has been changed / not present" << endl;
		exit(0);
	}

	return flag1 && flag2;
}


int main() {
	//cout << "WELCOME To my Quiz Application." << "\t" << "Without any further ado, lets start!" << endl << endl;
	//calling the dll function
	printWelcomeMessage();
	cout << endl << "------------------------------------------------------------------------------" << endl;
	Main application = Main();
	application.start();

}