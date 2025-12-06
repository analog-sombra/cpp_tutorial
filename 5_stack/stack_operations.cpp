/*
### Stack Operations

### s.push(element) operation
- adds an element to the top of the stack.
- the new element becomes the top element.

syntax:
    s.push(element);
    - s is the name of the stack.
    - element is the value to add to the stack.

example:
    stack<int> s;
    s.push(10);  // Stack: [10]
    s.push(20);  // Stack: [20, 10] (20 is on top)


### s.pop() operation
- removes the top element from the stack.
- does not return the removed element (use top() before pop() if needed).
- calling pop() on empty stack causes undefined behavior.

syntax:
    s.pop();
    - s is the name of the stack.

example:
    stack<int> s;
    s.push(10);
    s.push(20);
    s.pop();     // Removes 20, Stack: [10]


### s.top() operation
- returns a reference to the top element of the stack.
- does not remove the element.
- calling top() on empty stack causes undefined behavior.

syntax:
    s.top();
    - s is the name of the stack.

example:
    stack<int> s;
    s.push(10);
    s.push(20);
    cout << s.top();  // Output: 20 (20 is still on stack)


### s.empty() operation
- checks whether the stack is empty.
- returns true if stack has no elements.
- returns false if stack has elements.

syntax:
    s.empty();
    - s is the name of the stack.

example:
    stack<int> s;
    if (s.empty()) {
        cout << "Stack is empty" << endl;
    }


### s.size() operation
- returns the number of elements in the stack.
- returns a value of type size_t.

syntax:
    s.size();
    - s is the name of the stack.

example:
    stack<int> s;
    s.push(10);
    s.push(20);
    cout << s.size();  // Output: 2


### s.emplace(args...) operation
- constructs element in-place at the top of the stack.
- more efficient than push for complex types.
- forwards arguments directly to the constructor.

syntax:
    s.emplace(args...);
    - s is the name of the stack.
    - args are constructor arguments.

example:
    stack<string> s;
    s.emplace("Hello");  // Constructs string in-place


### s.swap(other_stack) operation
- swaps the contents of two stacks.
- both stacks must have the same type.

syntax:
    s1.swap(s2);
    - s1 and s2 are the names of the stacks.

example:
    stack<int> s1, s2;
    s1.push(1);
    s2.push(2);
    s1.swap(s2);  // s1 has 2, s2 has 1


### Best Practices:
- Always check if stack is empty before calling top() or pop()
- Use emplace() instead of push() for complex objects
- Remember: pop() doesn't return the value, use top() first

*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    stack<int> numbers;

    cout << "=== empty() - Check if Stack is Empty ===" << endl;
    if (numbers.empty())
    {
        cout << "Stack is empty" << endl;
    }
    cout << "Size: " << numbers.size() << endl;
    cout << endl;

    cout << "=== push() - Add Elements to Stack ===" << endl;
    numbers.push(10);
    cout << "Pushed 10, size: " << numbers.size() << endl;
    numbers.push(20);
    cout << "Pushed 20, size: " << numbers.size() << endl;
    numbers.push(30);
    cout << "Pushed 30, size: " << numbers.size() << endl;
    numbers.push(40);
    cout << "Pushed 40, size: " << numbers.size() << endl;
    numbers.push(50);
    cout << "Pushed 50, size: " << numbers.size() << endl;
    cout << endl;

    cout << "=== size() - Get Number of Elements ===" << endl;
    cout << "Current size: " << numbers.size() << endl;
    cout << endl;

    cout << "=== top() - View Top Element ===" << endl;
    cout << "Top element: " << numbers.top() << endl;
    cout << "Size after top(): " << numbers.size() << " (top doesn't remove)" << endl;
    cout << endl;

    cout << "=== pop() - Remove Top Element ===" << endl;
    cout << "Before pop - top: " << numbers.top() << ", size: " << numbers.size() << endl;
    numbers.pop();
    cout << "After pop - top: " << numbers.top() << ", size: " << numbers.size() << endl;
    cout << endl;

    cout << "=== Popping All Elements ===" << endl;
    int count = 1;
    while (!numbers.empty())
    {
        cout << count << ". Pop: " << numbers.top() << " (size: " << numbers.size() << ")" << endl;
        numbers.pop();
        count++;
    }
    cout << endl;

    cout << "=== After Popping All ===" << endl;
    cout << "Is empty: " << (numbers.empty() ? "true" : "false") << endl;
    cout << "Size: " << numbers.size() << endl;
    cout << endl;

    // Demonstrate safe top() and pop() usage
    cout << "=== Safe Usage Pattern ===" << endl;
    stack<int> safeStack;
    safeStack.push(100);
    safeStack.push(200);

    if (!safeStack.empty())
    {
        cout << "Top element: " << safeStack.top() << endl;
        safeStack.pop();
        cout << "Removed top element safely" << endl;
    }

    // Try to pop from empty stack (commented to prevent crash)
    // safeStack.pop();  // DANGER: Undefined behavior if stack is empty!

    cout << "Always check empty() before pop() or top()" << endl;
    cout << endl;

    // emplace() example
    cout << "=== emplace() - Construct Element In-Place ===" << endl;
    stack<string> words;
    
    words.push("Hello");
    cout << "Used push for 'Hello'" << endl;
    
    words.emplace("World");
    cout << "Used emplace for 'World'" << endl;
    
    cout << "Top: " << words.top() << endl;
    cout << "Size: " << words.size() << endl;
    cout << endl;

    // swap() example
    cout << "=== swap() - Swap Two Stacks ===" << endl;
    stack<int> stack1, stack2;

    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    stack2.push(10);
    stack2.push(20);

    cout << "Before swap:" << endl;
    cout << "stack1 top: " << stack1.top() << ", size: " << stack1.size() << endl;
    cout << "stack2 top: " << stack2.top() << ", size: " << stack2.size() << endl;

    stack1.swap(stack2);

    cout << "After swap:" << endl;
    cout << "stack1 top: " << stack1.top() << ", size: " << stack1.size() << endl;
    cout << "stack2 top: " << stack2.top() << ", size: " << stack2.size() << endl;
    cout << endl;

    // Modifying top element
    cout << "=== Modifying Top Element ===" << endl;
    stack<int> modStack;
    modStack.push(5);
    
    cout << "Original top: " << modStack.top() << endl;
    modStack.top() = 99;  // Modify the top element
    cout << "Modified top: " << modStack.top() << endl;
    cout << endl;

    // Processing elements
    cout << "=== Processing All Elements ===" << endl;
    stack<int> processStack;
    for (int i = 1; i <= 5; ++i)
    {
        processStack.push(i * 10);
    }

    cout << "Processing stack (LIFO order):" << endl;
    int position = 1;
    while (!processStack.empty())
    {
        int value = processStack.top();
        cout << "Position " << position << ": " << value << endl;
        processStack.pop();
        position++;
    }
    cout << endl;

    // Copying stack elements (need temporary storage)
    cout << "=== Viewing Stack Contents (Without Destroying) ===" << endl;
    stack<int> original;
    original.push(100);
    original.push(200);
    original.push(300);

    stack<int> temp = original;  // Copy stack

    cout << "Stack contents (top to bottom):" << endl;
    while (!temp.empty())
    {
        cout << "  " << temp.top() << endl;
        temp.pop();
    }

    cout << "Original stack still intact, size: " << original.size() << endl;

    return 0;
}
