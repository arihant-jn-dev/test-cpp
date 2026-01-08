#include "basic/inheritance.hpp"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::cout << "🧪 TESTING BASIC OOP CONCEPTS - Inheritance\n" << std::endl;
    
    try {
        // Test inheritance hierarchy
        std::cout << "===== INHERITANCE DEMO =====\n" << std::endl;
        
        // Test Car class (inherits from Vehicle)
        std::cout << "1. Car (Vehicle inheritance):" << std::endl;
        BasicConcepts::Car car("Toyota", "Camry", 2023, 28000.0, 4, "Gasoline", 2.5);
        car.displayBasicInfo();
        car.displaySpecifications();
        car.startEngine();
        car.openTrunk();
        car.stopEngine();
        
        std::cout << "\n2. Motorcycle (Vehicle inheritance):" << std::endl;
        
        // Test Motorcycle class (need all 6 parameters: brand, model, year, price, sidecar, type)
        BasicConcepts::Motorcycle motorcycle("Harley-Davidson", "Street 750", 2022, 7500.0, false, "Cruiser");
        motorcycle.displayBasicInfo();
        motorcycle.displaySpecifications();
        motorcycle.startEngine();
        motorcycle.stopEngine();
        
        std::cout << "\n3. Sports Car (Car inheritance):" << std::endl;
        
        // Test SportsCar class (need all 10 parameters)
        BasicConcepts::SportsCar sportsCar("Ferrari", "F8 Tributo", 2023, 280000.0, 2, "Premium", 3.9, 340, 2.9, true);
        sportsCar.displayBasicInfo();
        sportsCar.displaySpecifications();
        sportsCar.startEngine();
        sportsCar.activateSportMode();
        sportsCar.stopEngine();
        
        std::cout << "\n4. Multiple Inheritance - SmartCar:" << std::endl;
        
        // Test SmartCar (need exactly 10 parameters)
        BasicConcepts::SmartCar smartCar("Tesla", "Model S", 2023, 95000.0, 4, "Electric", 0.0, 500, "V8", "Autopilot");
        smartCar.displayBasicInfo();
        smartCar.displaySpecifications();
        smartCar.startEngine();
        smartCar.navigate("123 Main St");
        smartCar.stopEngine();
        
        std::cout << "\n5. Virtual Inheritance - Diamond Problem Solution:" << std::endl;
        
        // Test CarEntertainmentSystem (no-parameter constructor)
        BasicConcepts::CarEntertainmentSystem entertainment;
        entertainment.powerOn();
        entertainment.setTemperature(22);
        entertainment.powerOff();
        
        std::cout << "\n6. Access Control in Inheritance:" << std::endl;
        
        // Test different inheritance access levels
        std::cout << "--- Public Inheritance ---" << std::endl;
        BasicConcepts::PublicDerived pubDerived;
        pubDerived.publicMethod();
        
        std::cout << "\n--- Protected Inheritance ---" << std::endl;
        BasicConcepts::ProtectedDerived protDerived;
        
        std::cout << "\n--- Private Inheritance ---" << std::endl;
        BasicConcepts::PrivateDerived privDerived;
        
        std::cout << "\n7. Polymorphism with Inheritance:" << std::endl;
        
        // Test polymorphism using base class pointers
        std::vector<std::unique_ptr<BasicConcepts::Vehicle>> vehicles;
        vehicles.push_back(std::make_unique<BasicConcepts::Car>("BMW", "X5", 2023, 65000.0, 4, "Gasoline", 3.0));
        vehicles.push_back(std::make_unique<BasicConcepts::Motorcycle>("Yamaha", "YZF-R1", 2023, 17000.0, false, "Sport"));
        vehicles.push_back(std::make_unique<BasicConcepts::SportsCar>("Porsche", "911", 2023, 120000.0, 2, "Premium", 3.0, 320, 3.4, true));
        
        for (size_t i = 0; i < vehicles.size(); ++i) {
            std::cout << "\n--- Vehicle " << (i+1) << " polymorphism test ---" << std::endl;
            vehicles[i]->displayBasicInfo();
            vehicles[i]->startEngine();  // Virtual function call
            vehicles[i]->displaySpecifications();  // Pure virtual function call
            vehicles[i]->stopEngine();
        }
        
        std::cout << "\n8. Static Member Test:" << std::endl;
        
        // Test static member
        std::cout << "Total vehicles created: " << BasicConcepts::Vehicle::getTotalVehicles() << std::endl;
        
        std::cout << "\n9. Constructor/Destructor Chain Test:" << std::endl;
        
        // Test constructor/destructor order
        std::cout << "Creating SportsCar to show constructor chain..." << std::endl;
        {
            BasicConcepts::SportsCar tempCar("Lamborghini", "Huracan", 2023, 200000.0, 2, "Premium", 5.2, 630, 2.5, true);
            std::cout << "SportsCar created successfully" << std::endl;
        } // Destructor called here
        std::cout << "SportsCar destroyed (check destructor order)" << std::endl;
        
        std::cout << "\n10. Method Overriding Test:" << std::endl;
        
        // Test method overriding
        BasicConcepts::Car baseCar("Honda", "Civic", 2023, 25000.0, 4, "Gasoline", 2.0);
        BasicConcepts::SportsCar derivedSportsCar("McLaren", "720S", 2023, 300000.0, 2, "Premium", 4.0, 710, 2.9, true);
        
        std::cout << "Base Car startEngine: ";
        baseCar.startEngine();
        
        std::cout << "Sports Car startEngine (overridden): ";
        derivedSportsCar.startEngine();
        
        std::cout << "\n--- Virtual function polymorphism ---" << std::endl;
        BasicConcepts::Vehicle* polyPtr = &derivedSportsCar;
        std::cout << "Through base pointer: ";
        polyPtr->startEngine(); // Should call derived version due to virtual
        
        std::cout << "\n✅ Inheritance test completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Error during inheritance test: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
