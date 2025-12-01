/*
### Defalut initalization
syntax:
    vector <T> vector_name;
    - T is the type of elements.
    - vector_name is the name of the vector.


- creates an empty vector of the specified type T.

example:
    vector<int> numbers;
    - creates an empty vector of integers.


### coping elements from another vector
syntax:
    vector <T> vector_name (vector_to_copy);
    - T is the type of elements.
    - vector_name is the name of the new vector.
    - vector_to_copy is the existing vector from which elements will be copied.

    or
    vector <T> vector_name = vector_to_copy;
    - T is the type of elements.
    - vector_name is the name of the new vector.
    - vector_to_copy is the existing vector from which elements will be copied.


example:
    vector<int> original = {1, 2, 3, 4, 5};
    vector<int> copy1(original); // Using copy constructor
    vector<int> copy2 = original; // Using assignment operator
    vector<string> copy3 = original; // Error: type mismatch


### list initalizing a vector
- a vector from a list of zero or more initial element values enclosed in curly braces {}.
syntax:
    vector <T> vector_name = {element1, element2, element3, ...};
    - T is the type of elements.
    - vector_name is the name of the vector.
    - element1, element2, element3, ... are the initial elements of the vector.

example:
    vector<int> numbers = {1, 2, 3, 4, 5};
    - creates a vector of integers with initial elements 1, 2, 3, 4, and 5.


### initalizing a vector with a specific size
- A Vector can also be initialized from a count and an element value. We can also omit the vlaue and supply only a size.

syntax:
    vector <T> vector_name (size, value);
    - T is the type of elements.
    - vector_name is the name of the vector.
    - size is the number of elements in the vector.
    - value is the initial value for each element.

    or

    vector <T> vector_name (size);
    - T is the type of elements.
    - vector_name is the name of the vector.
    - size is the number of elements in the vector.

example:
    vector<int> numbers(5, 10); // Creates a vector of 5 integers, each initialized to 10
    vector<int> zeros(5); // Creates a vector of 5 integers, each initialized to 0


### List initalizer of Element count

example:
    vector<int> v1(5); v1 has 5 elements, each initialized to 0
    vector<int> v2{5}; v2 has 1 element with the value
    vector<int> v3(5, 10); v3 has 5 elements, each initialized to 10
    vector<int> v4{5, 10}; v4 has 2 elements:

    special case:
        vector<string> v1{10}; v1 has 10 elements, each initialized to an empty string
        vector<string> v2{10,"cup"}; v2 has 10 elements, each initialized to "cup"
        vector<string> s1(3); s1 has 3 elements, each initialized to an empty string
        vector<string> s2{"3"}; s2 has 1 element with the value "3"
        vector<string> s3(3, "hello"); s3 has 3 elements, each initialized to "hello"
        vector<string> s4{"3", "hello"}; s4 has 2 elements: "3" and "hello"

*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;
int main()
{
    // vector<string> v1{10};
    vector<string> v1(10,"cup");

    for (const auto &str : v1)
    {
        cout << "\"" << str << "\"" << endl; // Each element should be an empty string
    }

    return 0;
}