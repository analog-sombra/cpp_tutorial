/*
### Smart Pointers

### What are Smart Pointers?
- Objects that manage dynamically allocated memory automatically.
- Act like regular pointers but provide automatic memory management.
- Prevent memory leaks and dangling pointers.
- Part of C++11 standard (require <memory> header).

### Why Use Smart Pointers?
- Automatic cleanup: No need for manual delete
- Exception safety: Memory freed even if exception thrown
- Ownership semantics: Clear who owns the memory
- Prevent common errors: memory leaks, dangling pointers, double delete


### RAII (Resource Acquisition Is Initialization)
- Resource (memory) acquired in constructor
- Resource freed in destructor
- Automatic cleanup when smart pointer goes out of scope

example:
    {
        std::unique_ptr<int> ptr(new int(10));
        // Use ptr
    }  // ptr automatically deleted here


### Types of Smart Pointers:

1. unique_ptr
   - Exclusive ownership
   - Cannot be copied, only moved
   - Zero overhead compared to raw pointer
   - Use for single ownership

2. shared_ptr
   - Shared ownership
   - Reference counted
   - Automatically deleted when last shared_ptr is destroyed
   - Small overhead for reference counting
   - Use when multiple owners needed

3. weak_ptr
   - Non-owning reference to shared_ptr
   - Breaks circular references
   - Must convert to shared_ptr to access object
   - Use to observe object without affecting lifetime


### Header Required:
    #include <memory>


### Raw Pointer Problems:
    int* ptr = new int(10);
    // Forgot delete ptr;  → Memory leak!
    
    delete ptr;
    delete ptr;  → Double delete! Undefined behavior
    
    int* p = new int(10);
    delete p;
    *p = 20;  → Dangling pointer! Undefined behavior


### Smart Pointer Solutions:
    std::unique_ptr<int> ptr = std::make_unique<int>(10);
    // Automatic cleanup when ptr goes out of scope
    // Cannot accidentally double-delete
    // Cannot use after destruction


### Basic Syntax:
    std::unique_ptr<Type> ptr1 = std::make_unique<Type>(args);
    std::shared_ptr<Type> ptr2 = std::make_shared<Type>(args);
    std::weak_ptr<Type> ptr3 = ptr2;  // From shared_ptr


### Important Notes:
- Always prefer smart pointers over raw pointers for dynamic memory
- Use unique_ptr by default
- Use shared_ptr when shared ownership needed
- Use weak_ptr to break circular references
- Smart pointers have zero or minimal overhead
- Cannot convert unique_ptr to shared_ptr directly (use move)

*/

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class MyClass
{
private:
    string name;

public:
    MyClass(string n) : name(n)
    {
        cout << "  [MyClass '" << name << "' constructed]" << endl;
    }

    ~MyClass()
    {
        cout << "  [MyClass '" << name << "' destroyed]" << endl;
    }

    void display() const
    {
        cout << "  MyClass object: " << name << endl;
    }
};

void demonstrateRAII()
{
    cout << "Entering function (creating unique_ptr)" << endl;
    unique_ptr<MyClass> ptr = make_unique<MyClass>("RAII Demo");
    ptr->display();
    cout << "Exiting function (unique_ptr automatically destroyed)" << endl;
}

void rawPointerProblems()
{
    cout << "=== Raw Pointer Problems ===" << endl;
    
    cout << "\n1. Memory Leak:" << endl;
    cout << "   int* ptr = new int(10);" << endl;
    cout << "   // Forgot: delete ptr;" << endl;
    cout << "   → Memory is leaked!" << endl;

    cout << "\n2. Dangling Pointer:" << endl;
    cout << "   int* ptr = new int(10);" << endl;
    cout << "   delete ptr;" << endl;
    cout << "   *ptr = 20;  // Using deleted memory" << endl;
    cout << "   → Undefined behavior!" << endl;

    cout << "\n3. Double Delete:" << endl;
    cout << "   int* ptr = new int(10);" << endl;
    cout << "   delete ptr;" << endl;
    cout << "   delete ptr;  // Deleting twice" << endl;
    cout << "   → Undefined behavior!" << endl;

    cout << "\n4. Exception Safety:" << endl;
    cout << "   int* ptr = new int(10);" << endl;
    cout << "   riskyFunction();  // Throws exception" << endl;
    cout << "   delete ptr;  // Never reached!" << endl;
    cout << "   → Memory leaked!" << endl;
}

int main()
{
    cout << "=== What are Smart Pointers? ===" << endl;
    cout << "Smart pointers are objects that:" << endl;
    cout << "  - Manage dynamically allocated memory" << endl;
    cout << "  - Automatically free memory when no longer needed" << endl;
    cout << "  - Prevent memory leaks and dangling pointers" << endl;
    cout << "  - Provide ownership semantics" << endl;
    cout << endl;

    rawPointerProblems();
    cout << endl;

    cout << "=== RAII Demonstration ===" << endl;
    cout << "RAII = Resource Acquisition Is Initialization" << endl;
    cout << "Resource freed automatically in destructor" << endl;
    cout << endl;

    demonstrateRAII();
    cout << endl;

    cout << "=== Types of Smart Pointers ===" << endl;
    cout << "\n1. unique_ptr:" << endl;
    cout << "   - Exclusive ownership (only one owner)" << endl;
    cout << "   - Cannot be copied, only moved" << endl;
    cout << "   - Zero overhead vs raw pointer" << endl;
    cout << "   - Use case: Single owner, exclusive resource" << endl;
    cout << "   - Example: std::unique_ptr<int> ptr = std::make_unique<int>(42);" << endl;

    cout << "\n2. shared_ptr:" << endl;
    cout << "   - Shared ownership (multiple owners)" << endl;
    cout << "   - Reference counted" << endl;
    cout << "   - Deleted when last shared_ptr destroyed" << endl;
    cout << "   - Small overhead for reference count" << endl;
    cout << "   - Use case: Multiple owners, shared resource" << endl;
    cout << "   - Example: std::shared_ptr<int> ptr = std::make_shared<int>(42);" << endl;

    cout << "\n3. weak_ptr:" << endl;
    cout << "   - Non-owning reference to shared_ptr" << endl;
    cout << "   - Doesn't affect reference count" << endl;
    cout << "   - Breaks circular references" << endl;
    cout << "   - Must lock() to access object" << endl;
    cout << "   - Use case: Observer pattern, cache, breaking cycles" << endl;
    cout << "   - Example: std::weak_ptr<int> wptr = sharedPtr;" << endl;
    cout << endl;

    cout << "=== unique_ptr Quick Demo ===" << endl;
    {
        cout << "Creating unique_ptr" << endl;
        unique_ptr<MyClass> uptr = make_unique<MyClass>("UniqueDemo");
        uptr->display();
        cout << "Leaving scope (unique_ptr auto-deleted)" << endl;
    }
    cout << "After scope - object destroyed" << endl;
    cout << endl;

    cout << "=== shared_ptr Quick Demo ===" << endl;
    {
        cout << "Creating shared_ptr" << endl;
        shared_ptr<MyClass> sptr1 = make_shared<MyClass>("SharedDemo");
        cout << "Reference count: " << sptr1.use_count() << endl;

        {
            shared_ptr<MyClass> sptr2 = sptr1;
            cout << "After copying, reference count: " << sptr1.use_count() << endl;
            cout << "Leaving inner scope" << endl;
        }
        cout << "After inner scope, reference count: " << sptr1.use_count() << endl;
        cout << "Leaving outer scope" << endl;
    }
    cout << "After outer scope - object destroyed" << endl;
    cout << endl;

    cout << "=== weak_ptr Quick Demo ===" << endl;
    weak_ptr<MyClass> wptr;
    {
        shared_ptr<MyClass> sptr = make_shared<MyClass>("WeakDemo");
        wptr = sptr;

        cout << "weak_ptr.expired(): " << (wptr.expired() ? "true" : "false") << endl;
        cout << "Leaving scope (shared_ptr destroyed)" << endl;
    }
    cout << "After scope:" << endl;
    cout << "weak_ptr.expired(): " << (wptr.expired() ? "true" : "false") << endl;
    cout << endl;

    cout << "=== Raw Pointer vs Smart Pointer ===" << endl;
    cout << "\nRaw Pointer:" << endl;
    cout << "  int* ptr = new int(10);" << endl;
    cout << "  // ... use ptr ..." << endl;
    cout << "  delete ptr;  // Manual cleanup required!" << endl;
    cout << "  ptr = nullptr;  // Manual reset" << endl;

    cout << "\nSmart Pointer (unique_ptr):" << endl;
    cout << "  auto ptr = std::make_unique<int>(10);" << endl;
    cout << "  // ... use ptr ..." << endl;
    cout << "  // Automatic cleanup when out of scope!" << endl;
    cout << endl;

    cout << "=== When to Use Which Smart Pointer ===" << endl;
    cout << "\nUse unique_ptr when:" << endl;
    cout << "  - Single owner of resource" << endl;
    cout << "  - Transferring ownership (move semantics)" << endl;
    cout << "  - Default choice for dynamic memory" << endl;
    cout << "  - Factory functions returning objects" << endl;

    cout << "\nUse shared_ptr when:" << endl;
    cout << "  - Multiple owners needed" << endl;
    cout << "  - Unclear who should delete object" << endl;
    cout << "  - Sharing resources across threads" << endl;
    cout << "  - Implementing shared data structures" << endl;

    cout << "\nUse weak_ptr when:" << endl;
    cout << "  - Observing without owning" << endl;
    cout << "  - Breaking circular references" << endl;
    cout << "  - Cache implementations" << endl;
    cout << "  - Observer pattern" << endl;
    cout << endl;

    cout << "=== Benefits of Smart Pointers ===" << endl;
    cout << "1. Memory Safety: No memory leaks" << endl;
    cout << "2. Exception Safety: Cleanup even if exception thrown" << endl;
    cout << "3. Clear Ownership: Ownership semantics explicit" << endl;
    cout << "4. No Dangling Pointers: Cannot use after deletion" << endl;
    cout << "5. No Double Delete: Automatic management prevents this" << endl;
    cout << "6. Modern C++: Best practice for dynamic memory" << endl;
    cout << endl;

    cout << "=== Common Operations ===" << endl;
    cout << "Creation:" << endl;
    cout << "  auto uptr = std::make_unique<Type>(args);" << endl;
    cout << "  auto sptr = std::make_shared<Type>(args);" << endl;
    cout << endl;

    cout << "Access:" << endl;
    cout << "  *ptr        // Dereference" << endl;
    cout << "  ptr->method()  // Member access" << endl;
    cout << "  ptr.get()   // Get raw pointer" << endl;
    cout << endl;

    cout << "Ownership:" << endl;
    cout << "  unique_ptr: std::move(ptr)  // Transfer ownership" << endl;
    cout << "  shared_ptr: auto ptr2 = ptr1;  // Share ownership" << endl;
    cout << "  weak_ptr: auto sptr = wptr.lock();  // Temporary shared ownership" << endl;
    cout << endl;

    cout << "Reset:" << endl;
    cout << "  ptr.reset();        // Delete object, set to nullptr" << endl;
    cout << "  ptr.reset(new Type);  // Delete old, assign new" << endl;
    cout << endl;

    cout << "=== Best Practices ===" << endl;
    cout << "1. Prefer smart pointers over raw pointers for ownership" << endl;
    cout << "2. Use make_unique/make_shared instead of new" << endl;
    cout << "3. Default to unique_ptr, use shared_ptr when needed" << endl;
    cout << "4. Use weak_ptr to break circular references" << endl;
    cout << "5. Use raw pointers for non-owning references (parameters)" << endl;
    cout << "6. Never manually delete smart pointer's managed object" << endl;
    cout << "7. Don't store result of get() for later use" << endl;
    cout << endl;

    cout << "=== Header and Namespace ===" << endl;
    cout << "#include <memory>" << endl;
    cout << "std::unique_ptr" << endl;
    cout << "std::shared_ptr" << endl;
    cout << "std::weak_ptr" << endl;
    cout << "std::make_unique  // C++14" << endl;
    cout << "std::make_shared  // C++11" << endl;

    return 0;
}
