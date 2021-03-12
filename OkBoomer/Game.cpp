#include "Game.h"
#include "TextureManager.h"
#include <iostream>

// GAME.H AND GAME.CPP CONTAINS GAME LOOP METHODS

Game * Game::s_Instance = nullptr;

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

    // load sprite
    TextureManager::GetInstance()->Load("bg", "res/sprites/characternew.png");
    return m_IsRunning = true;
}

void Game::Update() {
    SDL_Log("updating...");
}

void Game::Render() {

    // Setting screen colour
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);
    // render texture Draw(coord_x on map, coord_y on map, width of image, height of image)
    TextureManager::GetInstance()->Draw("bg", 0, 0, 32, 32);
    SDL_RenderPresent(m_Renderer);

}

void Game::Events() {

    // Event handler so the system knows what to do with our SDL window.
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        Quit();
        break;
    }
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
