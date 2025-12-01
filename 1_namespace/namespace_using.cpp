/*
### using declaration vs using directive

### using declaration (recommended)
- Brings only specific names into the current scope.
- More precise and safer.
- Reduces chance of naming conflicts.

syntax:
    using namespace_name::member_name;

example:
    using std::cout;
    using std::endl;
    cout << "Hello" << endl; // Only cout and endl are available


### using directive (use with caution)
- Brings all names from a namespace into the current scope.
- Convenient but can cause naming conflicts.
- Not recommended in header files.

syntax:
    using namespace namespace_name;

example:
    using namespace std;
    cout << "Hello" << endl; // All std members available


### Best Practices:
1. Prefer using declarations over using directives
2. Never use "using namespace" in header files
3. Use fully qualified names in header files
4. Keep using directives local to functions when possible
5. Be cautious with using directives in large codebases

*/

#include <iostream>
#include <vector>
#include <string>

// Namespace with potential naming conflict
namespace Custom
{
    void print(int value)
    {
        std::cout << "Custom print (int): " << value << std::endl;
    }

    class string
    {
    public:
        void display()
        {
            std::cout << "Custom::string class" << std::endl;
        }
    };
}

int main()
{
    std::cout << "=== Using Fully Qualified Names (Safest) ===" << std::endl;
    std::cout << "Using std::cout with std:: prefix" << std::endl;
    std::vector<int> numbers1 = {1, 2, 3};
    std::cout << "Vector size: " << numbers1.size() << std::endl;
    std::cout << std::endl;

    std::cout << "=== Using Declaration (Recommended) ===" << std::endl;
    {
        using std::cout;
        using std::endl;
        using std::vector;

        cout << "Using declaration for specific members" << endl;
        vector<int> numbers2 = {4, 5, 6};
        cout << "Vector size: " << numbers2.size() << endl;
        cout << endl;
    }

    std::cout << "=== Using Directive in Limited Scope ===" << std::endl;
    {
        using namespace std;
        cout << "Using directive within block scope" << endl;
        vector<int> numbers3 = {7, 8, 9};
        cout << "Vector size: " << numbers3.size() << endl;
        cout << endl;
    }

    std::cout << "=== Demonstrating Naming Conflicts ===" << std::endl;
    {
        using std::cout;
        using std::endl;

        // Using specific members to avoid conflict
        std::string stdString = "Standard string";
        Custom::string customString;

        cout << "std::string: " << stdString << endl;
        customString.display();
        cout << endl;
    }

    std::cout << "=== What Happens with Naming Conflicts ===" << std::endl;
    {
        using std::cout;
        using std::endl;

        // This is safe - explicit namespace
        std::string str1 = "std::string";
        Custom::string str2;

        cout << "Using explicit namespaces prevents conflicts" << endl;
        cout << "std::string value: " << str1 << endl;
        str2.display();

        // If we did: using namespace std; using namespace Custom;
        // Then: string str; would be ambiguous!
        cout << endl;
    }

    std::cout << "=== Multiple Using Declarations ===" << std::endl;
    {
        using std::cout;
        using std::endl;
        using std::vector;
        using std::string;
        using Custom::print;

        cout << "Multiple using declarations keep code clear" << endl;
        vector<string> names = {"Alice", "Bob", "Charlie"};

        cout << "Names: ";
        for (const string &name : names)
        {
            cout << name << " ";
        }
        cout << endl;

        print(42); // Custom::print
        cout << endl;
    }

    std::cout << "=== Scope-Limited Using Directive ===" << std::endl;
    {
        // Using directive in function scope (acceptable)
        using namespace std;

        cout << "This is acceptable in function scope" << endl;
        cout << "But still prefer using declarations" << endl;
        
        vector<int> data = {10, 20, 30, 40, 50};
        cout << "Data elements: ";
        for (int val : data)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
