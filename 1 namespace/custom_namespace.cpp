
#include <iostream>
namespace Engine
{
    class Game
    {
    public:
        Game();
        ~Game();

        void Run();
        void Update();
        bool IsRunning() const;
    };
}
using namespace std;
Engine::Game::Game()
{
    // Constructor implementation
    cout << "Game initialized." << endl;
}

Engine::Game::~Game()
{
    // Destructor implementation
    cout << "Game terminated." << endl;
}

void Engine::Game::Run()
{
    // Run implementation
    cout << "Game is running." << endl;
}
void Engine::Game::Update()
{
    // Update implementation
    cout << "Game is updating." << endl;
}

int main()
{
    Engine::Game myGame;
    myGame.Run();
    myGame.Update();
    return 0;
}