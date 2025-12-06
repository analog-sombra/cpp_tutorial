/*
### Map Functions

### m.clear() operation
- removes all elements from the map.
- after calling clear(), the size of the map becomes 0.

syntax:
    m.clear();
    - m is the name of the map.

example:
    map<string, int> ages = {{"Alice", 25}, {"Bob", 30}};
    ages.clear(); // Map is now empty


### m.erase(key) operation
- removes the element with the specified key.
- returns the number of elements removed (0 or 1 for std::map).

syntax:
    m.erase(key);
    - m is the name of the map.
    - key is the key of the element to remove.

example:
    map<string, int> ages = {{"Alice", 25}, {"Bob", 30}};
    ages.erase("Alice"); // Removes Alice


### m.erase(iterator) operation
- removes the element at the specified iterator position.
- returns an iterator to the element following the erased element.

syntax:
    m.erase(iterator);
    - iterator points to the element to remove.

example:
    auto it = ages.find("Alice");
    if (it != ages.end()) {
        ages.erase(it);
    }


### m.swap(other_map) operation
- swaps the contents of two maps.
- both maps must have the same type.

syntax:
    m1.swap(m2);
    - m1 and m2 are the names of the maps.

example:
    map<string, int> m1 = {{"A", 1}};
    map<string, int> m2 = {{"B", 2}};
    m1.swap(m2); // m1 now has {"B", 2}, m2 has {"A", 1}


### m.contains(key) operation (C++20)
- checks if the map contains an element with the specified key.
- returns true if key exists, false otherwise.
- more readable than count() or find().

syntax:
    m.contains(key);
    - m is the name of the map.
    - key is the key to search for.

example:
    map<string, int> ages = {{"Alice", 25}};
    if (ages.contains("Alice")) { // C++20
        cout << "Alice exists" << endl;
    }


### m.emplace(key, value) operation
- constructs element in-place (more efficient than insert).
- returns a pair: iterator and bool (true if inserted).

syntax:
    m.emplace(key, value);

example:
    map<string, int> ages;
    ages.emplace("Alice", 25);


### m.max_size() operation
- returns the maximum number of elements the map can hold.
- theoretical limit based on system constraints.

syntax:
    m.max_size();

example:
    map<string, int> ages;
    cout << "Max size: " << ages.max_size() << endl;


### m.lower_bound(key) operation
- returns an iterator to the first element with key >= specified key.
- useful for range queries.

syntax:
    m.lower_bound(key);

example:
    map<int, string> m = {{1, "A"}, {3, "B"}, {5, "C"}};
    auto it = m.lower_bound(2); // Points to {3, "B"}


### m.upper_bound(key) operation
- returns an iterator to the first element with key > specified key.
- useful for range queries.

syntax:
    m.upper_bound(key);

example:
    map<int, string> m = {{1, "A"}, {3, "B"}, {5, "C"}};
    auto it = m.upper_bound(3); // Points to {5, "C"}


### m.equal_range(key) operation
- returns a pair of iterators: [lower_bound, upper_bound).
- for std::map, range contains at most one element.

syntax:
    m.equal_range(key);

example:
    auto range = m.equal_range(3);
    for (auto it = range.first; it != range.second; ++it) {
        cout << it->first << ": " << it->second << endl;
    }

*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, int> ages = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 35}, {"David", 28}};

    cout << "=== Original Map ===" << endl;
    for (const auto &pair : ages)
    {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << "Size: " << ages.size() << endl;
    cout << endl;

    cout << "=== erase(key) - Remove Element by Key ===" << endl;
    size_t removed = ages.erase("Bob");
    cout << "Removed " << removed << " element(s) (key: Bob)" << endl;
    cout << "Current map: ";
    for (const auto &pair : ages)
    {
        cout << pair.first << "=" << pair.second << " ";
    }
    cout << endl;
    cout << "Size after erase: " << ages.size() << endl;
    cout << endl;

    cout << "=== erase(iterator) - Remove Element by Iterator ===" << endl;
    auto it = ages.find("David");
    if (it != ages.end())
    {
        cout << "Found David, erasing..." << endl;
        ages.erase(it);
    }
    cout << "Current map: ";
    for (const auto &pair : ages)
    {
        cout << pair.first << "=" << pair.second << " ";
    }
    cout << endl;
    cout << endl;

    cout << "=== emplace() - Construct Element In-Place ===" << endl;
    auto result = ages.emplace("Eve", 32);
    if (result.second)
    {
        cout << "Successfully emplaced Eve" << endl;
    }
    
    ages.emplace("Frank", 40);
    cout << "Current map: ";
    for (const auto &pair : ages)
    {
        cout << pair.first << "=" << pair.second << " ";
    }
    cout << endl;
    cout << endl;

    cout << "=== swap() - Swap Contents of Two Maps ===" << endl;
    map<string, int> otherAges = {{"X", 10}, {"Y", 20}, {"Z", 30}};
    
    cout << "Before swap:" << endl;
    cout << "ages: ";
    for (const auto &pair : ages) { cout << pair.first << "=" << pair.second << " "; }
    cout << endl;
    cout << "otherAges: ";
    for (const auto &pair : otherAges) { cout << pair.first << "=" << pair.second << " "; }
    cout << endl;
    
    ages.swap(otherAges);
    
    cout << "After swap:" << endl;
    cout << "ages: ";
    for (const auto &pair : ages) { cout << pair.first << "=" << pair.second << " "; }
    cout << endl;
    cout << "otherAges: ";
    for (const auto &pair : otherAges) { cout << pair.first << "=" << pair.second << " "; }
    cout << endl;
    cout << endl;

    cout << "=== count() vs find() - Check Key Existence ===" << endl;
    // Using count()
    cout << "Using count(): ";
    if (ages.count("X") > 0)
    {
        cout << "X exists (value: " << ages["X"] << ")" << endl;
    }
    
    // Using find()
    cout << "Using find(): ";
    auto findIt = ages.find("Y");
    if (findIt != ages.end())
    {
        cout << "Y exists (value: " << findIt->second << ")" << endl;
    }
    cout << endl;

    cout << "=== Numeric Key Map for Range Operations ===" << endl;
    map<int, string> numbers = {{1, "One"}, {3, "Three"}, {5, "Five"}, {7, "Seven"}, {9, "Nine"}};
    
    cout << "Numbers map: ";
    for (const auto &pair : numbers)
    {
        cout << pair.first << "=" << pair.second << " ";
    }
    cout << endl;
    cout << endl;

    cout << "=== lower_bound() - First Element >= Key ===" << endl;
    auto lb = numbers.lower_bound(4);
    if (lb != numbers.end())
    {
        cout << "lower_bound(4): " << lb->first << " = " << lb->second << endl;
    }
    
    auto lb2 = numbers.lower_bound(5);
    if (lb2 != numbers.end())
    {
        cout << "lower_bound(5): " << lb2->first << " = " << lb2->second << endl;
    }
    cout << endl;

    cout << "=== upper_bound() - First Element > Key ===" << endl;
    auto ub = numbers.upper_bound(5);
    if (ub != numbers.end())
    {
        cout << "upper_bound(5): " << ub->first << " = " << ub->second << endl;
    }
    
    auto ub2 = numbers.upper_bound(4);
    if (ub2 != numbers.end())
    {
        cout << "upper_bound(4): " << ub2->first << " = " << ub2->second << endl;
    }
    cout << endl;

    cout << "=== equal_range() - Range of Elements with Key ===" << endl;
    auto range = numbers.equal_range(5);
    cout << "equal_range(5): ";
    for (auto it = range.first; it != range.second; ++it)
    {
        cout << it->first << "=" << it->second << " ";
    }
    cout << endl;
    cout << endl;

    cout << "=== max_size() - Maximum Possible Size ===" << endl;
    cout << "Maximum size: " << ages.max_size() << endl;
    cout << endl;

    cout << "=== clear() - Remove All Elements ===" << endl;
    cout << "Before clear, otherAges size: " << otherAges.size() << endl;
    otherAges.clear();
    cout << "After clear, otherAges size: " << otherAges.size() << endl;
    if (otherAges.empty())
    {
        cout << "otherAges is now empty" << endl;
    }

    return 0;
}
