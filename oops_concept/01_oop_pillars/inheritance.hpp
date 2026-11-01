#ifndef INHERITANCE_HPP
#define INHERITANCE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * ===============================================
 * INHERITANCE - CODE REUSABILITY AND HIERARCHY
 * ===============================================
 * 
 * Inheritance allows a class to inherit properties and methods from another class.
 * It promotes code reusability and establishes IS-A relationships.
 * 
 * INTERVIEW QUESTIONS COVERED:
 * 1. What is inheritance and its types?
 * 2. What is method overriding vs overloading?
 * 3. What is the order of constructor/destructor calls?
 * 4. What is the difference between IS-A (inheritance) and HAS-A (composition)?
 */

namespace BasicConcepts {

/**
 * Base Class - Vehicle
 * Demonstrates: Basic inheritance concepts, protected members, virtual functions
 */
class Vehicle {
protected:
    std::string brand;
    std::string model;
    int year;
    double price;
    static int totalVehicles; // Static member shared by all vehicles

public:
    // Constructor
    Vehicle(const std::string& b, const std::string& m, int y, double p)
        : brand(b), model(m), year(y), price(p) {
        totalVehicles++;
        std::cout << "Vehicle constructor called: " << brand << " " << model << std::endl;
    }
    
    // Virtual destructor (important for proper cleanup in inheritance)
    virtual ~Vehicle() {
        totalVehicles--;
        std::cout << "Vehicle destructor called: " << brand << " " << model << std::endl;
    }
    
    // Public interface
    const std::string& getBrand() const { return brand; }
    const std::string& getModel() const { return model; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    
    // Virtual function - can be overridden by derived classes
    virtual void startEngine() const {
        std::cout << "Starting " << brand << " " << model << " engine..." << std::endl;
    }
    
    virtual void stopEngine() const {
        std::cout << "Stopping " << brand << " " << model << " engine..." << std::endl;
    }
    
    // Pure virtual function - makes Vehicle an abstract class
    virtual void displaySpecifications() const = 0;
    
    // Non-virtual function - cannot be overridden (compile-time binding)
    void displayBasicInfo() const {
        std::cout << "Vehicle: " << brand << " " << model 
                  << " (" << year << ") - $" << price << std::endl;
    }
    
    // Static function
    static int getTotalVehicles() {
        return totalVehicles;
    }
};

// Static member definition
int Vehicle::totalVehicles = 0;

/**
 * Single Inheritance - Car inherits from Vehicle
 * Demonstrates: Basic inheritance, method overriding, constructor chaining
 */
class Car : public Vehicle {
private:
    int numberOfDoors;
    std::string fuelType;
    double engineCapacity;

public:
    // Constructor with base class initialization
    Car(const std::string& b, const std::string& m, int y, double p,
        int doors, const std::string& fuel, double engine)
        : Vehicle(b, m, y, p), numberOfDoors(doors), fuelType(fuel), engineCapacity(engine) {
        std::cout << "Car constructor called" << std::endl;
    }
    
    // Destructor
    ~Car() override {
        std::cout << "Car destructor called" << std::endl;
    }
    
    // Getters for car-specific attributes
    int getNumberOfDoors() const { return numberOfDoors; }
    const std::string& getFuelType() const { return fuelType; }
    double getEngineCapacity() const { return engineCapacity; }
    
    // Override virtual function from base class
    void startEngine() const override {
        std::cout << "Starting " << numberOfDoors << "-door " << brand 
                  << " " << model << " with " << engineCapacity << "L engine" << std::endl;
    }
    
    void stopEngine() const override {
        std::cout << "Stopping " << brand << " " << model << " car engine" << std::endl;
    }
    
    // Implement pure virtual function
    void displaySpecifications() const override {
        displayBasicInfo();
        std::cout << "Type: Car" << std::endl;
        std::cout << "Doors: " << numberOfDoors << std::endl;
        std::cout << "Fuel: " << fuelType << std::endl;
        std::cout << "Engine: " << engineCapacity << "L" << std::endl;
    }
    
    // Car-specific method
    void openTrunk() const {
        std::cout << "Opening trunk of " << brand << " " << model << std::endl;
    }
};

/**
 * Single Inheritance - Motorcycle inherits from Vehicle
 */
class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    std::string motorcycleType; // Sport, Cruiser, Touring, etc.

public:
    Motorcycle(const std::string& b, const std::string& m, int y, double p,
               bool sidecar, const std::string& type)
        : Vehicle(b, m, y, p), hasSidecar(sidecar), motorcycleType(type) {
        std::cout << "Motorcycle constructor called" << std::endl;
    }
    
    ~Motorcycle() override {
        std::cout << "Motorcycle destructor called" << std::endl;
    }
    
    bool getHasSidecar() const { return hasSidecar; }
    const std::string& getMotorcycleType() const { return motorcycleType; }
    
    void startEngine() const override {
        std::cout << "Starting " << motorcycleType << " motorcycle: " 
                  << brand << " " << model << std::endl;
    }
    
    void stopEngine() const override {
        std::cout << "Stopping " << brand << " " << model << " motorcycle" << std::endl;
    }
    
    void displaySpecifications() const override {
        displayBasicInfo();
        std::cout << "Type: Motorcycle (" << motorcycleType << ")" << std::endl;
        std::cout << "Sidecar: " << (hasSidecar ? "Yes" : "No") << std::endl;
    }
    
    void performWheelIE() const {
        std::cout << "Performing wheelie on " << brand << " " << model << std::endl;
    }
};

/**
 * Multilevel Inheritance - SportsCar inherits from Car
 * Demonstrates: Inheritance chain, method overriding at multiple levels
 */
class SportsCar : public Car {
private:
    int maxSpeed;
    double acceleration; // 0-60 mph time
    bool hasTurbo;

public:
    SportsCar(const std::string& b, const std::string& m, int y, double p,
              int doors, const std::string& fuel, double engine,
              int speed, double accel, bool turbo)
        : Car(b, m, y, p, doors, fuel, engine), 
          maxSpeed(speed), acceleration(accel), hasTurbo(turbo) {
        std::cout << "SportsCar constructor called" << std::endl;
    }
    
    ~SportsCar() override {
        std::cout << "SportsCar destructor called" << std::endl;
    }
    
    int getMaxSpeed() const { return maxSpeed; }
    double getAcceleration() const { return acceleration; }
    bool getHasTurbo() const { return hasTurbo; }
    
    // Override method from Car (which already overrode Vehicle)
    void startEngine() const override {
        std::cout << "Starting high-performance " << brand << " " << model 
                  << " sports car engine" << (hasTurbo ? " with turbo" : "") << std::endl;
    }
    
    void displaySpecifications() const override {
        Car::displaySpecifications(); // Call parent's implementation
        std::cout << "Category: Sports Car" << std::endl;
        std::cout << "Max Speed: " << maxSpeed << " mph" << std::endl;
        std::cout << "0-60 mph: " << acceleration << " seconds" << std::endl;
        std::cout << "Turbo: " << (hasTurbo ? "Yes" : "No") << std::endl;
    }
    
    void activateSportMode() const {
        std::cout << "Activating sport mode on " << brand << " " << model << std::endl;
    }
    
    void performLaunchControl() const {
        std::cout << "Engaging launch control - 0-60 in " << acceleration 
                  << " seconds!" << std::endl;
    }
};

/**
 * Composition (HAS-A) - combine classes without inheriting from them
 * A SmartCar IS-A Car (inheritance) and HAS-A Engine and GPS (composition).
 * Inheriting from Engine would wrongly say "a SmartCar IS-A Engine".
 * Rule of thumb for LLD: use inheritance for IS-A, composition for HAS-A.
 */

// A part that SmartCar owns (not a base class)
class Engine {
private:
    double horsepower;
    std::string engineType;

public:
    Engine(double hp, const std::string& type)
        : horsepower(hp), engineType(type) {
        std::cout << "Engine constructor called" << std::endl;
    }

    ~Engine() {
        std::cout << "Engine destructor called" << std::endl;
    }

    double getHorsepower() const { return horsepower; }
    const std::string& getEngineType() const { return engineType; }

    void start() const {
        std::cout << "Starting " << engineType << " engine ("
                  << horsepower << " HP)" << std::endl;
    }
};

// Another part that SmartCar owns
class GPS {
private:
    std::string currentLocation;
    bool isActive;

public:
    GPS() : currentLocation("Unknown"), isActive(false) {
        std::cout << "GPS constructor called" << std::endl;
    }

    ~GPS() {
        std::cout << "GPS destructor called" << std::endl;
    }
    
    void activate() {
        isActive = true;
        currentLocation = "Current Location";
        std::cout << "GPS activated" << std::endl;
    }
    
    void deactivate() {
        isActive = false;
        std::cout << "GPS deactivated" << std::endl;
    }
    
    const std::string& getLocation() const { return currentLocation; }
    bool getIsActive() const { return isActive; }
    
    void navigate(const std::string& destination) const {
        if (isActive) {
            std::cout << "Navigating to " << destination << std::endl;
        } else {
            std::cout << "GPS not active. Please activate first." << std::endl;
        }
    }
};

// SmartCar IS-A Car (inherits) and HAS-A Engine and GPS (members)
class SmartCar : public Car {
private:
    Engine engine;   // HAS-A
    GPS gps;         // HAS-A
    bool autonomousMode;
    std::string aiAssistant;

public:
    SmartCar(const std::string& b, const std::string& m, int y, double p,
             int doors, const std::string& fuel, double engineCap,
             double hp, const std::string& engineType, const std::string& ai)
        : Car(b, m, y, p, doors, fuel, engineCap),
          engine(hp, engineType),
          autonomousMode(false),
          aiAssistant(ai) {
        std::cout << "SmartCar constructor called" << std::endl;
    }

    ~SmartCar() override {
        std::cout << "SmartCar destructor called" << std::endl;
    }

    // SmartCar does the work by delegating to the parts it owns
    void startEngine() const override {
        std::cout << "SmartCar starting: ";
        engine.start();
    }

    void navigate(const std::string& destination) const {
        gps.navigate(destination);
    }

    void enableAutonomous() {
        autonomousMode = true;
        gps.activate();
        std::cout << "Autonomous mode enabled with " << aiAssistant << std::endl;
    }

    void disableAutonomous() {
        autonomousMode = false;
        gps.deactivate();
        std::cout << "Autonomous mode disabled" << std::endl;
    }

    void displaySpecifications() const override {
        Car::displaySpecifications();
        std::cout << "Engine: " << engine.getEngineType() << " (" << engine.getHorsepower() << " HP)" << std::endl;
        std::cout << "GPS: " << (gps.getIsActive() ? "Active" : "Inactive") << std::endl;
        std::cout << "AI Assistant: " << aiAssistant << std::endl;
        std::cout << "Autonomous: " << (autonomousMode ? "Enabled" : "Disabled") << std::endl;
    }
};

} // namespace BasicConcepts

/**
 * ===============================================
 * INTERVIEW QUESTIONS AND ANSWERS
 * ===============================================
 * 
 * Q1: What are the types of inheritance in C++?
 * A1: 1. Single inheritance - one base, one derived
 *     2. Multiple inheritance - multiple bases, one derived  
 *     3. Multilevel inheritance - inheritance chain
 *     4. Hierarchical inheritance - one base, multiple derived
 *     5. Hybrid inheritance - combination of above types
 * 
 * Q2: What is method overriding vs overloading?
 * A2: - Overriding: Redefining virtual function in derived class (runtime polymorphism)
 *     - Overloading: Multiple functions with same name, different parameters (compile-time)
 *
 * Q3: What is the order of constructor/destructor calls in inheritance?
 * A3: Constructors: Base class first, then derived class
 *     Destructors: Derived class first, then base class (reverse order)
 *
 * Q4: Why use virtual destructors?
 * A4: Virtual destructors ensure proper cleanup when deleting objects through
 *     base class pointers, preventing resource leaks.
 *
 * Q5: What is the difference between IS-A and HAS-A relationships?
 * A5: - IS-A: Inheritance relationship (Car IS-A Vehicle)
 *     - HAS-A: Composition relationship (SmartCar HAS-A Engine)
 *     Prefer composition when the relationship is HAS-A (see SmartCar above).
 *
 * Q6: Can constructors be virtual?
 * A6: No, constructors cannot be virtual because:
 *     - Virtual function calls require vtable
 *     - vtable is set up during object construction
 *     - Object doesn't exist during constructor call
 *
 * Protected/private inheritance and the diamond problem are in
 * 04_advanced_cpp/advanced_inheritance.hpp.
 */

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateInheritance() {
    std::cout << "\n===== INHERITANCE DEMO =====\n" << std::endl;
    
    // Single Inheritance
    std::cout << "1. Single Inheritance (Vehicle -> Car):" << std::endl;
    BasicConcepts::Car car("Toyota", "Camry", 2023, 30000.0, 4, "Gasoline", 2.5);
    std::cout << "Car brand: " << car.getBrand() << ", doors: " << car.getNumberOfDoors() << std::endl;

    // Multilevel Inheritance
    std::cout << "\n2. Multilevel Inheritance (Vehicle -> Car -> SportsCar):" << std::endl;
    BasicConcepts::SportsCar sports("Ferrari", "F8", 2023, 250000.0, 2, "Gasoline", 3.9, 340, 3.0, true);
    std::cout << "Sports car: " << sports.getBrand() << ", max speed: " << sports.getMaxSpeed() << " mph" << std::endl;

    // Composition
    std::cout << "\n3. Composition (SmartCar HAS-A Engine and GPS):" << std::endl;
    BasicConcepts::SmartCar smartCar("Tesla", "Model S", 2023, 95000.0, 4, "Electric", 0.0, 670, "Electric", "Autopilot");
    smartCar.startEngine();
    smartCar.enableAutonomous();
    smartCar.navigate("123 Main St");

    // Constructor/Destructor Order
    std::cout << "\n4. Constructor/Destructor Order:" << std::endl;
    {
        std::cout << "Creating SportsCar object:" << std::endl;
        BasicConcepts::SportsCar tempSports("Lamborghini", "Huracan", 2023, 300000.0, 2, "Gasoline", 5.2, 370, 2.9, true);
        std::cout << "SportsCar object created, now going out of scope..." << std::endl;
    }
    std::cout << "SportsCar object destroyed" << std::endl;
}

#endif // INHERITANCE_HPP
