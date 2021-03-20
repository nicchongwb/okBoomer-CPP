#include "Game.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Player.h"
#include "IOHandler.h"
#include "MapParser.h"
#include "Board.h"
#include "BombCollectable.h"
#include "ItemTimer.h"

#include <iostream>

/* Game class. This is where all our game loop methods
*  are defined.
*  Header file is Game.h
*/

Game * Game::s_Instance = nullptr;
Player * player1 = nullptr;
Player * player2 = nullptr;
std::vector <BombCollectable> * bombItemList = nullptr;
BombCollectable * bombItem = nullptr;
ItemTimer * itemTimer = nullptr;

bool Game::Init() {
    
    // Initialise random seed
    srand(time(NULL));

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
    TextureManager::GetInstance()->Load("bomb", "res/sprites/bombs2.bmp");

    // Initialise board
    Board::GetInstance()->initBoard();
    Board::GetInstance()->consoleBoard();

    // draws player1 to 0, 0.
    player1 = new Player(new Properties("player1", 0, 0, 32, 32));
    player2 = new Player(new Properties("player2", 576, 576, 32, 32));
    
    // Initialise bomb collectable item vector list
    bombItem = new BombCollectable(new Properties("bomb", 512, 64, 32, 32));
    bombItemList = bombItem->getListOfSpawnedBombs();

    itemTimer = new ItemTimer();

    Transform tf;

    tf.Log("Transform: ");

    return m_IsRunning = true;
}

void Game::Update() {

    player1->Update(0);
    player2->Update(0);
    m_LevelMap->Update();
    SpawnItem();

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
    
    for (int i = 0; i < bombItemList->size(); i++) {
        bombItemList->at(i).Draw();
    }
    SDL_RenderPresent(m_Renderer);

}

void Game::Events() {
    // Listen for events
    IOHandler::GetInstance()->Listen();
}

/* Methods to process game logic */
void Game::BombPlayer(int m_pid)
{
    if (m_pid == 1) {
        player1->takeDamage();
    }
    else if (m_pid == 2) {
        player2->takeDamage();
    }
}

void Game::CollectBomb(int m_pid)
{
    if (m_pid == 1) {
        player1->collectBomb();
    }
    else if (m_pid == 2) {
        player2->collectBomb();
    }
}

void Game::PlantBomb(int m_pid)
{
    if (m_pid == 1) {
        player1->plantBomb();
    }
    else if (m_pid == 2) {
        player2->plantBomb();
    }
}

void Game::SpawnItem()
{
    // Only one item exists in the game at this moment (bomb part item)
    // The code below spawns this item.

    // If the number of bomb parts (item) on the map exceeds MAX_BOMBITEM_SPAWNED, stop spawning.
    if (bombItemList->size() < MAX_BOMBITEM_SPAWNED) {
        
        // if timer not started yet, start it.
        if (!itemTimer->getTimerHasStarted()) {
            // stop the timer first because it has already been started in Game::init()
            itemTimer->stopTimer(); 
            itemTimer->startTimer();
        }
        // else, check if item is ready to spawn
        else {
        
            if (itemTimer->getReadyToSpawn()) {

                // if item is ready to spawn, spawn item on random coordinates
                while (true) {
                    int randX = rand() % 9;
                    int randY = rand() % 9;

                    // check if coordinates are valid for spawning.
                    if (Board::GetInstance()->getTileID(randX, randY) == 0) {

                        auto iter = bombItemList->begin(); // 'iter' is an iterator object that points the elements in bombListItem
                        bombItemList->insert(iter, BombCollectable(new Properties("bomb", randX * 64, randY * 64, 32, 32)));
                        // update board array to show that a collectable bomb part has spawned there
                        Board::GetInstance()->updateBoardWithItem(randX, randY, 4);
                        std::cout << "Item spawned at " << randX << randY << std::endl;
                        // reset the item spawn rate, and timer countdown
                        itemTimer->setReadyToSpawn(false);
                        itemTimer->setTimerHasStarted(false);
                        break;
                    }
                }
            }
        }
    }
}
/* Methods to process SDL GUI */
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
