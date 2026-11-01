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
 * 2. What is the difference between public, private, and protected inheritance?
 * 3. What is multiple inheritance and diamond problem?
 * 4. What is virtual inheritance?
 * 5. What is method overriding vs overloading?
 * 6. What is the order of constructor/destructor calls?
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
 * Multiple Inheritance Demonstration
 * Shows how a class can inherit from multiple base classes
 */

// First base class
class Engine {
protected:
    double horsepower;
    std::string engineType;

public:
    Engine(double hp, const std::string& type) 
        : horsepower(hp), engineType(type) {
        std::cout << "Engine constructor called" << std::endl;
    }
    
    virtual ~Engine() {
        std::cout << "Engine destructor called" << std::endl;
    }
    
    double getHorsepower() const { return horsepower; }
    const std::string& getEngineType() const { return engineType; }
    
    virtual void start() {
        std::cout << "Starting " << engineType << " engine (" 
                  << horsepower << " HP)" << std::endl;
    }
};

// Second base class
class GPS {
protected:
    std::string currentLocation;
    bool isActive;

public:
    GPS() : currentLocation("Unknown"), isActive(false) {
        std::cout << "GPS constructor called" << std::endl;
    }
    
    virtual ~GPS() {
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
    
    virtual void navigate(const std::string& destination) {
        if (isActive) {
            std::cout << "Navigating to " << destination << std::endl;
        } else {
            std::cout << "GPS not active. Please activate first." << std::endl;
        }
    }
};

// Multiple Inheritance - SmartCar inherits from both Car and GPS
class SmartCar : public Car, public Engine, public GPS {
private:
    bool autonomousMode;
    std::string aiAssistant;

public:
    SmartCar(const std::string& b, const std::string& m, int y, double p,
             int doors, const std::string& fuel, double engineCap,
             double hp, const std::string& engineType, const std::string& ai)
        : Car(b, m, y, p, doors, fuel, engineCap),
          Engine(hp, engineType),
          GPS(),
          autonomousMode(false),
          aiAssistant(ai) {
        std::cout << "SmartCar constructor called" << std::endl;
    }
    
    ~SmartCar() override {
        std::cout << "SmartCar destructor called" << std::endl;
    }
    
    // Resolve ambiguity - which start() method to use?
    void startEngine() const override {
        // Call specific base class method
        std::cout << "SmartCar starting: ";
        // Engine::start(); // Remove const conflict
        Car::startEngine();
    }
    
    void enableAutonomous() {
        autonomousMode = true;
        activate(); // Activate GPS
        std::cout << "Autonomous mode enabled with " << aiAssistant << std::endl;
    }
    
    void disableAutonomous() {
        autonomousMode = false;
        std::cout << "Autonomous mode disabled" << std::endl;
    }
    
    void displaySpecifications() const override {
        Car::displaySpecifications();
        std::cout << "Engine: " << getEngineType() << " (" << getHorsepower() << " HP)" << std::endl;
        std::cout << "GPS: " << (getIsActive() ? "Active" : "Inactive") << std::endl;
        std::cout << "AI Assistant: " << aiAssistant << std::endl;
        std::cout << "Autonomous: " << (autonomousMode ? "Enabled" : "Disabled") << std::endl;
    }
};

/**
 * Diamond Problem and Virtual Inheritance
 * Demonstrates: The diamond problem and how virtual inheritance solves it
 */

// Common base class
class PoweredDevice {
protected:
    bool isPoweredOn;
    double powerConsumption;

public:
    PoweredDevice(double power = 0.0) : isPoweredOn(false), powerConsumption(power) {
        std::cout << "PoweredDevice constructor called" << std::endl;
    }
    
    virtual ~PoweredDevice() {
        std::cout << "PoweredDevice destructor called" << std::endl;
    }
    
    virtual void powerOn() {
        isPoweredOn = true;
        std::cout << "Device powered on (consuming " << powerConsumption << "W)" << std::endl;
    }
    
    virtual void powerOff() {
        isPoweredOn = false;
        std::cout << "Device powered off" << std::endl;
    }
    
    bool getPowerStatus() const { return isPoweredOn; }
    double getPowerConsumption() const { return powerConsumption; }
};

// Virtual inheritance to solve diamond problem
class Radio : virtual public PoweredDevice {
protected:
    std::string currentStation;

public:
    Radio() : PoweredDevice(15.0), currentStation("FM 101.5") {
        std::cout << "Radio constructor called" << std::endl;
    }
    
    ~Radio() override {
        std::cout << "Radio destructor called" << std::endl;
    }
    
    void tuneToStation(const std::string& station) {
        if (isPoweredOn) {
            currentStation = station;
            std::cout << "Tuned to " << station << std::endl;
        }
    }
    
    const std::string& getCurrentStation() const { return currentStation; }
};

class AirConditioner : virtual public PoweredDevice {
protected:
    int temperature;
    std::string mode;

public:
    AirConditioner() : PoweredDevice(1500.0), temperature(72), mode("Cool") {
        std::cout << "AirConditioner constructor called" << std::endl;
    }
    
    ~AirConditioner() override {
        std::cout << "AirConditioner destructor called" << std::endl;
    }
    
    void setTemperature(int temp) {
        if (isPoweredOn) {
            temperature = temp;
            std::cout << "Temperature set to " << temp << "°F" << std::endl;
        }
    }
    
    int getTemperature() const { return temperature; }
    const std::string& getMode() const { return mode; }
};

// Multiple inheritance with virtual inheritance (solves diamond problem)
class CarEntertainmentSystem : public Radio, public AirConditioner {
private:
    std::string displayMode;

public:
    CarEntertainmentSystem() : PoweredDevice(200.0), displayMode("Dashboard") {
        std::cout << "CarEntertainmentSystem constructor called" << std::endl;
    }
    
    ~CarEntertainmentSystem() override {
        std::cout << "CarEntertainmentSystem destructor called" << std::endl;
    }
    
    // Override powerOn to handle both radio and AC
    void powerOn() override {
        PoweredDevice::powerOn(); // Only one call due to virtual inheritance
        std::cout << "Entertainment system fully activated" << std::endl;
    }
    
    void switchToRadio() {
        displayMode = "Radio";
        std::cout << "Switched to radio mode: " << getCurrentStation() << std::endl;
    }
    
    void switchToClimate() {
        displayMode = "Climate";
        std::cout << "Switched to climate mode: " << getTemperature() << "°F" << std::endl;
    }
    
    const std::string& getDisplayMode() const { return displayMode; }
};

/**
 * Access Specifier Inheritance Demonstration
 * Shows how different inheritance access specifiers affect member access
 */
class BaseClass {
private:
    int privateVar = 1;
protected:
    int protectedVar = 2;
public:
    int publicVar = 3;
    
    BaseClass() {
        std::cout << "BaseClass constructor" << std::endl;
    }
    
    void publicMethod() {
        std::cout << "BaseClass public method" << std::endl;
    }
};

// Public inheritance - most common
class PublicDerived : public BaseClass {
public:
    PublicDerived() {
        std::cout << "PublicDerived constructor" << std::endl;
    }
    
    void testAccess() {
        // privateVar;    // Error: cannot access private members
        protectedVar = 20; // OK: protected members accessible
        publicVar = 30;    // OK: public members accessible
        publicMethod();    // OK: public methods accessible
    }
};

// Protected inheritance
class ProtectedDerived : protected BaseClass {
public:
    ProtectedDerived() {
        std::cout << "ProtectedDerived constructor" << std::endl;
    }
    
    void testAccess() {
        // privateVar;    // Error: cannot access private members
        protectedVar = 200; // OK: protected members accessible
        publicVar = 300;    // OK: public members become protected
        publicMethod();     // OK: public methods become protected
    }
};

// Private inheritance
class PrivateDerived : private BaseClass {
public:
    PrivateDerived() {
        std::cout << "PrivateDerived constructor" << std::endl;
    }
    
    void testAccess() {
        // privateVar;    // Error: cannot access private members
        protectedVar = 2000; // OK: protected members become private
        publicVar = 3000;    // OK: public members become private
        publicMethod();      // OK: public methods become private
    }
    
    // Expose base class functionality if needed
    void callBaseMethod() {
        publicMethod(); // Can call within class
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
 * Q2: What is the difference between public, protected, and private inheritance?
 * A2: - Public: IS-A relationship, base class interface preserved
 *     - Protected: Base public members become protected in derived
 *     - Private: IMPLEMENTED-IN-TERMS-OF, base members become private
 * 
 * Q3: What is the diamond problem?
 * A3: When a class inherits from two classes that share a common base class,
 *     it creates ambiguity and duplicate base class instances.
 *     Solved using virtual inheritance.
 * 
 * Q4: What is virtual inheritance?
 * A4: Virtual inheritance ensures only one instance of a base class exists
 *     in a multiple inheritance hierarchy, solving the diamond problem.
 * 
 * Q5: What is method overriding vs overloading?
 * A5: - Overriding: Redefining virtual function in derived class (runtime polymorphism)
 *     - Overloading: Multiple functions with same name, different parameters (compile-time)
 * 
 * Q6: What is the order of constructor/destructor calls in inheritance?
 * A6: Constructors: Base class first, then derived class
 *     Destructors: Derived class first, then base class (reverse order)
 * 
 * Q7: Why use virtual destructors?
 * A7: Virtual destructors ensure proper cleanup when deleting objects through
 *     base class pointers, preventing resource leaks.
 * 
 * Q8: What is the difference between IS-A and HAS-A relationships?
 * A8: - IS-A: Inheritance relationship (Car IS-A Vehicle)
 *     - HAS-A: Composition relationship (Car HAS-A Engine)
 * 
 * Q9: Can constructors be virtual?
 * A9: No, constructors cannot be virtual because:
 *     - Virtual function calls require vtable
 *     - vtable is set up during object construction
 *     - Object doesn't exist during constructor call
 * 
 * Q10: What happens if we don't use virtual inheritance in diamond problem?
 * A10: - Derived class gets multiple copies of base class
 *      - Ambiguity in member access
 *      - Increased memory usage
 *      - Compilation errors for ambiguous calls
 */

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateInheritance() {
    std::cout << "\n===== INHERITANCE DEMO =====\n" << std::endl;
    
    // Single Inheritance
    std::cout << "1. Single Inheritance:" << std::endl;
    // Creating different vehicles
    BasicConcepts::Car car("Toyota", "Camry", 2023, 30000.0, 4, "Gasoline", 2.5);
    std::cout << "Car brand: " << car.getBrand() << ", doors: " << car.getNumberOfDoors() << std::endl;
    
    // Multiple Inheritance
    std::cout << "\n2. Multiple Inheritance:" << std::endl;
    BasicConcepts::SportsCar sports("Ferrari", "F8", 2023, 250000.0, 2, "Gasoline", 3.9, 340, 3.0, true);
    std::cout << "Sports car: " << sports.getBrand() << ", max speed: " << sports.getMaxSpeed() << " mph" << std::endl;
    
    // Multilevel Inheritance
    std::cout << "\n3. Multilevel Inheritance:" << std::endl;
    std::cout << "Demonstrating inheritance chain: Vehicle -> Car -> SportsCar" << std::endl;
    
    // Virtual Inheritance (Diamond Problem Solution)
    std::cout << "\n4. Virtual Inheritance (Diamond Problem):" << std::endl;
    BasicConcepts::CarEntertainmentSystem entertainment;
    std::cout << "Entertainment system demonstrates virtual inheritance" << std::endl;
    
    // Constructor/Destructor Order
    std::cout << "\n5. Constructor/Destructor Order:" << std::endl;
    {
        std::cout << "Creating SportsCar object:" << std::endl;
        BasicConcepts::SportsCar tempSports("Lamborghini", "Huracan", 2023, 300000.0, 2, "Gasoline", 5.2, 370, 2.9, true);
        std::cout << "SportsCar object created, now going out of scope..." << std::endl;
    }
    std::cout << "SportsCar object destroyed" << std::endl;
    
    // Access Control in Inheritance
    std::cout << "\n6. Access Control in Inheritance:" << std::endl;
    BasicConcepts::PublicDerived pubDerived;
    pubDerived.testAccess();
    
    BasicConcepts::PrivateDerived privDerived;
    privDerived.testAccess();
    
    BasicConcepts::ProtectedDerived protDerived;
    protDerived.testAccess();
}

#endif // INHERITANCE_HPP
