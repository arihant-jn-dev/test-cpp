#ifndef ADVANCED_INHERITANCE_HPP
#define ADVANCED_INHERITANCE_HPP

#include <iostream>
#include <string>

/**
 * ===============================================
 * ADVANCED INHERITANCE
 * ===============================================
 *
 * Moved here from 01_oop_pillars/inheritance.hpp. These are C++ quiz topics;
 * LLD designs only need public inheritance plus composition.
 *
 * INTERVIEW QUESTIONS COVERED:
 * 1. What is the difference between public, private, and protected inheritance?
 * 2. What is the diamond problem?
 * 3. What is virtual inheritance?
 */

namespace AdvancedCpp {

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

} // namespace AdvancedCpp

/**
 * ===============================================
 * INTERVIEW QUESTIONS AND ANSWERS
 * ===============================================
 *
 * Q1: What is the difference between public, protected, and private inheritance?
 * A1: - Public: IS-A relationship, base class interface preserved
 *     - Protected: Base public members become protected in derived
 *     - Private: IMPLEMENTED-IN-TERMS-OF, base members become private
 *
 * Q2: What is the diamond problem?
 * A2: When a class inherits from two classes that share a common base class,
 *     it creates ambiguity and duplicate base class instances.
 *     Solved using virtual inheritance.
 *
 * Q3: What is virtual inheritance?
 * A3: Virtual inheritance ensures only one instance of a base class exists
 *     in a multiple inheritance hierarchy, solving the diamond problem.
 *
 * Q4: What happens if we don't use virtual inheritance in diamond problem?
 * A4: - Derived class gets multiple copies of base class
 *     - Ambiguity in member access
 *     - Increased memory usage
 *     - Compilation errors for ambiguous calls
 */

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateAdvancedInheritance() {
    std::cout << "\n===== ADVANCED INHERITANCE DEMO =====\n" << std::endl;

    std::cout << "1. Virtual Inheritance (Diamond Problem):" << std::endl;
    AdvancedCpp::CarEntertainmentSystem entertainment;
    entertainment.powerOn();
    entertainment.setTemperature(22);
    entertainment.switchToRadio();
    entertainment.powerOff();

    std::cout << "\n2. Access Control in Inheritance:" << std::endl;
    AdvancedCpp::PublicDerived pubDerived;
    pubDerived.testAccess();
    pubDerived.publicMethod();

    AdvancedCpp::ProtectedDerived protDerived;
    protDerived.testAccess();

    AdvancedCpp::PrivateDerived privDerived;
    privDerived.testAccess();
}

#endif // ADVANCED_INHERITANCE_HPP
