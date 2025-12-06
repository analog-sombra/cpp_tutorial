/*
### Pointer Operations

### Address-of Operator (&)
- Returns the memory address of a variable.
- Used to obtain the address to assign to a pointer.

syntax:
    &variable_name

example:
    int x = 10;
    int* ptr = &x;


### Dereference Operator (*)
- Accesses or modifies the value at the address stored in a pointer.
- Also called "indirection operator".

syntax:
    *pointer_name

example:
    int x = 10;
    int* ptr = &x;
    cout << *ptr;       // Access value (10)
    *ptr = 20;          // Modify value


### Null Pointer Checks
- Always check if pointer is null before dereferencing.
- Prevents undefined behavior and crashes.

syntax:
    if (ptr != nullptr) {
        // Safe to use *ptr
    }

example:
    int* ptr = nullptr;
    if (ptr) {          // Shorthand for ptr != nullptr
        cout << *ptr;
    }


### Pointer Comparison
- Compare if two pointers point to the same address.
- Can use ==, !=, <, >, <=, >= operators.

syntax:
    ptr1 == ptr2        // Same address?
    ptr1 != ptr2        // Different address?

example:
    int x = 10;
    int* p1 = &x;
    int* p2 = &x;
    if (p1 == p2) {
        cout << "Same address";
    }


### const Pointers
- Pointer to const: Cannot modify the value
- const pointer: Cannot change the address
- const pointer to const: Both restrictions

syntax:
    const int* ptr;         // Pointer to const int (can't modify value)
    int* const ptr;         // const pointer to int (can't change address)
    const int* const ptr;   // const pointer to const int


### void Pointers
- Generic pointer that can point to any data type.
- Must be cast to appropriate type before dereferencing.

syntax:
    void* ptr;

example:
    int x = 10;
    void* ptr = &x;
    cout << *(static_cast<int*>(ptr));  // Must cast to int*


### Pointer to const vs const Pointer
- Read declarations from right to left.
- "ptr is a const pointer to int" vs "ptr is a pointer to const int"

*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "=== Address-of Operator (&) ===" << endl;
    int num = 42;
    double pi = 3.14159;
    string text = "Hello";

    cout << "num value: " << num << ", address: " << &num << endl;
    cout << "pi value: " << pi << ", address: " << &pi << endl;
    cout << "text value: " << text << ", address: " << &text << endl;
    cout << endl;

    cout << "=== Dereference Operator (*) ===" << endl;
    int value = 100;
    int* ptr = &value;

    cout << "value: " << value << endl;
    cout << "ptr stores address: " << ptr << endl;
    cout << "*ptr (dereference): " << *ptr << endl;
    cout << endl;

    cout << "Modifying value through pointer:" << endl;
    *ptr = 200;
    cout << "After *ptr = 200:" << endl;
    cout << "value: " << value << endl;
    cout << "*ptr: " << *ptr << endl;
    cout << endl;

    cout << "=== Null Pointer Checks ===" << endl;
    int* nullPtr = nullptr;
    int* validPtr = &value;

    cout << "Checking nullPtr:" << endl;
    if (nullPtr == nullptr)
    {
        cout << "  nullPtr is null - cannot dereference!" << endl;
    }
    else
    {
        cout << "  nullPtr is valid: " << *nullPtr << endl;
    }

    cout << "\nChecking validPtr:" << endl;
    if (validPtr != nullptr)
    {
        cout << "  validPtr is valid: " << *validPtr << endl;
    }
    else
    {
        cout << "  validPtr is null" << endl;
    }
    cout << endl;

    cout << "=== Shorthand Null Check ===" << endl;
    int* p1 = nullptr;
    int* p2 = &value;

    if (!p1)
    {
        cout << "p1 is null (using !p1)" << endl;
    }

    if (p2)
    {
        cout << "p2 is not null (using if(p2)), value: " << *p2 << endl;
    }
    cout << endl;

    cout << "=== Pointer Comparison ===" << endl;
    int x = 10, y = 20;
    int* px1 = &x;
    int* px2 = &x;
    int* py = &y;

    cout << "px1 points to x: " << px1 << endl;
    cout << "px2 points to x: " << px2 << endl;
    cout << "py points to y: " << py << endl;
    cout << endl;

    if (px1 == px2)
    {
        cout << "px1 == px2: true (both point to x)" << endl;
    }

    if (px1 != py)
    {
        cout << "px1 != py: true (point to different variables)" << endl;
    }
    cout << endl;

    cout << "=== Pointer to const (cannot modify value) ===" << endl;
    int data = 50;
    const int* constPtr = &data;

    cout << "data: " << data << endl;
    cout << "*constPtr: " << *constPtr << endl;

    // *constPtr = 100;  // ERROR: Cannot modify value through const pointer
    data = 100;          // OK: Can modify variable directly
    cout << "After data = 100:" << endl;
    cout << "*constPtr: " << *constPtr << endl;

    int data2 = 999;
    constPtr = &data2;   // OK: Can change what the pointer points to
    cout << "After constPtr = &data2:" << endl;
    cout << "*constPtr: " << *constPtr << endl;
    cout << endl;

    cout << "=== const Pointer (cannot change address) ===" << endl;
    int val1 = 111;
    int val2 = 222;
    int* const constAddress = &val1;

    cout << "*constAddress: " << *constAddress << endl;

    *constAddress = 333;  // OK: Can modify value
    cout << "After *constAddress = 333:" << endl;
    cout << "val1: " << val1 << endl;

    // constAddress = &val2;  // ERROR: Cannot change address
    cout << endl;

    cout << "=== const Pointer to const (both restrictions) ===" << endl;
    int readonly = 777;
    const int* const fullyConst = &readonly;

    cout << "*fullyConst: " << *fullyConst << endl;
    // *fullyConst = 888;        // ERROR: Cannot modify value
    // fullyConst = &data;       // ERROR: Cannot change address
    cout << "Cannot modify value or change address" << endl;
    cout << endl;

    cout << "=== void Pointers (Generic Pointers) ===" << endl;
    int intVal = 42;
    double doubleVal = 3.14;

    void* voidPtr;

    voidPtr = &intVal;
    cout << "void pointer to int: " << *(static_cast<int*>(voidPtr)) << endl;

    voidPtr = &doubleVal;
    cout << "void pointer to double: " << *(static_cast<double*>(voidPtr)) << endl;
    cout << "void* can point to any type, but needs casting to dereference" << endl;
    cout << endl;

    cout << "=== Pointer Validity Check Pattern ===" << endl;
    int* safePtr = new int(500);

    if (safePtr)
    {
        cout << "Pointer is valid" << endl;
        cout << "Value: " << *safePtr << endl;
        delete safePtr;
        safePtr = nullptr;  // Good practice after delete
    }

    if (!safePtr)
    {
        cout << "Pointer is now null after delete" << endl;
    }
    cout << endl;

    cout << "=== Reading Pointer Declarations ===" << endl;
    cout << "int* ptr;              // ptr is a pointer to int" << endl;
    cout << "const int* ptr;        // ptr is a pointer to const int" << endl;
    cout << "int* const ptr;        // ptr is a const pointer to int" << endl;
    cout << "const int* const ptr;  // ptr is a const pointer to const int" << endl;
    cout << endl;

    cout << "=== Pointer Assignment ===" << endl;
    int a = 10, b = 20;
    int* ptr1 = &a;
    int* ptr2;

    cout << "Before assignment:" << endl;
    cout << "*ptr1: " << *ptr1 << endl;

    ptr2 = ptr1;  // Copy address (both point to a)
    cout << "\nAfter ptr2 = ptr1:" << endl;
    cout << "*ptr1: " << *ptr1 << endl;
    cout << "*ptr2: " << *ptr2 << endl;
    cout << "Both pointers point to the same location" << endl;

    *ptr2 = 99;
    cout << "\nAfter *ptr2 = 99:" << endl;
    cout << "a: " << a << endl;
    cout << "*ptr1: " << *ptr1 << endl;
    cout << "*ptr2: " << *ptr2 << endl;

    return 0;
}
