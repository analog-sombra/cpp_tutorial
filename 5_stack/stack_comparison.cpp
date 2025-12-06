/*
### Stack Comparison Operators

### s1 == s2
- compares two stacks for equality.
- returns true if they have the same size and same elements in same order.
- compares from bottom to top.

syntax:
    s1 == s2;

example:
    stack<int> s1, s2;
    s1.push(1); s1.push(2);
    s2.push(1); s2.push(2);
    if (s1 == s2) { cout << "Equal"; }


### s1 != s2
- compares two stacks for inequality.
- returns true if stacks differ in size or elements.
- returns false if they are equal.

syntax:
    s1 != s2;

example:
    stack<int> s1, s2;
    s1.push(1);
    s2.push(2);
    if (s1 != s2) { cout << "Not equal"; }


### s1 < s2
- lexicographical comparison.
- compares elements from bottom to top.
- returns true if s1 is lexicographically less than s2.

syntax:
    s1 < s2;

example:
    stack<int> s1, s2;
    s1.push(1); s1.push(2);
    s2.push(1); s2.push(3);
    if (s1 < s2) { cout << "s1 is less than s2"; }


### s1 <= s2
- lexicographical comparison.
- returns true if s1 is less than or equal to s2.

syntax:
    s1 <= s2;

example:
    stack<int> s1, s2;
    s1.push(1);
    s2.push(1);
    if (s1 <= s2) { cout << "s1 is less than or equal to s2"; }


### s1 > s2
- lexicographical comparison.
- returns true if s1 is lexicographically greater than s2.

syntax:
    s1 > s2;

example:
    stack<int> s1, s2;
    s1.push(3);
    s2.push(2);
    if (s1 > s2) { cout << "s1 is greater than s2"; }


### s1 >= s2
- lexicographical comparison.
- returns true if s1 is greater than or equal to s2.

syntax:
    s1 >= s2;

example:
    stack<int> s1, s2;
    s1.push(2);
    s2.push(2);
    if (s1 >= s2) { cout << "s1 is greater than or equal to s2"; }


Note: Comparison is based on the underlying container
- Stack comparisons work like vector/deque comparisons
- Elements are compared from bottom to top
- First differing element determines the result

*/

#include <iostream>
#include <stack>

using namespace std;

// Helper function to create a stack from initializer list
template <typename T>
stack<T> makeStack(initializer_list<T> values)
{
    stack<T> s;
    for (const auto &val : values)
    {
        s.push(val);
    }
    return s;
}

// Helper function to display stack contents (destructive)
template <typename T>
void displayStack(stack<T> s, const string &name)
{
    cout << name << " (bottom to top): ";
    if (s.empty())
    {
        cout << "[empty]";
    }
    else
    {
        stack<T> temp;
        // Reverse to show bottom to top
        while (!s.empty())
        {
            temp.push(s.top());
            s.pop();
        }
        bool first = true;
        while (!temp.empty())
        {
            if (!first)
                cout << ", ";
            cout << temp.top();
            temp.pop();
            first = false;
        }
    }
    cout << endl;
}

int main()
{
    // Create test stacks
    stack<int> s1 = makeStack<int>({1, 2, 3});
    stack<int> s2 = makeStack<int>({1, 2, 3});
    stack<int> s3 = makeStack<int>({1, 2, 4});
    stack<int> s4 = makeStack<int>({1, 3, 3});
    stack<int> s5 = makeStack<int>({1, 2});

    cout << "Stack contents:" << endl;
    displayStack(s1, "s1");
    displayStack(s2, "s2");
    displayStack(s3, "s3");
    displayStack(s4, "s4");
    displayStack(s5, "s5");
    cout << endl;

    // Equality comparison (==)
    cout << "=== Equality Comparison (==) ===" << endl;
    cout << "s1 == s2: " << (s1 == s2 ? "true" : "false") << " (identical stacks)" << endl;
    cout << "s1 == s3: " << (s1 == s3 ? "true" : "false") << " (different top element)" << endl;
    cout << "s1 == s5: " << (s1 == s5 ? "true" : "false") << " (different sizes)" << endl;
    cout << endl;

    // Inequality comparison (!=)
    cout << "=== Inequality Comparison (!=) ===" << endl;
    cout << "s1 != s2: " << (s1 != s2 ? "true" : "false") << endl;
    cout << "s1 != s3: " << (s1 != s3 ? "true" : "false") << endl;
    cout << "s1 != s5: " << (s1 != s5 ? "true" : "false") << endl;
    cout << endl;

    // Less than (<)
    cout << "=== Less Than (<) ===" << endl;
    cout << "s1 < s3: " << (s1 < s3 ? "true" : "false") << " (3 < 4 at top)" << endl;
    cout << "s1 < s4: " << (s1 < s4 ? "true" : "false") << " (2 < 3 at middle)" << endl;
    cout << "s5 < s1: " << (s5 < s1 ? "true" : "false") << " (shorter stack)" << endl;
    cout << "s1 < s5: " << (s1 < s5 ? "true" : "false") << endl;
    cout << endl;

    // Less than or equal to (<=)
    cout << "=== Less Than or Equal To (<=) ===" << endl;
    cout << "s1 <= s2: " << (s1 <= s2 ? "true" : "false") << " (equal)" << endl;
    cout << "s1 <= s3: " << (s1 <= s3 ? "true" : "false") << " (less)" << endl;
    cout << "s3 <= s1: " << (s3 <= s1 ? "true" : "false") << endl;
    cout << endl;

    // Greater than (>)
    cout << "=== Greater Than (>) ===" << endl;
    cout << "s3 > s1: " << (s3 > s1 ? "true" : "false") << " (4 > 3 at top)" << endl;
    cout << "s4 > s1: " << (s4 > s1 ? "true" : "false") << " (3 > 2 at middle)" << endl;
    cout << "s1 > s5: " << (s1 > s5 ? "true" : "false") << " (longer stack)" << endl;
    cout << endl;

    // Greater than or equal to (>=)
    cout << "=== Greater Than or Equal To (>=) ===" << endl;
    cout << "s1 >= s2: " << (s1 >= s2 ? "true" : "false") << " (equal)" << endl;
    cout << "s3 >= s1: " << (s3 >= s1 ? "true" : "false") << " (greater)" << endl;
    cout << "s1 >= s3: " << (s1 >= s3 ? "true" : "false") << endl;
    cout << endl;

    // String stacks comparison
    cout << "=== String Stack Comparison ===" << endl;
    stack<string> str1 = makeStack<string>({"apple", "banana"});
    stack<string> str2 = makeStack<string>({"apple", "banana"});
    stack<string> str3 = makeStack<string>({"apple", "cherry"});

    displayStack(str1, "str1");
    displayStack(str2, "str2");
    displayStack(str3, "str3");
    cout << endl;

    cout << "str1 == str2: " << (str1 == str2 ? "true" : "false") << endl;
    cout << "str1 < str3: " << (str1 < str3 ? "true" : "false") << " (banana < cherry)" << endl;
    cout << "str3 > str1: " << (str3 > str1 ? "true" : "false") << endl;
    cout << endl;

    // Empty stack comparison
    cout << "=== Empty Stack Comparison ===" << endl;
    stack<int> empty1, empty2;
    stack<int> nonEmpty = makeStack<int>({1});

    cout << "empty1 == empty2: " << (empty1 == empty2 ? "true" : "false") << endl;
    cout << "empty1 < nonEmpty: " << (empty1 < nonEmpty ? "true" : "false") << endl;
    cout << "nonEmpty > empty1: " << (nonEmpty > empty1 ? "true" : "false") << endl;
    cout << endl;

    // Demonstrating lexicographical ordering
    cout << "=== Lexicographical Ordering Examples ===" << endl;
    stack<int> a = makeStack<int>({1, 2, 3});
    stack<int> b = makeStack<int>({1, 2, 4});
    stack<int> c = makeStack<int>({1, 3, 2});
    stack<int> d = makeStack<int>({1, 2, 3, 4});

    displayStack(a, "a");
    displayStack(b, "b");
    displayStack(c, "c");
    displayStack(d, "d");
    cout << endl;

    cout << "a < b: " << (a < b ? "true" : "false") << " (3 < 4)" << endl;
    cout << "a < c: " << (a < c ? "true" : "false") << " (2 < 3 at second position)" << endl;
    cout << "a < d: " << (a < d ? "true" : "false") << " (a is prefix of d)" << endl;
    cout << "d > a: " << (d > a ? "true" : "false") << " (longer with same prefix)" << endl;

    return 0;
}
