/*
### Stack Practical Examples

### Example 1: Balanced Parentheses Checker
- Problem: Check if parentheses in an expression are balanced.
- Solution: Use stack to track opening brackets.
- Algorithm:
  1. Push opening brackets onto stack
  2. When closing bracket found, check if it matches top of stack
  3. If stack is empty at end, brackets are balanced


### Example 2: Reverse a String
- Problem: Reverse the characters in a string.
- Solution: Push all characters onto stack, then pop them.
- Why it works: LIFO reverses the order automatically.


### Example 3: Undo/Redo Functionality
- Problem: Implement undo/redo operations (like in text editors).
- Solution: Use two stacks - one for undo, one for redo.
- Algorithm:
  1. When action performed, push to undo stack
  2. When undo called, pop from undo stack and push to redo stack
  3. When redo called, pop from redo stack and push to undo stack


### Example 4: Decimal to Binary Conversion
- Problem: Convert decimal number to binary.
- Solution: Push remainders onto stack while dividing by 2.
- Why it works: Remainders come out in reverse order.


### Example 5: Expression Evaluation
- Problem: Evaluate postfix expressions (Reverse Polish Notation).
- Solution: Use stack to store operands.
- Example: "3 4 + 2 *" = (3 + 4) * 2 = 14


### Real-world Applications:
- Browser back/forward buttons
- Function call stack in programming
- Syntax parsing (compilers)
- Backtracking algorithms
- Depth-First Search (DFS)
- Expression evaluation

*/

#include <iostream>
#include <stack>
#include <string>
#include <cctype> // for isdigit

using namespace std;

// Example 1: Balanced Parentheses Checker
bool isBalanced(const string &expression)
{
    stack<char> s;

    for (char ch : expression)
    {
        // Push opening brackets
        if (ch == '(' || ch == '{' || ch == '[')
        {
            s.push(ch);
        }
        // Check closing brackets
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (s.empty())
            {
                return false; // Closing bracket without opening
            }

            char top = s.top();
            s.pop();

            // Check if brackets match
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '['))
            {
                return false;
            }
        }
    }

    return s.empty(); // Stack should be empty if balanced
}

// Example 2: Reverse a String
string reverseString(const string &text)
{
    stack<char> s;

    // Push all characters
    for (char ch : text)
    {
        s.push(ch);
    }

    // Pop to build reversed string
    string reversed;
    while (!s.empty())
    {
        reversed += s.top();
        s.pop();
    }

    return reversed;
}

// Example 3: Simple Undo System
class TextEditor
{
private:
    stack<string> undoStack;
    stack<string> redoStack;
    string currentText;

public:
    TextEditor() : currentText("") {}

    void type(const string &text)
    {
        undoStack.push(currentText); // Save current state
        currentText += text;
        // Clear redo stack when new action performed
        while (!redoStack.empty())
        {
            redoStack.pop();
        }
    }

    void undo()
    {
        if (!undoStack.empty())
        {
            redoStack.push(currentText); // Save current for redo
            currentText = undoStack.top();
            undoStack.pop();
        }
        else
        {
            cout << "Nothing to undo" << endl;
        }
    }

    void redo()
    {
        if (!redoStack.empty())
        {
            undoStack.push(currentText); // Save current for undo
            currentText = redoStack.top();
            redoStack.pop();
        }
        else
        {
            cout << "Nothing to redo" << endl;
        }
    }

    string getText() const
    {
        return currentText;
    }
};

// Example 4: Decimal to Binary Conversion
string decimalToBinary(int decimal)
{
    if (decimal == 0)
    {
        return "0";
    }

    stack<int> s;

    // Push remainders onto stack
    while (decimal > 0)
    {
        s.push(decimal % 2);
        decimal /= 2;
    }

    // Pop to build binary string
    string binary;
    while (!s.empty())
    {
        binary += to_string(s.top());
        s.pop();
    }

    return binary;
}

// Example 5: Simple Postfix Expression Evaluator
// Assumes valid single-digit operands and basic operators
int evaluatePostfix(const string &expression)
{
    stack<int> s;

    for (char ch : expression)
    {
        // Skip spaces
        if (ch == ' ')
        {
            continue;
        }

        // If digit, push to stack
        if (isdigit(ch))
        {
            s.push(ch - '0'); // Convert char to int
        }
        // If operator, pop two operands and compute
        else
        {
            if (s.size() < 2)
            {
                throw runtime_error("Invalid expression");
            }

            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();

            int result;
            switch (ch)
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            default:
                throw runtime_error("Invalid operator");
            }

            s.push(result);
        }
    }

    if (s.size() != 1)
    {
        throw runtime_error("Invalid expression");
    }

    return s.top();
}

int main()
{
    cout << "=== Example 1: Balanced Parentheses Checker ===" << endl;

    string expr1 = "{[()]}";
    string expr2 = "{[(])}";
    string expr3 = "((()))";
    string expr4 = "((())";

    cout << "\"" << expr1 << "\" is " << (isBalanced(expr1) ? "balanced" : "not balanced") << endl;
    cout << "\"" << expr2 << "\" is " << (isBalanced(expr2) ? "balanced" : "not balanced") << endl;
    cout << "\"" << expr3 << "\" is " << (isBalanced(expr3) ? "balanced" : "not balanced") << endl;
    cout << "\"" << expr4 << "\" is " << (isBalanced(expr4) ? "balanced" : "not balanced") << endl;
    cout << endl;

    cout << "=== Example 2: Reverse a String ===" << endl;

    string text = "STACK";
    string reversed = reverseString(text);

    cout << "Original: " << text << endl;
    cout << "Reversed: " << reversed << endl;
    cout << endl;

    cout << "=== Example 3: Undo/Redo System ===" << endl;

    TextEditor editor;

    cout << "Initial: \"" << editor.getText() << "\"" << endl;

    editor.type("Hello");
    cout << "After typing 'Hello': \"" << editor.getText() << "\"" << endl;

    editor.type(" World");
    cout << "After typing ' World': \"" << editor.getText() << "\"" << endl;

    editor.type("!");
    cout << "After typing '!': \"" << editor.getText() << "\"" << endl;

    editor.undo();
    cout << "After undo: \"" << editor.getText() << "\"" << endl;

    editor.undo();
    cout << "After undo: \"" << editor.getText() << "\"" << endl;

    editor.redo();
    cout << "After redo: \"" << editor.getText() << "\"" << endl;

    editor.type(" C++");
    cout << "After typing ' C++': \"" << editor.getText() << "\"" << endl;

    editor.redo(); // Should show "Nothing to redo"
    cout << endl;

    cout << "=== Example 4: Decimal to Binary Conversion ===" << endl;

    int numbers[] = {10, 25, 42, 255, 128};

    for (int num : numbers)
    {
        cout << "Decimal " << num << " = Binary " << decimalToBinary(num) << endl;
    }
    cout << endl;

    cout << "=== Example 5: Postfix Expression Evaluator ===" << endl;

    try
    {
        string postfix1 = "34+2*"; // (3 + 4) * 2 = 14
        string postfix2 = "52-3*"; // (5 - 2) * 3 = 9
        string postfix3 = "62/53*+"; // (6 / 2) + (5 * 3) = 18

        cout << "\"" << postfix1 << "\" = " << evaluatePostfix(postfix1) << endl;
        cout << "\"" << postfix2 << "\" = " << evaluatePostfix(postfix2) << endl;
        cout << "\"" << postfix3 << "\" = " << evaluatePostfix(postfix3) << endl;
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    cout << "=== Summary ===" << endl;
    cout << "Stack is perfect for:" << endl;
    cout << "- Reversing order (strings, arrays)" << endl;
    cout << "- Matching pairs (parentheses, tags)" << endl;
    cout << "- Undo/Redo functionality" << endl;
    cout << "- Expression evaluation" << endl;
    cout << "- Backtracking algorithms" << endl;

    return 0;
}
