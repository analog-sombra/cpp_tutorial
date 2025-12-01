/*
### Array Functions

### arr.fill() operation
- fills the entire array with a specified value.
- sets all elements to the same value.

syntax:
    arr.fill(value);
    - arr is the name of the array.
    - value is the value to fill the array with.

example:
    array<int, 5> numbers;
    numbers.fill(10); // All elements become 10


### arr.swap() operation
- swaps the contents of two arrays.
- both arrays must have the same type and size.
- efficient swap operation.

syntax:
    arr1.swap(arr2);
    - arr1 and arr2 are the names of the arrays.

example:
    array<int, 3> arr1 = {1, 2, 3};
    array<int, 3> arr2 = {4, 5, 6};
    arr1.swap(arr2); // arr1 becomes {4, 5, 6}, arr2 becomes {1, 2, 3}


### arr.data() operation
- returns a pointer to the underlying array serving as element storage.
- useful for interfacing with C-style APIs.

syntax:
    arr.data();
    - arr is the name of the array.

example:
    array<int, 5> numbers = {1, 2, 3, 4, 5};
    int* ptr = numbers.data();
    cout << "First element via pointer: " << *ptr << endl;


### std::swap() operation
- non-member swap function for arrays.
- can be used alternatively to arr.swap().

syntax:
    std::swap(arr1, arr2);
    - arr1 and arr2 are the names of the arrays.

example:
    array<int, 3> arr1 = {1, 2, 3};
    array<int, 3> arr2 = {4, 5, 6};
    swap(arr1, arr2);


### std::get<N>(arr) operation
- accesses element at compile-time constant index N.
- index must be a compile-time constant.
- provides bounds checking at compile time.

syntax:
    std::get<N>(arr);
    - N is the compile-time constant index.
    - arr is the name of the array.

example:
    array<int, 5> numbers = {1, 2, 3, 4, 5};
    int third = get<2>(numbers); // Gets element at index 2


### iterators: begin(), end(), rbegin(), rend()
- begin(): returns iterator to the first element.
- end(): returns iterator to one past the last element.
- rbegin(): returns reverse iterator to the last element.
- rend(): returns reverse iterator to one before the first element.

syntax:
    arr.begin();
    arr.end();
    arr.rbegin();
    arr.rend();

example:
    array<int, 5> numbers = {1, 2, 3, 4, 5};
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }

*/

#include <iostream>
#include <array>
#include <algorithm> // for std::swap

using namespace std;

int main()
{
    array<int, 5> numbers = {1, 2, 3, 4, 5};

    cout << "Original array: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;

    // fill() - set all elements to a value
    array<int, 5> filled_array;
    filled_array.fill(99);
    cout << "Array after fill(99): ";
    for (int num : filled_array)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;

    // swap() - swap contents of two arrays
    array<int, 5> arr1 = {10, 20, 30, 40, 50};
    array<int, 5> arr2 = {100, 200, 300, 400, 500};
    
    cout << "Before swap:" << endl;
    cout << "arr1: ";
    for (int num : arr1) { cout << num << " "; }
    cout << endl;
    cout << "arr2: ";
    for (int num : arr2) { cout << num << " "; }
    cout << endl;
    
    arr1.swap(arr2);
    
    cout << "After swap:" << endl;
    cout << "arr1: ";
    for (int num : arr1) { cout << num << " "; }
    cout << endl;
    cout << "arr2: ";
    for (int num : arr2) { cout << num << " "; }
    cout << endl;
    cout << endl;

    // data() - get pointer to underlying array
    int *ptr = numbers.data();
    cout << "Using data() pointer:" << endl;
    cout << "First element: " << *ptr << endl;
    cout << "Second element: " << *(ptr + 1) << endl;
    cout << "Third element: " << *(ptr + 2) << endl;
    cout << endl;

    // std::get<N>() - compile-time element access
    cout << "Using std::get<N>():" << endl;
    cout << "Element at index 0: " << get<0>(numbers) << endl;
    cout << "Element at index 2: " << get<2>(numbers) << endl;
    cout << "Element at index 4: " << get<4>(numbers) << endl;
    cout << endl;

    // Iterators - begin(), end()
    cout << "Using iterators (begin to end):" << endl;
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    cout << endl;

    // Reverse iterators - rbegin(), rend()
    cout << "Using reverse iterators (rbegin to rend):" << endl;
    for (auto it = numbers.rbegin(); it != numbers.rend(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    cout << endl;

    // std::swap (non-member function)
    array<int, 3> x = {1, 2, 3};
    array<int, 3> y = {7, 8, 9};
    
    cout << "Before std::swap:" << endl;
    cout << "x: ";
    for (int num : x) { cout << num << " "; }
    cout << endl;
    cout << "y: ";
    for (int num : y) { cout << num << " "; }
    cout << endl;
    
    swap(x, y); // Using std::swap
    
    cout << "After std::swap:" << endl;
    cout << "x: ";
    for (int num : x) { cout << num << " "; }
    cout << endl;
    cout << "y: ";
    for (int num : y) { cout << num << " "; }
    cout << endl;

    return 0;
}
