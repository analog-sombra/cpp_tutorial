/*
### Practical Pointer Examples

This file contains real-world examples demonstrating practical uses of pointers:
1. Swap function (pass by reference)
2. Array reversal
3. String manipulation
4. Linked list basics
5. Dynamic array resize
6. Function returning multiple values
7. Pointer-based searching
8. Memory pool simulation


### Example 1: Swap Two Variables
- Pass pointers to swap actual variables
- Modifies original values


### Example 2: Reverse Array
- Use two pointers from both ends
- Swap elements while moving pointers


### Example 3: String Length and Copy
- Manual string operations using pointers
- Demonstrates char pointer usage


### Example 4: Simple Linked List
- Basic node structure with pointer to next
- Insert and traverse operations


### Example 5: Dynamic Array Resize
- Grow array when capacity reached
- Copy old data to new location


### Example 6: Multiple Return Values
- Return multiple values via pointer parameters
- Common pattern before std::tuple


### Example 7: Linear Search
- Return pointer to found element
- nullptr if not found


### Example 8: Circular Buffer
- Fixed-size buffer with wrap-around
- Uses pointers for read/write positions

*/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// === Example 1: Swap Function ===
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// === Example 2: Reverse Array ===
void reverseArray(int* arr, int size)
{
    int* start = arr;
    int* end = arr + size - 1;

    while (start < end)
    {
        int temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}

// === Example 3: String Operations ===
int stringLength(const char* str)
{
    const char* ptr = str;
    int length = 0;

    while (*ptr != '\0')
    {
        length++;
        ptr++;
    }

    return length;
}

void stringCopy(char* dest, const char* src)
{
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// === Example 4: Simple Linked List ===
struct Node
{
    int data;
    Node* next;
};

void insertNode(Node** head, int value)
{
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

void printList(Node* head)
{
    Node* current = head;
    while (current != nullptr)
    {
        cout << current->data;
        if (current->next != nullptr) cout << " -> ";
        current = current->next;
    }
    cout << endl;
}

void freeList(Node** head)
{
    Node* current = *head;
    while (current != nullptr)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    *head = nullptr;
}

// === Example 5: Dynamic Array Resize ===
class DynamicArray
{
private:
    int* data;
    int size;
    int capacity;

public:
    DynamicArray()
    {
        capacity = 2;
        size = 0;
        data = new int[capacity];
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    void push(int value)
    {
        if (size == capacity)
        {
            // Resize: double capacity
            capacity *= 2;
            int* newData = new int[capacity];

            // Copy old data
            for (int i = 0; i < size; ++i)
            {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
        }

        data[size++] = value;
    }

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }

    int& operator[](int index)
    {
        return data[index];
    }
};

// === Example 6: Multiple Return Values ===
void divideWithRemainder(int dividend, int divisor, int* quotient, int* remainder)
{
    *quotient = dividend / divisor;
    *remainder = dividend % divisor;
}

// === Example 7: Linear Search ===
int* findValue(int* arr, int size, int target)
{
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == target)
        {
            return &arr[i];
        }
    }
    return nullptr;
}

// === Example 8: Circular Buffer ===
class CircularBuffer
{
private:
    int* buffer;
    int capacity;
    int* writePtr;
    int* readPtr;
    int count;

public:
    CircularBuffer(int cap) : capacity(cap), count(0)
    {
        buffer = new int[capacity];
        writePtr = buffer;
        readPtr = buffer;
    }

    ~CircularBuffer()
    {
        delete[] buffer;
    }

    bool write(int value)
    {
        if (count == capacity)
            return false;

        *writePtr = value;
        writePtr++;
        
        if (writePtr == buffer + capacity)
            writePtr = buffer;

        count++;
        return true;
    }

    bool read(int* value)
    {
        if (count == 0)
            return false;

        *value = *readPtr;
        readPtr++;

        if (readPtr == buffer + capacity)
            readPtr = buffer;

        count--;
        return true;
    }

    int getCount() const { return count; }
};

int main()
{
    cout << "=== Example 1: Swap Function ===" << endl;
    int a = 10, b = 20;
    cout << "Before swap: a = " << a << ", b = " << b << endl;
    
    swap(&a, &b);
    cout << "After swap: a = " << a << ", b = " << b << endl;
    cout << "Pointers allow function to modify original variables" << endl;
    cout << endl;

    cout << "=== Example 2: Reverse Array ===" << endl;
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Original: ";
    for (int i = 0; i < size; ++i) cout << arr[i] << " ";
    cout << endl;

    reverseArray(arr, size);

    cout << "Reversed: ";
    for (int i = 0; i < size; ++i) cout << arr[i] << " ";
    cout << endl;
    cout << "Uses two pointers moving from both ends" << endl;
    cout << endl;

    cout << "=== Example 3: String Operations ===" << endl;
    const char* str1 = "Hello Pointers";
    cout << "String: \"" << str1 << "\"" << endl;
    cout << "Length (manual): " << stringLength(str1) << endl;
    cout << "Length (strlen): " << strlen(str1) << endl;
    cout << endl;

    char str2[50];
    stringCopy(str2, str1);
    cout << "Copied string: \"" << str2 << "\"" << endl;
    cout << "String operations use pointer arithmetic" << endl;
    cout << endl;

    cout << "=== Example 4: Simple Linked List ===" << endl;
    Node* head = nullptr;

    cout << "Inserting: 10, 20, 30, 40" << endl;
    insertNode(&head, 10);
    insertNode(&head, 20);
    insertNode(&head, 30);
    insertNode(&head, 40);

    cout << "List: ";
    printList(head);
    cout << "Each node contains data and pointer to next node" << endl;

    freeList(&head);
    cout << "List memory freed" << endl;
    cout << endl;

    cout << "=== Example 5: Dynamic Array with Auto-Resize ===" << endl;
    DynamicArray dynArr;

    cout << "Initial capacity: " << dynArr.getCapacity() << endl;
    cout << "Pushing elements: 1, 2, 3, 4, 5" << endl;

    for (int i = 1; i <= 5; ++i)
    {
        dynArr.push(i);
        cout << "  After push(" << i << "): size = " << dynArr.getSize() 
             << ", capacity = " << dynArr.getCapacity() << endl;
    }

    cout << "Array contents: ";
    for (int i = 0; i < dynArr.getSize(); ++i)
    {
        cout << dynArr[i] << " ";
    }
    cout << endl;
    cout << "Automatically resizes by allocating new memory and copying" << endl;
    cout << endl;

    cout << "=== Example 6: Multiple Return Values ===" << endl;
    int dividend = 17, divisor = 5;
    int quotient, remainder;

    divideWithRemainder(dividend, divisor, &quotient, &remainder);

    cout << dividend << " ÷ " << divisor << " = " << quotient 
         << " remainder " << remainder << endl;
    cout << "Function returns multiple values via pointer parameters" << endl;
    cout << endl;

    cout << "=== Example 7: Linear Search with Pointer ===" << endl;
    int numbers[] = {10, 25, 30, 45, 50, 65, 70};
    int sz = sizeof(numbers) / sizeof(numbers[0]);

    cout << "Array: ";
    for (int i = 0; i < sz; ++i) cout << numbers[i] << " ";
    cout << endl;

    int target = 45;
    int* found = findValue(numbers, sz, target);

    if (found != nullptr)
    {
        cout << "Found " << target << " at address " << found << endl;
        cout << "Value: " << *found << endl;
        
        *found = 99;
        cout << "Modified to 99 via pointer" << endl;
        cout << "Array now: ";
        for (int i = 0; i < sz; ++i) cout << numbers[i] << " ";
        cout << endl;
    }
    else
    {
        cout << target << " not found (nullptr returned)" << endl;
    }
    cout << endl;

    cout << "=== Example 8: Circular Buffer ===" << endl;
    CircularBuffer buffer(5);

    cout << "Circular buffer capacity: 5" << endl;
    cout << "Writing: 10, 20, 30, 40, 50" << endl;

    buffer.write(10);
    buffer.write(20);
    buffer.write(30);
    buffer.write(40);
    buffer.write(50);

    cout << "Buffer full: count = " << buffer.getCount() << endl;
    
    if (!buffer.write(60))
    {
        cout << "Cannot write 60 (buffer full)" << endl;
    }

    cout << "\nReading values:" << endl;
    int value;
    while (buffer.read(&value))
    {
        cout << "  Read: " << value << " (count = " << buffer.getCount() << ")" << endl;
    }

    cout << "\nCircular buffer uses pointers that wrap around" << endl;
    cout << endl;

    cout << "=== Example 9: Find Min and Max ===" << endl;
    int data[] = {45, 12, 78, 23, 91, 56, 34};
    int dataSize = sizeof(data) / sizeof(data[0]);

    int* minPtr = data;
    int* maxPtr = data;

    for (int i = 1; i < dataSize; ++i)
    {
        if (data[i] < *minPtr) minPtr = &data[i];
        if (data[i] > *maxPtr) maxPtr = &data[i];
    }

    cout << "Array: ";
    for (int i = 0; i < dataSize; ++i) cout << data[i] << " ";
    cout << endl;

    cout << "Min: " << *minPtr << " at index " << (minPtr - data) << endl;
    cout << "Max: " << *maxPtr << " at index " << (maxPtr - data) << endl;
    cout << "Pointers used to track positions in array" << endl;
    cout << endl;

    cout << "=== Example 10: Pass-by-Reference Simulation ===" << endl;
    cout << "C doesn't have references, but pointers simulate them:" << endl;
    cout << endl;

    int num = 5;
    cout << "Original: num = " << num << endl;

    int* numPtr = &num;
    *numPtr = 100;
    cout << "After *numPtr = 100: num = " << num << endl;
    cout << "Pointer provides indirect access to variable" << endl;
    cout << endl;

    cout << "=== Common Practical Uses ===" << endl;
    cout << "1. Pass large structures efficiently (avoid copying)" << endl;
    cout << "2. Modify function parameters (pass by reference)" << endl;
    cout << "3. Return multiple values from function" << endl;
    cout << "4. Dynamic data structures (linked lists, trees, graphs)" << endl;
    cout << "5. Arrays and strings manipulation" << endl;
    cout << "6. Memory management (heap allocation)" << endl;
    cout << "7. Callback functions (function pointers)" << endl;
    cout << "8. Implement polymorphism in C (vtables)" << endl;
    cout << endl;

    cout << "=== Summary ===" << endl;
    cout << "Pointers are powerful tools that enable:" << endl;
    cout << "  - Efficient memory usage" << endl;
    cout << "  - Dynamic data structures" << endl;
    cout << "  - Direct memory manipulation" << endl;
    cout << "  - Complex algorithms implementation" << endl;
    cout << "  - System-level programming" << endl;
    cout << endl;
    cout << "Remember: With great power comes great responsibility!" << endl;
    cout << "Always manage memory carefully and check for nullptr." << endl;

    return 0;
}
