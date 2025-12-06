/*
### Pointer Arithmetic

### What is Pointer Arithmetic?
- Operations that can be performed on pointers.
- Pointers can be incremented, decremented, added, or subtracted.
- Arithmetic operations move the pointer by multiples of the pointed type's size.

### Pointer Increment (++)
- Moves pointer to the next element.
- Increments by sizeof(type), not by 1 byte.

syntax:
    ptr++;              // Post-increment
    ++ptr;              // Pre-increment

example:
    int arr[] = {10, 20, 30};
    int* ptr = arr;
    ptr++;              // Now points to arr[1]


### Pointer Decrement (--)
- Moves pointer to the previous element.
- Decrements by sizeof(type).

syntax:
    ptr--;              // Post-decrement
    --ptr;              // Pre-decrement


### Pointer Addition
- Add an integer to a pointer to move it forward.

syntax:
    ptr + n             // Points n elements forward
    ptr += n            // Move ptr forward by n elements

example:
    int* ptr = arr;
    ptr = ptr + 2;      // Points to arr[2]


### Pointer Subtraction
- Subtract an integer to move pointer backward.
- Subtract two pointers to get distance between them.

syntax:
    ptr - n             // Points n elements backward
    ptr -= n            // Move ptr backward by n elements
    ptr1 - ptr2         // Distance between pointers (in elements)


### Pointer Comparison
- Compare positions of two pointers.
- Can use: ==, !=, <, >, <=, >=

syntax:
    ptr1 < ptr2         // ptr1 is before ptr2?
    ptr1 == ptr2        // Same location?


### Array Access via Pointer Arithmetic
- ptr[i] is equivalent to *(ptr + i)
- Array name is a pointer to its first element

syntax:
    arr[i] ≡ *(arr + i)
    ptr[i] ≡ *(ptr + i)


### Important Notes:
- Can only perform arithmetic on pointers of the same type
- Cannot add two pointers (ptr1 + ptr2 is invalid)
- Pointer arithmetic depends on the size of the type
- Moving beyond array bounds is undefined behavior

*/

#include <iostream>

using namespace std;

int main()
{
    cout << "=== Pointer Size and Type Matters ===" << endl;
    int intArr[] = {10, 20, 30, 40, 50};
    double doubleArr[] = {1.1, 2.2, 3.3, 4.4, 5.5};

    int* intPtr = intArr;
    double* doublePtr = doubleArr;

    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of double: " << sizeof(double) << " bytes" << endl;
    cout << endl;

    cout << "intPtr address: " << intPtr << endl;
    cout << "intPtr + 1 address: " << (intPtr + 1) << endl;
    cout << "Difference: " << (char*)(intPtr + 1) - (char*)intPtr << " bytes" << endl;
    cout << endl;

    cout << "doublePtr address: " << doublePtr << endl;
    cout << "doublePtr + 1 address: " << (doublePtr + 1) << endl;
    cout << "Difference: " << (char*)(doublePtr + 1) - (char*)doublePtr << " bytes" << endl;
    cout << endl;

    cout << "=== Pointer Increment (++) ===" << endl;
    int numbers[] = {100, 200, 300, 400, 500};
    int* ptr = numbers;

    cout << "Initial: ptr points to " << *ptr << endl;
    
    ptr++;
    cout << "After ptr++: ptr points to " << *ptr << endl;
    
    ++ptr;
    cout << "After ++ptr: ptr points to " << *ptr << endl;
    cout << endl;

    cout << "=== Pointer Decrement (--) ===" << endl;
    ptr--;
    cout << "After ptr--: ptr points to " << *ptr << endl;
    
    --ptr;
    cout << "After --ptr: ptr points to " << *ptr << endl;
    cout << endl;

    cout << "=== Pointer Addition ===" << endl;
    int data[] = {11, 22, 33, 44, 55, 66, 77};
    int* p = data;

    cout << "p points to: " << *p << " (data[0])" << endl;
    cout << "*(p + 1): " << *(p + 1) << " (data[1])" << endl;
    cout << "*(p + 2): " << *(p + 2) << " (data[2])" << endl;
    cout << "*(p + 3): " << *(p + 3) << " (data[3])" << endl;
    cout << endl;

    p = p + 3;
    cout << "After p = p + 3:" << endl;
    cout << "*p: " << *p << " (now points to data[3])" << endl;
    cout << endl;

    cout << "=== Pointer Subtraction ===" << endl;
    p = p - 2;
    cout << "After p = p - 2:" << endl;
    cout << "*p: " << *p << " (now points to data[1])" << endl;
    cout << endl;

    cout << "=== Distance Between Pointers ===" << endl;
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* start = array;
    int* end = array + 9;

    cout << "start points to: " << *start << " at " << start << endl;
    cout << "end points to: " << *end << " at " << end << endl;
    cout << "Distance (end - start): " << (end - start) << " elements" << endl;
    cout << "Memory difference: " << (char*)end - (char*)start << " bytes" << endl;
    cout << endl;

    cout << "=== Pointer Comparison ===" << endl;
    int values[] = {10, 20, 30, 40, 50};
    int* p1 = values;
    int* p2 = values + 2;
    int* p3 = values + 4;

    cout << "p1 points to: " << *p1 << endl;
    cout << "p2 points to: " << *p2 << endl;
    cout << "p3 points to: " << *p3 << endl;
    cout << endl;

    cout << "p1 < p2: " << (p1 < p2 ? "true" : "false") << endl;
    cout << "p2 < p3: " << (p2 < p3 ? "true" : "false") << endl;
    cout << "p1 == values: " << (p1 == values ? "true" : "false") << endl;
    cout << endl;

    cout << "=== Traversing Array with Pointer ===" << endl;
    int sequence[] = {5, 10, 15, 20, 25, 30};
    int size = sizeof(sequence) / sizeof(sequence[0]);
    int* traverse = sequence;

    cout << "Using pointer increment:" << endl;
    for (int i = 0; i < size; ++i)
    {
        cout << "  Element " << i << ": " << *traverse << endl;
        traverse++;
    }
    cout << endl;

    cout << "=== Array Access: ptr[i] vs *(ptr + i) ===" << endl;
    int nums[] = {100, 200, 300, 400, 500};
    int* numPtr = nums;

    cout << "Using array notation:" << endl;
    for (int i = 0; i < 5; ++i)
    {
        cout << "  numPtr[" << i << "] = " << numPtr[i] << endl;
    }
    cout << endl;

    cout << "Using pointer arithmetic:" << endl;
    for (int i = 0; i < 5; ++i)
    {
        cout << "  *(numPtr + " << i << ") = " << *(numPtr + i) << endl;
    }
    cout << "Both methods are equivalent!" << endl;
    cout << endl;

    cout << "=== Pointer Arithmetic in Loops ===" << endl;
    double prices[] = {19.99, 29.99, 39.99, 49.99, 59.99};
    double* pricePtr = prices;
    double* endPtr = prices + 5;

    cout << "Forward iteration:" << endl;
    while (pricePtr < endPtr)
    {
        cout << "  $" << *pricePtr << endl;
        pricePtr++;
    }
    cout << endl;

    cout << "Backward iteration:" << endl;
    pricePtr = prices + 4;  // Point to last element
    while (pricePtr >= prices)
    {
        cout << "  $" << *pricePtr << endl;
        pricePtr--;
    }
    cout << endl;

    cout << "=== Compound Assignment Operators ===" << endl;
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int* aPtr = arr;

    cout << "Initial: *aPtr = " << *aPtr << endl;
    
    aPtr += 3;
    cout << "After aPtr += 3: *aPtr = " << *aPtr << endl;
    
    aPtr -= 1;
    cout << "After aPtr -= 1: *aPtr = " << *aPtr << endl;
    cout << endl;

    cout << "=== Pointer Arithmetic vs Array Indexing Performance ===" << endl;
    cout << "Both are equally efficient in modern compilers" << endl;
    cout << "Pointer arithmetic: *(ptr + i)" << endl;
    cout << "Array indexing: arr[i]" << endl;
    cout << "Use whichever is more readable for your code" << endl;
    cout << endl;

    cout << "=== Important Rules ===" << endl;
    cout << "1. ptr++ moves by sizeof(type) bytes" << endl;
    cout << "2. Can subtract pointers: end - start" << endl;
    cout << "3. Cannot add pointers: ptr1 + ptr2 (invalid)" << endl;
    cout << "4. Pointer arithmetic only for arrays or dynamically allocated memory" << endl;
    cout << "5. Going out of bounds is undefined behavior" << endl;

    return 0;
}
