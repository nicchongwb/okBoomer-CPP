#include "Game.h"

int main(int argc, char** argv) {

    // Initialise Game
    Game::GetInstance()->Init();

    // Run game loop
    while (Game::GetInstance()->IsRunning()) {
        Game::GetInstance()->Events();
        Game::GetInstance()->Update();
        Game::GetInstance()->Render();
    }

    // When program exits, clean up memory
    Game::GetInstance()->Clean();

    return 0;
}
