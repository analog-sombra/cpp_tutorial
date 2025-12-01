/*
### Vector Comparison Operators

### v1 == v2
- compares two vectors for equality.
- returns true if they have the same size and all corresponding elements are equal.
- returns false otherwise.

syntax:
    v1 == v2;

example:
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 3};
    if (v1 == v2) { cout << "Equal"; }


### v1 != v2
- compares two vectors for inequality.
- returns true if they differ in size or any element is different.
- returns false if they are equal.

syntax:
    v1 != v2;

example:
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 4};
    if (v1 != v2) { cout << "Not equal"; }


### v1 < v2
- lexicographical comparison (dictionary order).
- compares element by element from left to right.
- returns true if v1 is lexicographically less than v2.

syntax:
    v1 < v2;

example:
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 4};
    if (v1 < v2) { cout << "v1 is less than v2"; }


### v1 <= v2
- lexicographical comparison.
- returns true if v1 is less than or equal to v2.

syntax:
    v1 <= v2;

example:
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 3};
    if (v1 <= v2) { cout << "v1 is less than or equal to v2"; }


### v1 > v2
- lexicographical comparison.
- returns true if v1 is lexicographically greater than v2.

syntax:
    v1 > v2;

example:
    vector<int> v1 = {1, 3, 3};
    vector<int> v2 = {1, 2, 4};
    if (v1 > v2) { cout << "v1 is greater than v2"; }


### v1 >= v2
- lexicographical comparison.
- returns true if v1 is greater than or equal to v2.

syntax:
    v1 >= v2;

example:
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 3};
    if (v1 >= v2) { cout << "v1 is greater than or equal to v2"; }


Note: Lexicographical comparison works like dictionary ordering:
- Compare first elements, if different, return result
- If same, compare second elements, and so on
- Shorter vector is less if all elements match
*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 3};
    vector<int> v3 = {1, 2, 4};
    vector<int> v4 = {1, 3, 2};
    vector<int> v5 = {1, 2};

    cout << "v1 = {1, 2, 3}" << endl;
    cout << "v2 = {1, 2, 3}" << endl;
    cout << "v3 = {1, 2, 4}" << endl;
    cout << "v4 = {1, 3, 2}" << endl;
    cout << "v5 = {1, 2}" << endl;
    cout << endl;

    // Equality comparison (==)
    cout << "=== Equality Comparison (==) ===" << endl;
    cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << endl;
    cout << "v1 == v3: " << (v1 == v3 ? "true" : "false") << endl;
    cout << endl;

    // Inequality comparison (!=)
    cout << "=== Inequality Comparison (!=) ===" << endl;
    cout << "v1 != v2: " << (v1 != v2 ? "true" : "false") << endl;
    cout << "v1 != v3: " << (v1 != v3 ? "true" : "false") << endl;
    cout << endl;

    // Less than (<)
    cout << "=== Less Than (<) ===" << endl;
    cout << "v1 < v3: " << (v1 < v3 ? "true" : "false") << " (3 < 4)" << endl;
    cout << "v1 < v4: " << (v1 < v4 ? "true" : "false") << " (2 < 3 at index 1)" << endl;
    cout << "v5 < v1: " << (v5 < v1 ? "true" : "false") << " (shorter is less if prefix matches)" << endl;
    cout << "v1 < v5: " << (v1 < v5 ? "true" : "false") << endl;
    cout << endl;

    // Less than or equal to (<=)
    cout << "=== Less Than or Equal To (<=) ===" << endl;
    cout << "v1 <= v2: " << (v1 <= v2 ? "true" : "false") << " (equal)" << endl;
    cout << "v1 <= v3: " << (v1 <= v3 ? "true" : "false") << " (less)" << endl;
    cout << "v3 <= v1: " << (v3 <= v1 ? "true" : "false") << endl;
    cout << endl;

    // Greater than (>)
    cout << "=== Greater Than (>) ===" << endl;
    cout << "v3 > v1: " << (v3 > v1 ? "true" : "false") << " (4 > 3)" << endl;
    cout << "v4 > v1: " << (v4 > v1 ? "true" : "false") << " (3 > 2 at index 1)" << endl;
    cout << "v1 > v5: " << (v1 > v5 ? "true" : "false") << " (longer is greater if prefix matches)" << endl;
    cout << endl;

    // Greater than or equal to (>=)
    cout << "=== Greater Than or Equal To (>=) ===" << endl;
    cout << "v1 >= v2: " << (v1 >= v2 ? "true" : "false") << " (equal)" << endl;
    cout << "v3 >= v1: " << (v3 >= v1 ? "true" : "false") << " (greater)" << endl;
    cout << "v1 >= v3: " << (v1 >= v3 ? "true" : "false") << endl;
    cout << endl;

    // Demonstrating lexicographical ordering
    cout << "=== Lexicographical Order ===" << endl;
    cout << "{1, 2} < {1, 2, 3}: " << (v5 < v1 ? "true" : "false") << endl;
    cout << "{1, 2, 3} < {1, 2, 4}: " << (v1 < v3 ? "true" : "false") << endl;
    cout << "{1, 2, 3} < {1, 3, 2}: " << (v1 < v4 ? "true" : "false") << endl;

    return 0;
}
