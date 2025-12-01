/*
### Nested Namespaces
- Namespaces can be nested inside other namespaces.
- Helps create hierarchical organization of code.

syntax:
    namespace outer {
        namespace inner {
            // declarations
        }
    }

Accessing:
    outer::inner::member_name;


### Multiple Namespaces
- You can define multiple namespaces in the same file.
- Same namespace can be defined in multiple files.

syntax:
    namespace A {
        // declarations
    }
    namespace B {
        // declarations
    }


### Namespace Aliasing
- Create shorter aliases for long namespace names.

syntax:
    namespace short_name = long::nested::namespace_name;

example:
    namespace MyLib = VeryLongLibraryName::SubModule;
    MyLib::function();


### Anonymous/Unnamed Namespaces
- Namespace without a name.
- Members are accessible only within the same file (internal linkage).

syntax:
    namespace {
        // declarations - file-local
    }

*/

#include <iostream>

// Multiple namespaces
namespace Math
{
    int add(int a, int b)
    {
        return a + b;
    }

    int multiply(int a, int b)
    {
        return a * b;
    }
}

namespace String
{
    void print(const char *message)
    {
        std::cout << message << std::endl;
    }
}

// Nested namespaces
namespace Company
{
    namespace Project
    {
        namespace Module
        {
            void execute()
            {
                std::cout << "Executing nested module" << std::endl;
            }
        }
    }
}

// Alternative C++17 nested namespace syntax
namespace Game::Engine::Graphics
{
    void render()
    {
        std::cout << "Rendering graphics" << std::endl;
    }
}

// Anonymous namespace (file-local)
namespace
{
    int secret = 42; // Only accessible in this file
    void helperFunction()
    {
        std::cout << "This is a file-local helper function" << std::endl;
    }
}

using namespace std;

int main()
{
    cout << "=== Multiple Namespaces ===" << endl;
    int result1 = Math::add(10, 20);
    int result2 = Math::multiply(5, 6);
    cout << "10 + 20 = " << result1 << endl;
    cout << "5 * 6 = " << result2 << endl;
    String::print("Hello from String namespace");
    cout << endl;

    cout << "=== Nested Namespaces ===" << endl;
    Company::Project::Module::execute();
    cout << endl;

    cout << "=== C++17 Nested Namespace Syntax ===" << endl;
    Game::Engine::Graphics::render();
    cout << endl;

    cout << "=== Namespace Aliasing ===" << endl;
    // Create alias for long nested namespace
    namespace CPM = Company::Project::Module;
    CPM::execute();

    namespace GEG = Game::Engine::Graphics;
    GEG::render();
    cout << endl;

    cout << "=== Anonymous Namespace ===" << endl;
    helperFunction(); // Accessible without namespace prefix
    cout << "Secret value: " << secret << endl;
    cout << endl;

    cout << "=== Using Declaration ===" << endl;
    using Math::add; // Only bring add into scope
    cout << "Using declaration - add(5, 3) = " << add(5, 3) << endl;
    // cout << multiply(2, 3); // ERROR: multiply not in scope
    cout << "Still need namespace for multiply: Math::multiply(2, 3) = " << Math::multiply(2, 3) << endl;

    return 0;
}
