#include "design_patterns/factory.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << "🧪 TESTING DESIGN PATTERNS - Factory Pattern\n" << std::endl;
    
    try {
        std::cout << "===== FACTORY PATTERN DEMO =====\n" << std::endl;
        
        // 1. Simple Factory Pattern
        std::cout << "1. Simple Factory Pattern - Shape Creation:" << std::endl;
        
        std::vector<std::string> shapeTypes = {"circle", "rectangle", "triangle"};
        std::vector<std::unique_ptr<DesignPatterns::Shape>> shapes;
        
        for (const auto& type : shapeTypes) {
            auto shape = DesignPatterns::ShapeFactory::createShape(type, 5.0);
            if (shape) {
                shapes.push_back(std::move(shape));
                std::cout << "Created " << type << ": ";
                shapes.back()->draw();
                std::cout << "Area: " << shapes.back()->getArea() << std::endl;
            }
        }
        
        // Test invalid shape type
        auto invalidShape = DesignPatterns::ShapeFactory::createShape("hexagon", 3.0);
        if (!invalidShape) {
            std::cout << "Factory correctly rejected invalid shape type: hexagon" << std::endl;
        }
        
        std::cout << std::endl;
        
        // 2. Factory Method Pattern
        std::cout << "2. Factory Method Pattern - Vehicle Creation:" << std::endl;
        
        // Create different vehicle factories
        DesignPatterns::CarFactory carFactory;
        DesignPatterns::MotorcycleFactory motorcycleFactory;
        DesignPatterns::TruckFactory truckFactory;
        
        std::vector<DesignPatterns::VehicleFactory*> factories = {
            &carFactory, &motorcycleFactory, &truckFactory
        };
        
        std::vector<std::unique_ptr<DesignPatterns::Vehicle>> vehicles;
        
        for (auto factory : factories) {
            auto vehicle = factory->createVehicle();
            vehicles.push_back(std::move(vehicle));
            
            std::cout << "Created vehicle: ";
            vehicles.back()->start();
            vehicles.back()->drive();
            vehicles.back()->stop();
            std::cout << std::endl;
        }
        
        std::cout << std::endl;
        
        // 3. Abstract Factory Pattern
        std::cout << "3. Abstract Factory Pattern - UI Theme Creation:" << std::endl;
        
        // Create different UI theme factories
        auto windowsFactory = std::make_unique<DesignPatterns::WindowsUIFactory>();
        auto macFactory = std::make_unique<DesignPatterns::MacUIFactory>();
        auto linuxFactory = std::make_unique<DesignPatterns::LinuxUIFactory>();
        
        std::vector<std::unique_ptr<DesignPatterns::UIFactory>> uiFactories;
        uiFactories.push_back(std::move(windowsFactory));
        uiFactories.push_back(std::move(macFactory));
        uiFactories.push_back(std::move(linuxFactory));
        
        for (auto& factory : uiFactories) {
            std::cout << "Creating UI elements for theme:" << std::endl;
            
            auto button = factory->createButton();
            auto checkbox = factory->createCheckbox();
            auto textbox = factory->createTextbox();
            
            button->render();
            checkbox->render();
            textbox->render();
            std::cout << std::endl;
        }
        
        std::cout << std::endl;
        
        // 4. Registration-based Factory
        std::cout << "4. Registration-based Factory - Document Creation:" << std::endl;
        
        DesignPatterns::DocumentFactory& docFactory = DesignPatterns::DocumentFactory::getInstance();
        
        // Register document types
        docFactory.registerDocument("pdf", []() { 
            return std::make_unique<DesignPatterns::PDFDocument>(); 
        });
        docFactory.registerDocument("word", []() { 
            return std::make_unique<DesignPatterns::WordDocument>(); 
        });
        docFactory.registerDocument("text", []() { 
            return std::make_unique<DesignPatterns::TextDocument>(); 
        });
        
        std::vector<std::string> docTypes = {"pdf", "word", "text"};
        
        for (const auto& type : docTypes) {
            auto document = docFactory.createDocument(type);
            if (document) {
                std::cout << "Created " << type << " document: ";
                document->open();
                document->save();
                document->close();
                std::cout << std::endl;
            }
        }
        
        // Test unregistered type
        auto unknownDoc = docFactory.createDocument("excel");
        if (!unknownDoc) {
            std::cout << "Factory correctly rejected unregistered document type: excel" << std::endl;
        }
        
        std::cout << std::endl;
        
        // 5. Parameterized Factory
        std::cout << "5. Parameterized Factory - Database Connection:" << std::endl;
        
        DesignPatterns::DatabaseFactory dbFactory;
        
        // Test different database configurations
        std::vector<DesignPatterns::DatabaseConfig> configs = {
            {"mysql", "localhost", 3306, "myapp", "user1", "pass1"},
            {"postgresql", "db.example.com", 5432, "testdb", "user2", "pass2"},
            {"mongodb", "mongo.cluster.com", 27017, "documents", "user3", "pass3"}
        };
        
        for (const auto& config : configs) {
            auto connection = dbFactory.createConnection(config);
            if (connection) {
                std::cout << "Created " << config.type << " connection:" << std::endl;
                if (connection->connect()) {
                    connection->execute("SELECT 1");
                    connection->disconnect();
                }
                std::cout << std::endl;
            }
        }
        
        std::cout << std::endl;
        
        // 6. Factory with Dependency Injection
        std::cout << "6. Factory with Configuration:" << std::endl;
        
        DesignPatterns::LoggerFactory loggerFactory;
        
        // Configure different loggers
        DesignPatterns::LoggerConfig consoleConfig{"console", "INFO", "logs/console.log"};
        DesignPatterns::LoggerConfig fileConfig{"file", "DEBUG", "logs/application.log"};
        DesignPatterns::LoggerConfig networkConfig{"network", "ERROR", "logs/network.log"};
        
        std::vector<DesignPatterns::LoggerConfig> logConfigs = {
            consoleConfig, fileConfig, networkConfig
        };
        
        for (const auto& config : logConfigs) {
            auto logger = loggerFactory.createLogger(config);
            if (logger) {
                std::cout << "Created " << config.type << " logger:" << std::endl;
                logger->log("INFO", "Application started");
                logger->log("DEBUG", "Debug information");
                logger->log("ERROR", "Error occurred");
                std::cout << std::endl;
            }
        }
        
        std::cout << std::endl;
        
        // 7. Complex Factory Scenario
        std::cout << "7. Complex Factory Scenario - Game Objects:" << std::endl;
        
        DesignPatterns::GameObjectFactory gameFactory;
        
        // Create different game objects with various configurations
        std::vector<std::pair<std::string, DesignPatterns::GameObjectConfig>> gameObjects = {
            {"warrior", {"warrior", 100, 25, 15, {"sword", "shield"}}},
            {"mage", {"mage", 60, 40, 8, {"staff", "spellbook"}}},
            {"archer", {"archer", 80, 30, 20, {"bow", "arrows"}}}
        };
        
        for (const auto& [type, config] : gameObjects) {
            auto gameObject = gameFactory.createGameObject(type, config);
            if (gameObject) {
                std::cout << "Created " << type << ":" << std::endl;
                gameObject->displayStats();
                gameObject->attack();
                gameObject->defend();
                std::cout << std::endl;
            }
        }
        
        std::cout << std::endl;
        
        // 8. Factory Performance Test
        std::cout << "8. Factory Performance and Memory Management:" << std::endl;
        
        const int numObjects = 1000;
        auto start = std::chrono::high_resolution_clock::now();
        
        std::vector<std::unique_ptr<DesignPatterns::Shape>> testShapes;
        testShapes.reserve(numObjects);
        
        for (int i = 0; i < numObjects; ++i) {
            std::string type = (i % 3 == 0) ? "circle" : (i % 3 == 1) ? "rectangle" : "triangle";
            auto shape = DesignPatterns::ShapeFactory::createShape(type, static_cast<double>(i % 10 + 1));
            if (shape) {
                testShapes.push_back(std::move(shape));
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Created " << testShapes.size() << " objects in " 
                  << duration.count() << " microseconds" << std::endl;
        std::cout << "Average time per object: " << (duration.count() / static_cast<double>(testShapes.size())) 
                  << " microseconds" << std::endl;
        
        // Calculate total area
        double totalArea = 0.0;
        for (const auto& shape : testShapes) {
            totalArea += shape->getArea();
        }
        std::cout << "Total area of all shapes: " << totalArea << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "✅ Factory pattern test completed successfully!" << std::endl;
        std::cout << "\n📚 Factory Pattern Types Demonstrated:" << std::endl;
        std::cout << "✅ Simple Factory - Basic object creation" << std::endl;
        std::cout << "✅ Factory Method - Polymorphic object creation" << std::endl;
        std::cout << "✅ Abstract Factory - Family of related objects" << std::endl;
        std::cout << "✅ Registration-based Factory - Runtime registration" << std::endl;
        std::cout << "✅ Parameterized Factory - Configuration-based creation" << std::endl;
        std::cout << "✅ Complex Factory - Real-world scenarios" << std::endl;
        std::cout << "✅ Performance and Memory Management" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Exception occurred: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
