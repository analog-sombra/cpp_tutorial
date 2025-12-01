/*
### adding elements to a vector
- Directly initialize the vector with values
-- good approach for small, known sets of data.
-- we want to make a copy of an existing array or vector.
-- we want to initialize a vector with a specific number of identical elements.

- Mostly, when we create a vector,
-- we don't know how many elements we'll need in advance.
-- we don't know the value of those elements.

example:
- we need a vector with values form 0-9 -> we can use list initialization
- we need a vector with values from 0-999 -> using list initialization would be a disaster


### the push_back() operation
- it is better to create an empty vector and use a vector member named push_back to add elements at run time.
- teakes a value and pushes that value as a new last element onto the back of the vector.

syntax:
    vector_name.push_back(value);
    - vector_name is the name of the vector.
    - value is the element to be added to the end of the vector.

example:
    vector<int> numbers; // Create an empty vector of integers
    for (int i = 0; i < 10; ++i) {
        numbers.push_back(i); // Add values 0 to 9 to the vector
    }
    - This code creates an empty vector of integers and then uses a loop to add the values 0 to 9 to the vector using the push_back() method.
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> numbers; // Create an empty vector of integers

    // Use a loop to add values 0 to 9 to the vector
    for (int i = 0; i < 10; ++i)
    {
        numbers.push_back(i); // Add value i to the end of the vector
    }

    // Print the elements of the vector
    cout << "Vector elements: " << endl;
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        cout << numbers[i] << endl; // Access elements using the subscript operator
    }

    return 0;
}