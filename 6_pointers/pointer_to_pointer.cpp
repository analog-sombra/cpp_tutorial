/*
### Pointer to Pointer (Double Pointer)

### What is Pointer to Pointer?
- A pointer that stores the address of another pointer.
- Also called double pointer or pointer to pointer.
- Can have multiple levels of indirection.

syntax:
    int** ptr;              // Pointer to pointer to int
    int*** ptr3;            // Pointer to pointer to pointer to int


### Declaration and Initialization
- Use ** for double pointer.
- Must point to address of another pointer.

syntax:
    int x = 10;
    int* ptr = &x;
    int** pptr = &ptr;      // pptr points to ptr


### Dereferencing Double Pointer
- *pptr gives the value of ptr (which is address of x).
- **pptr gives the value of x.

example:
    int x = 10;
    int* ptr = &x;
    int** pptr = &ptr;
    
    *pptr → ptr (address of x)
    **pptr → 10 (value of x)


### Memory Layout Visualization
    pptr    →    ptr    →    x
    [addr]  →   [addr]  →   [10]


### Common Uses:
1. Modifying pointer in function (pass pointer by reference)
2. Dynamic 2D arrays
3. Array of strings (char**)
4. Command line arguments (int main(int argc, char** argv))
5. Linked lists and tree data structures


### Modifying Pointer in Function
- To modify pointer itself (not just value it points to).
- Pass pointer to pointer.

syntax:
    void allocate(int** ptr) {
        *ptr = new int(42);
    }


### Triple Pointers and Beyond
- Can have multiple levels: ***, ****, etc.
- Rarely used beyond double pointers.
- Each * adds one level of indirection.


### Important Notes:
- Each * adds one level of indirection
- Must dereference appropriate number of times
- Common in dynamic 2D arrays
- Used in main() for command line arguments (char** argv)

*/

#include <iostream>
#include <string>

using namespace std;

void allocateMemory(int** ptr)
{
    *ptr = new int(100);
}

void modifyPointer(int** ptr, int* newAddress)
{
    *ptr = newAddress;
}

void swap(int** ptr1, int** ptr2)
{
    int* temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int main()
{
    cout << "=== Basic Pointer to Pointer ===" << endl;
    int x = 42;
    int* ptr = &x;
    int** pptr = &ptr;

    cout << "int x = 42;" << endl;
    cout << "int* ptr = &x;" << endl;
    cout << "int** pptr = &ptr;" << endl;
    cout << endl;

    cout << "Value of x: " << x << endl;
    cout << "Address of x (&x): " << &x << endl;
    cout << endl;

    cout << "Value of ptr: " << ptr << " (address of x)" << endl;
    cout << "Address of ptr (&ptr): " << &ptr << endl;
    cout << endl;

    cout << "Value of pptr: " << pptr << " (address of ptr)" << endl;
    cout << "Address of pptr (&pptr): " << &pptr << endl;
    cout << endl;

    cout << "=== Dereferencing Double Pointer ===" << endl;
    cout << "*pptr (dereference once): " << *pptr << " (value of ptr, which is address of x)" << endl;
    cout << "**pptr (dereference twice): " << **pptr << " (value of x)" << endl;
    cout << endl;

    cout << "=== Memory Layout Visualization ===" << endl;
    cout << "pptr (" << pptr << ") → ptr (" << *pptr << ") → x (" << **pptr << ")" << endl;
    cout << endl;

    cout << "=== Modifying Value Through Double Pointer ===" << endl;
    cout << "Before: x = " << x << endl;
    
    **pptr = 99;
    cout << "After **pptr = 99:" << endl;
    cout << "x = " << x << " (modified through double pointer)" << endl;
    cout << endl;

    cout << "=== Modifying Pointer Through Double Pointer ===" << endl;
    int y = 200;
    cout << "int y = 200;" << endl;
    cout << "Before: ptr points to x (" << x << ")" << endl;
    
    *pptr = &y;
    cout << "After *pptr = &y:" << endl;
    cout << "ptr now points to y (" << *ptr << ")" << endl;
    cout << endl;

    cout << "=== Allocating Memory via Double Pointer ===" << endl;
    int* dynPtr = nullptr;
    cout << "int* dynPtr = nullptr;" << endl;
    cout << "Before allocation: dynPtr = " << dynPtr << endl;
    
    allocateMemory(&dynPtr);
    cout << "After allocateMemory(&dynPtr):" << endl;
    cout << "dynPtr points to: " << *dynPtr << endl;
    
    delete dynPtr;
    cout << "Memory freed" << endl;
    cout << endl;

    cout << "=== Swapping Pointers ===" << endl;
    int a = 10, b = 20;
    int* ptrA = &a;
    int* ptrB = &b;

    cout << "Before swap:" << endl;
    cout << "  ptrA points to: " << *ptrA << endl;
    cout << "  ptrB points to: " << *ptrB << endl;
    
    swap(&ptrA, &ptrB);
    
    cout << "After swap(&ptrA, &ptrB):" << endl;
    cout << "  ptrA points to: " << *ptrA << endl;
    cout << "  ptrB points to: " << *ptrB << endl;
    cout << endl;

    cout << "=== Array of Pointers (Single Pointer) ===" << endl;
    int n1 = 1, n2 = 2, n3 = 3;
    int* ptrArray[3] = {&n1, &n2, &n3};

    cout << "int* ptrArray[3] - array of pointers" << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << "  ptrArray[" << i << "] points to: " << *ptrArray[i] << endl;
    }
    cout << endl;

    cout << "=== Pointer to Array of Pointers (Double Pointer) ===" << endl;
    int** ptrToArray = ptrArray;

    cout << "int** ptrToArray = ptrArray;" << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << "  *(ptrToArray + " << i << ") points to: " << **(ptrToArray + i) << endl;
    }
    cout << endl;

    cout << "=== Dynamic 2D Array with Double Pointer ===" << endl;
    int rows = 3, cols = 4;
    int** matrix = new int*[rows];

    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[cols];
    }

    cout << "Created " << rows << "x" << cols << " matrix" << endl;
    
    // Fill matrix
    int counter = 1;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            matrix[i][j] = counter++;
        }
    }

    cout << "Matrix contents:" << endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    // Free memory
    for (int i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    cout << "Matrix memory freed" << endl;
    cout << endl;

    cout << "=== Array of Strings (char**) ===" << endl;
    const char* names[] = {
        "Alice",
        "Bob",
        "Charlie",
        "Diana"
    };

    const char** namePtr = names;

    cout << "const char* names[] - array of string pointers" << endl;
    cout << "const char** namePtr = names;" << endl;
    cout << endl;

    for (int i = 0; i < 4; ++i)
    {
        cout << "  *(namePtr + " << i << ") = " << *(namePtr + i) << endl;
    }
    cout << endl;

    cout << "=== Command Line Arguments Simulation ===" << endl;
    cout << "int main(int argc, char** argv)" << endl;
    cout << "  argc: argument count" << endl;
    cout << "  argv: pointer to array of string pointers (char**)" << endl;
    cout << endl;

    // Simulate command line: program.exe arg1 arg2 arg3
    const char* simArgv[] = {"program.exe", "arg1", "arg2", "arg3"};
    int simArgc = 4;

    cout << "Simulated command: program.exe arg1 arg2 arg3" << endl;
    cout << "argc = " << simArgc << endl;
    for (int i = 0; i < simArgc; ++i)
    {
        cout << "  argv[" << i << "] = " << simArgv[i] << endl;
    }
    cout << endl;

    cout << "=== Triple Pointer (***) ===" << endl;
    int val = 777;
    int* p1 = &val;
    int** p2 = &p1;
    int*** p3 = &p2;

    cout << "int val = 777;" << endl;
    cout << "int* p1 = &val;" << endl;
    cout << "int** p2 = &p1;" << endl;
    cout << "int*** p3 = &p2;" << endl;
    cout << endl;

    cout << "*p3 (one dereference): " << *p3 << " (address stored in p2)" << endl;
    cout << "**p3 (two dereferences): " << **p3 << " (address stored in p1)" << endl;
    cout << "***p3 (three dereferences): " << ***p3 << " (value of val)" << endl;
    cout << endl;

    cout << "=== Practical Use: Changing Pointer in Function ===" << endl;
    int num1 = 50, num2 = 100;
    int* myPtr = &num1;

    cout << "Before: myPtr points to " << *myPtr << endl;
    
    modifyPointer(&myPtr, &num2);
    
    cout << "After modifyPointer(&myPtr, &num2):" << endl;
    cout << "myPtr now points to " << *myPtr << endl;
    cout << endl;

    cout << "=== Comparison: * vs ** ===" << endl;
    cout << "int* ptr:" << endl;
    cout << "  - Points to int" << endl;
    cout << "  - *ptr gives the int value" << endl;
    cout << "  - Used for: arrays, single values" << endl;
    cout << endl;

    cout << "int** pptr:" << endl;
    cout << "  - Points to int*" << endl;
    cout << "  - *pptr gives address (int*)" << endl;
    cout << "  - **pptr gives int value" << endl;
    cout << "  - Used for: 2D arrays, modifying pointers, string arrays" << endl;
    cout << endl;

    cout << "=== Pointer Levels Summary ===" << endl;
    int num = 42;
    int* ptr1 = &num;
    int** ptr2 = &ptr1;
    int*** ptr3 = &ptr2;

    cout << "Variable levels:" << endl;
    cout << "  num: " << num << " (value)" << endl;
    cout << "  ptr1 (*): points to num, *ptr1 = " << *ptr1 << endl;
    cout << "  ptr2 (**): points to ptr1, **ptr2 = " << **ptr2 << endl;
    cout << "  ptr3 (***): points to ptr2, ***ptr3 = " << ***ptr3 << endl;
    cout << endl;

    cout << "=== Important Concepts ===" << endl;
    cout << "1. int** is pointer to pointer to int" << endl;
    cout << "2. *pptr gives the address stored in pptr" << endl;
    cout << "3. **pptr gives the final value" << endl;
    cout << "4. Used for: 2D arrays, modifying pointers, char** argv" << endl;
    cout << "5. Each * adds one level of indirection" << endl;
    cout << "6. Must allocate/free each dimension separately for 2D arrays" << endl;
    cout << "7. Triple pointers (***) are rare in practice" << endl;

    return 0;
}
