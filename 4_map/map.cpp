/*
### Map (std::map)
- A map is an associative container that stores key-value pairs.
- Keys are unique - each key can appear only once in the map.
- Elements are automatically sorted by key in ascending order.
- Implemented as a balanced binary search tree (typically Red-Black Tree).

### Key Characteristics:
- Ordered: Elements are sorted by key
- Unique keys: Each key appears only once
- Key-value pairs: Each element is a pair of key and value
- Logarithmic time complexity: O(log n) for insert, find, erase

### When to use Map:
- Need to store key-value pairs
- Need automatic sorting by key
- Need fast lookup by key
- Keys must be unique

### Map vs Other Containers:
- Map: Ordered, unique keys, O(log n) operations
- unordered_map: Unordered, unique keys, O(1) average operations
- multimap: Ordered, duplicate keys allowed
- Vector: Indexed by integers, not key-value pairs

### Syntax:
    map<key_type, value_type> map_name;

### Examples:
    map<string, int> ages;           // Map of names to ages
    map<int, string> idToName;       // Map of IDs to names
    map<char, int> charFrequency;    // Map of characters to counts

### Initialization:
    // Empty map
    map<string, int> m1;

    // Initialize with pairs
    map<string, int> m2 = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 35}};

    // Using make_pair
    map<int, string> m3;
    m3.insert(make_pair(1, "One"));
    m3.insert(make_pair(2, "Two"));

    // Using pair constructor
    map<int, string> m4;
    m4.insert(pair<int, string>(1, "One"));

    // Using [] operator (most common)
    map<string, int> m5;
    m5["Alice"] = 25;
    m5["Bob"] = 30;

*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    cout << "=== Map Introduction ===" << endl;
    cout << "Map stores key-value pairs with unique keys" << endl;
    cout << "Elements are automatically sorted by key" << endl;
    cout << endl;

    // Creating an empty map
    map<string, int> ages;

    cout << "=== Adding Elements Using [] Operator ===" << endl;
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;
    ages["David"] = 28;

    cout << "Added 4 people with their ages" << endl;
    cout << endl;

    // Displaying the map (automatically sorted by key)
    cout << "=== Displaying Map (Auto-sorted by Key) ===" << endl;
    for (const auto &pair : ages)
    {
        cout << pair.first << ": " << pair.second << " years old" << endl;
    }
    cout << endl;

    // Initialize map with values
    cout << "=== Initializing Map with Values ===" << endl;
    map<int, string> idToName = {
        {101, "John"},
        {103, "Emma"},
        {102, "Michael"},
        {104, "Sophia"}};

    cout << "ID to Name mapping (sorted by ID):" << endl;
    for (const auto &pair : idToName)
    {
        cout << "ID " << pair.first << ": " << pair.second << endl;
    }
    cout << endl;

    // Character frequency example
    cout << "=== Character Frequency Example ===" << endl;
    string text = "hello world";
    map<char, int> frequency;

    for (char c : text)
    {
        if (c != ' ')
        { // Skip spaces
            frequency[c]++;
        }
    }

    cout << "Character frequencies in \"" << text << "\":" << endl;
    for (const auto &pair : frequency)
    {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }
    cout << endl;

    // Accessing elements
    cout << "=== Accessing Elements ===" << endl;
    cout << "Alice's age: " << ages["Alice"] << endl;
    cout << "Bob's age: " << ages["Bob"] << endl;
    cout << endl;

    // Map size
    cout << "=== Map Size ===" << endl;
    cout << "Number of entries in ages: " << ages.size() << endl;
    cout << "Number of entries in idToName: " << idToName.size() << endl;
    cout << endl;

    // Check if map is empty
    map<string, double> prices;
    cout << "=== Checking if Map is Empty ===" << endl;
    if (prices.empty())
    {
        cout << "Prices map is empty" << endl;
    }
    else
    {
        cout << "Prices map is not empty" << endl;
    }
    cout << endl;

    // Modifying values
    cout << "=== Modifying Values ===" << endl;
    cout << "Before: Alice's age = " << ages["Alice"] << endl;
    ages["Alice"] = 26; // Update value
    cout << "After: Alice's age = " << ages["Alice"] << endl;

    return 0;
}
