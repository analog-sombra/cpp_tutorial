/*
### Array Comparison Operators

### arr1 == arr2
- compares two arrays for equality.
- returns true if all corresponding elements are equal.
- returns false otherwise.
- both arrays must have the same size and type.

syntax:
    arr1 == arr2;

example:
    array<int, 3> arr1 = {1, 2, 3};
    array<int, 3> arr2 = {1, 2, 3};
    if (arr1 == arr2) { cout << "Equal"; }


### arr1 != arr2
- compares two arrays for inequality.
- returns true if any element is different.
- returns false if they are equal.

syntax:
    arr1 != arr2;

example:
    array<int, 3> arr1 = {1, 2, 3};
    array<int, 3> arr2 = {1, 2, 4};
    if (arr1 != arr2) { cout << "Not equal"; }


### arr1 < arr2
- lexicographical comparison (dictionary order).
- compares element by element from left to right.
- returns true if arr1 is lexicographically less than arr2.

syntax:
    arr1 < arr2;

example:
    array<int, 3> arr1 = {1, 2, 3};
    array<int, 3> arr2 = {1, 2, 4};
    if (arr1 < arr2) { cout << "arr1 is less than arr2"; }


### arr1 <= arr2
- lexicographical comparison.
- returns true if arr1 is less than or equal to arr2.

syntax:
    arr1 <= arr2;

example:
    array<int, 3> arr1 = {1, 2, 3};
    array<int, 3> arr2 = {1, 2, 3};
    if (arr1 <= arr2) { cout << "arr1 is less than or equal to arr2"; }


### arr1 > arr2
- lexicographical comparison.
- returns true if arr1 is lexicographically greater than arr2.

syntax:
    arr1 > arr2;

example:
    array<int, 3> arr1 = {1, 3, 3};
    array<int, 3> arr2 = {1, 2, 4};
    if (arr1 > arr2) { cout << "arr1 is greater than arr2"; }


### arr1 >= arr2
- lexicographical comparison.
- returns true if arr1 is greater than or equal to arr2.

syntax:
    arr1 >= arr2;

example:
    array<int, 3> arr1 = {1, 2, 3};
    array<int, 3> arr2 = {1, 2, 3};
    if (arr1 >= arr2) { cout << "arr1 is greater than or equal to arr2"; }


Note: Lexicographical comparison works like dictionary ordering:
- Compare first elements, if different, return result
- If same, compare second elements, and so on
- All arrays being compared must have the same size
*/

#include <iostream>
#include <array>

using namespace std;

int main()
{
    array<int, 3> arr1 = {1, 2, 3};
    array<int, 3> arr2 = {1, 2, 3};
    array<int, 3> arr3 = {1, 2, 4};
    array<int, 3> arr4 = {1, 3, 2};
    array<int, 3> arr5 = {0, 5, 5};

    cout << "arr1 = {1, 2, 3}" << endl;
    cout << "arr2 = {1, 2, 3}" << endl;
    cout << "arr3 = {1, 2, 4}" << endl;
    cout << "arr4 = {1, 3, 2}" << endl;
    cout << "arr5 = {0, 5, 5}" << endl;
    cout << endl;

    // Equality comparison (==)
    cout << "=== Equality Comparison (==) ===" << endl;
    cout << "arr1 == arr2: " << (arr1 == arr2 ? "true" : "false") << endl;
    cout << "arr1 == arr3: " << (arr1 == arr3 ? "true" : "false") << endl;
    cout << endl;

    // Inequality comparison (!=)
    cout << "=== Inequality Comparison (!=) ===" << endl;
    cout << "arr1 != arr2: " << (arr1 != arr2 ? "true" : "false") << endl;
    cout << "arr1 != arr3: " << (arr1 != arr3 ? "true" : "false") << endl;
    cout << endl;

    // Less than (<)
    cout << "=== Less Than (<) ===" << endl;
    cout << "arr1 < arr3: " << (arr1 < arr3 ? "true" : "false") << " (3 < 4 at index 2)" << endl;
    cout << "arr1 < arr4: " << (arr1 < arr4 ? "true" : "false") << " (2 < 3 at index 1)" << endl;
    cout << "arr5 < arr1: " << (arr5 < arr1 ? "true" : "false") << " (0 < 1 at index 0)" << endl;
    cout << "arr1 < arr5: " << (arr1 < arr5 ? "true" : "false") << endl;
    cout << endl;

    // Less than or equal to (<=)
    cout << "=== Less Than or Equal To (<=) ===" << endl;
    cout << "arr1 <= arr2: " << (arr1 <= arr2 ? "true" : "false") << " (equal)" << endl;
    cout << "arr1 <= arr3: " << (arr1 <= arr3 ? "true" : "false") << " (less)" << endl;
    cout << "arr3 <= arr1: " << (arr3 <= arr1 ? "true" : "false") << endl;
    cout << endl;

    // Greater than (>)
    cout << "=== Greater Than (>) ===" << endl;
    cout << "arr3 > arr1: " << (arr3 > arr1 ? "true" : "false") << " (4 > 3 at index 2)" << endl;
    cout << "arr4 > arr1: " << (arr4 > arr1 ? "true" : "false") << " (3 > 2 at index 1)" << endl;
    cout << "arr1 > arr5: " << (arr1 > arr5 ? "true" : "false") << " (1 > 0 at index 0)" << endl;
    cout << endl;

    // Greater than or equal to (>=)
    cout << "=== Greater Than or Equal To (>=) ===" << endl;
    cout << "arr1 >= arr2: " << (arr1 >= arr2 ? "true" : "false") << " (equal)" << endl;
    cout << "arr3 >= arr1: " << (arr3 >= arr1 ? "true" : "false") << " (greater)" << endl;
    cout << "arr1 >= arr3: " << (arr1 >= arr3 ? "true" : "false") << endl;
    cout << endl;

    // Demonstrating lexicographical ordering
    cout << "=== Lexicographical Order ===" << endl;
    cout << "{0, 5, 5} < {1, 2, 3}: " << (arr5 < arr1 ? "true" : "false") << endl;
    cout << "{1, 2, 3} < {1, 2, 4}: " << (arr1 < arr3 ? "true" : "false") << endl;
    cout << "{1, 2, 3} < {1, 3, 2}: " << (arr1 < arr4 ? "true" : "false") << endl;

    return 0;
}
