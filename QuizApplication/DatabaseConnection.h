#pragma once
#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql;

class DatabaseConnection {
private:
    const string server = "tcp://127.0.0.1:3306";
    const string username = "root";
    const string password = "Chinpat@2002";

    Driver* driver;
    Connection* con;

public:
    DatabaseConnection() {
        try {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (SQLException e) {
            cerr << "Could not connect to server. Error message: " << e.what() << endl;
            exit(1);
        }
    }

    ~DatabaseConnection() {
        delete con;
    }

    Connection* getConnection() {
        return con;
    }
};