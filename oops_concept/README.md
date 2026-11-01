# 🎯 C++ OOP Concepts for Interview Preparation

C++ object-oriented programming concepts, design patterns and modern C++ features, each as a header-only example with a small runnable program next to it. Everything targets C++17 with no external dependencies.

## 📁 Structure

Every concept is a `.hpp` with a `test_<concept>.cpp` beside it that runs its demo. Folders are numbered in suggested learning order.

```
oops_concept/
├── 01_oop_pillars/                 # The four pillars + building blocks
│   ├── class_object.hpp            # Classes, constructors, static members, `this`
│   ├── access_specifiers.hpp       # public / protected / private, friend, struct vs class
│   ├── encapsulation.hpp           # Data hiding, getters/setters, validation
│   ├── inheritance.hpp             # Single, multiple, multilevel, virtual (diamond)
│   ├── polymorphism.hpp            # Virtual functions, overloading, operators
│   ├── abstraction.hpp             # Abstract classes, pure virtual, interfaces
│   └── test_*.cpp                  # One runner per header above
│
├── 02_design_patterns/             # Grouped by GoF category
│   ├── creational/                 # singleton.hpp, factory.hpp
│   ├── structural/                 # adapter_decorator.hpp
│   └── behavioral/                 # observer.hpp, strategy.hpp
│
├── 03_modern_cpp/                  # smart_pointers, move_semantics, exception_handling
│
├── demos/                          # Programs that combine several pillars
│   ├── master_demo.cpp             # Most complete walkthrough
│   ├── core_concepts_demo.cpp      # Classes, static members, encapsulation, inheritance
│   └── quick_demo.cpp              # Shortest smoke test
│
├── archive/                        # Superseded versions kept for reference (not built)
│   └── encapsulation_old.hpp       # Earlier encapsulation with SecureBankAccount, Person/Address
│
└── run_all.sh                      # Build + run every test and demo
```

## 🚀 Running

```bash
# Everything (binaries and output go to build/)
./run_all.sh

# Only one area: any substring of the path works
./run_all.sh 01_oop_pillars
./run_all.sh behavioral

# A single concept, by hand, from inside its folder
cd 01_oop_pillars
g++ -std=c++17 test_inheritance.cpp -o test_inheritance && ./test_inheritance
```

## 📊 Status

| Area | Program | Status |
|------|---------|--------|
| Pillars | `test_class_object`, `test_access_specifiers`, `test_encapsulation`, `test_inheritance`, `test_polymorphism`, `test_abstraction` | ✅ Builds and runs |
| Creational | `test_singleton` | ✅ Builds and runs |
| Creational | `test_factory` | ❌ Compile error: `DesignPatterns` namespace undeclared |
| Structural | `test_adapter_decorator` | ❌ Compile error: no viable `operator=` (adapter_decorator.hpp:404) |
| Behavioral | `test_strategy` | ✅ Builds and runs |
| Behavioral | `test_observer` | ❌ Compile error: missing `#include <map>` (observer.hpp:251) |
| Modern C++ | `test_smart_pointers`, `test_exception_handling` | ✅ Builds and runs |
| Modern C++ | `test_move_semantics` | ❌ Compile error: `processValueHelper` used before declaration (move_semantics.hpp:159) |
| Demos | `master_demo`, `core_concepts_demo`, `quick_demo` | ✅ Builds and runs |

`./run_all.sh` prints the live version of this table.

## 📖 Concepts Covered

### 🔹 01 — OOP Pillars

**Classes and Objects** (`class_object.hpp`)
- Default, parameterized, and copy constructors
- Static vs non-static members
- `this` pointer usage, method chaining, constructor delegation

**Access Specifiers** (`access_specifiers.hpp`)
- `public`, `protected`, `private` and what each allows
- Inheritance access (public / protected / private inheritance)
- `friend`, and default access for `struct` vs `class`

**Encapsulation** (`encapsulation.hpp`)
- Getter and setter methods
- Data validation and security (PIN-protected bank account)
- Friend functions

**Inheritance** (`inheritance.hpp`)
- Single, multiple, and multilevel inheritance
- Virtual inheritance and the diamond problem
- Constructor/destructor call order

**Polymorphism** (`polymorphism.hpp`)
- Runtime: virtual functions, vtable
- Compile time: function overloading, templates
- Operator overloading

**Abstraction** (`abstraction.hpp`)
- Abstract classes and pure virtual functions
- Interface design, pure virtual destructors

### 🔹 02 — Design Patterns

**Creational**
- **Singleton** (`singleton.hpp`): classic thread-safe, Meyers' static-local, enum-based config manager. Use for loggers, config, DB connections.
- **Factory** (`factory.hpp`): simple factory, factory method, abstract factory, registration-based factory. Use for object creation and plugin systems.

**Structural**
- **Adapter & Decorator** (`adapter_decorator.hpp`): interface compatibility; adding behavior dynamically; text-processing pipeline. Use for legacy integration and feature layering.

**Behavioral**
- **Observer** (`observer.hpp`): classic subject/observer, lambda-based observers, type-safe event system. Use for GUI events, notifications, MVC.
- **Strategy** (`strategy.hpp`): payment, sorting and compression strategies. Use for swapping algorithms at runtime.

### 🔹 03 — Modern C++

- **Smart Pointers** (`smart_pointers.hpp`): `unique_ptr`, `shared_ptr`, `weak_ptr` (breaking cycles), RAII
- **Move Semantics** (`move_semantics.hpp`): rvalue references, move constructors, `std::forward`, Rule of Five
- **Exception Handling** (`exception_handling.hpp`): try/catch/throw, custom exceptions, basic/strong/no-throw guarantees, RAII cleanup. When run it writes `test_file.txt` and `transaction_log.txt` into the working directory.

## 📝 Learning Path

1. **Beginner:** `01_oop_pillars/` in order: class_object → access_specifiers → encapsulation → inheritance → polymorphism
2. **Intermediate:** `01_oop_pillars/abstraction.hpp`, then `02_design_patterns/creational/`, then `03_modern_cpp/smart_pointers.hpp`
3. **Advanced:** `02_design_patterns/behavioral/` and `structural/`, then `03_modern_cpp/move_semantics.hpp` and `exception_handling.hpp`

## 🎯 Interview Focus Areas

1. Virtual functions and the vtable mechanism
2. Diamond problem and virtual inheritance
3. Function overloading vs overriding
4. When to use which design pattern
5. Singleton thread safety
6. Factory pattern variations
7. Observer vs pub-sub
8. Adapter vs decorator
9. Smart pointer types and usage
10. Move semantics and perfect forwarding
11. Exception safety guarantees
12. RAII

### Practice Scenarios

- **Design a notification system** → Observer
- **Create a drawing application** → Factory + Strategy
- **Integrate legacy systems** → Adapter
- **Add features dynamically** → Decorator
- **Ensure a single instance** → Singleton
- **Manage resources safely** → Smart pointers + RAII
- **Optimize performance** → Move semantics
- **Handle errors gracefully** → Exception handling

## 🔧 Compiler Flags

```bash
g++ -std=c++17 file.cpp -o out              # basic
g++ -std=c++17 -O2 file.cpp -o out          # optimized
g++ -std=c++17 -g file.cpp -o out           # debug symbols
g++ -std=c++17 -Wall -Wextra file.cpp -o out  # all warnings
```

## ➕ Adding a New Concept

1. Put `<concept>.hpp` in the matching folder (a new GoF category gets its own subfolder under `02_design_patterns/`).
2. Add `test_<concept>.cpp` next to it with `#include "<concept>.hpp"` and a `main()` that calls its demo.
3. `./run_all.sh` picks it up automatically.
