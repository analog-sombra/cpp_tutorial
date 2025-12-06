/*
### Smart Pointer Comparison

This file compares unique_ptr, shared_ptr, and weak_ptr to help you choose
the right smart pointer for your use case.


### Quick Decision Guide:

Use unique_ptr when:
- Single owner of resource
- Transferring ownership
- Factory functions
- Default choice for dynamic allocation

Use shared_ptr when:
- Multiple owners needed
- Unclear who should delete
- Sharing across threads
- Reference-counted resources

Use weak_ptr when:
- Observing without owning
- Breaking circular references
- Cache implementations
- Non-owning back-references


### Feature Comparison Table:

                    unique_ptr      shared_ptr      weak_ptr
Ownership:          Exclusive       Shared          None
Copyable:           No              Yes             Yes
Movable:            Yes             Yes             Yes
Reference Count:    No              Yes             No (uses shared)
Overhead:           Zero            Small           Tiny
Direct Access:      Yes             Yes             No (must lock)
Thread Safe:        N/A             Count only      Count only


### Ownership Semantics:

unique_ptr:
- One owner at a time
- Cannot share ownership
- Transfer via std::move()

shared_ptr:
- Multiple owners simultaneously
- Reference counted
- Automatic cleanup when last owner destroyed

weak_ptr:
- No ownership
- Observes shared_ptr
- Doesn't affect lifetime


### Memory Layout:

unique_ptr:
[pointer] → [object]
Size: sizeof(void*)

shared_ptr:
[obj_ptr][ctrl_ptr] → [object] / [control block]
Size: 2 * sizeof(void*)

weak_ptr:
[obj_ptr][ctrl_ptr] → (references shared_ptr's control block)
Size: 2 * sizeof(void*)


### Performance Characteristics:

unique_ptr:
- Zero overhead
- Same as raw pointer
- No reference counting
- No atomic operations

shared_ptr:
- Small overhead (control block)
- Atomic increment/decrement
- Two allocations (unless make_shared)
- Thread-safe reference counting

weak_ptr:
- Minimal overhead
- No object ownership
- lock() creates temporary shared_ptr
- Thread-safe conversion


### Conversion Rules:

unique_ptr → shared_ptr: ✓ (via std::move)
unique_ptr → weak_ptr:   ✗ (cannot convert)
shared_ptr → unique_ptr: ✗ (cannot convert)
shared_ptr → weak_ptr:   ✓ (direct assignment)
weak_ptr → shared_ptr:   ✓ (via lock())
weak_ptr → unique_ptr:   ✗ (cannot convert)


### Thread Safety:

unique_ptr:
- Not inherently thread-safe
- No shared state to protect
- Safe if used by single thread

shared_ptr:
- Reference counting is thread-safe
- Object itself is NOT thread-safe
- Multiple threads can own same object safely
- Accessing object needs synchronization

weak_ptr:
- lock() is thread-safe
- Can safely check existence from multiple threads
- Object access still needs synchronization

*/

#include <iostream>
#include <memory>
#include <string>
#include <chrono>

using namespace std;

class Resource
{
private:
    string name;

public:
    Resource(string n) : name(n)
    {
        cout << "  [" << name << " created]" << endl;
    }

    ~Resource()
    {
        cout << "  [" << name << " destroyed]" << endl;
    }

    void use() const
    {
        cout << "  Using: " << name << endl;
    }

    string getName() const { return name; }
};

int main()
{
    cout << "=== Smart Pointer Size Comparison ===" << endl;
    cout << "sizeof(Resource*):        " << sizeof(Resource*) << " bytes" << endl;
    cout << "sizeof(unique_ptr):       " << sizeof(unique_ptr<Resource>) << " bytes" << endl;
    cout << "sizeof(shared_ptr):       " << sizeof(shared_ptr<Resource>) << " bytes" << endl;
    cout << "sizeof(weak_ptr):         " << sizeof(weak_ptr<Resource>) << " bytes" << endl;
    cout << endl;

    cout << "=== Ownership Demonstration ===" << endl;
    
    cout << "\n1. unique_ptr (Exclusive Ownership):" << endl;
    {
        unique_ptr<Resource> uptr = make_unique<Resource>("Unique");
        // unique_ptr<Resource> copy = uptr;  // ERROR: Cannot copy
        unique_ptr<Resource> moved = std::move(uptr);
        cout << "  After move: uptr is " << (uptr ? "valid" : "nullptr") << endl;
    }

    cout << "\n2. shared_ptr (Shared Ownership):" << endl;
    {
        shared_ptr<Resource> sptr1 = make_shared<Resource>("Shared");
        cout << "  Initial count: " << sptr1.use_count() << endl;
        
        shared_ptr<Resource> sptr2 = sptr1;  // Copy OK
        cout << "  After copy: count = " << sptr1.use_count() << endl;
        
        shared_ptr<Resource> sptr3 = std::move(sptr1);  // Move also OK
        cout << "  After move: count = " << sptr3.use_count() << endl;
    }

    cout << "\n3. weak_ptr (No Ownership):" << endl;
    {
        weak_ptr<Resource> wptr;
        {
            shared_ptr<Resource> sptr = make_shared<Resource>("Observed");
            wptr = sptr;
            cout << "  Inside scope: expired = " << wptr.expired() << endl;
        }
        cout << "  Outside scope: expired = " << wptr.expired() << endl;
    }
    cout << endl;

    cout << "=== Conversion Demonstration ===" << endl;
    
    cout << "\n1. unique_ptr → shared_ptr (via move):" << endl;
    {
        unique_ptr<Resource> uptr = make_unique<Resource>("U2S");
        shared_ptr<Resource> sptr = std::move(uptr);
        cout << "  Converted successfully" << endl;
        cout << "  uptr is now: " << (uptr ? "valid" : "nullptr") << endl;
        cout << "  sptr count: " << sptr.use_count() << endl;
    }

    cout << "\n2. shared_ptr → weak_ptr:" << endl;
    {
        shared_ptr<Resource> sptr = make_shared<Resource>("S2W");
        weak_ptr<Resource> wptr = sptr;
        cout << "  Converted successfully" << endl;
        cout << "  sptr count (unchanged): " << sptr.use_count() << endl;
    }

    cout << "\n3. weak_ptr → shared_ptr (via lock):" << endl;
    {
        shared_ptr<Resource> sptr = make_shared<Resource>("W2S");
        weak_ptr<Resource> wptr = sptr;
        
        if (auto locked = wptr.lock())
        {
            cout << "  Locked successfully" << endl;
            cout << "  Temp shared_ptr count: " << locked.use_count() << endl;
        }
    }
    cout << endl;

    cout << "=== Access Patterns ===" << endl;
    
    cout << "\n1. unique_ptr (Direct Access):" << endl;
    {
        auto uptr = make_unique<Resource>("UniqueAccess");
        uptr->use();
        (*uptr).use();
        Resource* raw = uptr.get();
        cout << "  Raw pointer: " << raw << endl;
    }

    cout << "\n2. shared_ptr (Direct Access):" << endl;
    {
        auto sptr = make_shared<Resource>("SharedAccess");
        sptr->use();
        (*sptr).use();
        Resource* raw = sptr.get();
        cout << "  Raw pointer: " << raw << endl;
    }

    cout << "\n3. weak_ptr (Indirect via lock):" << endl;
    {
        auto sptr = make_shared<Resource>("WeakAccess");
        weak_ptr<Resource> wptr = sptr;
        
        if (auto locked = wptr.lock())
        {
            locked->use();
        }
        // Cannot use wptr->use() or *wptr directly
    }
    cout << endl;

    cout << "=== Use Case: Single Owner ===" << endl;
    {
        unique_ptr<Resource> owner = make_unique<Resource>("SingleOwner");
        cout << "Best choice: unique_ptr" << endl;
        cout << "  - Zero overhead" << endl;
        cout << "  - Clear ownership semantics" << endl;
        cout << "  - Efficient" << endl;
    }
    cout << endl;

    cout << "=== Use Case: Multiple Owners ===" << endl;
    {
        shared_ptr<Resource> owner1 = make_shared<Resource>("MultiOwner");
        shared_ptr<Resource> owner2 = owner1;
        shared_ptr<Resource> owner3 = owner1;
        
        cout << "Best choice: shared_ptr" << endl;
        cout << "  - Reference counted" << endl;
        cout << "  - Automatic cleanup when last owner done" << endl;
        cout << "  - Current owners: " << owner1.use_count() << endl;
    }
    cout << endl;

    cout << "=== Use Case: Observer Pattern ===" << endl;
    {
        shared_ptr<Resource> subject = make_shared<Resource>("Subject");
        weak_ptr<Resource> observer = subject;
        
        cout << "Best choice: weak_ptr for observer" << endl;
        cout << "  - Doesn't keep subject alive" << endl;
        cout << "  - Can check if subject still exists" << endl;
        cout << "  - Prevents circular references" << endl;
        cout << "  Subject count: " << subject.use_count() << endl;
    }
    cout << endl;

    cout << "=== Use Case: Circular Reference ===" << endl;
    struct Node
    {
        shared_ptr<Node> next;
        weak_ptr<Node> prev;  // Break cycle with weak_ptr
        string data;
        
        Node(string d) : data(d)
        {
            cout << "  [Node " << data << " created]" << endl;
        }
        
        ~Node()
        {
            cout << "  [Node " << data << " destroyed]" << endl;
        }
    };
    
    {
        shared_ptr<Node> node1 = make_shared<Node>("A");
        shared_ptr<Node> node2 = make_shared<Node>("B");
        
        node1->next = node2;
        node2->prev = node1;  // weak_ptr breaks cycle
        
        cout << "Best choice: shared_ptr + weak_ptr" << endl;
        cout << "  - shared_ptr for forward (owning)" << endl;
        cout << "  - weak_ptr for backward (non-owning)" << endl;
        cout << "  - Prevents memory leak" << endl;
    }
    cout << endl;

    cout << "=== Performance Comparison ===" << endl;
    const int iterations = 1000000;
    
    cout << "\nCreation/Destruction (1M iterations):" << endl;
    
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        unique_ptr<int> ptr = make_unique<int>(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto uniqueDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "  unique_ptr: " << uniqueDuration << " ms" << endl;
    
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        shared_ptr<int> ptr = make_shared<int>(i);
    }
    end = chrono::high_resolution_clock::now();
    auto sharedDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "  shared_ptr: " << sharedDuration << " ms" << endl;
    
    cout << "  Overhead ratio: " << (double)sharedDuration / uniqueDuration << "x" << endl;
    cout << endl;

    cout << "=== When to Use Each ===" << endl;
    
    cout << "\nuse unique_ptr for:" << endl;
    cout << "  ✓ Factory functions returning new objects" << endl;
    cout << "  ✓ RAII wrappers (files, connections)" << endl;
    cout << "  ✓ Pimpl idiom implementation" << endl;
    cout << "  ✓ Containers of polymorphic objects" << endl;
    cout << "  ✓ Default choice for ownership" << endl;
    
    cout << "\nuse shared_ptr for:" << endl;
    cout << "  ✓ Multiple owners genuinely needed" << endl;
    cout << "  ✓ Sharing across threads" << endl;
    cout << "  ✓ Graph structures (with weak_ptr)" << endl;
    cout << "  ✓ Caching with shared ownership" << endl;
    cout << "  ✓ Callbacks that outlive creator" << endl;
    
    cout << "\nuse weak_ptr for:" << endl;
    cout << "  ✓ Breaking circular references" << endl;
    cout << "  ✓ Observer pattern (observers)" << endl;
    cout << "  ✓ Cache (don't keep alive)" << endl;
    cout << "  ✓ Parent pointers in trees" << endl;
    cout << "  ✓ Temporary observers" << endl;
    cout << endl;

    cout << "=== Common Mistakes ===" << endl;
    
    cout << "\n1. Using shared_ptr unnecessarily:" << endl;
    cout << "  BAD:  shared_ptr<Resource> ptr = make_shared<Resource>();" << endl;
    cout << "  GOOD: unique_ptr<Resource> ptr = make_unique<Resource>();" << endl;
    cout << "  Use unique_ptr by default!" << endl;
    
    cout << "\n2. Creating shared_ptr from raw pointer twice:" << endl;
    cout << "  Resource* raw = new Resource();" << endl;
    cout << "  shared_ptr<Resource> ptr1(raw);" << endl;
    cout << "  shared_ptr<Resource> ptr2(raw);  // WRONG! Double delete" << endl;
    
    cout << "\n3. Storing weak_ptr.lock() result long-term:" << endl;
    cout << "  shared_ptr<Resource> stored = wptr.lock();  // WRONG!" << endl;
    cout << "  // Object might be deleted while 'stored' exists" << endl;
    
    cout << "\n4. Not checking weak_ptr.lock() result:" << endl;
    cout << "  auto ptr = wptr.lock();" << endl;
    cout << "  ptr->use();  // WRONG! ptr might be nullptr" << endl;
    cout << endl;

    cout << "=== Decision Flow Chart ===" << endl;
    cout << "\nDo you need ownership?" << endl;
    cout << "  NO  → Use raw pointer or reference" << endl;
    cout << "  YES → Continue..." << endl;
    cout << endl;
    cout << "Do you need multiple owners?" << endl;
    cout << "  NO  → Use unique_ptr" << endl;
    cout << "  YES → Continue..." << endl;
    cout << endl;
    cout << "Do you need ownership?" << endl;
    cout << "  YES → Use shared_ptr" << endl;
    cout << "  NO  → Use weak_ptr" << endl;
    cout << endl;

    cout << "=== Summary Table ===" << endl;
    cout << "\n┌──────────────┬────────────┬────────────┬────────────┐" << endl;
    cout << "│   Feature    │ unique_ptr │ shared_ptr │  weak_ptr  │" << endl;
    cout << "├──────────────┼────────────┼────────────┼────────────┤" << endl;
    cout << "│ Ownership    │ Exclusive  │   Shared   │    None    │" << endl;
    cout << "│ Copyable     │     No     │    Yes     │    Yes     │" << endl;
    cout << "│ Ref Count    │     No     │    Yes     │     No     │" << endl;
    cout << "│ Overhead     │    Zero    │   Small    │   Tiny     │" << endl;
    cout << "│ Access       │   Direct   │   Direct   │ lock()     │" << endl;
    cout << "│ Thread Safe  │    N/A     │ Count only │ Count only │" << endl;
    cout << "└──────────────┴────────────┴────────────┴────────────┘" << endl;
    cout << endl;

    cout << "=== Best Practices Summary ===" << endl;
    cout << "1. Default to unique_ptr for ownership" << endl;
    cout << "2. Use shared_ptr only when truly needed" << endl;
    cout << "3. Use weak_ptr to break cycles and observe" << endl;
    cout << "4. Prefer make_unique/make_shared over new" << endl;
    cout << "5. Use raw pointers/references for non-ownership" << endl;
    cout << "6. Always check weak_ptr.lock() result" << endl;
    cout << "7. Don't create multiple shared_ptrs from same raw pointer" << endl;
    cout << "8. Consider performance when choosing shared_ptr" << endl;

    return 0;
}
