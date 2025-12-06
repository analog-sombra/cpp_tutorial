/*
// Array Type
 - Arrays are fixed-size sequential containers that store elements of the same type.
 - Unlike vectors, arrays have a fixed size that is determined at compile time.

Fixed-size arrays:
    - Size is determined at compile time
    - Cannot grow or shrink after declaration
    - More memory efficient than vectors for fixed-size data

Syntax:
    type array_name[size];
    
    Example:
    int numbers[5]; // Creates an array of 5 integers

Array initialization:
    - Direct initialization: int arr[5] = {1, 2, 3, 4, 5};
    - Partial initialization: int arr[5] = {1, 2}; // Rest are 0
    - Size inference: int arr[] = {1, 2, 3}; // Size is 3

Key Differences from Vectors:
    - Arrays: Fixed size, faster access, no dynamic memory allocation
    - Vectors: Dynamic size, slightly slower, automatic memory management

Accessing Elements:
    - Use index operator []: arr[0], arr[1], etc.
    - Use at() method (for std::array): arr.at(0)
    - Index starts at 0

Common Operations:
    - arr[n] - Access element at index n
    - sizeof(arr)/sizeof(arr[0]) - Get array size (for C-style arrays)
    - arr.size() - Get size (for std::array)
*/

#include <iostream>
#include <array> // include the array header for std::array
using namespace std;

int main() {
    // Create a fixed-size array using std::array
    array<int, 5> numbers = {1, 2, 3, 4, 5};

    // Display the elements of the array
    cout << "Array elements: ";
    for(int i: numbers) {
        cout << i << " ";
    }
    cout << endl;

    // Display the size of the array
    cout << "Array size: " << numbers.size() << endl;

    // Accessing elements using at() method (with bounds checking)
    cout << "Element at index 2 using at(): " << numbers.at(2) << endl;

    // Accessing elements using [] operator
    cout << "Element at index 3 using []: " << numbers[3] << endl;

    // Modify an element
    numbers[0] = 10;
    cout << "After modifying first element to 10: ";
    for(int i: numbers) {
        cout << i << " ";
    }
    cout << endl;

    // Check if array is empty
    if(numbers.empty()) {
        cout << "Array is empty" << endl;
    } else {
        cout << "Array is not empty" << endl;
    }

    // Access first and last elements
    cout << "First element: " << numbers.front() << endl;
    cout << "Last element: " << numbers.back() << endl;

    return 0;
}
