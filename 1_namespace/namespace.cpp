/*
### What is a Namespace?
- A Namespace is a declarative region that provides a scope to the identifiers (names of types, functions, variables, etc) inside it.
- Namespaces are used to organize code into logical groups and to prevent name collisions.
- Especially useful when your code base includes multiple libraries.

### Why use Namespaces?
- Prevent naming conflicts between different parts of code
- Organize code into logical groups
- Make code more maintainable and readable

### Namespace Syntax:
    namespace namespace_name {
        // declarations
    }

### Accessing namespace members:
1. Fully qualified name: namespace_name::member_name
2. Using declaration: using namespace_name::member_name;
3. Using directive: using namespace namespace_name;


### using declaration
- Lets us use a specific name from a namespace without qualifying it with the namespace name.

Syntax:
    using namespace_name::name;

Example:
    using std::cout;
    cout << "Hello"; // Can use cout directly


### using directive (using namespace std;)
- Brings all names from a namespace into the current scope.
- Convenient but can cause naming conflicts.

Syntax:
    using namespace namespace_name;

Example:
    using namespace std;
    cout << "Hello"; // Can use all std members directly

*/


// Custom namespace example
#include <iostream>

namespace MyNamespace {
    void displayMessage() {
        std::cout << "Hello from MyNamespace!" << std::endl;
    }
}

using namespace MyNamespace; // Using directive to bring all names from MyNamespace into the global scope
int main() {
    // Calling the function from MyNamespace
    // MyNamespace::displayMessage(); - Without using directive
    displayMessage(); // With using directive
    return 0;
}