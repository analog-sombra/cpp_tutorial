/*
### Dynamic Memory Allocation

### What is Dynamic Memory?
- Memory allocated at runtime (not compile time).
- Allocated on the heap (not stack).
- Must be manually managed (allocated and freed).
- Size can be determined at runtime.

### Stack vs Heap Memory
Stack:
- Automatic allocation and deallocation
- Limited size (typically few MB)
- Fast access
- Automatic cleanup

Heap:
- Manual allocation (new) and deallocation (delete)
- Large size (limited by system RAM)
- Slightly slower access
- Manual cleanup required


### new Operator
- Allocates memory on heap.
- Returns pointer to allocated memory.
- Throws exception if allocation fails.

syntax:
    type* ptr = new type;           // Single object
    type* ptr = new type(value);    // With initialization
    type* ptr = new type[size];     // Array


### delete Operator
- Frees memory allocated by new.
- Must match: new → delete, new[] → delete[]
- Prevents memory leaks.

syntax:
    delete ptr;             // For single object
    delete[] ptr;           // For array


### Memory Leaks
- Occur when allocated memory is not freed.
- Program loses reference to memory (cannot free it).
- Accumulates over time, wastes resources.

example:
    void badFunction() {
        int* ptr = new int(10);
        // forgot delete ptr;
    }  // Memory leaked!


### new with Initialization
- Can initialize during allocation.

syntax:
    int* ptr = new int(42);             // Single value
    int* arr = new int[5]{1, 2, 3, 4, 5}; // Array with values


### nullptr and Dynamic Memory
- Always initialize pointers to nullptr.
- Check for nullptr before using.
- Set pointer to nullptr after delete.

syntax:
    int* ptr = nullptr;
    if (ptr != nullptr) {
        // Safe to use
    }
    delete ptr;
    ptr = nullptr;  // Prevent dangling pointer


### nothrow Version
- Does not throw exception on failure.
- Returns nullptr instead.

syntax:
    int* ptr = new(nothrow) int;
    if (ptr == nullptr) {
        // Allocation failed
    }


### Dynamic 2D Arrays
- Allocate array of pointers, then allocate each row.

syntax:
    int** arr = new int*[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }


### Important Rules:
- Every new must have corresponding delete
- Use delete for single object, delete[] for array
- Don't delete same memory twice
- Set pointer to nullptr after delete
- Check for nullptr before using pointer
- Prefer smart pointers (modern C++) to avoid manual management

*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "=== Stack vs Heap Memory ===" << endl;
    cout << "Stack memory:" << endl;
    int stackVar = 10;
    cout << "  int stackVar = 10; (automatic, limited size)" << endl;
    cout << "  Address: " << &stackVar << endl;
    cout << endl;

    cout << "Heap memory:" << endl;
    int* heapVar = new int(20);
    cout << "  int* heapVar = new int(20); (manual, larger size)" << endl;
    cout << "  Address: " << heapVar << endl;
    cout << "  Value: " << *heapVar << endl;
    delete heapVar;
    cout << "  delete heapVar; (manual cleanup required)" << endl;
    cout << endl;

    cout << "=== Allocating Single Object ===" << endl;
    int* ptr = new int;
    cout << "int* ptr = new int;" << endl;
    cout << "Allocated memory at: " << ptr << endl;
    
    *ptr = 42;
    cout << "After *ptr = 42: " << *ptr << endl;
    
    delete ptr;
    cout << "delete ptr; (memory freed)" << endl;
    cout << endl;

    cout << "=== Allocating with Initialization ===" << endl;
    int* num = new int(100);
    double* pi = new double(3.14159);
    string* str = new string("Hello Dynamic Memory");

    cout << "int* num = new int(100): " << *num << endl;
    cout << "double* pi = new double(3.14159): " << *pi << endl;
    cout << "string* str = new string(\"...\"): " << *str << endl;

    delete num;
    delete pi;
    delete str;
    cout << "All memory freed" << endl;
    cout << endl;

    cout << "=== Allocating Array ===" << endl;
    int size = 5;
    int* arr = new int[size];

    cout << "int* arr = new int[" << size << "];" << endl;
    
    for (int i = 0; i < size; ++i)
    {
        arr[i] = (i + 1) * 10;
    }

    cout << "Array elements: ";
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    cout << "delete[] arr; (use delete[] for arrays)" << endl;
    cout << endl;

    cout << "=== Array with Initialization ===" << endl;
    int* initArr = new int[5]{10, 20, 30, 40, 50};

    cout << "int* initArr = new int[5]{10, 20, 30, 40, 50};" << endl;
    cout << "Elements: ";
    for (int i = 0; i < 5; ++i)
    {
        cout << initArr[i] << " ";
    }
    cout << endl;

    delete[] initArr;
    cout << endl;

    cout << "=== Runtime Size Determination ===" << endl;
    int n;
    cout << "How many elements? (simulating: 7)" << endl;
    n = 7;  // Simulated input

    int* dynamicArr = new int[n];
    cout << "Allocated array of " << n << " elements" << endl;

    for (int i = 0; i < n; ++i)
    {
        dynamicArr[i] = i * i;
    }

    cout << "Squares: ";
    for (int i = 0; i < n; ++i)
    {
        cout << dynamicArr[i] << " ";
    }
    cout << endl;

    delete[] dynamicArr;
    cout << endl;

    cout << "=== Memory Leak Demonstration ===" << endl;
    cout << "Bad code (causes memory leak):" << endl;
    cout << "  void badFunction() {" << endl;
    cout << "      int* ptr = new int(10);" << endl;
    cout << "      // Forgot: delete ptr;" << endl;
    cout << "  }  // Memory leaked! Cannot free it anymore" << endl;
    cout << endl;

    cout << "Good code (no leak):" << endl;
    cout << "  void goodFunction() {" << endl;
    cout << "      int* ptr = new int(10);" << endl;
    cout << "      delete ptr;  // Memory properly freed" << endl;
    cout << "  }" << endl;
    cout << endl;

    cout << "=== nullptr and Dynamic Memory ===" << endl;
    int* safePtr = nullptr;
    cout << "int* safePtr = nullptr;" << endl;
    cout << "Before allocation: safePtr == nullptr? " << (safePtr == nullptr ? "true" : "false") << endl;

    safePtr = new int(99);
    cout << "After allocation: *safePtr = " << *safePtr << endl;

    delete safePtr;
    safePtr = nullptr;
    cout << "After delete and reset: safePtr == nullptr? " << (safePtr == nullptr ? "true" : "false") << endl;
    cout << "Setting to nullptr prevents dangling pointer" << endl;
    cout << endl;

    cout << "=== Dangling Pointer Problem ===" << endl;
    int* danger = new int(50);
    cout << "int* danger = new int(50);" << endl;
    cout << "*danger = " << *danger << endl;

    delete danger;
    cout << "delete danger;" << endl;
    cout << "Now danger is dangling pointer (points to freed memory)" << endl;
    
    // danger is now dangling pointer
    // cout << *danger << endl;  // Undefined behavior! Don't do this!
    
    danger = nullptr;
    cout << "danger = nullptr; (safe practice)" << endl;
    cout << endl;

    cout << "=== nothrow Allocation ===" << endl;
    int* noThrowPtr = new(nothrow) int[1000000];

    if (noThrowPtr == nullptr)
    {
        cout << "Allocation failed (returned nullptr)" << endl;
    }
    else
    {
        cout << "Allocation succeeded" << endl;
        delete[] noThrowPtr;
    }
    cout << endl;

    cout << "=== Dynamic 2D Array ===" << endl;
    int rows = 3, cols = 4;
    int** matrix = new int*[rows];

    cout << "Allocating " << rows << "x" << cols << " matrix" << endl;
    
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[cols];
    }

    // Fill matrix
    int value = 1;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            matrix[i][j] = value++;
        }
    }

    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    // Free memory (must free each row, then array of pointers)
    for (int i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    cout << "Matrix memory freed" << endl;
    cout << endl;

    cout << "=== Dynamic Array of Strings ===" << endl;
    int numStrings = 3;
    string* strArray = new string[numStrings];

    strArray[0] = "First";
    strArray[1] = "Second";
    strArray[2] = "Third";

    cout << "String array:" << endl;
    for (int i = 0; i < numStrings; ++i)
    {
        cout << "  [" << i << "]: " << strArray[i] << endl;
    }

    delete[] strArray;
    cout << endl;

    cout << "=== Resizing Array (Manual) ===" << endl;
    int oldSize = 3;
    int* oldArr = new int[oldSize]{10, 20, 30};

    cout << "Original array: ";
    for (int i = 0; i < oldSize; ++i) cout << oldArr[i] << " ";
    cout << endl;

    int newSize = 5;
    int* newArr = new int[newSize];

    // Copy old data
    for (int i = 0; i < oldSize; ++i)
    {
        newArr[i] = oldArr[i];
    }
    // Initialize new elements
    for (int i = oldSize; i < newSize; ++i)
    {
        newArr[i] = 0;
    }

    delete[] oldArr;
    oldArr = newArr;

    cout << "Resized array: ";
    for (int i = 0; i < newSize; ++i) cout << oldArr[i] << " ";
    cout << endl;

    delete[] newArr;
    cout << endl;

    cout << "=== Common Mistakes ===" << endl;
    cout << "1. Memory leak: new without delete" << endl;
    cout << "   int* p = new int(5);" << endl;
    cout << "   // Forgot: delete p;" << endl;
    cout << endl;

    cout << "2. Double delete:" << endl;
    cout << "   delete p;" << endl;
    cout << "   delete p;  // ERROR! Undefined behavior" << endl;
    cout << endl;

    cout << "3. Using deleted memory:" << endl;
    cout << "   int* p = new int(5);" << endl;
    cout << "   delete p;" << endl;
    cout << "   cout << *p;  // ERROR! Dangling pointer" << endl;
    cout << endl;

    cout << "4. Wrong delete for array:" << endl;
    cout << "   int* arr = new int[5];" << endl;
    cout << "   delete arr;    // WRONG! Should be delete[]" << endl;
    cout << "   delete[] arr;  // Correct" << endl;
    cout << endl;

    cout << "=== Best Practices ===" << endl;
    cout << "1. Always initialize pointers to nullptr" << endl;
    cout << "2. Check for nullptr before using pointer" << endl;
    cout << "3. Set pointer to nullptr after delete" << endl;
    cout << "4. Match new with delete, new[] with delete[]" << endl;
    cout << "5. Don't delete same memory twice" << endl;
    cout << "6. Prefer smart pointers (unique_ptr, shared_ptr) in modern C++" << endl;
    cout << "7. Use RAII (Resource Acquisition Is Initialization)" << endl;
    cout << "8. Consider std::vector instead of raw dynamic arrays" << endl;
    cout << endl;

    cout << "=== Memory Management Summary ===" << endl;
    cout << "Allocation:" << endl;
    cout << "  Single object: int* p = new int(10);" << endl;
    cout << "  Array: int* arr = new int[size];" << endl;
    cout << "  2D array: int** m = new int*[rows]; then m[i] = new int[cols];" << endl;
    cout << endl;

    cout << "Deallocation:" << endl;
    cout << "  Single object: delete p;" << endl;
    cout << "  Array: delete[] arr;" << endl;
    cout << "  2D array: delete[] m[i]; for each row, then delete[] m;" << endl;
    cout << endl;

    cout << "Safety:" << endl;
    cout << "  Initialize: int* p = nullptr;" << endl;
    cout << "  Check: if (p != nullptr) { ... }" << endl;
    cout << "  Reset: delete p; p = nullptr;" << endl;

    return 0;
}
