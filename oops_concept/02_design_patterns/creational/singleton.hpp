#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>
#include <mutex>
#include <string>

/**
 * SINGLETON DESIGN PATTERN
 * - Ensures only ONE instance of a class exists
 * - Provides global access to that instance
 * - Common in interviews for database connections, loggers, configuration
 */

// ======================= CLASSIC SINGLETON =======================
class DatabaseConnection {
private:
    static DatabaseConnection* instance;
    static std::mutex mutex_;
    std::string connection_string;
    
    // Private constructor prevents external instantiation
    DatabaseConnection(const std::string& conn_str = "localhost:3306") 
        : connection_string(conn_str) {
        std::cout << "Database connection created to: " << conn_str << std::endl;
    }
    
    // Delete copy constructor and assignment operator
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    
public:
    // Thread-safe singleton instance
    static DatabaseConnection* getInstance(const std::string& conn_str = "localhost:3306") {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance == nullptr) {
            instance = new DatabaseConnection(conn_str);
        }
        return instance;
    }
    
    void query(const std::string& sql) {
        std::cout << "Executing query on " << connection_string << ": " << sql << std::endl;
    }
    
    void close() {
        std::cout << "Closing connection to " << connection_string << std::endl;
    }
    
    ~DatabaseConnection() {
        std::cout << "Database connection destroyed" << std::endl;
    }
};

// Static member definitions
DatabaseConnection* DatabaseConnection::instance = nullptr;
std::mutex DatabaseConnection::mutex_;

// ======================= MODERN C++ SINGLETON (RECOMMENDED) =======================
class Logger {
private:
    Logger() = default;
    
public:
    // Delete copy constructor and assignment
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    // Thread-safe singleton using static local variable
    static Logger& getInstance() {
        static Logger instance; // Guaranteed to be thread-safe in C++11+
        return instance;
    }
    
    void log(const std::string& message) {
        std::cout << "[LOG]: " << message << std::endl;
    }
    
    void error(const std::string& message) {
        std::cout << "[ERROR]: " << message << std::endl;
    }
    
    void info(const std::string& message) {
        std::cout << "[INFO]: " << message << std::endl;
    }
};

// ======================= ENUM SINGLETON (ADVANCED) =======================
class ConfigManager {
public:
    enum class Environment {
        DEVELOPMENT,
        TESTING,
        PRODUCTION
    };
    
private:
    Environment env;
    std::string config_path;
    
    ConfigManager() : env(Environment::DEVELOPMENT), config_path("config/dev.json") {}
    
public:
    static ConfigManager& getInstance() {
        static ConfigManager instance;
        return instance;
    }
    
    void setEnvironment(Environment new_env) {
        env = new_env;
        switch(env) {
            case Environment::DEVELOPMENT:
                config_path = "config/dev.json";
                break;
            case Environment::TESTING:
                config_path = "config/test.json";
                break;
            case Environment::PRODUCTION:
                config_path = "config/prod.json";
                break;
        }
    }
    
    std::string getConfigPath() const {
        return config_path;
    }
    
    void displayConfig() const {
        std::string env_str;
        switch(env) {
            case Environment::DEVELOPMENT: env_str = "DEVELOPMENT"; break;
            case Environment::TESTING: env_str = "TESTING"; break;
            case Environment::PRODUCTION: env_str = "PRODUCTION"; break;
        }
        std::cout << "Environment: " << env_str << ", Config: " << config_path << std::endl;
    }
};

// ======================= DEMONSTRATION FUNCTIONS =======================
inline void demonstrateSingleton() {
    std::cout << "\n===== SINGLETON PATTERN DEMO =====\n" << std::endl;
    
    // Classic Singleton
    std::cout << "1. Classic Singleton (DatabaseConnection):" << std::endl;
    auto* db1 = DatabaseConnection::getInstance("mysql://localhost:3306");
    auto* db2 = DatabaseConnection::getInstance("postgres://localhost:5432"); // Same instance!
    
    std::cout << "db1 == db2: " << (db1 == db2 ? "true" : "false") << std::endl;
    db1->query("SELECT * FROM users");
    db2->query("INSERT INTO logs VALUES ('test')");
    
    // Modern Singleton
    std::cout << "\n2. Modern Singleton (Logger):" << std::endl;
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();
    
    std::cout << "logger1 == logger2: " << (&logger1 == &logger2 ? "true" : "false") << std::endl;
    logger1.info("Application started");
    logger2.error("Something went wrong");
    
    // Configuration Singleton
    std::cout << "\n3. Configuration Singleton:" << std::endl;
    ConfigManager& config1 = ConfigManager::getInstance();
    config1.displayConfig();
    config1.setEnvironment(ConfigManager::Environment::PRODUCTION);
    
    ConfigManager& config2 = ConfigManager::getInstance();
    config2.displayConfig(); // Same instance, same state
    
    std::cout << "config1 == config2: " << (&config1 == &config2 ? "true" : "false") << std::endl;
}

#endif // SINGLETON_HPP
