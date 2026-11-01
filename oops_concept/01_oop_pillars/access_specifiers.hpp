#ifndef ACCESS_SPECIFIERS_HPP
#define ACCESS_SPECIFIERS_HPP

#include <iostream>
#include <string>

/*
 * Access Specifiers in C++ (detailed explanation and examples)
 *
 * This header explains the three primary access specifiers and related
 * concepts (friend, inheritance access, struct vs class default access) and
 * provides small, compile-safe examples demonstrating their usage and
 * why they matter.
 *
 * Put simply:
 * - `public` members are accessible from anywhere where the object is visible.
 * - `protected` members are accessible within the class and its derived classes.
 * - `private` members are accessible only inside the class itself (and friends).
 *
 * Importance:
 * - Encapsulation and information hiding: limit how users of a class
 *   interact with its internals, enabling safer APIs and easier refactoring.
 * - Access control helps enforce invariants and prevent misuse.
 * - Proper access choices improve readability and maintainability.
 */

namespace BasicConcepts {

// =========================
// Basic access example
// =========================
class AccessBase {
private:
    int privateData;   // Only accessible inside AccessBase and its friends

protected:
    int protectedData; // Accessible in AccessBase and derived classes

public:
    int publicData;    // Accessible from anywhere

    AccessBase(int pvt, int prot, int pub)
        : privateData(pvt), protectedData(prot), publicData(pub) {}

    // Public accessor for private data -- preferred to exposing member directly
    int getPrivateData() const { return privateData; }

    // A method that demonstrates internal access to all members
    void printAll() const {
        std::cout << "AccessBase: private=" << privateData
                  << " protected=" << protectedData
                  << " public=" << publicData << std::endl;
    }
};

// Derived class using public inheritance
class DerivedPublic : public AccessBase {
public:
    DerivedPublic(int pvt, int prot, int pub) : AccessBase(pvt, prot, pub) {}

    void showAccess() {
        // Can access protected and public members directly
        // privateData is NOT accessible here (would not compile)
        std::cout << "DerivedPublic: protected=" << protectedData
                  << " public=" << publicData << std::endl;
    }
};

// Derived class using private inheritance
class DerivedPrivate : private AccessBase {
public:
    DerivedPrivate(int pvt, int prot, int pub) : AccessBase(pvt, prot, pub) {}

    void showAccess() {
        // Within the derived class, protected and public members of the
        // base are still accessible, but the inheritance is private which
        // affects how outside code views the relationship.
        std::cout << "DerivedPrivate (inside): protected=" << protectedData
                  << " public=" << publicData << std::endl;
    }
};

// =========================
// Friend example
// =========================
class FriendExample {
private:
    int secret;

public:
    FriendExample(int s) : secret(s) {}

    // Declare a free function as friend so it can access private members
    friend void revealSecret(const FriendExample& f);
};

inline void revealSecret(const FriendExample& f) {
    std::cout << "FriendExample secret=" << f.secret << std::endl;
}

// =========================
// Struct vs Class default access
// =========================
// In a `struct`, members are public by default; in a `class`, they are private.
struct SimpleStruct {
    int a; // public by default
};

class SimpleClass {
    int a; // private by default
public:
    SimpleClass(int v) : a(v) {}
    int getA() const { return a; }
};

// =========================
// Demonstration function
// =========================
// This prints examples and shows which accesses are allowed.  Lines that would
// fail compilation are explained in comments rather than executed.
inline void demonstrateAccessSpecifiers() {
    std::cout << "\n===== ACCESS SPECIFIERS DEMO =====\n" << std::endl;

    AccessBase base(1, 2, 3);
    base.printAll();

    DerivedPublic dp(10, 20, 30);
    dp.showAccess();

    // Outside code can access public members, but not protected/private
    std::cout << "Outside access: base.publicData=" << base.publicData << std::endl;

    // The following lines would NOT compile if uncommented (shown for learning):
    // std::cout << base.protectedData; // error: 'protectedData' is protected
    // std::cout << base.privateData;   // error: 'privateData' is private

    // Private inheritance example: DerivedPrivate is privately derived from
    // AccessBase. Even though DerivedPrivate can access protected members
    // internally, outside code cannot treat it as an AccessBase.
    DerivedPrivate dpr(100, 200, 300);
    dpr.showAccess();
    // The following would NOT compile (private inheritance hides base):
    // AccessBase* p = &dpr; // error: cannot convert 'DerivedPrivate*' to 'AccessBase*'

    // Friend example
    FriendExample fe(999);
    revealSecret(fe); // friend function can access private member

    // Struct vs class defaults
    SimpleStruct ss{5};
    std::cout << "SimpleStruct.a=" << ss.a << " (public by default)" << std::endl;

    SimpleClass sc(7);
    std::cout << "SimpleClass.getA()=" << sc.getA() << " (a is private by default)" << std::endl;

    std::cout << "\nNotes:\n"
              << " - Use private to hide implementation details and enforce invariants.\n"
              << " - Use protected when derived classes need access but others should not.\n"
              << " - Use public to expose the class's API.\n"
              << " - Prefer getter/setter methods over exposing data directly.\n";
}

} // namespace BasicConcepts

#endif // ACCESS_SPECIFIERS_HPP
