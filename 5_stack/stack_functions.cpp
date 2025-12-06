/*
### Stack Functions and Advanced Operations

### Creating Stack with Different Underlying Containers
- By default, stack uses deque as underlying container.
- Can use vector, list, or deque.

syntax:
    stack<type> s1;                      // Uses deque (default)
    stack<type, vector<type>> s2;        // Uses vector
    stack<type, list<type>> s3;          // Uses list
    stack<type, deque<type>> s4;         // Explicitly uses deque


### std::swap() operation
- Non-member swap function for stacks.
- Can be used alternatively to member swap().

syntax:
    std::swap(s1, s2);
    swap(s1, s2);       // Without std::

example:
    stack<int> s1, s2;
    s1.push(1);
    s2.push(2);
    swap(s1, s2);  // s1 has 2, s2 has 1


### Copying and Moving Stacks
- Stack supports copy constructor and assignment.
- Stack supports move semantics (C++11).

syntax:
    stack<int> s1;
    stack<int> s2 = s1;           // Copy constructor
    stack<int> s3(s1);            // Copy constructor
    stack<int> s4 = move(s1);     // Move constructor


### Creating Stack from Other Containers
- Initialize stack with contents of another container.

syntax:
    vector<int> vec = {1, 2, 3};
    stack<int, vector<int>> s(vec);


### Checking Stack Capacity (Underlying Container)
- Stack doesn't have capacity() method directly.
- Need to access underlying container (implementation-specific).


### Stack Size Limits
- Stack size is limited by:
  1. Available memory
  2. Underlying container's max_size()
  3. System constraints


### Common Patterns:
1. Processing all elements (destructive):
   while (!s.empty()) {
       process(s.top());
       s.pop();
   }

2. Copying stack for non-destructive iteration:
   stack<int> temp = original;
   while (!temp.empty()) {
       process(temp.top());
       temp.pop();
   }

3. Building stack from array/vector:
   for (auto val : container) {
       s.push(val);
   }


### Performance Characteristics:
- push(): O(1) amortized
- pop(): O(1)
- top(): O(1)
- size(): O(1)
- empty(): O(1)


### Memory Management:
- Stack automatically manages memory of underlying container.
- When stack is destroyed, all elements are cleaned up.
- No manual memory management needed.

*/

#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <deque>

using namespace std;

// Helper function to display stack (makes a copy)
template <typename T>
void displayStack(stack<T> s, const string &name)
{
    cout << name << " (top to bottom): ";
    if (s.empty())
    {
        cout << "[empty]";
    }
    else
    {
        while (!s.empty())
        {
            cout << s.top();
            s.pop();
            if (!s.empty())
                cout << " -> ";
        }
    }
    cout << endl;
}

int main()
{
    cout << "=== Creating Stacks with Different Underlying Containers ===" << endl;

    // Default (uses deque)
    stack<int> defaultStack;
    defaultStack.push(1);
    defaultStack.push(2);
    cout << "Default stack (deque): top = " << defaultStack.top() << endl;

    // Using vector
    stack<int, vector<int>> vectorStack;
    vectorStack.push(10);
    vectorStack.push(20);
    cout << "Vector-based stack: top = " << vectorStack.top() << endl;

    // Using list
    stack<int, list<int>> listStack;
    listStack.push(100);
    listStack.push(200);
    cout << "List-based stack: top = " << listStack.top() << endl;

    // Explicitly using deque
    stack<int, deque<int>> dequeStack;
    dequeStack.push(1000);
    dequeStack.push(2000);
    cout << "Deque-based stack: top = " << dequeStack.top() << endl;
    cout << endl;

    cout << "=== Copying Stacks ===" << endl;
    stack<int> original;
    original.push(1);
    original.push(2);
    original.push(3);

    // Copy constructor
    stack<int> copy1 = original;
    stack<int> copy2(original);

    cout << "Original stack size: " << original.size() << endl;
    cout << "Copy1 stack size: " << copy1.size() << endl;
    cout << "Copy2 stack size: " << copy2.size() << endl;

    displayStack(original, "Original");
    displayStack(copy1, "Copy1");
    displayStack(copy2, "Copy2");
    cout << endl;

    cout << "=== Copy Assignment ===" << endl;
    stack<int> source;
    source.push(10);
    source.push(20);
    source.push(30);

    stack<int> destination;
    destination.push(99); // Will be replaced

    cout << "Before assignment:" << endl;
    displayStack(source, "Source");
    displayStack(destination, "Destination");

    destination = source; // Copy assignment

    cout << "After assignment:" << endl;
    displayStack(source, "Source");
    displayStack(destination, "Destination");
    cout << endl;

    cout << "=== std::swap (Non-member Function) ===" << endl;
    stack<string> s1, s2;
    s1.push("Apple");
    s1.push("Banana");
    s2.push("Cherry");
    s2.push("Date");
    s2.push("Elderberry");

    cout << "Before swap:" << endl;
    displayStack(s1, "s1");
    displayStack(s2, "s2");

    swap(s1, s2); // Using std::swap

    cout << "After swap:" << endl;
    displayStack(s1, "s1");
    displayStack(s2, "s2");
    cout << endl;

    cout << "=== Creating Stack from Vector ===" << endl;
    vector<int> vec = {1, 2, 3, 4, 5};
    
    cout << "Vector contents: ";
    for (int val : vec)
    {
        cout << val << " ";
    }
    cout << endl;

    // Create stack from vector (using deque internally)
    stack<int> fromVec;
    for (int val : vec)
    {
        fromVec.push(val);
    }

    displayStack(fromVec, "Stack from vector");
    cout << endl;

    cout << "=== Non-destructive Stack Iteration ===" << endl;
    stack<int> numbers;
    for (int i = 1; i <= 5; ++i)
    {
        numbers.push(i * 10);
    }

    cout << "Original stack size: " << numbers.size() << endl;

    // Make a copy to iterate without destroying original
    stack<int> temp = numbers;
    cout << "Iterating through copy: ";
    while (!temp.empty())
    {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;

    cout << "Original stack still intact, size: " << numbers.size() << endl;
    cout << endl;

    cout << "=== Destructive Stack Iteration ===" << endl;
    stack<int> toProcess;
    toProcess.push(100);
    toProcess.push(200);
    toProcess.push(300);

    cout << "Processing and destroying stack:" << endl;
    int position = 1;
    while (!toProcess.empty())
    {
        cout << "  " << position << ". Processing: " << toProcess.top() << endl;
        toProcess.pop();
        position++;
    }
    cout << "Stack is now empty, size: " << toProcess.size() << endl;
    cout << endl;

    cout << "=== Building Stack from Array ===" << endl;
    int arr[] = {5, 10, 15, 20, 25};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    stack<int> fromArray;
    for (int i = 0; i < arrSize; ++i)
    {
        fromArray.push(arr[i]);
    }

    displayStack(fromArray, "Stack from array");
    cout << endl;

    cout << "=== Stack Size and Memory ===" << endl;
    stack<double> doubles;
    cout << "Empty stack size: " << doubles.size() << endl;

    for (int i = 0; i < 10; ++i)
    {
        doubles.push(i * 1.5);
    }
    cout << "After 10 pushes, size: " << doubles.size() << endl;

    for (int i = 0; i < 5; ++i)
    {
        doubles.pop();
    }
    cout << "After 5 pops, size: " << doubles.size() << endl;
    cout << endl;

    cout << "=== Practical Pattern: Collecting Results ===" << endl;
    stack<int> results;

    // Simulate some computation
    for (int i = 1; i <= 5; ++i)
    {
        int result = i * i; // Square numbers
        results.push(result);
        cout << "Computed: " << result << endl;
    }

    cout << "\nResults in LIFO order:" << endl;
    vector<int> collected;
    while (!results.empty())
    {
        collected.push_back(results.top());
        cout << results.top() << " ";
        results.pop();
    }
    cout << endl;
    cout << endl;

    cout << "=== Move Semantics (C++11) ===" << endl;
    stack<string> moveSource;
    moveSource.push("Will");
    moveSource.push("Be");
    moveSource.push("Moved");

    cout << "Source size before move: " << moveSource.size() << endl;

    stack<string> moveDestination = move(moveSource);

    cout << "Source size after move: " << moveSource.size() << " (moved from)" << endl;
    cout << "Destination size: " << moveDestination.size() << endl;
    displayStack(moveDestination, "Moved stack");
    cout << endl;

    cout << "=== Performance Characteristics ===" << endl;
    cout << "All stack operations are O(1):" << endl;
    cout << "- push(): O(1) amortized" << endl;
    cout << "- pop(): O(1)" << endl;
    cout << "- top(): O(1)" << endl;
    cout << "- size(): O(1)" << endl;
    cout << "- empty(): O(1)" << endl;
    cout << endl;

    cout << "=== Choosing Underlying Container ===" << endl;
    cout << "deque (default): Good balance, allows efficient push/pop at both ends" << endl;
    cout << "vector: Better cache locality, but may reallocate" << endl;
    cout << "list: No reallocation, but worse cache performance" << endl;

    return 0;
}
