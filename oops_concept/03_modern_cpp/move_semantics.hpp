#ifndef MOVE_SEMANTICS_HPP
#define MOVE_SEMANTICS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>

/**
 * MOVE SEMANTICS IN C++11/14/17
 * - Efficient transfer of resources
 * - Rvalue references
 * - Perfect forwarding
 * - Rule of Three/Five/Zero
 * - Very important for modern C++ interviews
 */

// ======================= RESOURCE CLASS WITH MOVE SEMANTICS =======================
class MyString {
private:
    char* data;
    size_t size;
    
public:
    // Default constructor
    MyString() : data(nullptr), size(0) {
        std::cout << "🔧 MyString default constructor" << std::endl;
    }
    
    // Constructor with C-string
    MyString(const char* str) {
        if (str) {
            size = strlen(str);
            data = new char[size + 1];
            strcpy(data, str);
            std::cout << "🔧 MyString constructor: \"" << data << "\"" << std::endl;
        } else {
            data = nullptr;
            size = 0;
            std::cout << "🔧 MyString constructor: null" << std::endl;
        }
    }
    
    // Copy constructor (Rule of Three/Five)
    MyString(const MyString& other) {
        size = other.size;
        if (other.data) {
            data = new char[size + 1];
            strcpy(data, other.data);
            std::cout << "📋 MyString copy constructor: \"" << data << "\"" << std::endl;
        } else {
            data = nullptr;
            std::cout << "📋 MyString copy constructor: null" << std::endl;
        }
    }
    
    // Move constructor (C++11)
    MyString(MyString&& other) noexcept {
        data = other.data;
        size = other.size;
        
        // Reset the moved-from object
        other.data = nullptr;
        other.size = 0;
        
        std::cout << "🚀 MyString move constructor: \"" << (data ? data : "null") << "\"" << std::endl;
    }
    
    // Copy assignment operator
    MyString& operator=(const MyString& other) {
        std::cout << "📋 MyString copy assignment" << std::endl;
        
        if (this != &other) {
            // Clean up current resource
            delete[] data;
            
            // Copy from other
            size = other.size;
            if (other.data) {
                data = new char[size + 1];
                strcpy(data, other.data);
            } else {
                data = nullptr;
            }
        }
        return *this;
    }
    
    // Move assignment operator (C++11)
    MyString& operator=(MyString&& other) noexcept {
        std::cout << "🚀 MyString move assignment" << std::endl;
        
        if (this != &other) {
            // Clean up current resource
            delete[] data;
            
            // Move from other
            data = other.data;
            size = other.size;
            
            // Reset the moved-from object
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    // Destructor
    ~MyString() {
        if (data) {
            std::cout << "🗑️  MyString destructor: \"" << data << "\"" << std::endl;
        } else {
            std::cout << "🗑️  MyString destructor: null" << std::endl;
        }
        delete[] data;
    }
    
    // Utility methods
    const char* c_str() const { return data ? data : ""; }
    size_t length() const { return size; }
    bool empty() const { return size == 0 || data == nullptr; }
    
    void print() const {
        std::cout << "String: \"" << (data ? data : "null") << "\" (size: " << size << ")" << std::endl;
    }
};

// ======================= RVALUE REFERENCE EXAMPLES =======================
void demonstrateRvalueReferences() {
    std::cout << "\n--- RVALUE REFERENCES ---" << std::endl;
    
    std::cout << "1. Lvalue vs Rvalue references:" << std::endl;
    
    MyString str1("Hello");           // Regular constructor
    MyString str2 = str1;             // Copy constructor (lvalue)
    MyString str3 = MyString("World"); // Move constructor (rvalue)
    
    std::cout << "\n2. std::move demonstration:" << std::endl;
    MyString str4("Original");
    MyString str5 = std::move(str4);  // Explicit move
    
    std::cout << "After move:" << std::endl;
    std::cout << "str4: "; str4.print();
    std::cout << "str5: "; str5.print();
    
    std::cout << "\n3. Move assignment:" << std::endl;
    MyString str6("Destination");
    str6 = MyString("Source");        // Move assignment with temporary
    std::cout << "str6: "; str6.print();
}

// ======================= PERFECT FORWARDING =======================
template<typename T>
void processValue(T&& value) {
    std::cout << "Processing value: " << value << std::endl;
    
    // Perfect forwarding to another function
    processValueHelper(std::forward<T>(value));
}

void processValueHelper(int& value) {
    std::cout << "  -> Processing lvalue reference: " << value << std::endl;
    value += 10; // Can modify lvalue
}

void processValueHelper(const int& value) {
    std::cout << "  -> Processing const lvalue reference: " << value << std::endl;
}

void processValueHelper(int&& value) {
    std::cout << "  -> Processing rvalue reference: " << value << std::endl;
    value += 20; // Can modify rvalue
}

void demonstratePerfectForwarding() {
    std::cout << "\n--- PERFECT FORWARDING ---" << std::endl;
    
    int lvalue = 42;
    const int const_lvalue = 24;
    
    std::cout << "1. Forwarding lvalue:" << std::endl;
    processValue(lvalue);
    std::cout << "lvalue after processing: " << lvalue << std::endl;
    
    std::cout << "\n2. Forwarding const lvalue:" << std::endl;
    processValue(const_lvalue);
    
    std::cout << "\n3. Forwarding rvalue:" << std::endl;
    processValue(100);
    
    std::cout << "\n4. Forwarding moved value:" << std::endl;
    int movable = 50;
    processValue(std::move(movable));
}

// ======================= MOVE SEMANTICS IN CONTAINERS =======================
class BigObject {
private:
    std::vector<int> data;
    std::string name;
    
public:
    BigObject(const std::string& n, size_t size) : name(n), data(size) {
        std::fill(data.begin(), data.end(), 42);
        std::cout << "🔧 BigObject created: " << name << " (size: " << size << ")" << std::endl;
    }
    
    // Copy constructor
    BigObject(const BigObject& other) : name(other.name + "_copy"), data(other.data) {
        std::cout << "📋 BigObject copied: " << name << " (size: " << data.size() << ")" << std::endl;
    }
    
    // Move constructor
    BigObject(BigObject&& other) noexcept 
        : name(std::move(other.name)), data(std::move(other.data)) {
        std::cout << "🚀 BigObject moved: " << name << " (size: " << data.size() << ")" << std::endl;
        other.name = "moved_from";
    }
    
    // Copy assignment
    BigObject& operator=(const BigObject& other) {
        if (this != &other) {
            name = other.name + "_assigned";
            data = other.data;
            std::cout << "📋 BigObject copy assigned: " << name << std::endl;
        }
        return *this;
    }
    
    // Move assignment
    BigObject& operator=(BigObject&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            data = std::move(other.data);
            std::cout << "🚀 BigObject move assigned: " << name << std::endl;
            other.name = "moved_from";
        }
        return *this;
    }
    
    ~BigObject() {
        std::cout << "🗑️  BigObject destroyed: " << name << std::endl;
    }
    
    const std::string& getName() const { return name; }
    size_t size() const { return data.size(); }
};

void demonstrateContainerMoveSemantics() {
    std::cout << "\n--- MOVE SEMANTICS IN CONTAINERS ---" << std::endl;
    
    std::cout << "1. Vector with move semantics:" << std::endl;
    std::vector<BigObject> objects;
    
    // Adding objects to vector
    objects.emplace_back("Object1", 1000);           // Direct construction
    objects.push_back(BigObject("Object2", 2000));   // Move constructor
    
    BigObject obj3("Object3", 3000);
    objects.push_back(std::move(obj3));              // Explicit move
    
    std::cout << "\nObjects in vector:" << std::endl;
    for (const auto& obj : objects) {
        std::cout << "  " << obj.getName() << " (size: " << obj.size() << ")" << std::endl;
    }
    
    std::cout << "\n2. Vector reallocation with move:" << std::endl;
    // This will trigger reallocation and use move constructors
    objects.reserve(10);
    objects.emplace_back("Object4", 4000);
}

// ======================= RETURN VALUE OPTIMIZATION =======================
MyString createString(const std::string& content) {
    std::cout << "Creating string in function" << std::endl;
    return MyString(content.c_str()); // RVO/NRVO may optimize this
}

BigObject createBigObject(const std::string& name, size_t size) {
    std::cout << "Creating big object in function" << std::endl;
    BigObject obj(name, size);
    // Some processing...
    return obj; // NRVO (Named Return Value Optimization)
}

void demonstrateRVO() {
    std::cout << "\n--- RETURN VALUE OPTIMIZATION ---" << std::endl;
    
    std::cout << "1. RVO example:" << std::endl;
    MyString str = createString("RVO_Test");
    str.print();
    
    std::cout << "\n2. NRVO example:" << std::endl;
    BigObject obj = createBigObject("NRVO_Test", 500);
    std::cout << "Returned object: " << obj.getName() << std::endl;
}

// ======================= MOVE-ONLY TYPES =======================
class MoveOnlyResource {
private:
    std::unique_ptr<int[]> data;
    size_t size;
    std::string name;
    
public:
    // Constructor
    MoveOnlyResource(const std::string& n, size_t s) 
        : data(std::make_unique<int[]>(s)), size(s), name(n) {
        std::cout << "🔧 MoveOnlyResource created: " << name << std::endl;
    }
    
    // Delete copy constructor and copy assignment
    MoveOnlyResource(const MoveOnlyResource&) = delete;
    MoveOnlyResource& operator=(const MoveOnlyResource&) = delete;
    
    // Move constructor
    MoveOnlyResource(MoveOnlyResource&& other) noexcept
        : data(std::move(other.data)), size(other.size), name(std::move(other.name)) {
        other.size = 0;
        std::cout << "🚀 MoveOnlyResource moved: " << name << std::endl;
    }
    
    // Move assignment
    MoveOnlyResource& operator=(MoveOnlyResource&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            size = other.size;
            name = std::move(other.name);
            other.size = 0;
            std::cout << "🚀 MoveOnlyResource move assigned: " << name << std::endl;
        }
        return *this;
    }
    
    ~MoveOnlyResource() {
        std::cout << "🗑️  MoveOnlyResource destroyed: " << name << std::endl;
    }
    
    const std::string& getName() const { return name; }
    size_t getSize() const { return size; }
    bool isValid() const { return data != nullptr; }
};

void demonstrateMoveOnlyTypes() {
    std::cout << "\n--- MOVE-ONLY TYPES ---" << std::endl;
    
    std::cout << "1. Creating move-only resource:" << std::endl;
    MoveOnlyResource resource1("Resource1", 100);
    
    std::cout << "\n2. Moving resource:" << std::endl;
    MoveOnlyResource resource2 = std::move(resource1);
    
    std::cout << "After move:" << std::endl;
    std::cout << "resource1 valid: " << resource1.isValid() << std::endl;
    std::cout << "resource2 valid: " << resource2.isValid() << ", name: " << resource2.getName() << std::endl;
    
    std::cout << "\n3. Vector of move-only types:" << std::endl;
    std::vector<MoveOnlyResource> resources;
    resources.emplace_back("VectorResource1", 50);
    resources.emplace_back("VectorResource2", 75);
    resources.push_back(std::move(resource2));
    
    std::cout << "Resources in vector:" << std::endl;
    for (const auto& res : resources) {
        std::cout << "  " << res.getName() << " (valid: " << res.isValid() << ")" << std::endl;
    }
}

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateMoveSemantics() {
    std::cout << "\n===== MOVE SEMANTICS DEMO =====\n" << std::endl;
    
    demonstrateRvalueReferences();
    demonstratePerfectForwarding();
    demonstrateContainerMoveSemantics();
    demonstrateRVO();
    demonstrateMoveOnlyTypes();
    
    std::cout << "\n===== MOVE SEMANTICS BEST PRACTICES =====\n" << std::endl;
    std::cout << "✅ Implement move constructor and move assignment for resource-owning classes" << std::endl;
    std::cout << "✅ Mark move operations as noexcept when possible" << std::endl;
    std::cout << "✅ Use std::move for explicit moves" << std::endl;
    std::cout << "✅ Use std::forward for perfect forwarding" << std::endl;
    std::cout << "✅ Consider the Rule of Five for resource management" << std::endl;
    std::cout << "✅ Use emplace_back instead of push_back for efficiency" << std::endl;
    std::cout << "❌ Don't use moved-from objects except for destruction or assignment" << std::endl;
    std::cout << "❌ Don't return std::move from functions (blocks RVO)" << std::endl;
}

#endif // MOVE_SEMANTICS_HPP
