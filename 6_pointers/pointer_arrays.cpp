/*
### Pointers and Arrays

### Arrays and Pointers Relationship
- Array name is a constant pointer to the first element.
- Array elements are stored in contiguous memory.
- Can access array elements using pointer notation.

syntax:
    int arr[5];
    int* ptr = arr;         // arr is equivalent to &arr[0]
    arr[i] ≡ *(arr + i)     // Array indexing via pointer arithmetic


### Array Name as Pointer
- Array name decays to a pointer in most contexts.
- Exception: sizeof(arr) gives total array size, not pointer size.

example:
    int arr[5] = {1, 2, 3, 4, 5};
    int* ptr = arr;         // Valid: array name converts to pointer
    // arr = ptr;           // Invalid: cannot assign to array name


### Pointer to Array
- A pointer that points to an entire array.
- Different from pointer to first element.

syntax:
    int (*ptr)[size];       // Pointer to array of size elements

example:
    int arr[5] = {1, 2, 3, 4, 5};
    int (*ptr)[5] = &arr;   // Pointer to entire array


### Array of Pointers
- Array where each element is a pointer.
- Common use: array of strings, dynamic structures.

syntax:
    type* arr[size];        // Array of pointers

example:
    int* arr[3];            // Array of 3 int pointers
    const char* names[3];   // Array of 3 string pointers


### Multidimensional Arrays and Pointers
- 2D array is array of arrays.
- Can access via pointer notation.

syntax:
    int arr[rows][cols];
    int (*ptr)[cols] = arr; // Pointer to array of cols elements


### Passing Arrays to Functions
- Arrays decay to pointers when passed to functions.
- Function receives pointer, not copy of array.

syntax:
    void func(int arr[], int size);      // Array notation
    void func(int* arr, int size);       // Pointer notation (equivalent)


### Array Size and Pointer Difference
- sizeof(array) gives total size in bytes.
- sizeof(pointer) gives size of pointer (typically 4 or 8 bytes).
- Must pass array size separately to functions.


### Important Notes:
- Cannot get array size from pointer alone
- Array name is constant, cannot be reassigned
- Pointer can be reassigned to point elsewhere
- Array subscript arr[i] is syntactic sugar for *(arr + i)

*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "=== Array Name as Pointer ===" << endl;
    int arr[5] = {10, 20, 30, 40, 50};

    cout << "Array name (arr): " << arr << endl;
    cout << "Address of first element (&arr[0]): " << &arr[0] << endl;
    cout << "These addresses are the same!" << endl;
    cout << endl;

    cout << "Accessing via array notation:" << endl;
    cout << "  arr[0] = " << arr[0] << endl;
    cout << "  arr[1] = " << arr[1] << endl;
    cout << endl;

    cout << "Accessing via pointer notation:" << endl;
    cout << "  *arr = " << *arr << endl;
    cout << "  *(arr + 1) = " << *(arr + 1) << endl;
    cout << "Both methods access the same elements!" << endl;
    cout << endl;

    cout << "=== Pointer to First Element vs Array Name ===" << endl;
    int numbers[] = {100, 200, 300, 400, 500};
    int* ptr = numbers;

    cout << "ptr points to: " << *ptr << endl;
    cout << "numbers[0]: " << numbers[0] << endl;
    cout << endl;

    ptr++;
    cout << "After ptr++, ptr points to: " << *ptr << endl;
    // numbers++;  // ERROR: Cannot increment array name (constant pointer)
    cout << "Cannot increment array name (it's constant)" << endl;
    cout << endl;

    cout << "=== sizeof() Difference ===" << endl;
    int data[] = {1, 2, 3, 4, 5};
    int* dataPtr = data;

    cout << "sizeof(data) = " << sizeof(data) << " bytes (entire array)" << endl;
    cout << "sizeof(dataPtr) = " << sizeof(dataPtr) << " bytes (pointer size)" << endl;
    cout << "Array size: " << sizeof(data) / sizeof(data[0]) << " elements" << endl;
    cout << endl;

    cout << "=== Pointer to Array (Entire Array) ===" << endl;
    int arr2[5] = {11, 22, 33, 44, 55};
    int (*ptrToArray)[5] = &arr2;

    cout << "ptrToArray points to entire array at: " << ptrToArray << endl;
    cout << "Dereferencing: *ptrToArray = " << *ptrToArray << endl;
    cout << "This gives address of first element: " << *ptrToArray << endl;
    cout << "Access first element: (*ptrToArray)[0] = " << (*ptrToArray)[0] << endl;
    cout << "Access second element: (*ptrToArray)[1] = " << (*ptrToArray)[1] << endl;
    cout << endl;

    cout << "=== Array of Pointers ===" << endl;
    int a = 10, b = 20, c = 30;
    int* ptrArray[3];

    ptrArray[0] = &a;
    ptrArray[1] = &b;
    ptrArray[2] = &c;

    cout << "ptrArray is an array of 3 int pointers" << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << "  ptrArray[" << i << "] points to address " << ptrArray[i] 
             << " with value " << *ptrArray[i] << endl;
    }
    cout << endl;

    cout << "=== Array of String Pointers ===" << endl;
    const char* names[4] = {
        "Alice",
        "Bob",
        "Charlie",
        "Diana"
    };

    cout << "Names array contains pointers to string literals:" << endl;
    for (int i = 0; i < 4; ++i)
    {
        cout << "  names[" << i << "] = " << names[i] << endl;
    }
    cout << endl;

    cout << "=== Iterating Array with Pointer ===" << endl;
    int values[] = {5, 15, 25, 35, 45, 55};
    int size = sizeof(values) / sizeof(values[0]);

    cout << "Using pointer iteration:" << endl;
    int* p = values;
    for (int i = 0; i < size; ++i)
    {
        cout << "  values[" << i << "] = " << *(p + i) << endl;
    }
    cout << endl;

    cout << "=== 2D Array and Pointers ===" << endl;
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    cout << "matrix is an array of 3 arrays" << endl;
    cout << "matrix[0] is pointer to first row: " << matrix[0] << endl;
    cout << "matrix[1] is pointer to second row: " << matrix[1] << endl;
    cout << endl;

    cout << "Accessing elements:" << endl;
    cout << "  matrix[0][0] = " << matrix[0][0] << endl;
    cout << "  *(matrix[0] + 0) = " << *(matrix[0] + 0) << " (same)" << endl;
    cout << "  matrix[1][2] = " << matrix[1][2] << endl;
    cout << "  *(*(matrix + 1) + 2) = " << *(*(matrix + 1) + 2) << " (same)" << endl;
    cout << endl;

    cout << "=== Pointer to 2D Array ===" << endl;
    int (*ptr2D)[4] = matrix;

    cout << "ptr2D points to rows of matrix" << endl;
    cout << "Accessing via pointer:" << endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << *(*(ptr2D + i) + j) << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "=== Dynamic Array with Pointer ===" << endl;
    int* dynamicArray = new int[5];

    for (int i = 0; i < 5; ++i)
    {
        dynamicArray[i] = (i + 1) * 10;
    }

    cout << "Dynamic array elements:" << endl;
    for (int i = 0; i < 5; ++i)
    {
        cout << "  dynamicArray[" << i << "] = " << dynamicArray[i] << endl;
    }

    delete[] dynamicArray;
    cout << "Memory freed with delete[]" << endl;
    cout << endl;

    cout << "=== Array Decay in Function Calls ===" << endl;
    cout << "When passing array to function:" << endl;
    cout << "  void func(int arr[10])  ->  becomes  ->  void func(int* arr)" << endl;
    cout << "Array size information is lost!" << endl;
    cout << "Always pass size as separate parameter" << endl;
    cout << endl;

    cout << "=== Character Arrays and Pointers ===" << endl;
    char str1[] = "Hello";
    char* str2 = (char*)"World";

    cout << "str1 (array): " << str1 << endl;
    cout << "str2 (pointer): " << str2 << endl;
    cout << endl;

    cout << "str1 is modifiable array:" << endl;
    str1[0] = 'h';
    cout << "  After str1[0] = 'h': " << str1 << endl;
    
    cout << "str2 points to string literal (read-only)" << endl;
    // str2[0] = 'w';  // Undefined behavior (modifying string literal)
    cout << endl;

    cout << "=== Pointer Arithmetic on Character Arrays ===" << endl;
    char text[] = "Programming";
    char* cp = text;

    cout << "Original string: " << text << endl;
    cout << "Starting from position 3: " << (cp + 3) << endl;
    cout << "Characters:" << endl;
    while (*cp != '\0')
    {
        cout << "  " << *cp;
        cp++;
    }
    cout << endl << endl;

    cout << "=== Array vs Pointer Declaration ===" << endl;
    int arr3[5] = {1, 2, 3, 4, 5};
    int* ptr3 = arr3;

    cout << "Array declaration: int arr3[5]" << endl;
    cout << "  - Allocates memory for 5 integers" << endl;
    cout << "  - arr3 is constant (cannot reassign)" << endl;
    cout << "  - sizeof(arr3) = " << sizeof(arr3) << " bytes" << endl;
    cout << endl;

    cout << "Pointer declaration: int* ptr3" << endl;
    cout << "  - Allocates memory for pointer only" << endl;
    cout << "  - ptr3 can be reassigned" << endl;
    cout << "  - sizeof(ptr3) = " << sizeof(ptr3) << " bytes" << endl;
    cout << endl;

    cout << "=== Important Concepts ===" << endl;
    cout << "1. Array name decays to pointer in most contexts" << endl;
    cout << "2. arr[i] is equivalent to *(arr + i)" << endl;
    cout << "3. Cannot get array size from pointer alone" << endl;
    cout << "4. Pointer to array: int (*ptr)[size]" << endl;
    cout << "5. Array of pointers: int* arr[size]" << endl;
    cout << "6. 2D array: array of arrays" << endl;
    cout << "7. Always pass array size to functions" << endl;

    return 0;
}
