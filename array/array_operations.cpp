/*
### Array Operations

### arr.empty() operation
- checks whether the array is empty.
- for std::array with size > 0, always returns false.
- useful for generic programming.

syntax:
    arr.empty();
    - arr is the name of the array.

example:
    array<int, 5> numbers;
    if (numbers.empty()) {
        cout << "The array is empty." << endl;
    }


### arr.size() operation
- returns the number of elements in the array.
- the size is fixed at compile time.
- returns a value of type size_type.

syntax:
    arr.size();
    - arr is the name of the array.

example:
    array<int, 5> numbers = {1, 2, 3, 4, 5};
    cout << "The size of the array is: " << numbers.size() << endl;


### arr[n] operation
- accesses the element at index n of the array.
- no bounds checking (faster but unsafe).

syntax:
    arr[n];
    - arr is the name of the array.
    - n is the index of the element to access (0-based index).

example:
    array<int, 5> numbers = {10, 20, 30, 40, 50};
    cout << "Element at index 2: " << numbers[2] << endl;


### arr.at(n) operation
- accesses the element at index n with bounds checking.
- throws out_of_range exception if index is invalid.
- safer but slightly slower than [].

syntax:
    arr.at(n);
    - arr is the name of the array.
    - n is the index of the element to access.

example:
    array<int, 5> numbers = {10, 20, 30, 40, 50};
    cout << "Element at index 2: " << numbers.at(2) << endl;


### arr1 = arr2
- assigns the contents of array arr2 to array arr1.
- both arrays must have the same size and type.

syntax:
    arr1 = arr2;
    - arr1 and arr2 are the names of the arrays.

example:
    array<int, 3> arr1 = {1, 2, 3};
    array<int, 3> arr2 = {4, 5, 6};
    arr1 = arr2; // Now arr1 contains {4, 5, 6}


### arr1 == arr2
- compares two arrays for equality.
- returns true if all corresponding elements are equal.
- both arrays must have the same size and type.

syntax:
    arr1 == arr2;
    - arr1 and arr2 are the names of the arrays.

example:
    array<int, 3> arr1 = {1, 2, 3};
    array<int, 3> arr2 = {1, 2, 3};
    if (arr1 == arr2) {
        cout << "The arrays are equal." << endl;
    }


### arr.front() operation
- returns a reference to the first element in the array.

syntax:
    arr.front();
    - arr is the name of the array.

example:
    array<int, 5> numbers = {1, 2, 3, 4, 5};
    cout << "First element: " << numbers.front() << endl;


### arr.back() operation
- returns a reference to the last element in the array.

syntax:
    arr.back();
    - arr is the name of the array.

example:
    array<int, 5> numbers = {1, 2, 3, 4, 5};
    cout << "Last element: " << numbers.back() << endl;

*/

#include <iostream>
#include <array>

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

    // Check if the array is empty
    if (numbers.empty())
    {
        cout << "The array is empty." << endl;
    }
    else
    {
        cout << "The array is not empty." << endl;
    }
    cout << endl;

    // Get and print the size of the array
    cout << "The size of the array is: " << numbers.size() << endl;
    cout << endl;

    // Access element using [] operator
    int index = 2;
    cout << "Element at index " << index << " using []: " << numbers[index] << endl;
    cout << endl;

    // Access element using at() method (with bounds checking)
    cout << "Element at index " << index << " using at(): " << numbers.at(index) << endl;
    cout << endl;

    // Access first and last elements
    cout << "First element (front): " << numbers.front() << endl;
    cout << "Last element (back): " << numbers.back() << endl;
    cout << endl;

    // Modify an element
    numbers[0] = 10;
    cout << "After modifying first element to 10: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;

    // Assign contents of one array to another
    array<int, 5> new_numbers = {100, 200, 300, 400, 500};
    numbers = new_numbers;
    cout << "After assignment from new_numbers: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;

    // Compare two arrays for equality
    array<int, 5> compare_array = {100, 200, 300, 400, 500};
    if (numbers == compare_array)
    {
        cout << "The arrays are equal." << endl;
    }
    else
    {
        cout << "The arrays are not equal." << endl;
    }
    cout << endl;

    // Compare with different array
    array<int, 5> different_array = {100, 200, 300, 400, 999};
    if (numbers == different_array)
    {
        cout << "The arrays are equal." << endl;
    }
    else
    {
        cout << "The arrays are not equal." << endl;
    }

    return 0;
}
