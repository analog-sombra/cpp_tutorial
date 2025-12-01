
/*
// Vector Type
 - vectors are sequence that represent a variable-sized arrays.

 containers - contains other objects
    - sequence containers
    - vector
    - deque
    - list

variable-size arrays - colleaction of objects
    - can grow and shrink in size


class template
    - a vector is a class template.
    - a blueprint from which specific class types can be created.
- Template:
    - Not funcations or classes
    - guideline for the compiler to use to create classes or functions

0 instantiation - Describle the procedure the compiler employs to build classes or functions out of templates.


- We specify which class to instantiate by supplying additional information depending on the template.

- Enclose it in two angle brackets after the template name.

- for Vectors:
 we specify the type of the objects the vector will hold inside the angle brackets.

 vector<type> vector_name;

    
*/


#include <iostream>
#include <vector> // include the vector header
using namespace std;
int main() {
    // Create a vector of integers
    vector<int> numbers = {1,2,3,4,5};

   
    // Display the elements of the vector
    cout << "Vector elements: " << endl;
   
    for(int i: numbers) {
        std::cout << i << " ";
    }
    cout << endl;

    // Display the size of the vector
    cout << "Vector size: " << numbers.size() << endl;

    // Accessing elements using at() method
    cout << "Element at index 2 using at(): " << numbers.at(2) << endl;

    // Accessing elements using [] operator
    cout << "Element at index 3 using []: " << numbers[3] << endl;

    // Add an element using push_back
    numbers.push_back(6);
    cout << "After adding 6, vector size: " << numbers.size() << endl;

    // Display all elements again
    cout << "Updated vector elements: ";
    for(int i: numbers) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}