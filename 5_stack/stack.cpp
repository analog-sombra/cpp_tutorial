/*
### Stack (std::stack)
- A stack is a container adapter that provides LIFO (Last-In-First-Out) operations.
- Elements are added and removed from the same end (top of the stack).
- Like a stack of plates: you can only add/remove from the top.

### LIFO - Last In, First Out:
- The last element added is the first one to be removed.
- Only the top element is accessible.
- No random access to elements in the middle.

### Key Characteristics:
- LIFO structure
- Only top element is accessible
- No iterators (can't traverse through stack)
- Built on top of other containers (deque, vector, or list)

### When to use Stack:
- Function call management (call stack)
- Undo/Redo functionality
- Expression evaluation (parentheses matching)
- Backtracking algorithms
- Depth-First Search (DFS)

### Underlying Container:
By default, stack uses deque as the underlying container.
You can specify a different container:
    stack<int> s1;                    // Uses deque
    stack<int, vector<int>> s2;       // Uses vector
    stack<int, list<int>> s3;         // Uses list


### Basic Operations:
- push(element): Add element to the top
- pop(): Remove top element
- top(): Access top element
- empty(): Check if stack is empty
- size(): Get number of elements


### Syntax:
    stack<type> stack_name;

### Examples:
    stack<int> numbers;              // Stack of integers
    stack<string> words;             // Stack of strings
    stack<char> characters;          // Stack of characters


### Important Notes:
- No begin(), end() iterators
- No [] operator or at() method
- Only top element is accessible
- Cannot traverse through stack directly
- Must pop elements to access lower elements

*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    cout << "=== Stack Introduction - LIFO Structure ===" << endl;
    cout << "LIFO: Last In, First Out" << endl;
    cout << "Like a stack of plates - add/remove from top only" << endl;
    cout << endl;

    // Creating a stack
    stack<int> numbers;

    cout << "=== Checking if Stack is Empty ===" << endl;
    if (numbers.empty())
    {
        cout << "Stack is empty" << endl;
    }
    cout << "Stack size: " << numbers.size() << endl;
    cout << endl;

    cout << "=== Pushing Elements onto Stack ===" << endl;
    numbers.push(10);
    cout << "Pushed: 10" << endl;
    numbers.push(20);
    cout << "Pushed: 20" << endl;
    numbers.push(30);
    cout << "Pushed: 30" << endl;
    numbers.push(40);
    cout << "Pushed: 40" << endl;
    numbers.push(50);
    cout << "Pushed: 50" << endl;
    cout << endl;

    cout << "=== Stack State ===" << endl;
    cout << "Stack size: " << numbers.size() << endl;
    cout << "Top element: " << numbers.top() << endl;
    cout << "Stack visualization (top to bottom): 50, 40, 30, 20, 10" << endl;
    cout << endl;

    cout << "=== Accessing Top Element ===" << endl;
    cout << "Current top: " << numbers.top() << endl;
    cout << "Note: Can only access the top element!" << endl;
    cout << endl;

    cout << "=== Popping Elements (LIFO Order) ===" << endl;
    while (!numbers.empty())
    {
        cout << "Popped: " << numbers.top() << endl;
        numbers.pop();
        cout << "  Remaining size: " << numbers.size() << endl;
    }
    cout << endl;

    cout << "=== After Popping All Elements ===" << endl;
    if (numbers.empty())
    {
        cout << "Stack is now empty" << endl;
    }
    cout << endl;

    // String stack example
    cout << "=== String Stack Example ===" << endl;
    stack<string> words;

    words.push("Hello");
    words.push("World");
    words.push("Stack");
    words.push("Example");

    cout << "Pushed: Hello, World, Stack, Example" << endl;
    cout << "Stack size: " << words.size() << endl;
    cout << endl;

    cout << "Popping in LIFO order:" << endl;
    while (!words.empty())
    {
        cout << "  " << words.top() << endl;
        words.pop();
    }
    cout << endl;

    // Character stack for simple example
    cout << "=== Character Stack - Reversing a String ===" << endl;
    string text = "STACK";
    stack<char> charStack;

    cout << "Original string: " << text << endl;

    // Push all characters onto stack
    for (char c : text)
    {
        charStack.push(c);
    }

    cout << "Reversed string: ";
    while (!charStack.empty())
    {
        cout << charStack.top();
        charStack.pop();
    }
    cout << endl;
    cout << endl;

    // Demonstrating LIFO with numbers
    cout << "=== LIFO Demonstration ===" << endl;
    stack<int> demo;

    cout << "Push sequence: 1, 2, 3, 4, 5" << endl;
    for (int i = 1; i <= 5; ++i)
    {
        demo.push(i);
    }

    cout << "Pop sequence (LIFO): ";
    while (!demo.empty())
    {
        cout << demo.top() << " ";
        demo.pop();
    }
    cout << endl;
    cout << "Notice: Reverse order (5, 4, 3, 2, 1)" << endl;
    cout << endl;

    // Stack operations summary
    cout << "=== Stack Operations Summary ===" << endl;
    stack<int> s;
    
    s.push(100);
    cout << "push(100): Added 100 to top" << endl;
    cout << "top(): " << s.top() << " (view top without removing)" << endl;
    cout << "size(): " << s.size() << endl;
    cout << "empty(): " << (s.empty() ? "true" : "false") << endl;
    
    s.pop();
    cout << "pop(): Removed top element" << endl;
    cout << "empty(): " << (s.empty() ? "true" : "false") << endl;

    return 0;
}
