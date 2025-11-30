// - A Namespace is a declarative region that provides a scope to the identifiers (names of types, functions, variables, etc) inside it.
// - Namespaces are used to organize code into logical groups and to prevent name collisions that can occur especially when your code base includes multiple libraries.


/*
Namespace using declaration

A using declaration lets us use a name from a namespace without qualifying it with the namespace name.

Syntax:
using namespace_name::name;

Example:
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl; // Using std::cout without 'using' declaration
    using std::cout; // Using declaration
    cout << "Hello again!" << std::endl; // Now we can use cout directly
    return 0;
}



-- using namespace std;

using namespace std; // Using directive
int main() {
    cout << "Hello, World!" << endl; // Now we can use cout and endl directly
    return 0;
}

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