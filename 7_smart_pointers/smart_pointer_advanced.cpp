/*
### Advanced Smart Pointer Features

This file covers advanced smart pointer topics:
1. Custom deleters
2. Smart pointers with arrays
3. Aliasing constructor
4. enable_shared_from_this
5. make_unique/make_shared details
6. Smart pointers with incomplete types
7. Performance optimization


### Custom Deleters

Purpose:
- Specify custom cleanup function
- Useful for non-standard resources (files, handles, APIs)
- Different cleanup logic than delete

syntax (unique_ptr):
    auto deleter = [](Type* ptr) { customCleanup(ptr); delete ptr; };
    std::unique_ptr<Type, decltype(deleter)> ptr(new Type, deleter);

syntax (shared_ptr):
    auto deleter = [](Type* ptr) { customCleanup(ptr); delete ptr; };
    std::shared_ptr<Type> ptr(new Type, deleter);


### Smart Pointers with Arrays

unique_ptr with array:
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);
    arr[0] = 42;  // Array indexing supported

shared_ptr with array (C++17):
    std::shared_ptr<int[]> arr(new int[10]);
    arr[0] = 42;

shared_ptr with array (pre-C++17):
    std::shared_ptr<int> arr(new int[10], std::default_delete<int[]>());


### Aliasing Constructor

Purpose:
- shared_ptr owns one object but points to another
- Useful for pointing to member of owned object
- Member kept alive as long as shared_ptr exists

syntax:
    struct Data { int x, y; };
    auto dataPtr = std::make_shared<Data>();
    std::shared_ptr<int> xPtr(dataPtr, &dataPtr->x);


### enable_shared_from_this

Purpose:
- Get shared_ptr to this inside member function
- Creates shared_ptr from raw this pointer safely
- Required when object needs to return itself as shared_ptr

syntax:
    class MyClass : public std::enable_shared_from_this<MyClass> {
        std::shared_ptr<MyClass> getPtr() {
            return shared_from_this();
        }
    };


### make_unique vs new

make_unique advantages:
- Exception safe
- Cannot forget delete
- More concise
- Uniform initialization syntax
- Auto type deduction

Exception safety:
    func(unique_ptr<T>(new T), unique_ptr<U>(new U));  // Unsafe!
    func(make_unique<T>(), make_unique<U>());          // Safe


### make_shared vs new

make_shared advantages:
- Single allocation (object + control block)
- Better cache locality
- Faster allocation/deallocation
- Exception safe

Disadvantage:
- Memory not freed until weak_ptrs destroyed
- Slightly larger control block


### Incomplete Types

Forward declaration:
    class Incomplete;
    
    std::unique_ptr<Incomplete> ptr;  // OK in header
    // Implementation must be available for destruction


### Performance Tips:
- Use make_unique/make_shared for efficiency
- Pass by const reference to avoid ref count changes
- Use unique_ptr by default (zero overhead)
- Consider raw pointers for non-owning references
- Beware of control block overhead in shared_ptr

*/

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

// === Custom Deleters ===

class FileHandle
{
private:
    FILE* file;

public:
    FileHandle(const char* filename)
    {
        file = fopen(filename, "w");
        if (file)
        {
            cout << "  [File opened: " << filename << "]" << endl;
        }
    }

    void write(const string& text)
    {
        if (file)
        {
            fprintf(file, "%s\n", text.c_str());
        }
    }

    FILE* get() { return file; }
};

void customFileDeleter(FileHandle* fh)
{
    cout << "  [Custom deleter: closing file]" << endl;
    if (fh->get())
    {
        fclose(fh->get());
    }
    delete fh;
}

// === enable_shared_from_this ===

class Node : public enable_shared_from_this<Node>
{
private:
    string name;

public:
    Node(string n) : name(n)
    {
        cout << "  [Node '" << name << "' created]" << endl;
    }

    ~Node()
    {
        cout << "  [Node '" << name << "' destroyed]" << endl;
    }

    shared_ptr<Node> getSharedPtr()
    {
        return shared_from_this();
    }

    string getName() const { return name; }
};

// === Aliasing Example ===

struct Point3D
{
    int x, y, z;

    Point3D(int x_, int y_, int z_) : x(x_), y(y_), z(z_)
    {
        cout << "  [Point3D created: (" << x << ", " << y << ", " << z << ")]" << endl;
    }

    ~Point3D()
    {
        cout << "  [Point3D destroyed]" << endl;
    }
};

int main()
{
    cout << "=== Custom Deleters with unique_ptr ===" << endl;
    {
        auto fileDeleter = [](FileHandle* fh) {
            cout << "  [Lambda deleter: closing file]" << endl;
            if (fh->get()) fclose(fh->get());
            delete fh;
        };

        unique_ptr<FileHandle, decltype(fileDeleter)> filePtr(
            new FileHandle("test_unique.txt"),
            fileDeleter
        );

        filePtr->write("Hello from unique_ptr");
        cout << "Leaving scope..." << endl;
    }
    cout << "File automatically closed via custom deleter" << endl;
    cout << endl;

    cout << "=== Custom Deleters with shared_ptr ===" << endl;
    {
        shared_ptr<FileHandle> filePtr(
            new FileHandle("test_shared.txt"),
            customFileDeleter
        );

        filePtr->write("Hello from shared_ptr");
        
        shared_ptr<FileHandle> copy = filePtr;
        cout << "Reference count: " << filePtr.use_count() << endl;
        cout << "Leaving scope..." << endl;
    }
    cout << "File closed when last shared_ptr destroyed" << endl;
    cout << endl;

    cout << "=== Custom Deleter with Lambda ===" << endl;
    {
        shared_ptr<int> ptr(
            new int(42),
            [](int* p) {
                cout << "  [Custom lambda: deleting int with value " << *p << "]" << endl;
                delete p;
            }
        );

        cout << "*ptr = " << *ptr << endl;
        cout << "Leaving scope..." << endl;
    }
    cout << endl;

    cout << "=== unique_ptr with Array ===" << endl;
    {
        unique_ptr<int[]> arr = make_unique<int[]>(5);
        
        cout << "Created array of 5 ints" << endl;
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
        cout << "Uses delete[] automatically" << endl;
    }
    cout << endl;

    cout << "=== shared_ptr with Array (C++17) ===" << endl;
    {
        shared_ptr<int[]> arr(new int[5]);
        
        for (int i = 0; i < 5; ++i)
        {
            arr[i] = i * i;
        }

        cout << "Array elements: ";
        for (int i = 0; i < 5; ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "=== shared_ptr with Array (Custom Deleter) ===" << endl;
    {
        shared_ptr<int> arr(
            new int[5],
            default_delete<int[]>()  // Use array delete
        );

        for (int i = 0; i < 5; ++i)
        {
            arr.get()[i] = i + 100;
        }

        cout << "Array elements: ";
        for (int i = 0; i < 5; ++i)
        {
            cout << arr.get()[i] << " ";
        }
        cout << endl;
        cout << "Custom deleter ensures delete[] is used" << endl;
    }
    cout << endl;

    cout << "=== Aliasing Constructor ===" << endl;
    {
        shared_ptr<Point3D> point = make_shared<Point3D>(10, 20, 30);
        cout << "Created Point3D" << endl;
        cout << "point use_count: " << point.use_count() << endl;

        // Create shared_ptr to member (aliasing)
        shared_ptr<int> xPtr(point, &point->x);
        shared_ptr<int> yPtr(point, &point->y);
        shared_ptr<int> zPtr(point, &point->z);

        cout << "\nCreated aliased shared_ptrs to members:" << endl;
        cout << "  point use_count: " << point.use_count() << endl;
        cout << "  xPtr use_count: " << xPtr.use_count() << endl;
        cout << "  All share ownership of Point3D" << endl;

        cout << "\nMember values via aliased pointers:" << endl;
        cout << "  *xPtr = " << *xPtr << endl;
        cout << "  *yPtr = " << *yPtr << endl;
        cout << "  *zPtr = " << *zPtr << endl;

        point.reset();
        cout << "\nAfter point.reset():" << endl;
        cout << "  point is nullptr but Point3D still alive" << endl;
        cout << "  *xPtr = " << *xPtr << " (still valid)" << endl;
        cout << "  xPtr use_count: " << xPtr.use_count() << endl;

        cout << "\nLeaving scope..." << endl;
    }
    cout << "Point3D destroyed when last aliased pointer destroyed" << endl;
    cout << endl;

    cout << "=== enable_shared_from_this ===" << endl;
    {
        shared_ptr<Node> node1 = make_shared<Node>("Node1");
        
        cout << "Getting shared_ptr from within object:" << endl;
        shared_ptr<Node> node2 = node1->getSharedPtr();
        
        cout << "  node1 use_count: " << node1.use_count() << endl;
        cout << "  node2 use_count: " << node2.use_count() << endl;
        cout << "  Both point to same object" << endl;

        // WARNING: Don't use shared_from_this() in constructor!
        // cout << "NOTE: Never call shared_from_this() in constructor" << endl;
    }
    cout << endl;

    cout << "=== enable_shared_from_this Use Case ===" << endl;
    cout << "Common scenario: Register callback with this" << endl;
    cout << endl;
    cout << "class Widget : public enable_shared_from_this<Widget> {" << endl;
    cout << "    void registerCallback() {" << endl;
    cout << "        callbacks.push_back(shared_from_this());" << endl;
    cout << "    }" << endl;
    cout << "};" << endl;
    cout << endl;

    cout << "=== make_unique Exception Safety ===" << endl;
    cout << "\nUnsafe (potential leak if exception thrown):" << endl;
    cout << "  process(unique_ptr<T>(new T), unique_ptr<U>(new U));" << endl;
    cout << "  Order of evaluation undefined!" << endl;
    cout << "  If new T succeeds but new U throws, T is leaked" << endl;
    cout << endl;

    cout << "Safe (guaranteed no leak):" << endl;
    cout << "  process(make_unique<T>(), make_unique<U>());" << endl;
    cout << "  Each allocation is exception-safe" << endl;
    cout << endl;

    cout << "=== make_shared Performance ===" << endl;
    cout << "\nUsing new (two allocations):" << endl;
    cout << "  shared_ptr<int> ptr(new int(42));" << endl;
    cout << "  1. Allocate int" << endl;
    cout << "  2. Allocate control block" << endl;
    cout << "  Total: 2 allocations, worse cache locality" << endl;
    cout << endl;

    cout << "Using make_shared (one allocation):" << endl;
    cout << "  shared_ptr<int> ptr = make_shared<int>(42);" << endl;
    cout << "  1. Allocate int + control block together" << endl;
    cout << "  Total: 1 allocation, better cache locality" << endl;
    cout << "  Faster and more efficient!" << endl;
    cout << endl;

    cout << "=== Control Block Contents ===" << endl;
    cout << "shared_ptr control block contains:" << endl;
    cout << "  - Reference count (strong references)" << endl;
    cout << "  - Weak count (weak_ptr references)" << endl;
    cout << "  - Deleter (if custom)" << endl;
    cout << "  - Allocator (if custom)" << endl;
    cout << "  - Virtual dispatch table (for type erasure)" << endl;
    cout << endl;

    cout << "Typical size:" << endl;
    cout << "  - Without custom deleter: ~16-24 bytes" << endl;
    cout << "  - With custom deleter: + sizeof(deleter)" << endl;
    cout << endl;

    cout << "=== nullptr with Smart Pointers ===" << endl;
    {
        unique_ptr<int> uptr = nullptr;
        shared_ptr<int> sptr = nullptr;

        cout << "Both can be nullptr:" << endl;
        cout << "  uptr == nullptr: " << (uptr == nullptr ? "true" : "false") << endl;
        cout << "  sptr == nullptr: " << (sptr == nullptr ? "true" : "false") << endl;

        if (!uptr) cout << "  uptr is empty" << endl;
        if (!sptr) cout << "  sptr is empty" << endl;
    }
    cout << endl;

    cout << "=== Array Comparison ===" << endl;
    cout << "\nRaw array:" << endl;
    cout << "  int* arr = new int[10];" << endl;
    cout << "  // ..." << endl;
    cout << "  delete[] arr;  // Must remember delete[]" << endl;
    cout << endl;

    cout << "unique_ptr with array:" << endl;
    cout << "  auto arr = make_unique<int[]>(10);" << endl;
    cout << "  arr[0] = 42;  // Array indexing works" << endl;
    cout << "  // Automatic delete[] in destructor" << endl;
    cout << endl;

    cout << "std::vector (usually better):" << endl;
    cout << "  vector<int> arr(10);" << endl;
    cout << "  arr[0] = 42;" << endl;
    cout << "  // Automatic, resizable, bounds checking" << endl;
    cout << endl;

    cout << "=== Incomplete Type Support ===" << endl;
    cout << "Forward declaration:" << endl;
    cout << "  class MyClass;  // Incomplete type" << endl;
    cout << endl;

    cout << "unique_ptr:" << endl;
    cout << "  - Can declare with incomplete type" << endl;
    cout << "  - Destructor must see complete type" << endl;
    cout << "  - Use in pimpl idiom" << endl;
    cout << endl;

    cout << "shared_ptr:" << endl;
    cout << "  - Stores deleter in control block" << endl;
    cout << "  - Can destroy with incomplete type" << endl;
    cout << "  - More flexible but larger overhead" << endl;
    cout << endl;

    cout << "=== Best Practices Summary ===" << endl;
    cout << "1. Use make_unique/make_shared instead of new" << endl;
    cout << "2. Use custom deleters for non-standard resources" << endl;
    cout << "3. Use unique_ptr<T[]> for arrays (or better: std::vector)" << endl;
    cout << "4. Use aliasing constructor for sub-object pointers" << endl;
    cout << "5. Inherit from enable_shared_from_this when needed" << endl;
    cout << "6. Be aware of make_shared memory behavior with weak_ptr" << endl;
    cout << "7. Use default_delete<T[]> for shared_ptr with arrays" << endl;
    cout << "8. Never call shared_from_this() in constructor" << endl;
    cout << endl;

    cout << "=== Advanced Patterns ===" << endl;
    cout << "\n1. Pimpl Idiom:" << endl;
    cout << "   class Widget {" << endl;
    cout << "       unique_ptr<Impl> pImpl;" << endl;
    cout << "   };" << endl;
    cout << endl;

    cout << "2. Factory with Custom Deleter:" << endl;
    cout << "   auto factory() {" << endl;
    cout << "       return shared_ptr<Resource>(create(), destroyer);" << endl;
    cout << "   }" << endl;
    cout << endl;

    cout << "3. Intrusive Reference Counting:" << endl;
    cout << "   class RefCounted : public enable_shared_from_this<RefCounted>" << endl;
    cout << endl;

    cout << "4. Array of Polymorphic Objects:" << endl;
    cout << "   vector<unique_ptr<Base>> objects;" << endl;
    cout << "   objects.push_back(make_unique<Derived>());" << endl;

    return 0;
}
