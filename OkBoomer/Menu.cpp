#include "Menu.h"
#include "Game.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Player.h"
#include "IOHandler.h"
#include "MapParser.h"
#include "Board.h"
#include "BombCollectable.h"
#include "BombPlanted.h"
#include "ItemTimer.h"
#include "SDL_ttf.h"
#include "UILabel.h"

#include <iostream>
//#include <SDL_mixer.h>

#define YOFFSET 60

/* Menu class. This is where all our Menu loop methods
*  are defined.
*  Header file is Menu.h
*/

// initialise static alrPressed variables to false;


Menu* Menu::s_Instance = nullptr;

bool Menu::s_AlrPressedSpace = false;


bool Menu::Init() {

    // Initialise random seed
    srand(time(NULL));

    // If SDL cannot initalise, print error message
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // TTF Init
    if (TTF_Init() == -1) {
        printf("Failded to initialize TTL: %s", TTF_GetError());
    }
    // load font
    //TextureManager::GetInstance()->AddFont("arialbold", "res/fonts/arialbd.ttf", 13);

    // create SDL window
    m_Window = SDL_CreateWindow("OkBoomer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREN_HEIGHT, SDL_WINDOW_BORDERLESS);

    if (m_Window == nullptr) {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    // create SDL renderer
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (m_Renderer == nullptr) {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }

    Transform tf;

    return m_IsRunning = true;
}

void Menu::Render() {

    /*Screen for Menu State*/
    // Setting screen colour
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_Renderer);
    TTF_Font* Arial = TTF_OpenFont("res/fonts/arialbd.ttf",25); //this opens a font style and sets a size

    //Font color
    SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
    SDL_Color Gold = { 255,215,0 };
    SDL_Color Red = { 255,0,0 };

    //write text
    SDL_Surface* surfaceMessage1 = TTF_RenderText_Solid(Arial, "OK, BOOMER!", Gold);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Arial, "PRESS SPACEBAR TO START", White); 
    SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(Arial, "GAME OVER", Red);
    SDL_Surface* surfaceMessage5 = TTF_RenderText_Solid(Arial, "[esc] to quit", White);

    SDL_Surface* surfaceMessage3 = TTF_RenderText_Solid(Arial, "LUKE SKYWALKER WINS", Gold);
    SDL_Surface* surfaceMessage4 = TTF_RenderText_Solid(Arial, "YODA WINS", Gold);

    //now you can convert it into a texture
    SDL_Texture* Message1 = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage1);
    SDL_Texture* Message2 = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage2);
    SDL_Texture* Message3 = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage3);
    SDL_Texture* Message4 = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage4);
    SDL_Texture* Message5 = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage5);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage);
    
    //Rectangle for text display
    SDL_Rect Message_rect; //create a rect for "spacebar" text
    Message_rect.x = 70;  //controls the rect's x coordinate 
    Message_rect.y = 340; // controls the rect's y coordinte
    Message_rect.w = 500; // controls the width of the rect
    Message_rect.h = 70; // controls the height of the rect

    SDL_Rect Message_rect1; //create a rect for title/winner
    Message_rect1.x = 66.5;  //controls the rect's x coordinate 
    Message_rect1.y = 250; // controls the rect's y coordinte
    Message_rect1.w = 510; // controls the width of the rect
    Message_rect1.h = 80; // controls the height of the rect

    SDL_Rect Message_rect2; //create a rect for GameOVer
    Message_rect2.x = 66;  //controls the rect's x coordinate 
    Message_rect2.y = 150; // controls the rect's y coordinte
    Message_rect2.w = 510; // controls the width of the rect
    Message_rect2.h = 80; // controls the height of the rect

    SDL_Rect Message_rect3; //create a rect for esc option
    Message_rect3.x = 5;  //controls the rect's x coordinate 
    Message_rect3.y = 3; // controls the rect's y coordinte
    Message_rect3.w = 120; // controls the width of the rect
    Message_rect3.h = 30; // controls the height of the rect



    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
    if (Game::GetInstance()->getPlayAgain()==false) {
        SDL_RenderCopy(m_Renderer, Message, NULL, &Message_rect);
        SDL_RenderCopy(m_Renderer, Message1, NULL, &Message_rect1);
        SDL_RenderCopy(m_Renderer, Message5, NULL, &Message_rect3);
    }
    else {
        //GameOver screen
        if (Game::GetInstance()->getWhoWins() == true) {
            SDL_RenderCopy(m_Renderer, Message2, NULL, &Message_rect2);
            SDL_RenderCopy(m_Renderer, Message3, NULL, &Message_rect1);
            SDL_RenderCopy(m_Renderer, Message, NULL, &Message_rect);
            SDL_RenderCopy(m_Renderer, Message5, NULL, &Message_rect3);
        }
        else{
            SDL_RenderCopy(m_Renderer, Message2, NULL, &Message_rect2);
            SDL_RenderCopy(m_Renderer, Message4, NULL, &Message_rect1);
            SDL_RenderCopy(m_Renderer, Message, NULL, &Message_rect);
            SDL_RenderCopy(m_Renderer, Message5, NULL, &Message_rect3);
        }

    }

    //Key space Pushed to start game
    if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_SPACE)) {
        
        if (s_AlrPressedSpace==false) {
            printf("START\n");
            Menu::Clean();
            // Initialise Game
            Player::s_PlayerCount = 0;
            Game::GetInstance()->Init();

            // Run game loop
        while (Game::GetInstance()->IsRunning()) {
            Game::GetInstance()->Events();
            Game::GetInstance()->Update();
            Game::GetInstance()->Render();
        }
        }

    }
    //exit program when esc key is pressed
    else if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_ESCAPE)) {
        exit(1);
    }
    SDL_RenderPresent(m_Renderer);
    

}

void Menu::Events() {
    // Listen for events
    IOHandler::GetInstance()->Listen();
}



/* Methods to process SDL GUI */
bool Menu::Clean() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
   // Mix_Quit();

    return true;
}

void Menu::Quit() {
    m_IsRunning = false;
}
