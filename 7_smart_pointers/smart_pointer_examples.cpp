/*
### Smart Pointer Practical Examples

This file contains real-world examples demonstrating practical uses of smart pointers:
1. Resource management (files, connections)
2. Factory pattern
3. Observer pattern
4. Pimpl idiom
5. Cache implementation
6. Graph/tree structures
7. Plugin system
8. Undo/redo system


### Example 1: RAII Resource Manager
- Automatic file/connection cleanup
- Exception-safe resource handling


### Example 2: Factory Pattern
- Return unique_ptr from factory
- Transfer ownership to caller


### Example 3: Observer Pattern
- Subject uses weak_ptr for observers
- Observers don't keep subject alive


### Example 4: Pimpl Idiom
- Hide implementation details
- Reduce compilation dependencies


### Example 5: Cache with weak_ptr
- Cache doesn't keep objects alive
- Automatic cleanup of unused entries


### Example 6: Tree Structure
- Parent uses unique_ptr (owns children)
- Children use weak_ptr (reference parent)


### Example 7: Callback System
- Store callbacks as shared_ptr
- Automatic cleanup when callback object destroyed


### Example 8: Undo/Redo Stack
- Commands stored as unique_ptr
- Clear ownership semantics

*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <stack>

using namespace std;

// === Example 1: RAII Resource Manager ===

class DatabaseConnection
{
private:
    string connectionString;
    bool connected;

public:
    DatabaseConnection(const string& connStr) : connectionString(connStr), connected(true)
    {
        cout << "  [DB Connected: " << connectionString << "]" << endl;
    }

    ~DatabaseConnection()
    {
        if (connected)
        {
            cout << "  [DB Disconnected: " << connectionString << "]" << endl;
        }
    }

    void query(const string& sql)
    {
        if (connected)
        {
            cout << "  Executing: " << sql << endl;
        }
    }

    void disconnect()
    {
        connected = false;
        cout << "  [DB Manually disconnected]" << endl;
    }
};

// === Example 2: Factory Pattern ===

class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual string getType() const = 0;
};

class Circle : public Shape
{
private:
    int radius;

public:
    Circle(int r) : radius(r)
    {
        cout << "  [Circle created with radius " << radius << "]" << endl;
    }

    ~Circle()
    {
        cout << "  [Circle destroyed]" << endl;
    }

    void draw() const override
    {
        cout << "  Drawing circle (radius: " << radius << ")" << endl;
    }

    string getType() const override { return "Circle"; }
};

class Rectangle : public Shape
{
private:
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h)
    {
        cout << "  [Rectangle created " << width << "x" << height << "]" << endl;
    }

    ~Rectangle()
    {
        cout << "  [Rectangle destroyed]" << endl;
    }

    void draw() const override
    {
        cout << "  Drawing rectangle (" << width << "x" << height << ")" << endl;
    }

    string getType() const override { return "Rectangle"; }
};

unique_ptr<Shape> createShape(const string& type, int param1, int param2 = 0)
{
    if (type == "circle")
    {
        return make_unique<Circle>(param1);
    }
    else if (type == "rectangle")
    {
        return make_unique<Rectangle>(param1, param2);
    }
    return nullptr;
}

// === Example 3: Observer Pattern ===

class Subject;

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void onNotify(const string& message) = 0;
    virtual string getName() const = 0;
};

class ConcreteObserver : public Observer
{
private:
    string name;

public:
    ConcreteObserver(string n) : name(n)
    {
        cout << "  [Observer '" << name << "' created]" << endl;
    }

    ~ConcreteObserver()
    {
        cout << "  [Observer '" << name << "' destroyed]" << endl;
    }

    void onNotify(const string& message) override
    {
        cout << "  " << name << " received: " << message << endl;
    }

    string getName() const override { return name; }
};

class Subject
{
private:
    vector<weak_ptr<Observer>> observers;

public:
    void attach(shared_ptr<Observer> obs)
    {
        observers.push_back(obs);
        cout << "  Observer attached" << endl;
    }

    void notify(const string& message)
    {
        cout << "  Notifying observers..." << endl;
        
        // Remove expired observers
        observers.erase(
            remove_if(observers.begin(), observers.end(),
                [](const weak_ptr<Observer>& wp) { return wp.expired(); }),
            observers.end()
        );

        for (auto& weakObs : observers)
        {
            if (auto obs = weakObs.lock())
            {
                obs->onNotify(message);
            }
        }
    }

    size_t observerCount() const
    {
        return count_if(observers.begin(), observers.end(),
            [](const weak_ptr<Observer>& wp) { return !wp.expired(); });
    }
};

// === Example 4: Tree Structure ===

class TreeNode
{
private:
    string data;
    vector<unique_ptr<TreeNode>> children;
    weak_ptr<TreeNode> parent;

public:
    TreeNode(string d) : data(d)
    {
        cout << "  [TreeNode '" << data << "' created]" << endl;
    }

    ~TreeNode()
    {
        cout << "  [TreeNode '" << data << "' destroyed]" << endl;
    }

    void addChild(unique_ptr<TreeNode> child)
    {
        children.push_back(std::move(child));
    }

    void setParent(weak_ptr<TreeNode> p)
    {
        parent = p;
    }

    void print(int indent = 0) const
    {
        for (int i = 0; i < indent; ++i) cout << "  ";
        cout << data << endl;
        
        for (const auto& child : children)
        {
            child->print(indent + 1);
        }
    }

    string getData() const { return data; }
    size_t childCount() const { return children.size(); }
};

// === Example 5: Cache Implementation ===

template<typename Key, typename Value>
class Cache
{
private:
    map<Key, weak_ptr<Value>> cache;

public:
    shared_ptr<Value> get(const Key& key)
    {
        auto it = cache.find(key);
        if (it != cache.end())
        {
            if (auto cached = it->second.lock())
            {
                cout << "  Cache hit for key: " << key << endl;
                return cached;
            }
            else
            {
                cout << "  Cache expired for key: " << key << endl;
                cache.erase(it);
            }
        }
        cout << "  Cache miss for key: " << key << endl;
        return nullptr;
    }

    void put(const Key& key, shared_ptr<Value> value)
    {
        cache[key] = value;
        cout << "  Cached key: " << key << endl;
    }

    size_t size() const
    {
        return count_if(cache.begin(), cache.end(),
            [](const auto& pair) { return !pair.second.expired(); });
    }

    void cleanup()
    {
        for (auto it = cache.begin(); it != cache.end(); )
        {
            if (it->second.expired())
            {
                it = cache.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
};

// === Example 6: Command Pattern (Undo/Redo) ===

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual string describe() const = 0;
};

class AddCommand : public Command
{
private:
    int& value;
    int amount;

public:
    AddCommand(int& val, int amt) : value(val), amount(amt) {}

    void execute() override
    {
        value += amount;
        cout << "  Executed: Add " << amount << " (result: " << value << ")" << endl;
    }

    void undo() override
    {
        value -= amount;
        cout << "  Undone: Add " << amount << " (result: " << value << ")" << endl;
    }

    string describe() const override
    {
        return "Add " + to_string(amount);
    }
};

class MultiplyCommand : public Command
{
private:
    int& value;
    int factor;

public:
    MultiplyCommand(int& val, int fac) : value(val), factor(fac) {}

    void execute() override
    {
        value *= factor;
        cout << "  Executed: Multiply by " << factor << " (result: " << value << ")" << endl;
    }

    void undo() override
    {
        value /= factor;
        cout << "  Undone: Multiply by " << factor << " (result: " << value << ")" << endl;
    }

    string describe() const override
    {
        return "Multiply by " + to_string(factor);
    }
};

class CommandManager
{
private:
    stack<unique_ptr<Command>> undoStack;
    stack<unique_ptr<Command>> redoStack;

public:
    void executeCommand(unique_ptr<Command> cmd)
    {
        cmd->execute();
        undoStack.push(std::move(cmd));
        
        // Clear redo stack on new command
        while (!redoStack.empty()) redoStack.pop();
    }

    void undo()
    {
        if (!undoStack.empty())
        {
            auto cmd = std::move(undoStack.top());
            undoStack.pop();
            
            cmd->undo();
            redoStack.push(std::move(cmd));
        }
        else
        {
            cout << "  Nothing to undo" << endl;
        }
    }

    void redo()
    {
        if (!redoStack.empty())
        {
            auto cmd = std::move(redoStack.top());
            redoStack.pop();
            
            cmd->execute();
            undoStack.push(std::move(cmd));
        }
        else
        {
            cout << "  Nothing to redo" << endl;
        }
    }
};

int main()
{
    cout << "=== Example 1: RAII Resource Management ===" << endl;
    {
        unique_ptr<DatabaseConnection> db = make_unique<DatabaseConnection>("localhost:5432");
        db->query("SELECT * FROM users");
        db->query("INSERT INTO logs VALUES (...)");
        cout << "Leaving scope..." << endl;
    }
    cout << "Database automatically disconnected" << endl;
    cout << endl;

    cout << "=== Example 2: Factory Pattern ===" << endl;
    {
        vector<unique_ptr<Shape>> shapes;

        shapes.push_back(createShape("circle", 5));
        shapes.push_back(createShape("rectangle", 10, 20));
        shapes.push_back(createShape("circle", 3));

        cout << "\nDrawing all shapes:" << endl;
        for (const auto& shape : shapes)
        {
            if (shape)
            {
                shape->draw();
            }
        }

        cout << "\nLeaving scope..." << endl;
    }
    cout << "All shapes destroyed" << endl;
    cout << endl;

    cout << "=== Example 3: Observer Pattern ===" << endl;
    {
        Subject subject;

        {
            auto obs1 = make_shared<ConcreteObserver>("Observer1");
            auto obs2 = make_shared<ConcreteObserver>("Observer2");
            auto obs3 = make_shared<ConcreteObserver>("Observer3");

            subject.attach(obs1);
            subject.attach(obs2);
            subject.attach(obs3);

            cout << "\nNotifying with all observers active:" << endl;
            subject.notify("First notification");

            cout << "\nDestroying Observer2..." << endl;
        }

        cout << "\nNotifying after Observer2 destroyed:" << endl;
        cout << "Active observers: " << subject.observerCount() << endl;
        subject.notify("Second notification");
    }
    cout << endl;

    cout << "=== Example 4: Tree Structure ===" << endl;
    {
        auto root = make_unique<TreeNode>("Root");
        auto child1 = make_unique<TreeNode>("Child1");
        auto child2 = make_unique<TreeNode>("Child2");
        auto grandchild1 = make_unique<TreeNode>("Grandchild1");
        auto grandchild2 = make_unique<TreeNode>("Grandchild2");

        child1->addChild(std::move(grandchild1));
        child1->addChild(std::move(grandchild2));

        root->addChild(std::move(child1));
        root->addChild(std::move(child2));

        cout << "\nTree structure:" << endl;
        root->print();

        cout << "\nLeaving scope (cascading destruction)..." << endl;
    }
    cout << "All nodes destroyed in proper order" << endl;
    cout << endl;

    cout << "=== Example 5: Cache Implementation ===" << endl;
    {
        Cache<string, string> cache;

        {
            auto data1 = make_shared<string>("Value1");
            auto data2 = make_shared<string>("Value2");

            cache.put("key1", data1);
            cache.put("key2", data2);

            cout << "\nCache size: " << cache.size() << endl;

            cout << "\nAccessing cached data:" << endl;
            auto retrieved = cache.get("key1");
            if (retrieved)
            {
                cout << "  Retrieved: " << *retrieved << endl;
            }

            cout << "\nLeaving scope (data1 and data2 destroyed)..." << endl;
        }

        cout << "\nAfter data destroyed:" << endl;
        cout << "Cache size before cleanup: " << cache.size() << endl;
        
        auto retrieved = cache.get("key1");
        if (!retrieved)
        {
            cout << "Data no longer available (correct behavior)" << endl;
        }

        cache.cleanup();
        cout << "Cache size after cleanup: " << cache.size() << endl;
    }
    cout << endl;

    cout << "=== Example 6: Command Pattern (Undo/Redo) ===" << endl;
    {
        int value = 10;
        CommandManager manager;

        cout << "Initial value: " << value << endl;
        cout << endl;

        cout << "Executing commands:" << endl;
        manager.executeCommand(make_unique<AddCommand>(value, 5));
        manager.executeCommand(make_unique<MultiplyCommand>(value, 2));
        manager.executeCommand(make_unique<AddCommand>(value, 10));

        cout << "\nCurrent value: " << value << endl;
        cout << endl;

        cout << "Undoing operations:" << endl;
        manager.undo();
        manager.undo();

        cout << "\nCurrent value: " << value << endl;
        cout << endl;

        cout << "Redoing operations:" << endl;
        manager.redo();

        cout << "\nFinal value: " << value << endl;
    }
    cout << endl;

    cout << "=== Example 7: Polymorphic Container ===" << endl;
    {
        vector<unique_ptr<Shape>> shapeCollection;

        shapeCollection.push_back(make_unique<Circle>(7));
        shapeCollection.push_back(make_unique<Rectangle>(15, 10));
        shapeCollection.push_back(make_unique<Circle>(4));
        shapeCollection.push_back(make_unique<Rectangle>(20, 5));

        cout << "\nProcessing shape collection:" << endl;
        for (const auto& shape : shapeCollection)
        {
            cout << "Type: " << shape->getType() << " - ";
            shape->draw();
        }

        cout << "\nRemoving circles..." << endl;
        shapeCollection.erase(
            remove_if(shapeCollection.begin(), shapeCollection.end(),
                [](const unique_ptr<Shape>& s) { return s->getType() == "Circle"; }),
            shapeCollection.end()
        );

        cout << "\nRemaining shapes:" << endl;
        for (const auto& shape : shapeCollection)
        {
            shape->draw();
        }
    }
    cout << endl;

    cout << "=== Benefits Summary ===" << endl;
    cout << "\n1. RAII: Automatic resource cleanup" << endl;
    cout << "   - No memory leaks" << endl;
    cout << "   - Exception-safe" << endl;
    cout << "   - Deterministic destruction" << endl;

    cout << "\n2. Factory Pattern: Clear ownership transfer" << endl;
    cout << "   - Caller receives ownership" << endl;
    cout << "   - No ambiguity about who deletes" << endl;
    cout << "   - Type-safe polymorphism" << endl;

    cout << "\n3. Observer Pattern: Weak references" << endl;
    cout << "   - Observers don't keep subject alive" << endl;
    cout << "   - Automatic cleanup of dead observers" << endl;
    cout << "   - No circular references" << endl;

    cout << "\n4. Tree/Graph: Clear ownership hierarchy" << endl;
    cout << "   - Parent owns children (unique_ptr)" << endl;
    cout << "   - Children reference parent (weak_ptr)" << endl;
    cout << "   - Automatic cascading deletion" << endl;

    cout << "\n5. Cache: Non-owning references" << endl;
    cout << "   - Cache doesn't keep data alive" << endl;
    cout << "   - Automatic eviction of unused data" << endl;
    cout << "   - Memory-efficient" << endl;

    cout << "\n6. Command Pattern: Undo/Redo" << endl;
    cout << "   - Clear ownership of commands" << endl;
    cout << "   - Easy transfer between stacks" << endl;
    cout << "   - Type-safe polymorphism" << endl;
    cout << endl;

    cout << "=== Real-World Use Cases ===" << endl;
    cout << "1. GUI frameworks (widget ownership)" << endl;
    cout << "2. Game engines (entity management)" << endl;
    cout << "3. Resource managers (texture, sound loading)" << endl;
    cout << "4. Document editors (undo/redo systems)" << endl;
    cout << "5. Network libraries (connection pools)" << endl;
    cout << "6. Plugin systems (dynamic loading)" << endl;
    cout << "7. Event systems (callback registration)" << endl;
    cout << "8. Scene graphs (3D rendering)" << endl;

    return 0;
}
