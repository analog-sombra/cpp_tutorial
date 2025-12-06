/*
### std::unique_ptr

### What is unique_ptr?
- Smart pointer with exclusive ownership.
- Only one unique_ptr can own an object at a time.
- Cannot be copied, only moved.
- Zero overhead compared to raw pointer.
- Automatically deletes object when destroyed.

### Ownership Semantics
- Exclusive: Only one owner
- Non-copyable: Cannot copy unique_ptr
- Movable: Can transfer ownership via std::move()
- RAII: Resource freed in destructor


### Creating unique_ptr:

syntax:
    std::unique_ptr<Type> ptr1(new Type);              // Using new (old way)
    std::unique_ptr<Type> ptr2 = std::make_unique<Type>(args);  // Recommended (C++14)


### Why make_unique?
- Exception safe
- More concise
- Prevents memory leaks in constructor exceptions
- Recommended best practice


### Accessing Object:
    *ptr        // Dereference
    ptr->method()    // Member access
    ptr.get()   // Get raw pointer (doesn't transfer ownership)


### Transfer Ownership (Move):
- unique_ptr cannot be copied
- Must use std::move() to transfer ownership

syntax:
    std::unique_ptr<int> ptr1 = std::make_unique<int>(10);
    std::unique_ptr<int> ptr2 = std::move(ptr1);  // ptr1 is now nullptr


### Release Ownership:
    ptr.release()   // Returns raw pointer, ptr becomes nullptr
    ptr.reset()     // Deletes object, ptr becomes nullptr
    ptr.reset(new Type)  // Deletes old, assigns new


### unique_ptr as Function Parameter:
- Pass by value: Transfers ownership (use std::move)
- Pass by reference: Borrow without transferring
- Return by value: Automatic move, transfers ownership


### unique_ptr with Arrays:
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);
    arr[0] = 42;  // Array indexing works


### Custom Deleters:
- Specify custom cleanup function
- Useful for non-standard cleanup (files, handles)

syntax:
    std::unique_ptr<Type, Deleter> ptr(new Type, customDeleter);


### Important Notes:
- Default choice for owning pointers
- Zero runtime overhead
- Perfect for factory functions
- Use make_unique instead of new
- Cannot be stored in STL containers that require copying (use std::vector<unique_ptr> with move)

*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Resource
{
private:
    string name;

public:
    Resource(string n) : name(n)
    {
        cout << "  [Resource '" << name << "' acquired]" << endl;
    }

    ~Resource()
    {
        cout << "  [Resource '" << name << "' released]" << endl;
    }

    void use() const
    {
        cout << "  Using resource: " << name << endl;
    }

    string getName() const { return name; }
};

// Function that takes ownership
void takeOwnership(unique_ptr<Resource> ptr)
{
    cout << "takeOwnership() received: ";
    ptr->use();
    cout << "takeOwnership() scope ends (resource will be deleted)" << endl;
}

// Function that borrows without taking ownership
void borrowResource(const unique_ptr<Resource>& ptr)
{
    cout << "borrowResource() using: ";
    ptr->use();
    cout << "borrowResource() returns (resource still owned by caller)" << endl;
}

// Function that returns unique_ptr (transfers ownership to caller)
unique_ptr<Resource> createResource(string name)
{
    cout << "createResource() creating: " << name << endl;
    return make_unique<Resource>(name);
}

int main()
{
    cout << "=== Creating unique_ptr ===" << endl;
    unique_ptr<int> ptr1(new int(42));
    cout << "unique_ptr<int> ptr1(new int(42));" << endl;
    cout << "*ptr1 = " << *ptr1 << endl;
    cout << endl;

    cout << "=== Using make_unique (Recommended) ===" << endl;
    auto ptr2 = make_unique<int>(100);
    cout << "auto ptr2 = make_unique<int>(100);" << endl;
    cout << "*ptr2 = " << *ptr2 << endl;
    cout << "make_unique is exception-safe and more concise" << endl;
    cout << endl;

    cout << "=== unique_ptr with Custom Class ===" << endl;
    {
        unique_ptr<Resource> res = make_unique<Resource>("Resource1");
        res->use();
        cout << "Leaving scope..." << endl;
    }
    cout << "Resource automatically deleted" << endl;
    cout << endl;

    cout << "=== Accessing Object ===" << endl;
    auto numPtr = make_unique<int>(55);
    cout << "Dereference (*ptr): " << *numPtr << endl;
    
    auto resPtr = make_unique<Resource>("AccessDemo");
    cout << "Member access (ptr->): ";
    resPtr->use();
    
    cout << "Raw pointer (ptr.get()): " << resPtr.get() << endl;
    cout << "Note: get() doesn't transfer ownership" << endl;
    cout << endl;

    cout << "=== Move Semantics (Transfer Ownership) ===" << endl;
    unique_ptr<Resource> owner1 = make_unique<Resource>("Movable");
    cout << "owner1 created" << endl;
    cout << "owner1.get(): " << owner1.get() << endl;
    
    unique_ptr<Resource> owner2 = std::move(owner1);
    cout << "\nAfter owner2 = std::move(owner1):" << endl;
    cout << "owner1.get(): " << owner1.get() << " (nullptr)" << endl;
    cout << "owner2.get(): " << owner2.get() << endl;
    cout << "Ownership transferred to owner2" << endl;
    cout << endl;

    cout << "=== Cannot Copy unique_ptr ===" << endl;
    auto original = make_unique<int>(99);
    // auto copy = original;  // ERROR: Copy constructor deleted
    cout << "unique_ptr<int> copy = original;  // Compilation error!" << endl;
    cout << "unique_ptr is non-copyable (exclusive ownership)" << endl;
    cout << endl;

    cout << "=== reset() - Delete and Reset ===" << endl;
    unique_ptr<Resource> resetDemo = make_unique<Resource>("ResetDemo");
    cout << "Before reset(): " << resetDemo.get() << endl;
    
    resetDemo.reset();
    cout << "After reset(): " << resetDemo.get() << " (nullptr)" << endl;
    cout << "Object deleted, pointer set to nullptr" << endl;
    cout << endl;

    cout << "=== reset() with New Object ===" << endl;
    unique_ptr<Resource> resetDemo2 = make_unique<Resource>("First");
    cout << "Before reset(new Resource):" << endl;
    
    resetDemo2.reset(new Resource("Second"));
    cout << "After reset(new Resource): Old deleted, new assigned" << endl;
    cout << endl;

    cout << "=== release() - Surrender Ownership ===" << endl;
    unique_ptr<Resource> releaseDemo = make_unique<Resource>("ReleaseDemo");
    cout << "Before release():" << endl;
    cout << "  releaseDemo.get(): " << releaseDemo.get() << endl;
    
    Resource* rawPtr = releaseDemo.release();
    cout << "After release():" << endl;
    cout << "  releaseDemo.get(): " << releaseDemo.get() << " (nullptr)" << endl;
    cout << "  rawPtr: " << rawPtr << endl;
    cout << "  Now responsible for manual delete!" << endl;
    
    delete rawPtr;
    cout << "  delete rawPtr; (manual cleanup)" << endl;
    cout << endl;

    cout << "=== Passing unique_ptr to Function (Take Ownership) ===" << endl;
    unique_ptr<Resource> ownedRes = make_unique<Resource>("OwnedResource");
    cout << "Before function call: " << ownedRes.get() << endl;
    
    takeOwnership(std::move(ownedRes));
    
    cout << "After function call: " << ownedRes.get() << " (nullptr)" << endl;
    cout << "Ownership transferred, resource deleted in function" << endl;
    cout << endl;

    cout << "=== Passing unique_ptr to Function (Borrow) ===" << endl;
    unique_ptr<Resource> borrowedRes = make_unique<Resource>("BorrowedResource");
    cout << "Before function call: " << borrowedRes.get() << endl;
    
    borrowResource(borrowedRes);
    
    cout << "After function call: " << borrowedRes.get() << " (still owned)" << endl;
    cout << "Ownership retained by caller" << endl;
    cout << endl;

    cout << "=== Returning unique_ptr from Function ===" << endl;
    unique_ptr<Resource> returned = createResource("ReturnedResource");
    cout << "Caller received ownership: ";
    returned->use();
    cout << endl;

    cout << "=== unique_ptr with Arrays ===" << endl;
    unique_ptr<int[]> arr = make_unique<int[]>(5);
    
    cout << "Created array of 5 integers" << endl;
    for (int i = 0; i < 5; ++i)
    {
        arr[i] = (i + 1) * 10;
    }

    cout << "Array elements: ";
    for (int i = 0; i < 5; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Array automatically deleted (uses delete[] internally)" << endl;
    cout << endl;

    cout << "=== unique_ptr in Containers ===" << endl;
    vector<unique_ptr<Resource>> resources;
    
    cout << "Adding resources to vector:" << endl;
    resources.push_back(make_unique<Resource>("Vec1"));
    resources.push_back(make_unique<Resource>("Vec2"));
    resources.push_back(make_unique<Resource>("Vec3"));
    
    cout << "\nIterating through vector:" << endl;
    for (const auto& res : resources)
    {
        res->use();
    }
    
    cout << "\nLeaving scope (vector and all resources deleted)..." << endl;
    cout << endl;

    cout << "=== Checking for nullptr ===" << endl;
    unique_ptr<int> nullCheck;
    
    cout << "unique_ptr<int> nullCheck;" << endl;
    if (!nullCheck)
    {
        cout << "nullCheck is nullptr (default constructed)" << endl;
    }
    
    nullCheck = make_unique<int>(77);
    if (nullCheck)
    {
        cout << "nullCheck is valid: " << *nullCheck << endl;
    }
    cout << endl;

    cout << "=== unique_ptr Boolean Context ===" << endl;
    unique_ptr<int> boolPtr;
    
    cout << "Before assignment:" << endl;
    cout << "  if (boolPtr): " << (boolPtr ? "true" : "false") << endl;
    
    boolPtr = make_unique<int>(123);
    cout << "After assignment:" << endl;
    cout << "  if (boolPtr): " << (boolPtr ? "true" : "false") << endl;
    cout << endl;

    cout << "=== swap() Two unique_ptrs ===" << endl;
    auto swap1 = make_unique<Resource>("Swap1");
    auto swap2 = make_unique<Resource>("Swap2");
    
    cout << "Before swap:" << endl;
    cout << "  swap1: " << swap1->getName() << endl;
    cout << "  swap2: " << swap2->getName() << endl;
    
    swap1.swap(swap2);
    
    cout << "After swap:" << endl;
    cout << "  swap1: " << swap1->getName() << endl;
    cout << "  swap2: " << swap2->getName() << endl;
    cout << endl;

    cout << "=== Factory Pattern with unique_ptr ===" << endl;
    cout << "Factory functions return unique_ptr to transfer ownership:" << endl;
    cout << "  unique_ptr<Type> create() {" << endl;
    cout << "      return make_unique<Type>(args);" << endl;
    cout << "  }" << endl;
    cout << "Caller receives ownership automatically (no std::move needed)" << endl;
    cout << endl;

    cout << "=== Performance ===" << endl;
    cout << "unique_ptr has ZERO overhead compared to raw pointer:" << endl;
    cout << "  - Same size as raw pointer" << endl;
    cout << "  - No reference counting" << endl;
    cout << "  - Compiler optimizations apply" << endl;
    cout << "  - Inlined operations" << endl;
    cout << "Always prefer unique_ptr over raw pointer for ownership!" << endl;
    cout << endl;

    cout << "=== Common Use Cases ===" << endl;
    cout << "1. Factory functions returning objects" << endl;
    cout << "2. RAII resource management (files, connections, etc.)" << endl;
    cout << "3. Storing dynamically allocated objects" << endl;
    cout << "4. Implementing pimpl idiom" << endl;
    cout << "5. Returning from functions (transfer ownership)" << endl;
    cout << "6. Containers of polymorphic objects" << endl;
    cout << endl;

    cout << "=== Best Practices ===" << endl;
    cout << "1. Use make_unique instead of new" << endl;
    cout << "2. Pass by const& to borrow without transferring ownership" << endl;
    cout << "3. Pass by value (with std::move) to transfer ownership" << endl;
    cout << "4. Return by value to give ownership to caller" << endl;
    cout << "5. Use get() only for passing to legacy APIs" << endl;
    cout << "6. Set to nullptr after release() if keeping raw pointer" << endl;
    cout << "7. Use unique_ptr by default, shared_ptr when needed" << endl;
    cout << endl;

    cout << "=== Common Operations Summary ===" << endl;
    cout << "Create:  auto ptr = std::make_unique<Type>(args);" << endl;
    cout << "Access:  *ptr, ptr->member(), ptr.get()" << endl;
    cout << "Move:    auto ptr2 = std::move(ptr1);" << endl;
    cout << "Reset:   ptr.reset(); or ptr.reset(new Type);" << endl;
    cout << "Release: Type* raw = ptr.release();" << endl;
    cout << "Check:   if (ptr) or if (!ptr)" << endl;
    cout << "Swap:    ptr1.swap(ptr2);" << endl;

    return 0;
}
