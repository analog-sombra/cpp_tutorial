/*
### Pointers and Functions

### Pointers as Function Parameters
- Pass address of variable to function.
- Function can modify original variable (pass by reference).
- More efficient for large objects (no copying).

syntax:
    void func(int* ptr) {
        *ptr = 100;         // Modifies original
    }


### Returning Pointers from Functions
- Function can return pointer to data.
- Never return pointer to local variable!
- Can return pointer to static, global, or dynamic memory.

syntax:
    int* func() {
        static int x = 10;
        return &x;          // Safe: static variable
    }


### Function Pointers
- Pointer that points to a function instead of data.
- Used for callbacks, function tables, strategy patterns.

syntax:
    returnType (*pointerName)(paramTypes);

example:
    int (*funcPtr)(int, int);       // Pointer to function taking 2 ints, returning int
    funcPtr = &add;                 // Point to function
    int result = funcPtr(5, 3);     // Call through pointer


### Declaring Function Pointers
- Parentheses are important: (*ptr) vs *ptr()

    int (*ptr)(int);        // Pointer to function returning int
    int* ptr(int);          // Function returning pointer to int


### Array of Function Pointers
- Store multiple function addresses in array.
- Useful for menu systems, command dispatch.

syntax:
    returnType (*arr[])(paramTypes) = {func1, func2, func3};


### Callback Functions
- Pass function pointer as parameter to another function.
- The called function "calls back" the passed function.

example:
    void processArray(int arr[], int size, void (*callback)(int));


### typedef for Function Pointers
- Simplify complex function pointer declarations.

syntax:
    typedef returnType (*TypeName)(paramTypes);
    TypeName ptr = &function;


### Important Notes:
- Function name decays to pointer (like arrays)
- Can use &func or just func for function address
- Can use (*ptr)() or ptr() to call through pointer
- Never return pointer to local variable

*/

#include <iostream>
#include <string>

using namespace std;

// Simple functions for demonstration
void printMessage(string msg)
{
    cout << "Message: " << msg << endl;
}

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    return (b != 0) ? a / b : 0;
}

// Function using pointer parameter
void modifyValue(int* ptr)
{
    *ptr = 100;
}

// Function using pointer to modify array
void doubleArrayValues(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        arr[i] *= 2;
    }
}

// Function returning pointer (static variable)
int* getStaticPointer()
{
    static int value = 42;
    return &value;
}

// Function returning pointer (dynamic memory)
int* createArray(int size)
{
    return new int[size];
}

// Callback example: process each element
void processArray(int arr[], int size, void (*callback)(int))
{
    for (int i = 0; i < size; ++i)
    {
        callback(arr[i]);
    }
}

void printElement(int x)
{
    cout << x << " ";
}

void printSquare(int x)
{
    cout << (x * x) << " ";
}

// Sorting with comparison function pointer
void bubbleSort(int arr[], int size, bool (*compare)(int, int))
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (compare(arr[j], arr[j + 1]))
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

bool ascending(int a, int b)
{
    return a > b;
}

bool descending(int a, int b)
{
    return a < b;
}

int main()
{
    cout << "=== Pointers as Function Parameters ===" << endl;
    int number = 50;
    cout << "Before: number = " << number << endl;
    
    modifyValue(&number);
    cout << "After modifyValue(&number): number = " << number << endl;
    cout << "Function modified the original variable!" << endl;
    cout << endl;

    cout << "=== Pass by Value vs Pass by Pointer ===" << endl;
    int x = 10;
    int* xPtr = &x;

    cout << "Pass by value: function receives copy (cannot modify original)" << endl;
    cout << "Pass by pointer: function receives address (can modify original)" << endl;
    cout << "Original x = " << x << endl;
    cout << endl;

    cout << "=== Modifying Array via Pointer ===" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Before: ";
    for (int i = 0; i < size; ++i) cout << arr[i] << " ";
    cout << endl;

    doubleArrayValues(arr, size);

    cout << "After doubleArrayValues(): ";
    for (int i = 0; i < size; ++i) cout << arr[i] << " ";
    cout << endl << endl;

    cout << "=== Returning Pointer from Function ===" << endl;
    int* ptr = getStaticPointer();
    cout << "Returned pointer points to: " << *ptr << endl;
    
    *ptr = 99;
    cout << "Modified to: " << *ptr << endl;
    
    int* ptr2 = getStaticPointer();
    cout << "Calling again: " << *ptr2 << " (same static variable)" << endl;
    cout << endl;

    cout << "=== Returning Pointer to Dynamic Memory ===" << endl;
    int* dynamicArr = createArray(5);
    
    cout << "Created dynamic array of 5 elements" << endl;
    for (int i = 0; i < 5; ++i)
    {
        dynamicArr[i] = (i + 1) * 10;
    }
    
    cout << "Array: ";
    for (int i = 0; i < 5; ++i)
    {
        cout << dynamicArr[i] << " ";
    }
    cout << endl;
    
    delete[] dynamicArr;
    cout << "Memory freed" << endl;
    cout << endl;

    cout << "=== Function Pointers - Basic ===" << endl;
    int (*operation)(int, int);

    operation = add;
    cout << "operation = add;" << endl;
    cout << "operation(10, 5) = " << operation(10, 5) << endl;
    cout << endl;

    operation = subtract;
    cout << "operation = subtract;" << endl;
    cout << "operation(10, 5) = " << operation(10, 5) << endl;
    cout << endl;

    cout << "=== Function Pointer with & and without ===" << endl;
    int (*funcPtr1)(int, int) = &multiply;
    int (*funcPtr2)(int, int) = multiply;

    cout << "Both ways work (function name decays to pointer):" << endl;
    cout << "funcPtr1 = &multiply: funcPtr1(6, 7) = " << funcPtr1(6, 7) << endl;
    cout << "funcPtr2 = multiply:  funcPtr2(6, 7) = " << funcPtr2(6, 7) << endl;
    cout << endl;

    cout << "=== Calling Function Through Pointer ===" << endl;
    int (*mathFunc)(int, int) = add;
    
    cout << "Two ways to call:" << endl;
    cout << "  (*mathFunc)(8, 3) = " << (*mathFunc)(8, 3) << endl;
    cout << "  mathFunc(8, 3) = " << mathFunc(8, 3) << endl;
    cout << "Both are equivalent!" << endl;
    cout << endl;

    cout << "=== Array of Function Pointers ===" << endl;
    int (*operations[4])(int, int) = {add, subtract, multiply, divide};
    const char* opNames[] = {"add", "subtract", "multiply", "divide"};

    int a = 20, b = 5;
    cout << "a = " << a << ", b = " << b << endl;
    
    for (int i = 0; i < 4; ++i)
    {
        cout << opNames[i] << "(a, b) = " << operations[i](a, b) << endl;
    }
    cout << endl;

    cout << "=== Calculator using Function Pointers ===" << endl;
    char op;
    int num1 = 15, num2 = 3;
    int (*calc)(int, int) = nullptr;

    cout << "Select operation for " << num1 << " and " << num2 << ":" << endl;
    cout << "  + : Addition" << endl;
    cout << "  - : Subtraction" << endl;
    cout << "  * : Multiplication" << endl;
    cout << "  / : Division" << endl;
    
    // Simulate user choosing '*'
    op = '*';
    cout << "Simulating: User selects '" << op << "'" << endl;

    switch (op)
    {
        case '+': calc = add; break;
        case '-': calc = subtract; break;
        case '*': calc = multiply; break;
        case '/': calc = divide; break;
    }

    if (calc != nullptr)
    {
        cout << "Result: " << num1 << " " << op << " " << num2 << " = " << calc(num1, num2) << endl;
    }
    cout << endl;

    cout << "=== Callback Functions ===" << endl;
    int numbers[] = {1, 2, 3, 4, 5};
    int sz = sizeof(numbers) / sizeof(numbers[0]);

    cout << "Array: ";
    for (int i = 0; i < sz; ++i) cout << numbers[i] << " ";
    cout << endl;

    cout << "Process with printElement callback: ";
    processArray(numbers, sz, printElement);
    cout << endl;

    cout << "Process with printSquare callback: ";
    processArray(numbers, sz, printSquare);
    cout << endl << endl;

    cout << "=== Sorting with Custom Comparison ===" << endl;
    int values[] = {64, 34, 25, 12, 22, 11, 90};
    int valSize = sizeof(values) / sizeof(values[0]);

    cout << "Original: ";
    for (int i = 0; i < valSize; ++i) cout << values[i] << " ";
    cout << endl;

    bubbleSort(values, valSize, ascending);
    cout << "Sorted ascending: ";
    for (int i = 0; i < valSize; ++i) cout << values[i] << " ";
    cout << endl;

    bubbleSort(values, valSize, descending);
    cout << "Sorted descending: ";
    for (int i = 0; i < valSize; ++i) cout << values[i] << " ";
    cout << endl << endl;

    cout << "=== typedef for Function Pointers ===" << endl;
    typedef int (*MathOperation)(int, int);
    
    MathOperation op1 = add;
    MathOperation op2 = multiply;

    cout << "typedef int (*MathOperation)(int, int);" << endl;
    cout << "MathOperation op1 = add;" << endl;
    cout << "MathOperation op2 = multiply;" << endl;
    cout << "op1(10, 3) = " << op1(10, 3) << endl;
    cout << "op2(10, 3) = " << op2(10, 3) << endl;
    cout << "typedef makes declarations cleaner!" << endl;
    cout << endl;

    cout << "=== Function Pointer as Return Type ===" << endl;
    cout << "Complex but valid:" << endl;
    cout << "  int (*getOperation(char op))(int, int)" << endl;
    cout << "This function returns a function pointer!" << endl;
    cout << "Better with typedef:" << endl;
    cout << "  MathOperation getOperation(char op)" << endl;
    cout << endl;

    cout << "=== Common Uses of Function Pointers ===" << endl;
    cout << "1. Callbacks: Pass function to be called later" << endl;
    cout << "2. Polymorphism: Select function at runtime" << endl;
    cout << "3. Plugin systems: Load functions dynamically" << endl;
    cout << "4. Event handlers: Register callback functions" << endl;
    cout << "5. Strategy pattern: Switch algorithms" << endl;
    cout << endl;

    cout << "=== Important Rules ===" << endl;
    cout << "1. Function name decays to pointer (like arrays)" << endl;
    cout << "2. Can use &func or func for function address" << endl;
    cout << "3. Can use (*ptr)() or ptr() to call" << endl;
    cout << "4. Never return pointer to local variable" << endl;
    cout << "5. Use typedef to simplify complex declarations" << endl;
    cout << "6. Function pointers enable runtime polymorphism" << endl;

    return 0;
}
