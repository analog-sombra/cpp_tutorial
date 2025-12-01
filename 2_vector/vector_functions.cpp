/*
### Vector Functions

### v.clear() operation
- removes all elements from the vector.
- after calling clear(), the size of the vector becomes 0.

syntax:
    v.clear();
    - v is the name of the vector.

example:
    vector<int> numbers = {1, 2, 3, 4, 5};
    numbers.clear(); // Removes all elements


### v.pop_back() operation
- removes the last element from the vector.
- reduces the size of the vector by 1.

syntax:
    v.pop_back();
    - v is the name of the vector.

example:
    vector<int> numbers = {1, 2, 3, 4, 5};
    numbers.pop_back(); // Removes 5


### v.insert() operation
- inserts elements at a specified position in the vector.
- can insert single element or multiple elements.

syntax:
    v.insert(position, value);
    - v is the name of the vector.
    - position is an iterator pointing to the location where the element should be inserted.
    - value is the element to be inserted.

example:
    vector<int> numbers = {1, 2, 3, 4, 5};
    numbers.insert(numbers.begin() + 2, 10); // Inserts 10 at index 2


### v.erase() operation
- removes elements from the vector at a specified position or range.

syntax:
    v.erase(position);
    v.erase(first, last);
    - v is the name of the vector.
    - position is an iterator pointing to the element to be removed.
    - first, last define a range of elements to be removed.

example:
    vector<int> numbers = {1, 2, 3, 4, 5};
    numbers.erase(numbers.begin() + 2); // Removes element at index 2


### v.resize() operation
- changes the size of the vector.
- if new size is greater, new elements are added (default-initialized).
- if new size is smaller, elements are removed from the end.

syntax:
    v.resize(new_size);
    v.resize(new_size, value);
    - v is the name of the vector.
    - new_size is the new size of the vector.
    - value is the value to initialize new elements (optional).

example:
    vector<int> numbers = {1, 2, 3};
    numbers.resize(5, 0); // Resizes to 5, new elements are 0


### v.reserve() operation
- reserves memory for the vector without changing its size.
- useful for performance optimization when you know the approximate size.

syntax:
    v.reserve(capacity);
    - v is the name of the vector.
    - capacity is the amount of memory to reserve.

example:
    vector<int> numbers;
    numbers.reserve(100); // Reserves memory for 100 elements


### v.capacity() operation
- returns the amount of memory currently allocated for the vector.
- capacity is always >= size.

syntax:
    v.capacity();
    - v is the name of the vector.

example:
    vector<int> numbers = {1, 2, 3};
    cout << "Capacity: " << numbers.capacity() << endl;


### v.front() operation
- returns a reference to the first element in the vector.

syntax:
    v.front();
    - v is the name of the vector.

example:
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << "First element: " << numbers.front() << endl;


### v.back() operation
- returns a reference to the last element in the vector.

syntax:
    v.back();
    - v is the name of the vector.

example:
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << "Last element: " << numbers.back() << endl;


### v.data() operation
- returns a pointer to the underlying array serving as element storage.

syntax:
    v.data();
    - v is the name of the vector.

example:
    vector<int> numbers = {1, 2, 3, 4, 5};
    int* ptr = numbers.data();
    cout << "First element via pointer: " << *ptr << endl;

*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> numbers = {1, 2, 3, 4, 5};

    // Display original vector
    cout << "Original vector: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "Size: " << numbers.size() << ", Capacity: " << numbers.capacity() << endl;
    cout << endl;

    // front() and back()
    cout << "First element (front): " << numbers.front() << endl;
    cout << "Last element (back): " << numbers.back() << endl;
    cout << endl;

    // pop_back() - remove last element
    numbers.pop_back();
    cout << "After pop_back: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "Size: " << numbers.size() << endl;
    cout << endl;

    // insert() - insert element at position
    numbers.insert(numbers.begin() + 2, 10);
    cout << "After inserting 10 at index 2: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;

    // erase() - remove element at position
    numbers.erase(numbers.begin() + 1);
    cout << "After erasing element at index 1: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;

    // resize() - change vector size
    numbers.resize(7, 99);
    cout << "After resizing to 7 with value 99: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "Size: " << numbers.size() << ", Capacity: " << numbers.capacity() << endl;
    cout << endl;

    // reserve() - reserve memory
    numbers.reserve(20);
    cout << "After reserving 20: ";
    cout << "Size: " << numbers.size() << ", Capacity: " << numbers.capacity() << endl;
    cout << endl;

    // data() - get pointer to underlying array
    int *ptr = numbers.data();
    cout << "First element via data() pointer: " << *ptr << endl;
    cout << "Second element via pointer: " << *(ptr + 1) << endl;
    cout << endl;

    // clear() - remove all elements
    numbers.clear();
    cout << "After clear(): ";
    cout << "Size: " << numbers.size() << ", Capacity: " << numbers.capacity() << endl;
    
    if (numbers.empty())
    {
        cout << "Vector is now empty." << endl;
    }

    return 0;
}
