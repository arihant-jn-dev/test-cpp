#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>
#include <string>

/**
 * SINGLETON DESIGN PATTERN
 * - Ensures only ONE instance of a class exists
 * - Provides global access to that instance
 * - Common in interviews for database connections, loggers, configuration
 *
 * Recipe: private constructor + deleted copy + static getInstance() that
 * returns a static local object. This is the version to write in interviews.
 * (A pointer + mutex version is in 04_advanced_cpp/advanced_patterns.hpp.)
 */

// ======================= SINGLETON (RECOMMENDED) =======================
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

// ======================= CONFIG SINGLETON (SAME RECIPE, WITH STATE) =======================
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
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

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
    
    // Singleton
    std::cout << "1. Singleton (Logger):" << std::endl;
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();
    
    std::cout << "logger1 == logger2: " << (&logger1 == &logger2 ? "true" : "false") << std::endl;
    logger1.info("Application started");
    logger2.error("Something went wrong");
    
    // Configuration Singleton
    std::cout << "\n2. Configuration Singleton:" << std::endl;
    ConfigManager& config1 = ConfigManager::getInstance();
    config1.displayConfig();
    config1.setEnvironment(ConfigManager::Environment::PRODUCTION);
    
    ConfigManager& config2 = ConfigManager::getInstance();
    config2.displayConfig(); // Same instance, same state
    
    std::cout << "config1 == config2: " << (&config1 == &config2 ? "true" : "false") << std::endl;
}

#endif // SINGLETON_HPP
