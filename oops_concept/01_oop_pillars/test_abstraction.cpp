#include "abstraction.hpp"
#include <iostream>
#include <memory>

int main() {
    std::cout << "🧪 Testing Abstraction - Database Connection Example\n" << std::endl;
    
    try {
        // Test Database Connection Abstraction
        std::cout << "1. Testing Database Connection Abstraction:" << std::endl;
        
        // Create MySQL connection
        AdvancedConcepts::MySQLConnection mysql("localhost", "testdb", "user", "password");
        
        if (mysql.connect()) {
            std::cout << "MySQL Connection Info:" << std::endl;
            std::cout << "  Type: " << mysql.getDatabaseType() << std::endl;
            std::cout << "  Connection String: " << mysql.getConnectionString() << std::endl;
            std::cout << "  Is Connected: " << (mysql.isConnectionActive() ? "Yes" : "No") << std::endl;
            
            // Execute a query
            if (mysql.executeQuery("SELECT * FROM users")) {
                auto results = mysql.getResults();
                std::cout << "  Query Results: " << results.size() << " rows" << std::endl;
                for (const auto& result : results) {
                    std::cout << "    " << result << std::endl;
                }
            }
            
            // Test transactional query
            mysql.executeTransactionalQuery("INSERT INTO logs VALUES ('test entry')");
            
            mysql.disconnect();
        }
        
        std::cout << std::endl;
        
        // Create PostgreSQL connection
        AdvancedConcepts::PostgreSQLConnection postgres("localhost", "testdb", "user", "password");
        
        if (postgres.connect()) {
            std::cout << "PostgreSQL Connection Info:" << std::endl;
            std::cout << "  Type: " << postgres.getDatabaseType() << std::endl;
            std::cout << "  Connection String: " << postgres.getConnectionString() << std::endl;
            std::cout << "  Is Connected: " << (postgres.isConnectionActive() ? "Yes" : "No") << std::endl;
            
            // Execute a query
            if (postgres.executeQuery("SELECT COUNT(*) FROM orders")) {
                auto results = postgres.getResults();
                std::cout << "  Query Results: " << results.size() << " rows" << std::endl;
            }
            
            postgres.disconnect();
        }
        
        std::cout << std::endl;
        
        // Test Document abstraction
        std::cout << "2. Testing Document Abstraction:" << std::endl;
        
        AdvancedConcepts::Document doc("My Document", "This is document content", "Author Name", 5);
        
        doc.print();
        std::string serialized = doc.serialize();
        std::cout << "Serialized: " << serialized << std::endl;
        
        // Test comparison
        AdvancedConcepts::Document doc2("Another Document", "Different content", "Another Author", 3);
        std::cout << "Document comparison: " << doc.compareTo(doc2) << std::endl;
        
        std::cout << std::endl;
        
        // Test UI Factory pattern
        std::cout << "3. Testing UI Factory Abstraction:" << std::endl;
        
        AdvancedConcepts::WindowsUIFactory windowsFactory;
        AdvancedConcepts::MacUIFactory macFactory;
        
        std::cout << "Windows UI:" << std::endl;
        auto windowsButton = windowsFactory.createButton("winBtn", "Click me");
        auto windowsTextField = windowsFactory.createTextField("winTxt", "Enter text");
        windowsButton->render();
        windowsTextField->render();
        
        std::cout << "\nMac UI:" << std::endl;
        auto macButton = macFactory.createButton("macBtn", "Click me");
        auto macTextField = macFactory.createTextField("macTxt", "Enter text");
        macButton->render();
        macTextField->render();
        
        std::cout << "\n✅ Abstraction test completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
