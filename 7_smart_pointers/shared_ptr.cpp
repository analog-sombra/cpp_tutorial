/*
### std::shared_ptr

### What is shared_ptr?
- Smart pointer with shared ownership.
- Multiple shared_ptr can own the same object.
- Uses reference counting to track owners.
- Object deleted when last shared_ptr is destroyed.
- Thread-safe reference counting.

### Reference Counting
- Keeps track of how many shared_ptr own the object.
- Incremented when shared_ptr is copied.
- Decremented when shared_ptr is destroyed or reset.
- Object deleted when count reaches zero.


### Creating shared_ptr:

syntax:
    std::shared_ptr<Type> ptr1(new Type);              // Using new
    std::shared_ptr<Type> ptr2 = std::make_shared<Type>(args);  // Recommended


### Why make_shared?
- Single allocation (object + control block)
- Better performance
- Exception safe
- Recommended best practice


### Copying shared_ptr:
- Copying increases reference count
- Both pointers share ownership

syntax:
    std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
    std::shared_ptr<int> ptr2 = ptr1;  // Copy, ref count = 2


### Reference Count:
    ptr.use_count()     // Returns number of owners
    ptr.unique()        // Returns true if only one owner


### Accessing Object:
    *ptr            // Dereference
    ptr->method()   // Member access
    ptr.get()       // Get raw pointer


### Reset:
    ptr.reset()         // Release ownership, decrement ref count
    ptr.reset(new Type) // Release old, assign new


### Converting unique_ptr to shared_ptr:
    std::unique_ptr<int> uptr = std::make_unique<int>(10);
    std::shared_ptr<int> sptr = std::move(uptr);  // Transfer ownership


### shared_ptr with Arrays:
- Need custom deleter for arrays (or use shared_ptr<T[]> in C++17)

syntax:
    std::shared_ptr<int> arr(new int[10], std::default_delete<int[]>());


### Performance:
- Small overhead for reference counting
- Control block stores: reference count, weak count, deleter
- Thread-safe atomic operations (slightly slower)
- Two pointers internally (object + control block)


### Important Notes:
- Use when multiple owners needed
- Thread-safe reference counting
- Beware of circular references (use weak_ptr)
- Prefer make_shared over new
- Can be copied and assigned freely
- Slightly more overhead than unique_ptr

*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Asset
{
private:
    string name;

public:
    Asset(string n) : name(n)
    {
        cout << "  [Asset '" << name << "' created]" << endl;
    }

    ~Asset()
    {
        cout << "  [Asset '" << name << "' destroyed]" << endl;
    }

    void use() const
    {
        cout << "  Using asset: " << name << endl;
    }

    string getName() const { return name; }
};

void shareAsset(shared_ptr<Asset> ptr)
{
    cout << "shareAsset() received asset" << endl;
    cout << "  Reference count inside function: " << ptr.use_count() << endl;
    ptr->use();
}

shared_ptr<Asset> createAsset(string name)
{
    return make_shared<Asset>(name);
}

int main()
{
    cout << "=== Creating shared_ptr ===" << endl;
    shared_ptr<int> ptr1(new int(42));
    cout << "shared_ptr<int> ptr1(new int(42));" << endl;
    cout << "*ptr1 = " << *ptr1 << endl;
    cout << "Reference count: " << ptr1.use_count() << endl;
    cout << endl;

    cout << "=== Using make_shared (Recommended) ===" << endl;
    auto ptr2 = make_shared<int>(100);
    cout << "auto ptr2 = make_shared<int>(100);" << endl;
    cout << "*ptr2 = " << *ptr2 << endl;
    cout << "Reference count: " << ptr2.use_count() << endl;
    cout << "make_shared is more efficient (single allocation)" << endl;
    cout << endl;

    cout << "=== Shared Ownership ===" << endl;
    {
        shared_ptr<Asset> asset1 = make_shared<Asset>("SharedAsset");
        cout << "asset1 ref count: " << asset1.use_count() << endl;
        
        {
            shared_ptr<Asset> asset2 = asset1;
            cout << "\nAfter asset2 = asset1 (copying):" << endl;
            cout << "  asset1 ref count: " << asset1.use_count() << endl;
            cout << "  asset2 ref count: " << asset2.use_count() << endl;
            cout << "Both share ownership" << endl;
            
            cout << "\nLeaving inner scope..." << endl;
        }
        cout << "After inner scope:" << endl;
        cout << "  asset1 ref count: " << asset1.use_count() << endl;
        cout << "  asset2 destroyed, ref count decreased" << endl;
        
        cout << "\nLeaving outer scope..." << endl;
    }
    cout << "Last owner destroyed, asset deleted" << endl;
    cout << endl;

    cout << "=== Reference Count Demonstration ===" << endl;
    auto original = make_shared<Asset>("RefCountDemo");
    cout << "After creation: use_count = " << original.use_count() << endl;

    auto copy1 = original;
    cout << "After copy1: use_count = " << original.use_count() << endl;

    auto copy2 = original;
    cout << "After copy2: use_count = " << original.use_count() << endl;

    auto copy3 = original;
    cout << "After copy3: use_count = " << original.use_count() << endl;

    copy1.reset();
    cout << "After copy1.reset(): use_count = " << original.use_count() << endl;

    copy2.reset();
    cout << "After copy2.reset(): use_count = " << original.use_count() << endl;
    cout << endl;

    cout << "=== Passing shared_ptr to Function ===" << endl;
    shared_ptr<Asset> funcAsset = make_shared<Asset>("FunctionAsset");
    cout << "Before function call: use_count = " << funcAsset.use_count() << endl;
    
    shareAsset(funcAsset);
    
    cout << "After function returns: use_count = " << funcAsset.use_count() << endl;
    cout << "Temporary copy created in function, then destroyed" << endl;
    cout << endl;

    cout << "=== Returning shared_ptr from Function ===" << endl;
    shared_ptr<Asset> returnedAsset = createAsset("ReturnedAsset");
    cout << "Returned asset ref count: " << returnedAsset.use_count() << endl;
    cout << "Ownership transferred to caller" << endl;
    cout << endl;

    cout << "=== reset() - Release Ownership ===" << endl;
    auto resetDemo = make_shared<Asset>("ResetDemo");
    cout << "Before reset(): use_count = " << resetDemo.use_count() << endl;
    cout << "  resetDemo.get() = " << resetDemo.get() << endl;
    
    resetDemo.reset();
    cout << "After reset():" << endl;
    cout << "  use_count = " << resetDemo.use_count() << endl;
    cout << "  resetDemo.get() = " << resetDemo.get() << " (nullptr)" << endl;
    cout << endl;

    cout << "=== reset() with New Object ===" << endl;
    shared_ptr<Asset> resetDemo2 = make_shared<Asset>("First");
    cout << "Current asset: " << resetDemo2->getName() << endl;
    cout << "Before reset(new Asset): use_count = " << resetDemo2.use_count() << endl;
    
    resetDemo2.reset(new Asset("Second"));
    cout << "After reset(): use_count = " << resetDemo2.use_count() << endl;
    cout << "Old asset deleted, new asset assigned" << endl;
    cout << endl;

    cout << "=== unique() - Check if Only Owner ===" << endl;
    auto uniqueCheck = make_shared<int>(999);
    cout << "After creation:" << endl;
    cout << "  use_count: " << uniqueCheck.use_count() << endl;
    cout << "  unique(): " << (uniqueCheck.unique() ? "true" : "false") << endl;

    auto sharedCheck = uniqueCheck;
    cout << "\nAfter creating copy:" << endl;
    cout << "  use_count: " << uniqueCheck.use_count() << endl;
    cout << "  unique(): " << (uniqueCheck.unique() ? "true" : "false") << endl;
    cout << endl;

    cout << "=== Converting unique_ptr to shared_ptr ===" << endl;
    unique_ptr<Asset> uptr = make_unique<Asset>("UniqueToShared");
    cout << "Created as unique_ptr" << endl;
    
    shared_ptr<Asset> sptr = std::move(uptr);
    cout << "Converted to shared_ptr via std::move" << endl;
    cout << "  uptr is now nullptr" << endl;
    cout << "  sptr ref count: " << sptr.use_count() << endl;
    cout << endl;

    cout << "=== shared_ptr in Containers ===" << endl;
    vector<shared_ptr<Asset>> assets;
    
    cout << "Creating shared assets:" << endl;
    auto sharedAsset = make_shared<Asset>("SharedInVector");
    cout << "sharedAsset ref count: " << sharedAsset.use_count() << endl;
    
    assets.push_back(sharedAsset);
    cout << "After push_back: ref count = " << sharedAsset.use_count() << endl;
    
    assets.push_back(sharedAsset);
    cout << "After 2nd push_back: ref count = " << sharedAsset.use_count() << endl;
    
    cout << "\nVector and local variable all share ownership" << endl;
    cout << "Clearing vector..." << endl;
    assets.clear();
    cout << "After clear(): ref count = " << sharedAsset.use_count() << endl;
    cout << endl;

    cout << "=== Aliasing Constructor ===" << endl;
    struct Point { int x, y; };
    auto pointPtr = make_shared<Point>();
    pointPtr->x = 10;
    pointPtr->y = 20;

    shared_ptr<int> xPtr(pointPtr, &pointPtr->x);
    cout << "Created shared_ptr to member (aliasing)" << endl;
    cout << "  pointPtr ref count: " << pointPtr.use_count() << endl;
    cout << "  xPtr ref count: " << xPtr.use_count() << endl;
    cout << "  *xPtr = " << *xPtr << endl;
    cout << "xPtr shares ownership of Point but points to x member" << endl;
    cout << endl;

    cout << "=== get() - Access Raw Pointer ===" << endl;
    auto rawAccessPtr = make_shared<Asset>("RawAccess");
    Asset* raw = rawAccessPtr.get();
    
    cout << "shared_ptr: " << rawAccessPtr.get() << endl;
    cout << "raw pointer: " << raw << endl;
    cout << "Both point to same object" << endl;
    cout << "WARNING: Don't delete raw pointer!" << endl;
    cout << endl;

    cout << "=== Checking for nullptr ===" << endl;
    shared_ptr<int> nullPtr;
    cout << "Default constructed shared_ptr:" << endl;
    cout << "  use_count: " << nullPtr.use_count() << endl;
    cout << "  is nullptr: " << (nullPtr == nullptr ? "true" : "false") << endl;
    cout << "  boolean: " << (nullPtr ? "true" : "false") << endl;

    nullPtr = make_shared<int>(42);
    cout << "\nAfter assignment:" << endl;
    cout << "  use_count: " << nullPtr.use_count() << endl;
    cout << "  is nullptr: " << (nullPtr == nullptr ? "true" : "false") << endl;
    cout << "  boolean: " << (nullPtr ? "true" : "false") << endl;
    cout << endl;

    cout << "=== swap() Two shared_ptrs ===" << endl;
    auto swap1 = make_shared<Asset>("Swap1");
    auto swap2 = make_shared<Asset>("Swap2");
    
    cout << "Before swap:" << endl;
    cout << "  swap1: " << swap1->getName() << " (count: " << swap1.use_count() << ")" << endl;
    cout << "  swap2: " << swap2->getName() << " (count: " << swap2.use_count() << ")" << endl;
    
    swap1.swap(swap2);
    
    cout << "After swap:" << endl;
    cout << "  swap1: " << swap1->getName() << " (count: " << swap1.use_count() << ")" << endl;
    cout << "  swap2: " << swap2->getName() << " (count: " << swap2.use_count() << ")" << endl;
    cout << endl;

    cout << "=== Comparison Operators ===" << endl;
    auto cmp1 = make_shared<int>(10);
    auto cmp2 = cmp1;
    auto cmp3 = make_shared<int>(10);

    cout << "cmp1 and cmp2 point to same object:" << endl;
    cout << "  cmp1 == cmp2: " << (cmp1 == cmp2 ? "true" : "false") << endl;
    
    cout << "cmp1 and cmp3 point to different objects:" << endl;
    cout << "  cmp1 == cmp3: " << (cmp1 == cmp3 ? "true" : "false") << endl;
    cout << endl;

    cout << "=== Owner_before for Strict Weak Ordering ===" << endl;
    cout << "For use in ordered containers (std::map, std::set):" << endl;
    cout << "  ptr1.owner_before(ptr2)" << endl;
    cout << "Provides consistent ordering even with aliasing" << endl;
    cout << endl;

    cout << "=== Performance Characteristics ===" << endl;
    cout << "shared_ptr overhead:" << endl;
    cout << "  - Control block: ~16-24 bytes (ref count, weak count, deleter)" << endl;
    cout << "  - Atomic operations: Thread-safe but slightly slower" << endl;
    cout << "  - Two pointers: object ptr + control block ptr" << endl;
    cout << "\nmake_shared benefits:" << endl;
    cout << "  - Single allocation (object + control block)" << endl;
    cout << "  - Better cache locality" << endl;
    cout << "  - Faster than new + shared_ptr constructor" << endl;
    cout << endl;

    cout << "=== Common Use Cases ===" << endl;
    cout << "1. Multiple owners of resource" << endl;
    cout << "2. Sharing data between threads" << endl;
    cout << "3. Caching and resource pools" << endl;
    cout << "4. Observer pattern implementations" << endl;
    cout << "5. Graph structures (nodes with multiple parents)" << endl;
    cout << "6. Callback storage (multiple subscribers)" << endl;
    cout << endl;

    cout << "=== Best Practices ===" << endl;
    cout << "1. Use make_shared instead of new" << endl;
    cout << "2. Prefer pass by const& to avoid unnecessary copies" << endl;
    cout << "3. Use weak_ptr to break circular references" << endl;
    cout << "4. Don't mix shared_ptr and raw pointer ownership" << endl;
    cout << "5. Don't create shared_ptr from same raw pointer twice" << endl;
    cout << "6. Be aware of thread safety (ref counting is, object isn't)" << endl;
    cout << "7. Prefer unique_ptr if exclusive ownership works" << endl;
    cout << endl;

    cout << "=== Common Mistakes ===" << endl;
    cout << "1. Creating two shared_ptrs from same raw pointer:" << endl;
    cout << "   int* raw = new int(10);" << endl;
    cout << "   shared_ptr<int> ptr1(raw);" << endl;
    cout << "   shared_ptr<int> ptr2(raw);  // WRONG! Double delete" << endl;
    cout << endl;

    cout << "2. Circular references without weak_ptr:" << endl;
    cout << "   struct Node {" << endl;
    cout << "       shared_ptr<Node> next;  // Circular reference" << endl;
    cout << "   };  // Memory leak!" << endl;
    cout << "   Fix: Use weak_ptr for one direction" << endl;
    cout << endl;

    cout << "=== Common Operations Summary ===" << endl;
    cout << "Create:    auto ptr = std::make_shared<Type>(args);" << endl;
    cout << "Copy:      auto ptr2 = ptr1;" << endl;
    cout << "Access:    *ptr, ptr->member(), ptr.get()" << endl;
    cout << "Count:     ptr.use_count(), ptr.unique()" << endl;
    cout << "Reset:     ptr.reset(); or ptr.reset(new Type);" << endl;
    cout << "Check:     if (ptr) or if (!ptr)" << endl;
    cout << "Swap:      ptr1.swap(ptr2);" << endl;
    cout << "Compare:   ptr1 == ptr2, ptr1 != ptr2" << endl;

    return 0;
}
