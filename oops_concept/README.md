# 🎯 C++ OOP Concepts for Interview Preparation

C++ object-oriented programming concepts, design patterns and modern C++ features, each as a header-only example with a small runnable program next to it. Everything targets C++17 with no external dependencies.

Folders `01`–`03` use only simple syntax you'd write in an LLD round. Fancier C++ (templates, move semantics, lambdas, `std::function`, `dynamic_cast`) lives in `04_advanced_cpp/`, which is optional.

## 📁 Structure

Every concept is a `.hpp` with a `test_<concept>.cpp` beside it that runs its demo. Folders are numbered in suggested learning order.

```
oops_concept/
├── 01_oop_pillars/                 # The four pillars + building blocks
│   ├── class_object.hpp            # Classes, constructors, static members, `this`
│   ├── access_specifiers.hpp       # public / protected / private, friend, struct vs class
│   ├── encapsulation.hpp           # Data hiding, getters/setters, validation
│   ├── inheritance.hpp             # Single, multilevel inheritance + composition (HAS-A)
│   ├── polymorphism.hpp            # Virtual functions, overloading, interfaces
│   ├── abstraction.hpp             # Abstract classes, pure virtual, interfaces
│   └── test_*.cpp                  # One runner per header above
│
├── 02_design_patterns/             # Grouped by GoF category
│   ├── creational/                 # singleton.hpp, factory.hpp
│   ├── structural/                 # adapter_decorator.hpp
│   └── behavioral/                 # observer.hpp, strategy.hpp
│
├── 03_modern_cpp/                  # smart_pointers, exception_handling
│
├── 04_advanced_cpp/                # Optional: C++ quiz topics, not needed for LLD
│   ├── rule_of_five.hpp            # Raw new/delete + all five special members
│   ├── advanced_inheritance.hpp    # Diamond problem, protected/private inheritance
│   ├── advanced_polymorphism.hpp   # Operator overloading, templates, functors, dynamic_cast
│   ├── advanced_patterns.hpp       # Mutex singleton, registration factory, lambda observers
│   ├── advanced_modern_cpp.hpp     # unique_ptr arrays, custom deleters, conditional noexcept
│   └── move_semantics.hpp          # Rvalue references, std::move, perfect forwarding
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

## ✍️ Code Style (folders 01–03)

- **Pointers:** `std::shared_ptr` + `std::make_shared` everywhere, so you never need `std::move`.
- **Interfaces:** an abstract class with `virtual ... = 0;`, a `virtual ~X() = default;`, and `override` in derived classes.
- **Types:** variables that hold an interface are declared with that type, e.g. `std::shared_ptr<Coffee> coffee = std::make_shared<Espresso>();`. Range loops still use `for (const auto& x : list)`.
- **No:** templates you write yourself, lambdas, `std::function`, `dynamic_cast`, operator overloading, move constructors.
- **Singleton:** private constructor + deleted copy + `static` local instance (see `Logger`).

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

All 22 programs build and run (`./run_all.sh` prints the live result):

| Area | Programs |
|------|----------|
| Pillars | `test_class_object`, `test_access_specifiers`, `test_encapsulation`, `test_inheritance`, `test_polymorphism`, `test_abstraction` |
| Design patterns | `test_singleton`, `test_factory`, `test_adapter_decorator`, `test_observer`, `test_strategy` |
| Modern C++ | `test_smart_pointers`, `test_exception_handling` |
| Advanced (optional) | `test_rule_of_five`, `test_advanced_inheritance`, `test_advanced_polymorphism`, `test_advanced_patterns`, `test_advanced_modern_cpp`, `test_move_semantics` |
| Demos | `master_demo`, `core_concepts_demo`, `quick_demo` |

## 📖 Concepts Covered

### 🔹 01 — OOP Pillars

**Classes and Objects** (`class_object.hpp`)
- Default, parameterized, and copy constructors; copy assignment
- Static vs non-static members
- `this` pointer usage and method chaining

**Access Specifiers** (`access_specifiers.hpp`)
- `public`, `protected`, `private` and what each allows
- Inheritance access (public / protected / private inheritance)
- `friend`, and default access for `struct` vs `class`

**Encapsulation** (`encapsulation.hpp`)
- Getter and setter methods
- Data validation and security (PIN-protected bank account)
- Friend functions

**Inheritance** (`inheritance.hpp`)
- Single and multilevel inheritance (`Vehicle` → `Car` → `SportsCar`)
- Composition: `SmartCar` IS-A `Car` and HAS-A `Engine` and `GPS`
- Constructor/destructor call order, virtual destructors

**Polymorphism** (`polymorphism.hpp`)
- Runtime: virtual functions, vtable, a container of base-class pointers
- Compile time: function overloading
- Interfaces: one class implementing two interfaces (`GameSprite`)

**Abstraction** (`abstraction.hpp`)
- Abstract classes and pure virtual functions
- Interfaces, and an abstract class that mixes pure virtual and normal methods (`Comparable`)

### 🔹 02 — Design Patterns

**Creational**
- **Singleton** (`singleton.hpp`): static-local `Logger` and a `ConfigManager` with state. Use for loggers, config, DB connections.
- **Factory** (`factory.hpp`): simple factory, factory method, abstract factory. Use for object creation and plugin systems.

**Structural**
- **Adapter & Decorator** (`adapter_decorator.hpp`): interface compatibility; adding behavior dynamically; text-processing pipeline. Use for legacy integration and feature layering.

**Behavioral**
- **Observer** (`observer.hpp`): subject/observer with notifiers, news agency, stock market. Use for notifications, event systems, MVC.
- **Strategy** (`strategy.hpp`): payment, sorting and compression strategies. Use for swapping algorithms at runtime.

### 🔹 03 — Modern C++

- **Smart Pointers** (`smart_pointers.hpp`): `unique_ptr` (single owner), `shared_ptr` (reference counting), `weak_ptr` (breaking cycles), RAII
- **Exception Handling** (`exception_handling.hpp`): try/catch/throw, custom exceptions, basic/strong/no-throw guarantees, RAII cleanup. When run it writes `test_file.txt` and `transaction_log.txt` into the working directory.

### 🔹 04 — Advanced C++ (optional)

Moved out of 01–03 so the core stays simple. Read these for C++ quiz questions, not for LLD design.

- **Rule of Five** (`rule_of_five.hpp`): deep copy, move constructor/assignment, conversion constructor with raw memory
- **Advanced Inheritance** (`advanced_inheritance.hpp`): diamond problem and virtual inheritance; protected/private inheritance
- **Advanced Polymorphism** (`advanced_polymorphism.hpp`): operator overloading, function and class templates, functors, `dynamic_cast`/`typeid`, vtable demo
- **Advanced Patterns** (`advanced_patterns.hpp`): pointer + mutex singleton, registration-based factory, lambda observers, event system
- **Advanced Modern C++** (`advanced_modern_cpp.hpp`): `unique_ptr<int[]>`, custom deleters, conditional `noexcept`
- **Move Semantics** (`move_semantics.hpp`): rvalue references, move constructors, `std::forward`, Rule of Five

## 📝 Learning Path

1. **Beginner:** `01_oop_pillars/` in order: class_object → access_specifiers → encapsulation → inheritance → polymorphism → abstraction
2. **Patterns:** `02_design_patterns/creational/`, then `behavioral/`, then `structural/`
3. **Modern C++:** `03_modern_cpp/smart_pointers.hpp`, then `exception_handling.hpp`
4. **Optional:** `04_advanced_cpp/` for C++ language quiz questions

## 🎯 Interview Focus Areas

1. Virtual functions and the vtable mechanism
2. IS-A (inheritance) vs HAS-A (composition)
3. Function overloading vs overriding
4. When to use which design pattern
5. Singleton thread safety (static local variables are thread-safe since C++11)
6. Factory pattern variations
7. Observer vs pub-sub
8. Adapter vs decorator
9. Smart pointer types and usage
10. Exception safety guarantees
11. RAII
12. Diamond problem and move semantics (see `04_advanced_cpp/`)

### Practice Scenarios

- **Design a notification system** → Observer
- **Create a drawing application** → Factory + Strategy
- **Integrate legacy systems** → Adapter
- **Add features dynamically** → Decorator
- **Ensure a single instance** → Singleton
- **Manage resources safely** → Smart pointers + RAII
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
