#include "advanced/abstraction.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << "🧪 TESTING ADVANCED OOP CONCEPTS - Abstraction\n" << std::endl;
    
    try {
        std::cout << "===== ABSTRACTION DEMO =====\n" << std::endl;
        
        // 1. Abstract Classes and Pure Virtual Functions
        std::cout << "1. Abstract Classes and Pure Virtual Functions:" << std::endl;
        
        // Cannot instantiate abstract classes
        // AdvancedConcepts::Shape shape; // Compilation error
        // AdvancedConcepts::Animal animal; // Compilation error
        
        // Create concrete implementations
        AdvancedConcepts::Rectangle rect(5.0, 8.0);
        AdvancedConcepts::Circle circle(3.0);
        AdvancedConcepts::Triangle triangle(4.0, 6.0);
        
        std::cout << "Rectangle:" << std::endl;
        rect.draw();
        std::cout << "Area: " << rect.calculateArea() << std::endl;
        std::cout << "Perimeter: " << rect.calculatePerimeter() << std::endl;
        
        std::cout << "\nCircle:" << std::endl;
        circle.draw();
        std::cout << "Area: " << circle.calculateArea() << std::endl;
        std::cout << "Perimeter: " << circle.calculatePerimeter() << std::endl;
        
        std::cout << "\nTriangle:" << std::endl;
        triangle.draw();
        std::cout << "Area: " << triangle.calculateArea() << std::endl;
        std::cout << "Perimeter: " << triangle.calculatePerimeter() << std::endl;
        
        std::cout << std::endl;
        
        // 2. Polymorphism with Abstract Classes
        std::cout << "2. Polymorphism with Abstract Base Classes:" << std::endl;
        
        std::vector<AdvancedConcepts::Shape*> shapes = {
            new AdvancedConcepts::Rectangle(3.0, 4.0),
            new AdvancedConcepts::Circle(2.5),
            new AdvancedConcepts::Triangle(5.0, 12.0),
            new AdvancedConcepts::Rectangle(7.0, 2.0)
        };
        
        double totalArea = 0.0;
        std::cout << "Processing shapes polymorphically:" << std::endl;
        
        for (size_t i = 0; i < shapes.size(); ++i) {
            std::cout << "Shape " << (i+1) << ": ";
            shapes[i]->draw();
            double area = shapes[i]->calculateArea();
            std::cout << "  Area: " << area << std::endl;
            totalArea += area;
        }
        
        std::cout << "Total area of all shapes: " << totalArea << std::endl;
        
        // Clean up
        for (auto shape : shapes) {
            delete shape;
        }
        
        std::cout << std::endl;
        
        // 3. Abstract Animal Classes
        std::cout << "3. Abstract Animal Hierarchy:" << std::endl;
        
        AdvancedConcepts::Dog dog("Buddy", 3);
        AdvancedConcepts::Cat cat("Whiskers", 2);
        AdvancedConcepts::Bird bird("Tweety", 1);
        
        std::vector<AdvancedConcepts::Animal*> animals = { &dog, &cat, &bird };
        
        std::cout << "Animal behaviors:" << std::endl;
        for (auto animal : animals) {
            animal->displayInfo();
            animal->makeSound();
            animal->move();
            std::cout << std::endl;
        }
        
        std::cout << std::endl;
        
        // 4. Interface Implementation
        std::cout << "4. Interface-like Abstract Classes:" << std::endl;
        
        AdvancedConcepts::FileProcessor csvProcessor;
        AdvancedConcepts::DatabaseProcessor dbProcessor;
        AdvancedConcepts::APIProcessor apiProcessor;
        
        std::vector<AdvancedConcepts::DataProcessor*> processors = {
            &csvProcessor, &dbProcessor, &apiProcessor
        };
        
        std::string testData = "Sample data for processing";
        
        std::cout << "Processing data through different implementations:" << std::endl;
        for (size_t i = 0; i < processors.size(); ++i) {
            std::cout << "Processor " << (i+1) << ":" << std::endl;
            
            if (processors[i]->validate(testData)) {
                std::string processedData = processors[i]->process(testData);
                bool saved = processors[i]->save(processedData);
                std::cout << "Processing result: " << (saved ? "Success" : "Failed") << std::endl;
            } else {
                std::cout << "Data validation failed" << std::endl;
            }
            std::cout << std::endl;
        }
        
        std::cout << std::endl;
        
        // 5. Factory Method Pattern with Abstraction
        std::cout << "5. Factory Method Pattern:" << std::endl;
        
        AdvancedConcepts::ShapeFactory factory;
        
        std::vector<std::string> shapeTypes = {"rectangle", "circle", "triangle"};
        std::vector<AdvancedConcepts::Shape*> factoryShapes;
        
        std::cout << "Creating shapes using factory:" << std::endl;
        for (const auto& type : shapeTypes) {
            auto shape = factory.createShape(type);
            if (shape) {
                factoryShapes.push_back(shape);
                std::cout << "Created " << type << ": ";
                shape->draw();
            }
        }
        
        // Try invalid shape type
        auto invalidShape = factory.createShape("hexagon");
        if (!invalidShape) {
            std::cout << "Factory correctly rejected invalid shape type" << std::endl;
        }
        
        // Clean up factory shapes
        for (auto shape : factoryShapes) {
            delete shape;
        }
        
        std::cout << std::endl;
        
        // 6. Template-based Abstraction
        std::cout << "6. Template-based Abstraction:" << std::endl;
        
        AdvancedConcepts::Container<int> intContainer;
        AdvancedConcepts::Container<std::string> stringContainer;
        AdvancedConcepts::Container<double> doubleContainer;
        
        // Add elements
        intContainer.add(10);
        intContainer.add(20);
        intContainer.add(30);
        
        stringContainer.add("Hello");
        stringContainer.add("World");
        stringContainer.add("Abstraction");
        
        doubleContainer.add(3.14);
        doubleContainer.add(2.71);
        doubleContainer.add(1.41);
        
        std::cout << "Integer container (" << intContainer.size() << " elements):" << std::endl;
        intContainer.display();
        
        std::cout << "\nString container (" << stringContainer.size() << " elements):" << std::endl;
        stringContainer.display();
        
        std::cout << "\nDouble container (" << doubleContainer.size() << " elements):" << std::endl;
        doubleContainer.display();
        
        // Search operations
        std::cout << "\nSearch operations:" << std::endl;
        std::cout << "Integer 20 found: " << (intContainer.contains(20) ? "Yes" : "No") << std::endl;
        std::cout << "String 'Test' found: " << (stringContainer.contains("Test") ? "Yes" : "No") << std::endl;
        std::cout << "Double 3.14 found: " << (doubleContainer.contains(3.14) ? "Yes" : "No") << std::endl;
        
        // Remove operations
        intContainer.remove(20);
        std::cout << "\nAfter removing 20 from integer container:" << std::endl;
        intContainer.display();
        
        std::cout << std::endl;
        
        // 7. Multiple Levels of Abstraction
        std::cout << "7. Multiple Levels of Abstraction:" << std::endl;
        
        // Database abstraction layers
        AdvancedConcepts::MySQLDatabase mysql;
        AdvancedConcepts::PostgreSQLDatabase postgres;
        AdvancedConcepts::MongoDatabase mongo;
        
        std::vector<AdvancedConcepts::Database*> databases = { &mysql, &postgres, &mongo };
        
        std::cout << "Testing different database implementations:" << std::endl;
        for (auto db : databases) {
            std::cout << "\nTesting database:" << std::endl;
            
            if (db->connect()) {
                db->executeQuery("SELECT * FROM users");
                db->executeQuery("INSERT INTO logs VALUES ('test')");
                db->disconnect();
            }
        }
        
        std::cout << std::endl;
        
        // 8. Abstract Class with Non-Virtual Methods
        std::cout << "8. Mixed Abstract and Concrete Methods:" << std::endl;
        
        AdvancedConcepts::Document doc1;
        AdvancedConcepts::PDFDocument pdfDoc;
        AdvancedConcepts::WordDocument wordDoc;
        
        std::vector<AdvancedConcepts::Document*> documents = { &doc1, &pdfDoc, &wordDoc };
        
        std::cout << "Document processing:" << std::endl;
        for (auto doc : documents) {
            std::cout << "\nProcessing document:" << std::endl;
            doc->open();     // Concrete implementation
            doc->process();  // Pure virtual - different for each type
            doc->save();     // Concrete implementation
            doc->close();    // Concrete implementation
        }
        
        std::cout << std::endl;
        
        std::cout << "✅ Abstraction test completed successfully!" << std::endl;
        std::cout << "\n📚 Key Abstraction Concepts Demonstrated:" << std::endl;
        std::cout << "✅ Pure virtual functions and abstract classes" << std::endl;
        std::cout << "✅ Interface-like design with abstract base classes" << std::endl;
        std::cout << "✅ Polymorphism through abstraction" << std::endl;
        std::cout << "✅ Factory method pattern" << std::endl;
        std::cout << "✅ Template-based generic abstraction" << std::endl;
        std::cout << "✅ Multiple levels of abstraction" << std::endl;
        std::cout << "✅ Mixed abstract and concrete methods" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Exception occurred: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
