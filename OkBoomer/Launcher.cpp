#include "Game.h"
#include "Menu.h"

int main(int argc, char** argv) {


    //Initialise Menu
    Menu::GetInstance()->Init();

    //Display Menu
    while (Menu::GetInstance()->IsRunning()) {
        Game::GetInstance()->Events();
        Menu::GetInstance()->Render();
    }

    // Initialise Game
   // Game::GetInstance()->Init();

    // Run game loop
    /*while (Game::GetInstance()->IsRunning()) {
        Game::GetInstance()->Events();
        Game::GetInstance()->Update();
        Game::GetInstance()->Render();
    }*/

    // When program exits, clean up memory
    Game::GetInstance()->Clean();
    Menu::GetInstance()->Clean();

    return 0;
}
