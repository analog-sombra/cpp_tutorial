/*
### std::weak_ptr

### What is weak_ptr?
- Non-owning smart pointer to object managed by shared_ptr.
- Does NOT increase reference count.
- Used to observe object without affecting its lifetime.
- Must convert to shared_ptr to access object.

### Purpose:
- Break circular references between shared_ptrs
- Observe objects without ownership
- Check if object still exists
- Cache implementations


### Creating weak_ptr:
- Can only be created from shared_ptr
- Cannot be created from raw pointer or unique_ptr

syntax:
    std::shared_ptr<int> sptr = std::make_shared<int>(10);
    std::weak_ptr<int> wptr = sptr;  // Create from shared_ptr


### Key Operations:

lock()
- Returns shared_ptr to object if it exists
- Returns empty shared_ptr if object destroyed
- Thread-safe access to object

syntax:
    std::shared_ptr<int> sptr = wptr.lock();
    if (sptr) {
        // Object exists, use it
    }


expired()
- Returns true if object has been destroyed
- Returns false if object still exists
- Equivalent to use_count() == 0

syntax:
    if (wptr.expired()) {
        // Object no longer exists
    }


use_count()
- Returns reference count of managed object
- Returns 0 if object destroyed


reset()
- Releases reference to managed object
- weak_ptr becomes empty


### Circular Reference Problem:

Bad (Memory Leak):
    struct Node {
        shared_ptr<Node> next;
        shared_ptr<Node> prev;  // Circular reference!
    };

Good (Using weak_ptr):
    struct Node {
        shared_ptr<Node> next;
        weak_ptr<Node> prev;    // Break cycle
    };


### weak_ptr Does NOT:
- Increase reference count
- Keep object alive
- Prevent deletion of object
- Allow direct access to object


### Important Notes:
- weak_ptr must be converted to shared_ptr to access object
- Always check if lock() returns valid shared_ptr
- Useful for caching, observer pattern, parent pointers
- Thread-safe when checking existence
- Does not contribute to object ownership

*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Observer;

class Subject
{
private:
    string name;
    vector<weak_ptr<Observer>> observers;

public:
    Subject(string n) : name(n)
    {
        cout << "  [Subject '" << name << "' created]" << endl;
    }

    ~Subject()
    {
        cout << "  [Subject '" << name << "' destroyed]" << endl;
    }

    void addObserver(shared_ptr<Observer> obs)
    {
        observers.push_back(obs);
        cout << "  Observer added to " << name << endl;
    }

    void notify();

    string getName() const { return name; }
};

class Observer
{
private:
    string name;

public:
    Observer(string n) : name(n)
    {
        cout << "  [Observer '" << name << "' created]" << endl;
    }

    ~Observer()
    {
        cout << "  [Observer '" << name << "' destroyed]" << endl;
    }

    void update(const string& message)
    {
        cout << "  Observer '" << name << "' received: " << message << endl;
    }

    string getName() const { return name; }
};

void Subject::notify()
{
    cout << "  Notifying observers..." << endl;
    for (auto& weakObs : observers)
    {
        if (auto obs = weakObs.lock())
        {
            obs->update("Update from " + name);
        }
        else
        {
            cout << "    (Observer no longer exists)" << endl;
        }
    }
}

// Circular reference demonstration
struct Node
{
    string data;
    shared_ptr<Node> next;
    weak_ptr<Node> prev;  // Using weak_ptr to break cycle

    Node(string d) : data(d)
    {
        cout << "  [Node '" << data << "' created]" << endl;
    }

    ~Node()
    {
        cout << "  [Node '" << data << "' destroyed]" << endl;
    }
};

int main()
{
    cout << "=== Creating weak_ptr ===" << endl;
    shared_ptr<int> sptr = make_shared<int>(42);
    weak_ptr<int> wptr = sptr;

    cout << "shared_ptr created with value: " << *sptr << endl;
    cout << "weak_ptr created from shared_ptr" << endl;
    cout << "shared_ptr use_count: " << sptr.use_count() << endl;
    cout << "weak_ptr use_count: " << wptr.use_count() << endl;
    cout << "weak_ptr does NOT increase reference count!" << endl;
    cout << endl;

    cout << "=== expired() Check ===" << endl;
    {
        shared_ptr<int> tempPtr = make_shared<int>(100);
        weak_ptr<int> weakCheck = tempPtr;

        cout << "Inside scope:" << endl;
        cout << "  weak_ptr.expired(): " << (weakCheck.expired() ? "true" : "false") << endl;
        cout << "  shared_ptr.use_count(): " << tempPtr.use_count() << endl;
        cout << "Leaving scope (shared_ptr destroyed)..." << endl;
    }
    cout << "Outside scope:" << endl;
    weak_ptr<int> weakCheck;
    {
        shared_ptr<int> temp = make_shared<int>(100);
        weakCheck = temp;
    }
    cout << "  weak_ptr.expired(): " << (weakCheck.expired() ? "true" : "false") << endl;
    cout << "Object no longer exists!" << endl;
    cout << endl;

    cout << "=== lock() - Safe Access ===" << endl;
    shared_ptr<string> message = make_shared<string>("Hello");
    weak_ptr<string> weakMsg = message;

    cout << "Attempting to access via lock():" << endl;
    if (auto lockedPtr = weakMsg.lock())
    {
        cout << "  Object exists: " << *lockedPtr << endl;
        cout << "  Temporary shared_ptr created" << endl;
    }
    else
    {
        cout << "  Object no longer exists" << endl;
    }
    cout << endl;

    cout << "=== lock() After Object Destroyed ===" << endl;
    weak_ptr<string> weakMsg2;
    {
        shared_ptr<string> tempMsg = make_shared<string>("Temporary");
        weakMsg2 = tempMsg;
        cout << "Before destruction: lock() succeeds" << endl;
    }
    
    cout << "After destruction: " << endl;
    if (auto lockedPtr = weakMsg2.lock())
    {
        cout << "  Unexpected: lock() succeeded" << endl;
    }
    else
    {
        cout << "  Expected: lock() returned nullptr" << endl;
    }
    cout << endl;

    cout << "=== Breaking Circular References ===" << endl;
    cout << "Creating linked list with weak_ptr for prev:" << endl;
    {
        shared_ptr<Node> node1 = make_shared<Node>("Node1");
        shared_ptr<Node> node2 = make_shared<Node>("Node2");
        shared_ptr<Node> node3 = make_shared<Node>("Node3");

        node1->next = node2;
        node2->prev = node1;  // weak_ptr (doesn't increase ref count)
        node2->next = node3;
        node3->prev = node2;  // weak_ptr

        cout << "\nReference counts:" << endl;
        cout << "  node1: " << node1.use_count() << endl;
        cout << "  node2: " << node2.use_count() << endl;
        cout << "  node3: " << node3.use_count() << endl;

        cout << "\nAccessing prev via lock():" << endl;
        if (auto prevNode = node2->prev.lock())
        {
            cout << "  node2->prev exists: " << prevNode->data << endl;
        }

        cout << "\nLeaving scope (all nodes will be destroyed)..." << endl;
    }
    cout << "All nodes properly destroyed (no memory leak)" << endl;
    cout << endl;

    cout << "=== Observer Pattern ===" << endl;
    {
        shared_ptr<Subject> subject = make_shared<Subject>("NewsPublisher");
        shared_ptr<Observer> obs1 = make_shared<Observer>("Observer1");
        shared_ptr<Observer> obs2 = make_shared<Observer>("Observer2");

        subject->addObserver(obs1);
        subject->addObserver(obs2);

        cout << "\nNotifying while all observers exist:" << endl;
        subject->notify();

        cout << "\nDestroying observer1..." << endl;
        obs1.reset();

        cout << "\nNotifying after observer1 destroyed:" << endl;
        subject->notify();
        
        cout << "\nLeaving scope..." << endl;
    }
    cout << "Subject and remaining observer destroyed" << endl;
    cout << endl;

    cout << "=== use_count() via weak_ptr ===" << endl;
    shared_ptr<int> counter = make_shared<int>(999);
    weak_ptr<int> weakCounter = counter;

    cout << "Initial: use_count = " << weakCounter.use_count() << endl;

    auto counter2 = counter;
    cout << "After copy: use_count = " << weakCounter.use_count() << endl;

    auto counter3 = counter;
    cout << "After 2nd copy: use_count = " << weakCounter.use_count() << endl;

    counter2.reset();
    cout << "After reset 1: use_count = " << weakCounter.use_count() << endl;

    counter3.reset();
    cout << "After reset 2: use_count = " << weakCounter.use_count() << endl;
    cout << endl;

    cout << "=== reset() weak_ptr ===" << endl;
    shared_ptr<int> value = make_shared<int>(777);
    weak_ptr<int> weakValue = value;

    cout << "Before reset:" << endl;
    cout << "  expired: " << (weakValue.expired() ? "true" : "false") << endl;
    cout << "  use_count: " << weakValue.use_count() << endl;

    weakValue.reset();
    cout << "After weakValue.reset():" << endl;
    cout << "  expired: " << (weakValue.expired() ? "true" : "false") << endl;
    cout << "  use_count: " << weakValue.use_count() << endl;
    cout << "weak_ptr released, but object still exists (shared_ptr owns it)" << endl;
    cout << endl;

    cout << "=== Caching with weak_ptr ===" << endl;
    cout << "Cache scenario: Store weak_ptr to avoid keeping objects alive" << endl;
    
    vector<weak_ptr<string>> cache;
    
    {
        shared_ptr<string> str1 = make_shared<string>("Cached1");
        shared_ptr<string> str2 = make_shared<string>("Cached2");
        
        cache.push_back(str1);
        cache.push_back(str2);
        
        cout << "Objects added to cache" << endl;
        cout << "Cache size: " << cache.size() << endl;
        
        cout << "\nAccessing cached objects:" << endl;
        for (size_t i = 0; i < cache.size(); ++i)
        {
            if (auto cached = cache[i].lock())
            {
                cout << "  Cache[" << i << "]: " << *cached << endl;
            }
        }
        
        cout << "\nLeaving scope (original shared_ptrs destroyed)..." << endl;
    }
    
    cout << "\nAfter scope, checking cache:" << endl;
    for (size_t i = 0; i < cache.size(); ++i)
    {
        if (auto cached = cache[i].lock())
        {
            cout << "  Cache[" << i << "]: " << *cached << " (alive)" << endl;
        }
        else
        {
            cout << "  Cache[" << i << "]: expired" << endl;
        }
    }
    cout << "Objects not kept alive by cache (correct behavior)" << endl;
    cout << endl;

    cout << "=== Comparison with nullptr ===" << endl;
    weak_ptr<int> emptyWeak;
    shared_ptr<int> sharedForWeak = make_shared<int>(42);
    weak_ptr<int> validWeak = sharedForWeak;

    cout << "Empty weak_ptr:" << endl;
    cout << "  expired: " << (emptyWeak.expired() ? "true" : "false") << endl;
    cout << "  use_count: " << emptyWeak.use_count() << endl;

    cout << "\nValid weak_ptr:" << endl;
    cout << "  expired: " << (validWeak.expired() ? "true" : "false") << endl;
    cout << "  use_count: " << validWeak.use_count() << endl;
    cout << endl;

    cout << "=== Thread Safety Note ===" << endl;
    cout << "weak_ptr::lock() is thread-safe:" << endl;
    cout << "  - Atomically checks existence and creates shared_ptr" << endl;
    cout << "  - Safe to use from multiple threads" << endl;
    cout << "  - Object won't be deleted between check and access" << endl;
    cout << endl;

    cout << "=== Common Use Cases ===" << endl;
    cout << "1. Breaking circular references (doubly-linked lists, graphs)" << endl;
    cout << "2. Observer pattern (observers don't own subject)" << endl;
    cout << "3. Caching (cache doesn't keep objects alive)" << endl;
    cout << "4. Parent pointers in tree structures" << endl;
    cout << "5. Callback registration (callbacks don't own target)" << endl;
    cout << endl;

    cout << "=== Best Practices ===" << endl;
    cout << "1. Always use lock() before accessing object" << endl;
    cout << "2. Check if lock() returns valid shared_ptr" << endl;
    cout << "3. Use expired() for quick existence check" << endl;
    cout << "4. Use weak_ptr for back-references in data structures" << endl;
    cout << "5. Don't store result of lock() for later use" << endl;
    cout << "6. Use weak_ptr in observer pattern for observers" << endl;
    cout << endl;

    cout << "=== Circular Reference Example ===" << endl;
    cout << "BAD (memory leak):" << endl;
    cout << "  struct Node {" << endl;
    cout << "      shared_ptr<Node> next;" << endl;
    cout << "      shared_ptr<Node> prev;  // Circular reference!" << endl;
    cout << "  };" << endl;
    cout << endl;

    cout << "GOOD (no leak):" << endl;
    cout << "  struct Node {" << endl;
    cout << "      shared_ptr<Node> next;  // Owns next node" << endl;
    cout << "      weak_ptr<Node> prev;    // Observes prev node" << endl;
    cout << "  };" << endl;
    cout << endl;

    cout << "=== Common Operations Summary ===" << endl;
    cout << "Create:    weak_ptr<Type> wptr = sharedPtr;" << endl;
    cout << "Lock:      shared_ptr<Type> sptr = wptr.lock();" << endl;
    cout << "Check:     if (wptr.expired()) or if (auto p = wptr.lock())" << endl;
    cout << "Count:     wptr.use_count()" << endl;
    cout << "Reset:     wptr.reset();" << endl;
    cout << endl;

    cout << "=== Key Differences ===" << endl;
    cout << "shared_ptr:" << endl;
    cout << "  - Owns object" << endl;
    cout << "  - Increases reference count" << endl;
    cout << "  - Keeps object alive" << endl;
    cout << "  - Direct access: *ptr, ptr->" << endl;
    cout << endl;

    cout << "weak_ptr:" << endl;
    cout << "  - Observes object" << endl;
    cout << "  - Does NOT increase reference count" << endl;
    cout << "  - Does NOT keep object alive" << endl;
    cout << "  - Must lock() to access" << endl;

    return 0;
}
