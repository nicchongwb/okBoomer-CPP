#include "Game.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Player.h"
#include "IOHandler.h"
#include "MapParser.h"

#include <iostream>

/* Game class. This is where all our game loop methods
*  are defined.
*  Header file is Game.h
*/

Game * Game::s_Instance = nullptr;
Player * player1 = nullptr;
Player * player2 = nullptr;

bool Game::Init() {
    
    // If SDL cannot initalise, print error message
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // create SDL window
    m_Window = SDL_CreateWindow("OkBoomer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREN_HEIGHT, 0);
    
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

    // load map
    if (!MapParser::GetInstance()->Load()) {
        std::cout << "Failed to load map" << std::endl;
        return false;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("MAP");


    // load sprite
    TextureManager::GetInstance()->Load("player1", "res/sprites/characternew.png");
    TextureManager::GetInstance()->Load("player2", "res/sprites/characternew.png");
    //TextureManager::GetInstance()->Load("bomb", "res/sprites/bombs2.bmp");

    // draws player1 to 0, 0.
    player1 = new Player(new Properties("player1", 0, 0, 32, 32));
    player2 = new Player(new Properties("player2", 576, 576, 32, 32));
    
    Transform tf;

    tf.Log("Transform: ");

    return m_IsRunning = true;
}

void Game::Update() {

    player1->Update(0);
    player2->Update(0);
    m_LevelMap->Update();
}

void Game::Render() {

    
    // Setting screen colour
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    // Render Map
    m_LevelMap->Render();

    // Example of using Draw to draw item to the map: (see TextureManager.cpp for more info on fields)
    // TextureManager::GetInstance()->Draw("bomb", 64, 64, 32, 32, 0, 0);

    player1->Draw();
    player2->Draw();
    SDL_RenderPresent(m_Renderer);

}

void Game::Events() {
    // Listen for events
    IOHandler::GetInstance()->Listen();
}

bool Game::Clean() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();

    return true;
}

void Game::Quit() {
    m_IsRunning = false;
}
