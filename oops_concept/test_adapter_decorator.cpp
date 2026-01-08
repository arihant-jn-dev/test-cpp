#include "design_patterns/adapter_decorator.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << "🧪 TESTING DESIGN PATTERNS - Adapter & Decorator Patterns\n" << std::endl;
    
    try {
        std::cout << "===== ADAPTER & DECORATOR PATTERNS DEMO =====\n" << std::endl;
        
        // 1. Adapter Pattern - Legacy System Integration
        std::cout << "1. Adapter Pattern - Legacy System Integration:" << std::endl;
        
        // Legacy audio system that doesn't fit our interface
        DesignPatterns::LegacyAudioSystem legacySystem("Vintage Audio Pro", "44.1kHz");
        
        // Adapt it to our modern interface
        DesignPatterns::AudioAdapter adapter(&legacySystem);
        
        std::cout << "Using legacy system through adapter:" << std::endl;
        adapter.play("music.mp3");
        adapter.pause();
        adapter.stop();
        adapter.setVolume(75);
        
        std::cout << std::endl;
        
        // 2. Object Adapter vs Class Adapter
        std::cout << "2. Object Adapter Pattern:" << std::endl;
        
        DesignPatterns::EuropeanSocket europeanSocket;
        DesignPatterns::SocketAdapter socketAdapter(&europeanSocket);
        
        std::cout << "Using European socket with US plug through adapter:" << std::endl;
        socketAdapter.plugIn();
        socketAdapter.providePower();
        socketAdapter.unplug();
        
        std::cout << std::endl;
        
        // 3. Adapter for Data Format Conversion
        std::cout << "3. Adapter for Data Format Conversion:" << std::endl;
        
        DesignPatterns::XMLDataSource xmlSource;
        DesignPatterns::XMLToJSONAdapter dataAdapter(&xmlSource);
        
        std::cout << "Converting XML data to JSON format:" << std::endl;
        std::string jsonData = dataAdapter.getJSONData();
        std::cout << "Converted data: " << jsonData << std::endl;
        
        std::cout << std::endl;
        
        // 4. Basic Decorator Pattern
        std::cout << "4. Basic Decorator Pattern - Text Processing:" << std::endl;
        
        auto plainText = std::make_unique<DesignPatterns::PlainText>("Hello World");
        std::cout << "Plain text: " << plainText->getText() << std::endl;
        
        // Decorate with bold
        auto boldText = std::make_unique<DesignPatterns::BoldDecorator>(std::move(plainText));
        std::cout << "Bold text: " << boldText->getText() << std::endl;
        
        // Decorate with italic (chaining decorators)
        auto italicBoldText = std::make_unique<DesignPatterns::ItalicDecorator>(std::move(boldText));
        std::cout << "Italic + Bold text: " << italicBoldText->getText() << std::endl;
        
        // Decorate with underline
        auto fullFormattedText = std::make_unique<DesignPatterns::UnderlineDecorator>(std::move(italicBoldText));
        std::cout << "Full formatted text: " << fullFormattedText->getText() << std::endl;
        
        std::cout << std::endl;
        
        // 5. Coffee Shop Decorator Example
        std::cout << "5. Coffee Shop Decorator Pattern:" << std::endl;
        
        // Start with basic coffee
        auto coffee = std::make_unique<DesignPatterns::BasicCoffee>();
        std::cout << "Basic coffee: " << coffee->getDescription() 
                  << " - Cost: $" << coffee->getCost() << std::endl;
        
        // Add milk
        coffee = std::make_unique<DesignPatterns::MilkDecorator>(std::move(coffee));
        std::cout << "With milk: " << coffee->getDescription() 
                  << " - Cost: $" << coffee->getCost() << std::endl;
        
        // Add sugar
        coffee = std::make_unique<DesignPatterns::SugarDecorator>(std::move(coffee));
        std::cout << "With sugar: " << coffee->getDescription() 
                  << " - Cost: $" << coffee->getCost() << std::endl;
        
        // Add whipped cream
        coffee = std::make_unique<DesignPatterns::WhippedCreamDecorator>(std::move(coffee));
        std::cout << "Final coffee: " << coffee->getDescription() 
                  << " - Cost: $" << coffee->getCost() << std::endl;
        
        std::cout << std::endl;
        
        // 6. Multiple Adapter Pattern
        std::cout << "6. Multiple Adapter Pattern - Payment Processing:" << std::endl;
        
        // Different third-party payment systems
        DesignPatterns::PayPalPayment paypal("user@example.com", "password123");
        DesignPatterns::StripePayment stripe("sk_test_123456789");
        DesignPatterns::SquarePayment square("sq_app_id_123", "sq_app_secret_456");
        
        // Adapt them to our unified interface
        DesignPatterns::PayPalAdapter paypalAdapter(&paypal);
        DesignPatterns::StripeAdapter stripeAdapter(&stripe);
        DesignPatterns::SquareAdapter squareAdapter(&square);
        
        std::vector<DesignPatterns::PaymentProcessor*> processors = {
            &paypalAdapter, &stripeAdapter, &squareAdapter
        };
        
        double amount = 99.99;
        for (size_t i = 0; i < processors.size(); ++i) {
            std::cout << "Payment processor " << (i+1) << ":" << std::endl;
            if (processors[i]->processPayment(amount)) {
                std::cout << "Payment of $" << amount << " processed successfully" << std::endl;
            } else {
                std::cout << "Payment processing failed" << std::endl;
            }
            std::cout << std::endl;
        }
        
        std::cout << std::endl;
        
        // 7. Window Decorator Pattern
        std::cout << "7. Window System Decorator Pattern:" << std::endl;
        
        auto window = std::make_unique<DesignPatterns::SimpleWindow>("Main Window");
        std::cout << "Simple window: ";
        window->draw();
        
        // Add scroll bars
        window = std::make_unique<DesignPatterns::ScrollBarDecorator>(std::move(window));
        std::cout << "With scrollbars: ";
        window->draw();
        
        // Add border
        window = std::make_unique<DesignPatterns::BorderDecorator>(std::move(window));
        std::cout << "With border: ";
        window->draw();
        
        // Add title bar
        window = std::make_unique<DesignPatterns::TitleBarDecorator>(std::move(window));
        std::cout << "Full window: ";
        window->draw();
        
        std::cout << std::endl;
        
        // 8. Two-way Adapter Pattern
        std::cout << "8. Two-way Adapter Pattern:" << std::endl;
        
        DesignPatterns::MetricSystem metricSystem;
        DesignPatterns::ImperialSystem imperialSystem;
        DesignPatterns::TwoWayAdapter measurementAdapter(&metricSystem, &imperialSystem);
        
        std::cout << "Converting measurements:" << std::endl;
        measurementAdapter.setMetricDistance(100.0); // 100 meters
        std::cout << "100 meters = " << measurementAdapter.getImperialDistance() << " feet" << std::endl;
        
        measurementAdapter.setImperialDistance(328.0); // 328 feet
        std::cout << "328 feet = " << measurementAdapter.getMetricDistance() << " meters" << std::endl;
        
        std::cout << std::endl;
        
        // 9. Complex Decorator Chain
        std::cout << "9. Complex Decorator Chain - Pizza Ordering:" << std::endl;
        
        auto pizza = std::make_unique<DesignPatterns::BasicPizza>();
        std::cout << "Basic pizza: " << pizza->getDescription() 
                  << " - Price: $" << pizza->getPrice() << std::endl;
        
        // Build a supreme pizza
        pizza = std::make_unique<DesignPatterns::CheeseDecorator>(std::move(pizza));
        pizza = std::make_unique<DesignPatterns::PepperoniDecorator>(std::move(pizza));
        pizza = std::make_unique<DesignPatterns::MushroomDecorator>(std::move(pizza));
        pizza = std::make_unique<DesignPatterns::PepperDecorator>(std::move(pizza));
        
        std::cout << "Supreme pizza: " << pizza->getDescription() 
                  << " - Price: $" << pizza->getPrice() << std::endl;
        
        std::cout << std::endl;
        
        // 10. Adapter and Decorator Together
        std::cout << "10. Combining Adapter and Decorator Patterns:" << std::endl;
        
        // Legacy printer
        DesignPatterns::LegacyPrinter legacyPrinter("HP LaserJet 1000");
        
        // Adapt it to modern interface
        auto modernPrinter = std::make_unique<DesignPatterns::PrinterAdapter>(&legacyPrinter);
        
        // Decorate with additional features
        modernPrinter = std::make_unique<DesignPatterns::ColorPrintDecorator>(std::move(modernPrinter));
        modernPrinter = std::make_unique<DesignPatterns::DuplexPrintDecorator>(std::move(modernPrinter));
        modernPrinter = std::make_unique<DesignPatterns::WatermarkDecorator>(std::move(modernPrinter));
        
        std::cout << "Enhanced legacy printer:" << std::endl;
        modernPrinter->print("Test document");
        
        std::cout << std::endl;
        
        std::cout << "✅ Adapter and Decorator patterns test completed successfully!" << std::endl;
        std::cout << "\n📚 Patterns Demonstrated:" << std::endl;
        std::cout << "✅ Object Adapter - Legacy system integration" << std::endl;
        std::cout << "✅ Class Adapter - Interface compatibility" << std::endl;
        std::cout << "✅ Two-way Adapter - Bidirectional conversion" << std::endl;
        std::cout << "✅ Basic Decorator - Feature enhancement" << std::endl;
        std::cout << "✅ Decorator Chaining - Multiple feature layers" << std::endl;
        std::cout << "✅ Combined Patterns - Adapter + Decorator" << std::endl;
        std::cout << "✅ Real-world Examples - Payment, UI, Text processing" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Exception occurred: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
