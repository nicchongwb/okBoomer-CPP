#include "Game.h"
#include "Menu.h"

int main(int argc, char** argv) {


    //Initialise Menu
    Menu::GetInstance()->Init();

    //Display Menu
    while (Menu::GetInstance()->IsRunning()) {
        Menu::GetInstance()->Events();
        Menu::GetInstance()->Render();
    }
    // When program exits, clean up memory
    Game::GetInstance()->Clean();
    Menu::GetInstance()->Clean();

    return 0;
}
