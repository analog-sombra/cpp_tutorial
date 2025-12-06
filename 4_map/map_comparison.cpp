/*
### Map Comparison Operators

### m1 == m2
- compares two maps for equality.
- returns true if they have the same size, same keys, and same values for each key.
- returns false otherwise.

syntax:
    m1 == m2;

example:
    map<string, int> m1 = {{"A", 1}, {"B", 2}};
    map<string, int> m2 = {{"A", 1}, {"B", 2}};
    if (m1 == m2) { cout << "Equal"; }


### m1 != m2
- compares two maps for inequality.
- returns true if maps differ in size, keys, or values.
- returns false if they are equal.

syntax:
    m1 != m2;

example:
    map<string, int> m1 = {{"A", 1}};
    map<string, int> m2 = {{"B", 2}};
    if (m1 != m2) { cout << "Not equal"; }


### m1 < m2
- lexicographical comparison.
- compares elements pair by pair (key first, then value).
- returns true if m1 is lexicographically less than m2.

syntax:
    m1 < m2;

example:
    map<string, int> m1 = {{"A", 1}};
    map<string, int> m2 = {{"A", 2}};
    if (m1 < m2) { cout << "m1 is less than m2"; }


### m1 <= m2
- lexicographical comparison.
- returns true if m1 is less than or equal to m2.

syntax:
    m1 <= m2;

example:
    map<string, int> m1 = {{"A", 1}};
    map<string, int> m2 = {{"A", 1}};
    if (m1 <= m2) { cout << "m1 is less than or equal to m2"; }


### m1 > m2
- lexicographical comparison.
- returns true if m1 is lexicographically greater than m2.

syntax:
    m1 > m2;

example:
    map<string, int> m1 = {{"B", 1}};
    map<string, int> m2 = {{"A", 1}};
    if (m1 > m2) { cout << "m1 is greater than m2"; }


### m1 >= m2
- lexicographical comparison.
- returns true if m1 is greater than or equal to m2.

syntax:
    m1 >= m2;

example:
    map<string, int> m1 = {{"A", 2}};
    map<string, int> m2 = {{"A", 2}};
    if (m1 >= m2) { cout << "m1 is greater than or equal to m2"; }


Note: Lexicographical comparison for maps:
- First compares by keys (alphabetically for strings, numerically for numbers)
- If keys are equal, compares by values
- Shorter map is less if all elements match
*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, int> m1 = {{"Alice", 25}, {"Bob", 30}};
    map<string, int> m2 = {{"Alice", 25}, {"Bob", 30}};
    map<string, int> m3 = {{"Alice", 25}, {"Bob", 35}};
    map<string, int> m4 = {{"Alice", 25}, {"Charlie", 30}};
    map<string, int> m5 = {{"Alice", 25}};

    cout << "Map contents:" << endl;
    cout << "m1: {Alice=25, Bob=30}" << endl;
    cout << "m2: {Alice=25, Bob=30}" << endl;
    cout << "m3: {Alice=25, Bob=35}" << endl;
    cout << "m4: {Alice=25, Charlie=30}" << endl;
    cout << "m5: {Alice=25}" << endl;
    cout << endl;

    // Equality comparison (==)
    cout << "=== Equality Comparison (==) ===" << endl;
    cout << "m1 == m2: " << (m1 == m2 ? "true" : "false") << " (same keys and values)" << endl;
    cout << "m1 == m3: " << (m1 == m3 ? "true" : "false") << " (different value for Bob)" << endl;
    cout << "m1 == m4: " << (m1 == m4 ? "true" : "false") << " (different second key)" << endl;
    cout << endl;

    // Inequality comparison (!=)
    cout << "=== Inequality Comparison (!=) ===" << endl;
    cout << "m1 != m2: " << (m1 != m2 ? "true" : "false") << endl;
    cout << "m1 != m3: " << (m1 != m3 ? "true" : "false") << endl;
    cout << "m1 != m5: " << (m1 != m5 ? "true" : "false") << " (different sizes)" << endl;
    cout << endl;

    // Less than (<)
    cout << "=== Less Than (<) ===" << endl;
    cout << "m1 < m3: " << (m1 < m3 ? "true" : "false") << " (30 < 35 for Bob)" << endl;
    cout << "m1 < m4: " << (m1 < m4 ? "true" : "false") << " (Bob < Charlie)" << endl;
    cout << "m5 < m1: " << (m5 < m1 ? "true" : "false") << " (shorter map, prefix matches)" << endl;
    cout << "m1 < m5: " << (m1 < m5 ? "true" : "false") << endl;
    cout << endl;

    // Less than or equal to (<=)
    cout << "=== Less Than or Equal To (<=) ===" << endl;
    cout << "m1 <= m2: " << (m1 <= m2 ? "true" : "false") << " (equal)" << endl;
    cout << "m1 <= m3: " << (m1 <= m3 ? "true" : "false") << " (less)" << endl;
    cout << "m3 <= m1: " << (m3 <= m1 ? "true" : "false") << endl;
    cout << endl;

    // Greater than (>)
    cout << "=== Greater Than (>) ===" << endl;
    cout << "m3 > m1: " << (m3 > m1 ? "true" : "false") << " (35 > 30 for Bob)" << endl;
    cout << "m4 > m1: " << (m4 > m1 ? "true" : "false") << " (Charlie > Bob)" << endl;
    cout << "m1 > m5: " << (m1 > m5 ? "true" : "false") << " (longer map, prefix matches)" << endl;
    cout << endl;

    // Greater than or equal to (>=)
    cout << "=== Greater Than or Equal To (>=) ===" << endl;
    cout << "m1 >= m2: " << (m1 >= m2 ? "true" : "false") << " (equal)" << endl;
    cout << "m3 >= m1: " << (m3 >= m1 ? "true" : "false") << " (greater)" << endl;
    cout << "m1 >= m3: " << (m1 >= m3 ? "true" : "false") << endl;
    cout << endl;

    // Numeric keys comparison
    cout << "=== Numeric Keys Comparison ===" << endl;
    map<int, string> n1 = {{1, "A"}, {2, "B"}};
    map<int, string> n2 = {{1, "A"}, {3, "C"}};
    map<int, string> n3 = {{1, "A"}, {2, "B"}};

    cout << "n1 = {{1, A}, {2, B}}" << endl;
    cout << "n2 = {{1, A}, {3, C}}" << endl;
    cout << "n3 = {{1, A}, {2, B}}" << endl;
    cout << endl;

    cout << "n1 == n3: " << (n1 == n3 ? "true" : "false") << endl;
    cout << "n1 < n2: " << (n1 < n2 ? "true" : "false") << " (2 < 3)" << endl;
    cout << "n2 > n1: " << (n2 > n1 ? "true" : "false") << " (3 > 2)" << endl;
    cout << endl;

    // Value comparison with same keys
    cout << "=== Same Keys, Different Values ===" << endl;
    map<string, int> v1 = {{"X", 10}, {"Y", 20}};
    map<string, int> v2 = {{"X", 10}, {"Y", 25}};
    map<string, int> v3 = {{"X", 15}, {"Y", 20}};

    cout << "v1 = {{X, 10}, {Y, 20}}" << endl;
    cout << "v2 = {{X, 10}, {Y, 25}}" << endl;
    cout << "v3 = {{X, 15}, {Y, 20}}" << endl;
    cout << endl;

    cout << "v1 < v2: " << (v1 < v2 ? "true" : "false") << " (20 < 25 for Y)" << endl;
    cout << "v1 < v3: " << (v1 < v3 ? "true" : "false") << " (10 < 15 for X)" << endl;
    cout << "v2 > v1: " << (v2 > v1 ? "true" : "false") << endl;
    cout << "v3 > v1: " << (v3 > v1 ? "true" : "false") << endl;

    return 0;
}
