#include "basic/class_object.hpp"
#include <iostream>

int main() {
    std::cout << "🧪 TESTING BASIC OOP CONCEPTS - Classes and Objects\n" << std::endl;
    
    try {
        std::cout << "===== CLASS AND OBJECT DEMO =====\n" << std::endl;
        
        // Test Person class - Basic class structure
        std::cout << "1. Basic Class Structure (Person):" << std::endl;
        BasicConcepts::Person person1("John Doe", 30, "john.doe@email.com");
        person1.display();
        std::cout << "Name: " << person1.getName() << std::endl;
        std::cout << "Age: " << person1.getAge() << std::endl;
        std::cout << "Email: " << person1.getEmail() << std::endl;
        
        std::cout << "\n2. Copy Constructor:" << std::endl;
        BasicConcepts::Person person2(person1);  // Copy constructor
        person2.display();
        
        std::cout << "\n3. Move Constructor:" << std::endl;
        BasicConcepts::Person person3(std::move(BasicConcepts::Person("Jane Smith", 25, "jane@email.com")));
        person3.display();
        
        std::cout << "\n4. Assignment Operators:" << std::endl;
        BasicConcepts::Person person4;  // Default constructor
        person4 = person1;  // Copy assignment
        person4.display();
        
        std::cout << "\n5. Object Creation and Destruction:" << std::endl;
        {
            BasicConcepts::Person tempPerson("Temporary", 20, "temp@email.com");
            tempPerson.display();
        } // Destructor called here
        std::cout << "Temporary object destroyed" << std::endl;
        
        std::cout << "\n6. Setters and Getters:" << std::endl;
        BasicConcepts::Person person5;
        person5.setName("Alice Johnson");
        person5.setAge(28);
        person5.setEmail("alice@email.com");
        person5.display();
        
        std::cout << "\n7. PointClass (Basic Class Demo):" << std::endl;
        BasicConcepts::PointClass point1(10, 20);
        BasicConcepts::PointClass point2(point1);  // Copy constructor
        
        std::cout << "Point1 coordinates: (" << point1.getX() << ", " << point1.getY() << ")" << std::endl;
        std::cout << "Point2 coordinates: (" << point2.getX() << ", " << point2.getY() << ")" << std::endl;
        
        std::cout << "\n8. Counter Class (Static Members):" << std::endl;
        std::cout << "Initial object count: " << BasicConcepts::Counter::getTotalObjects() << std::endl;
        
        BasicConcepts::Counter counter1;
        BasicConcepts::Counter counter2;
        BasicConcepts::Counter counter3;
        
        std::cout << "Object 1 ID: " << counter1.getId() << std::endl;
        std::cout << "Object 2 ID: " << counter2.getId() << std::endl;
        std::cout << "Object 3 ID: " << counter3.getId() << std::endl;
        std::cout << "Total objects: " << BasicConcepts::Counter::getTotalObjects() << std::endl;
        
        std::cout << "\n9. ConstructorDemo (Multiple Constructors):" << std::endl;
        BasicConcepts::ConstructorDemo demo1;                    // Default
        BasicConcepts::ConstructorDemo demo2(42);                // Single parameter (int)
        BasicConcepts::ConstructorDemo demo3(size_t(5));         // Size parameter
        
        demo1.display();
        demo2.display();
        demo3.display();
        
        std::cout << "\n10. Copy and Move Semantics:" << std::endl;
        BasicConcepts::ConstructorDemo demo5(demo2);            // Copy constructor
        BasicConcepts::ConstructorDemo demo6(std::move(demo3)); // Move constructor
        
        demo5.display();
        demo6.display();
        demo3.display();  // Should be in moved-from state
        
        std::cout << "\n11. Static Methods:" << std::endl;
        BasicConcepts::Person::printClassInfo();
        
        std::cout << "\n12. Demonstration Function:" << std::endl;
        demonstrateClassObject();
        
        std::cout << "\n13. Object Lifetime Management:" << std::endl;
        {
            std::cout << "Creating objects in inner scope..." << std::endl;
            BasicConcepts::Counter scopeCounter1;
            BasicConcepts::Counter scopeCounter2;
            std::cout << "Objects in scope, total count: " << BasicConcepts::Counter::getTotalObjects() << std::endl;
        }
        std::cout << "Objects destroyed, total count: " << BasicConcepts::Counter::getTotalObjects() << std::endl;
        
        std::cout << "\n14. Class vs Object Concept:" << std::endl;
        std::cout << "Class Person is a blueprint/template" << std::endl;
        std::cout << "Objects person1, person2, etc. are instances of Person class" << std::endl;
        std::cout << "Each object has its own copy of member variables" << std::endl;
        std::cout << "But they share the same member functions" << std::endl;
        
        std::cout << "\n15. Constructor Chaining and Initialization:" << std::endl;
        BasicConcepts::Person chainTest("Test Person", 35, "test@email.com");
        std::cout << "Object created with parameterized constructor" << std::endl;
        chainTest.display();
        
        // Test assignment operator
        BasicConcepts::Person assignTest;
        assignTest = chainTest;
        std::cout << "After assignment:" << std::endl;
        assignTest.display();
        
        std::cout << "\n16. Static Counter Reset:" << std::endl;
        std::cout << "Before reset: " << BasicConcepts::Counter::getTotalObjects() << std::endl;
        BasicConcepts::Counter::resetCounter();
        std::cout << "After reset: " << BasicConcepts::Counter::getTotalObjects() << std::endl;
        
        std::cout << "\n✅ Classes and Objects test completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Error during class/object test: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
