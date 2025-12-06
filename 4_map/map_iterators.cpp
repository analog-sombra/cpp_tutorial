/*
### Map Iterators

### What are Iterators?
- Iterators are objects that point to elements in a container.
- They allow traversing through the container.
- For maps, iterators point to key-value pairs.

### Types of Iterators:
- begin(): Returns iterator to the first element
- end(): Returns iterator to one past the last element
- rbegin(): Returns reverse iterator to the last element
- rend(): Returns reverse iterator to one before the first element
- cbegin(): Returns const iterator to the first element
- cend(): Returns const iterator to one past the last element


### Accessing Elements via Iterator:
- it->first: Access the key
- it->second: Access the value
- (*it).first: Alternative way to access key
- (*it).second: Alternative way to access value


### Range-based For Loop (Recommended):
syntax:
    for (const auto& pair : map_name) {
        // pair.first is the key
        // pair.second is the value
    }

example:
    map<string, int> ages = {{"Alice", 25}, {"Bob", 30}};
    for (const auto& pair : ages) {
        cout << pair.first << ": " << pair.second << endl;
    }


### Structured Bindings (C++17):
syntax:
    for (const auto& [key, value] : map_name) {
        // use key and value directly
    }

example:
    for (const auto& [name, age] : ages) {
        cout << name << " is " << age << " years old" << endl;
    }


### Iterator-based Loop:
syntax:
    for (auto it = map_name.begin(); it != map_name.end(); ++it) {
        // it->first is the key
        // it->second is the value
    }


### Const Iterator:
- Used when you don't want to modify the map elements.
- Good practice for read-only operations.

syntax:
    for (auto it = map_name.cbegin(); it != map_name.cend(); ++it) {
        // read-only access
    }


### Reverse Iterator:
- Traverse the map in reverse order (descending key order).

syntax:
    for (auto it = map_name.rbegin(); it != map_name.rend(); ++it) {
        // reverse order
    }

*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, int> ages = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35},
        {"David", 28},
        {"Eve", 32}};

    cout << "=== Range-based For Loop (Most Common) ===" << endl;
    for (const auto &pair : ages)
    {
        cout << pair.first << ": " << pair.second << " years old" << endl;
    }
    cout << endl;

    cout << "=== Structured Bindings (C++17) ===" << endl;
    for (const auto &[name, age] : ages)
    {
        cout << name << " is " << age << " years old" << endl;
    }
    cout << endl;

    cout << "=== Iterator-based Loop ===" << endl;
    for (auto it = ages.begin(); it != ages.end(); ++it)
    {
        cout << "Key: " << it->first << ", Value: " << it->second << endl;
    }
    cout << endl;

    cout << "=== Using (*it).first and (*it).second ===" << endl;
    auto it = ages.begin();
    cout << "First element: " << (*it).first << " = " << (*it).second << endl;
    cout << endl;

    cout << "=== Const Iterator (Read-only) ===" << endl;
    for (auto it = ages.cbegin(); it != ages.cend(); ++it)
    {
        cout << it->first << ": " << it->second << endl;
        // it->second = 99; // ERROR: Cannot modify through const iterator
    }
    cout << endl;

    cout << "=== Reverse Iterator (Descending Order) ===" << endl;
    for (auto it = ages.rbegin(); it != ages.rend(); ++it)
    {
        cout << it->first << ": " << it->second << endl;
    }
    cout << endl;

    cout << "=== Accessing First and Last Elements ===" << endl;
    if (!ages.empty())
    {
        auto first = ages.begin();
        auto last = ages.rbegin(); // Last element via reverse iterator

        cout << "First element: " << first->first << " = " << first->second << endl;
        cout << "Last element: " << last->first << " = " << last->second << endl;
    }
    cout << endl;

    cout << "=== Modifying Values via Iterator ===" << endl;
    for (auto it = ages.begin(); it != ages.end(); ++it)
    {
        it->second += 1; // Increment all ages by 1
        // it->first = "NewKey"; // ERROR: Cannot modify keys
    }

    cout << "Ages after increment:" << endl;
    for (const auto &[name, age] : ages)
    {
        cout << name << ": " << age << endl;
    }
    cout << endl;

    cout << "=== Finding and Using Iterator ===" << endl;
    auto findIt = ages.find("Charlie");
    if (findIt != ages.end())
    {
        cout << "Found: " << findIt->first << " = " << findIt->second << endl;
        findIt->second = 40; // Modify Charlie's age
        cout << "Updated: " << findIt->first << " = " << findIt->second << endl;
    }
    cout << endl;

    cout << "=== Iterating from Specific Position ===" << endl;
    auto startIt = ages.find("Charlie");
    if (startIt != ages.end())
    {
        cout << "Elements from Charlie onwards:" << endl;
        for (auto it = startIt; it != ages.end(); ++it)
        {
            cout << it->first << ": " << it->second << endl;
        }
    }
    cout << endl;

    cout << "=== Numeric Key Map with Iterators ===" << endl;
    map<int, string> numbers = {{1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"}};

    cout << "Forward iteration:" << endl;
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        cout << it->first << " -> " << it->second << endl;
    }
    cout << endl;

    cout << "Reverse iteration:" << endl;
    for (auto it = numbers.rbegin(); it != numbers.rend(); ++it)
    {
        cout << it->first << " -> " << it->second << endl;
    }
    cout << endl;

    cout << "=== Using std::advance to Move Iterator ===" << endl;
    auto advanceIt = ages.begin();
    advance(advanceIt, 2); // Move iterator 2 positions forward
    cout << "Element at position 2: " << advanceIt->first << " = " << advanceIt->second << endl;
    cout << endl;

    cout << "=== Using std::next and std::prev ===" << endl;
    auto firstIt = ages.begin();
    auto secondIt = next(firstIt); // Next element
    cout << "First: " << firstIt->first << " = " << firstIt->second << endl;
    cout << "Second: " << secondIt->first << " = " << secondIt->second << endl;

    auto lastIt = ages.end();
    auto secondLastIt = prev(lastIt); // Previous element
    cout << "Second last: " << secondLastIt->first << " = " << secondLastIt->second << endl;

    return 0;
}
