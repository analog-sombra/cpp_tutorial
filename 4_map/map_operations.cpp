/*
### Map Operations

### m.empty() operation
- checks whether the map is empty (i.e., contains no elements).
- returns true if m is empty.
- returns false if m is not empty.

syntax:
    m.empty();
    - m is the name of the map.

example:
    map<string, int> ages;
    if (ages.empty()) {
        cout << "Map is empty" << endl;
    }


### m.size() operation
- returns the number of key-value pairs in the map.
- returns a value of type size_type.

syntax:
    m.size();
    - m is the name of the map.

example:
    map<string, int> ages = {{"Alice", 25}, {"Bob", 30}};
    cout << "Size: " << ages.size() << endl; // Output: 2


### m[key] operation
- accesses the value associated with the key.
- if key doesn't exist, creates a new element with that key.
- returns a reference to the value.

syntax:
    m[key];
    - m is the name of the map.
    - key is the key to access.

example:
    map<string, int> ages;
    ages["Alice"] = 25; // Insert or update
    cout << ages["Alice"] << endl; // Access


### m.at(key) operation
- accesses the value associated with the key (with bounds checking).
- throws std::out_of_range exception if key doesn't exist.
- safer than [] but throws exception for missing keys.

syntax:
    m.at(key);
    - m is the name of the map.
    - key is the key to access.

example:
    map<string, int> ages = {{"Alice", 25}};
    cout << ages.at("Alice") << endl; // Output: 25
    // ages.at("Bob") would throw exception


### m.insert() operation
- inserts a new key-value pair into the map.
- if key already exists, insertion fails.
- returns a pair: iterator to element and bool (true if inserted, false if exists).

syntax:
    m.insert({key, value});
    m.insert(make_pair(key, value));
    m.insert(pair<KeyType, ValueType>(key, value));

example:
    map<string, int> ages;
    ages.insert({"Alice", 25});
    auto result = ages.insert({"Alice", 30}); // Fails, Alice exists
    if (!result.second) {
        cout << "Key already exists" << endl;
    }


### m.find(key) operation
- searches for an element with the specified key.
- returns an iterator to the element if found.
- returns m.end() if not found.

syntax:
    m.find(key);
    - m is the name of the map.
    - key is the key to search for.

example:
    map<string, int> ages = {{"Alice", 25}};
    auto it = ages.find("Alice");
    if (it != ages.end()) {
        cout << "Found: " << it->first << " = " << it->second << endl;
    }


### m.count(key) operation
- returns the number of elements with the specified key.
- for std::map, always returns 0 or 1 (keys are unique).
- useful for checking if a key exists.

syntax:
    m.count(key);
    - m is the name of the map.
    - key is the key to search for.

example:
    map<string, int> ages = {{"Alice", 25}};
    if (ages.count("Alice") > 0) {
        cout << "Alice exists in map" << endl;
    }


### m1 = m2 operation
- assigns the contents of map m2 to map m1.
- replaces all elements in m1.

syntax:
    m1 = m2;

example:
    map<string, int> m1 = {{"A", 1}};
    map<string, int> m2 = {{"B", 2}, {"C", 3}};
    m1 = m2; // m1 now contains {"B", 2}, {"C", 3}


### m1 == m2 operation
- compares two maps for equality.
- returns true if they have the same keys with same values.

syntax:
    m1 == m2;

example:
    map<string, int> m1 = {{"Alice", 25}};
    map<string, int> m2 = {{"Alice", 25}};
    if (m1 == m2) {
        cout << "Maps are equal" << endl;
    }

*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, int> ages;

    cout << "=== empty() - Check if Map is Empty ===" << endl;
    if (ages.empty())
    {
        cout << "Map is empty" << endl;
    }
    cout << endl;

    // Add elements
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;

    cout << "=== size() - Get Number of Elements ===" << endl;
    cout << "Map size: " << ages.size() << endl;
    cout << endl;

    cout << "=== empty() After Adding Elements ===" << endl;
    if (!ages.empty())
    {
        cout << "Map is not empty" << endl;
    }
    cout << endl;

    cout << "=== [] Operator - Access/Insert Elements ===" << endl;
    cout << "Alice's age: " << ages["Alice"] << endl;
    cout << "Bob's age: " << ages["Bob"] << endl;
    ages["David"] = 28; // Insert new element
    cout << "Added David with age: " << ages["David"] << endl;
    cout << endl;

    cout << "=== at() - Safe Access with Bounds Checking ===" << endl;
    try
    {
        cout << "Charlie's age using at(): " << ages.at("Charlie") << endl;
        cout << "Trying to access non-existent key 'Eve'..." << endl;
        cout << ages.at("Eve") << endl; // This will throw exception
    }
    catch (const out_of_range &e)
    {
        cout << "Exception caught: Key 'Eve' not found!" << endl;
    }
    cout << endl;

    cout << "=== insert() - Insert Elements ===" << endl;
    auto result1 = ages.insert({"Eve", 32});
    if (result1.second)
    {
        cout << "Successfully inserted Eve" << endl;
    }

    auto result2 = ages.insert({"Alice", 99}); // Alice already exists
    if (!result2.second)
    {
        cout << "Failed to insert: Alice already exists with age " 
             << result2.first->second << endl;
    }
    cout << endl;

    cout << "=== insert() with make_pair ===" << endl;
    ages.insert(make_pair("Frank", 40));
    cout << "Inserted Frank using make_pair" << endl;
    cout << endl;

    cout << "=== Current Map Contents ===" << endl;
    for (const auto &pair : ages)
    {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << endl;

    cout << "=== find() - Search for Elements ===" << endl;
    auto it = ages.find("Bob");
    if (it != ages.end())
    {
        cout << "Found: " << it->first << " = " << it->second << endl;
    }
    else
    {
        cout << "Bob not found" << endl;
    }

    auto it2 = ages.find("Unknown");
    if (it2 == ages.end())
    {
        cout << "Unknown not found in map" << endl;
    }
    cout << endl;

    cout << "=== count() - Check if Key Exists ===" << endl;
    cout << "Does 'Alice' exist? " << (ages.count("Alice") > 0 ? "Yes" : "No") << endl;
    cout << "Does 'Zoe' exist? " << (ages.count("Zoe") > 0 ? "Yes" : "No") << endl;
    cout << endl;

    cout << "=== Assignment Operator (=) ===" << endl;
    map<string, int> newAges = {{"X", 10}, {"Y", 20}};
    cout << "Before assignment, ages size: " << ages.size() << endl;
    cout << "Before assignment, newAges size: " << newAges.size() << endl;
    
    newAges = ages; // Copy all elements
    
    cout << "After assignment, newAges size: " << newAges.size() << endl;
    cout << "newAges contains: ";
    for (const auto &pair : newAges)
    {
        cout << pair.first << "=" << pair.second << " ";
    }
    cout << endl;
    cout << endl;

    cout << "=== Equality Comparison (==) ===" << endl;
    map<string, int> map1 = {{"A", 1}, {"B", 2}};
    map<string, int> map2 = {{"A", 1}, {"B", 2}};
    map<string, int> map3 = {{"A", 1}, {"B", 3}};

    cout << "map1 == map2: " << (map1 == map2 ? "true" : "false") << endl;
    cout << "map1 == map3: " << (map1 == map3 ? "true" : "false") << endl;

    return 0;
}
