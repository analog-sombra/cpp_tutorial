/*
### v.empty() operation
- checks whether the vector is empty (i.e., contains no elements).
- true, if v is empty.
- false, if v is not empty.

syntax:
    v.empty();
    - v is the name of the vector.
example:
    vector<int> numbers;
    if (numbers.empty()) {
        cout << "The vector is empty." << endl;
    } else {
        cout << "The vector is not empty." << endl;
    }


### v.size() operation
- returns the number of elements in the vector.
- returns a value of type size_type, which is an unsigned integral type.
syntax:
    v.size();
    - v is the name of the vector.

example:
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << "The size of the vector is: " << numbers.size() << endl;


### push_back() operation
- adds a new element at the end of the vector, after its current last element.

syntax:
    v.push_back(element);
    - v is the name of the vector.
    - element is the value to be added to the vector.

example:
    vector<int> numbers;
    numbers.push_back(10); // Adds 10 to the end of the vector
    numbers.push_back(20); // Adds 20 to the end of the vector


### v[n] operation
- accesses the element at index n of the vector.

syntax:
    v[n];
    - v is the name of the vector.
    - n is the index of the element to access (0-based index).

example:
    vector<int> numbers = {10, 20, 30, 40, 50};
    cout << "Element at index 2: " << numbers[2] << endl; // Outputs 30


### v1 = v2
- assigns the contents of vector v2 to vector v1, replacing its current contents.

syntax:
    v1 = v2;
    - v1 and v2 are the names of the vectors.

example:
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {4, 5, 6};
    v1 = v2; // Now v1 contains {4, 5, 6}

### v1 == v2
- compares two vectors v1 and v2 for equality. Returns true if they have the same size and all corresponding elements are equal; otherwise, returns false.

syntax:
    v1 == v2;
    - v1 and v2 are the names of the vectors.

example:
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 3};
    if (v1 == v2) {
        cout << "The vectors are equal." << endl;
    } else {
        cout << "The vectors are not equal." << endl;
    }

*/

#include <iostream>
#include <vector>

using namespace std;
int main()
{
    vector<int> numbers; // Create an empty vector of integers

    // Check if the vector is empty
    if (numbers.empty())
    {
        cout << "The vector is empty." << endl;
    }
    else
    {
        cout << "The vector is not empty." << endl;
    }

    // Add some elements to the vector
    numbers = {1, 2, 3, 4, 5};

    // Check again if the vector is empty
    if (numbers.empty())
    {
        cout << "The vector is empty." << endl;
    }
    else
    {
        cout << "The vector is not empty." << endl;
    }

    // Get and print the size of the vector
    cout << "The size of the vector is: " << numbers.size() << endl;

    // Add a new element to the end of the vector
    numbers.push_back(6);
    cout << "After push_back, the size of the vector is: " << numbers.size() << endl;

    // Access and print an element at a specific index
    int index = 2;
    cout << "Element at index " << index << ": " << numbers[index] << endl;

    // Assign contents of one vector to another
    vector<int> new_numbers = {10, 20, 30};
    numbers = new_numbers;
    cout << "After assignment, the elements in numbers are: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;

    // Compare two vectors for equality
    vector<int> compare_vector = {10, 20, 30};
    if (numbers == compare_vector)
    {
        cout << "The vectors are equal." << endl;
    }
    else
    {
        cout << "The vectors are not equal." << endl;
    }
    return 0;
}