/*
### Pointers
- A pointer is a variable that stores the memory address of another variable.
- Pointers allow direct memory manipulation and efficient data handling.

### Memory Address:
- Every variable in memory has an address.
- Address is the location where the variable is stored.
- Memory addresses are typically displayed in hexadecimal format.

### Why Use Pointers?
- Dynamic memory allocation
- Efficient array and string handling
- Pass large data structures efficiently to functions
- Create complex data structures (linked lists, trees)
- Interact with hardware and system resources

### Pointer Declaration:
syntax:
    type* pointer_name;
    type *pointer_name;    // Alternative style
    type * pointer_name;   // Alternative style

examples:
    int* ptr;              // Pointer to int
    double* dptr;          // Pointer to double
    char* cptr;            // Pointer to char
    string* sptr;          // Pointer to string


### Address-of Operator (&):
- Returns the memory address of a variable.
- Used to initialize pointers.

syntax:
    &variable_name

example:
    int x = 10;
    int* ptr = &x;         // ptr now holds the address of x


### Dereference Operator (*):
- Accesses the value at the memory address stored in the pointer.
- Also called "indirection operator".

syntax:
    *pointer_name

example:
    int x = 10;
    int* ptr = &x;
    cout << *ptr;          // Output: 10 (value at address ptr)


### Null Pointer:
- Pointer that doesn't point to any valid memory location.
- Good practice to initialize pointers to nullptr (C++11) or NULL.

syntax:
    int* ptr = nullptr;    // C++11
    int* ptr = NULL;       // Older style
    int* ptr = 0;          // Also valid


### Pointer Size:
- Pointer size depends on the system architecture.
- 32-bit system: 4 bytes
- 64-bit system: 8 bytes
- All pointer types have the same size (regardless of type they point to)

*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "=== What is a Pointer? ===" << endl;
    cout << "A pointer stores the memory address of another variable" << endl;
    cout << endl;

    cout << "=== Memory Addresses ===" << endl;
    int number = 42;
    double pi = 3.14159;
    char letter = 'A';

    cout << "Variable 'number' value: " << number << endl;
    cout << "Variable 'number' address: " << &number << endl;
    cout << endl;

    cout << "Variable 'pi' value: " << pi << endl;
    cout << "Variable 'pi' address: " << &pi << endl;
    cout << endl;

    cout << "Variable 'letter' value: " << letter << endl;
    cout << "Variable 'letter' address: " << static_cast<void*>(&letter) << endl;
    cout << endl;

    cout << "=== Pointer Declaration and Initialization ===" << endl;
    int value = 100;
    int* ptr;              // Declare pointer
    ptr = &value;          // Initialize with address of value

    cout << "Value: " << value << endl;
    cout << "Address of value: " << &value << endl;
    cout << "Pointer ptr stores: " << ptr << endl;
    cout << "Pointer ptr points to the address of value" << endl;
    cout << endl;

    cout << "=== Direct Initialization ===" << endl;
    int x = 50;
    int* xPtr = &x;        // Declare and initialize in one line

    cout << "x = " << x << endl;
    cout << "Address of x = " << &x << endl;
    cout << "xPtr = " << xPtr << endl;
    cout << "xPtr stores the address of x" << endl;
    cout << endl;

    cout << "=== Dereferencing Pointers (*) ===" << endl;
    int num = 25;
    int* numPtr = &num;

    cout << "num = " << num << endl;
    cout << "Address of num (&num) = " << &num << endl;
    cout << "numPtr (address stored) = " << numPtr << endl;
    cout << "*numPtr (value at address) = " << *numPtr << endl;
    cout << endl;

    cout << "=== Modifying Value Through Pointer ===" << endl;
    int data = 10;
    int* dataPtr = &data;

    cout << "Before: data = " << data << endl;
    *dataPtr = 99;         // Change value through pointer
    cout << "After: data = " << data << endl;
    cout << "Changed data to 99 using *dataPtr = 99" << endl;
    cout << endl;

    cout << "=== Multiple Pointers to Same Variable ===" << endl;
    int shared = 777;
    int* ptr1 = &shared;
    int* ptr2 = &shared;

    cout << "shared = " << shared << endl;
    cout << "ptr1 points to: " << ptr1 << ", value: " << *ptr1 << endl;
    cout << "ptr2 points to: " << ptr2 << ", value: " << *ptr2 << endl;

    *ptr1 = 888;
    cout << "\nAfter *ptr1 = 888:" << endl;
    cout << "shared = " << shared << endl;
    cout << "*ptr2 = " << *ptr2 << endl;
    cout << "Both pointers access the same memory location" << endl;
    cout << endl;

    cout << "=== Null Pointers ===" << endl;
    int* nullPtr = nullptr;  // C++11 style

    cout << "nullPtr = " << nullPtr << endl;
    cout << "nullPtr points to nothing (null)" << endl;

    if (nullPtr == nullptr)
    {
        cout << "Pointer is null - safe to check before dereferencing" << endl;
    }

    // Dangerous: Never dereference a null pointer!
    // cout << *nullPtr;  // This would crash the program!
    cout << endl;

    cout << "=== Pointer Size ===" << endl;
    int* intPtr;
    double* doublePtr;
    char* charPtr;
    string* stringPtr;

    cout << "Size of int* pointer: " << sizeof(intPtr) << " bytes" << endl;
    cout << "Size of double* pointer: " << sizeof(doublePtr) << " bytes" << endl;
    cout << "Size of char* pointer: " << sizeof(charPtr) << " bytes" << endl;
    cout << "Size of string* pointer: " << sizeof(stringPtr) << " bytes" << endl;
    cout << "All pointers have the same size (system-dependent)" << endl;
    cout << endl;

    cout << "=== Pointers with Different Types ===" << endl;
    int intVal = 42;
    double doubleVal = 3.14;
    string strVal = "Hello";

    int* intPointer = &intVal;
    double* doublePointer = &doubleVal;
    string* stringPointer = &strVal;

    cout << "int value: " << *intPointer << endl;
    cout << "double value: " << *doublePointer << endl;
    cout << "string value: " << *stringPointer << endl;
    cout << endl;

    cout << "=== Pointer Reassignment ===" << endl;
    int a = 10, b = 20;
    int* p = &a;

    cout << "Initially p points to a:" << endl;
    cout << "a = " << a << ", *p = " << *p << endl;

    p = &b;  // Reassign pointer to different variable
    cout << "\nAfter p = &b:" << endl;
    cout << "b = " << b << ", *p = " << *p << endl;
    cout << "Pointer can be reassigned to point to different variables" << endl;
    cout << endl;

    cout << "=== Key Concepts Summary ===" << endl;
    cout << "1. & (address-of): Gets the memory address of a variable" << endl;
    cout << "2. * (dereference): Accesses the value at a pointer's address" << endl;
    cout << "3. Pointers store memory addresses, not values" << endl;
    cout << "4. Always initialize pointers (nullptr if no target yet)" << endl;
    cout << "5. Check for nullptr before dereferencing" << endl;

    return 0;
}
