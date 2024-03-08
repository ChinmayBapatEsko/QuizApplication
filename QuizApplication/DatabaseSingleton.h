/*
#include "DatabaseConnection.h"

class DatabaseSingleton {
private:
    static Connection* connection;

    // Private constructor to prevent instantiation
    DatabaseSingleton() {}

public:
    // Static method to get the database connection instance
    static Connection* getConnection() {
        if (!connection) {
            // Create the connection if it doesn't exist
            connection = DatabaseConnection().getConnection();
        }
        return connection;
    }

    // Prevent copying and assignment
    DatabaseSingleton(const DatabaseSingleton&) = delete;
    DatabaseSingleton& operator=(const DatabaseSingleton&) = delete;
};

// Initialize the static connection pointer
Connection* DatabaseSingleton::connection = nullptr;
*/