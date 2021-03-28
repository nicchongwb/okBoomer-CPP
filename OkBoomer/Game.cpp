#include "Game.h"
#include "Menu.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Player.h"
#include "IOHandler.h"
#include "MapParser.h"
#include "Board.h"
#include "ItemTimer.h"
#include "SDL_ttf.h"
#include "UILabel.h"

#define YOFFSET 60

/* Game class. This is where all our game loop methods
*  are defined.
*  Header file is Game.h
*/

bool Game::gameOver = false;
bool Game::playAgain = false;
//True = Player1 wins, False= Player 2 wins
bool Game::whoWins;
bool Game::s_AlrPressedSpace = false;

Game * Game::s_Instance = nullptr;
Player * player1 = nullptr;
Player * player2 = nullptr;
std::vector <BombCollectable> * s_bombItemList = nullptr; // we only have one copy of bombItemList at all times.
std::vector <BombPlanted>* s_bombPlantedList = nullptr;
BombCollectable * bombItem = nullptr;
BombPlanted* bombPlanted = nullptr;
ItemTimer * itemTimer = nullptr;



bool Game::Init() {
    
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
    TextureManager::GetInstance()->AddFont("arialbold", "res/fonts/arialbd.ttf", 13);

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
    bombItem = new BombCollectable(new Properties("bomb", 0, 0, 32, 32));
    s_bombItemList = bombItem->getListOfSpawnedBombs();

    bombPlanted = new BombPlanted(new Properties("bomb", 0, 0, 32, 32));
    s_bombPlantedList = bombPlanted->getListOfPlantedBombs();

    itemTimer = new ItemTimer();

    Transform tf;

    return m_IsRunning = true;
}

void Game::Update() {

    // Update players
    player1->Update(0);
    player2->Update(0);
    // Update Map
    m_LevelMap->Update();

    // Update planted bombs
    for (int i = 0; i < s_bombPlantedList->size(); i++) {
        s_bombPlantedList->at(i).Update(0);
    }

    // Function for spawning items
    SpawnItem();

}

//check playAgain status for start menu display
bool Game::getPlayAgain() {
    return playAgain;
}

//check winner status for gameover menu display
bool Game::getWhoWins() {
    return whoWins;
}

void Game::Render() {
    
    //Screen for Game State
    // Setting screen colour
    SDL_SetRenderDrawColor(m_Renderer, 13, 165, 149, 255);
   
    SDL_RenderClear(m_Renderer);

    /*Check if Game Over*/
    int player1Health = player1->GetHealth();
    int player2Health = player2->GetHealth();

    if (player1Health == 0) {
        Game::Clean();
        gameOver = true;
        whoWins = false;
        player1Health += 10;

    }
    if (player2Health == 0) {
        Game::Clean();
        gameOver = true;
        whoWins = true;
        player2Health += 10;
       
    }

    //go to menu(gameover) screen
    if (gameOver == true) {
        gameOver = false;
        playAgain = true;
        Game::Clean();
        Game::Quit();
        Menu::GetInstance()->Init();
        //Display Menu
        while (Menu::GetInstance()->IsRunning()) {
            Menu::GetInstance()->Events();
            Menu::GetInstance()->Render();
        }
    }
  
    /* Scoreboard Section */
    TextureManager::GetInstance()->DrawIcon("player1", 32, 15, 32, 32, 4, 3, SDL_FLIP_NONE);
    TextureManager::GetInstance()->DrawIcon("player2", 576, 15, 32, 32, 0, 0, SDL_FLIP_NONE);

    SDL_Color color = { 255, 255, 255 };
    UILabel p1Name(76, 15, "Luke Skywalker", "arialbold", color);
    UILabel p2Name(480, 15, "Yoda", "arialbold", color);

    std::string p1HealthStr = "Health: " + std::to_string(player1->GetHealth()) + "/10";
    std::string p2HealthStr = "Health: " + std::to_string(player2->GetHealth()) + "/10";
    UILabel p1Health(76, 30, p1HealthStr, "arialbold", color);
    UILabel p2Health(480, 30, p2HealthStr, "arialbold", color);
    
    p1Name.draw();
    p2Name.draw();
    p1Health.draw();
    p2Health.draw();

    /* Inventory Section */
    TextureManager::GetInstance()->DrawIcon("bomb", 32, 715, 32, 32, 0, 0, SDL_FLIP_NONE);
    TextureManager::GetInstance()->DrawIcon("bomb", 590, 715, 32, 32, 0, 0, SDL_FLIP_NONE);

    std::string p1BombStr = "Bombs: " + std::to_string(player1->GetBomb()) + "/3";
    std::string p2BombStr = "Bombs: " + std::to_string(player2->GetBomb()) + "/3";
    UILabel p1Bomb(76, 715, p1BombStr, "arialbold", color);
    UILabel p2Bomb(480, 715, p2BombStr, "arialbold", color);

    std::string p1BombColStr = "Bomb Parts: " + std::to_string(player1->GetBombCol()) + "/2";
    std::string p2BombColStr = "Bomb Parts: " + std::to_string(player2->GetBombCol()) + "/2";
    UILabel p1BombCol(76, 730, p1BombColStr, "arialbold", color);
    UILabel p2BombCol(480, 730, p2BombColStr, "arialbold", color);

    p1Bomb.draw();
    p2Bomb.draw();
    p1BombCol.draw();
    p2BombCol.draw();

    // Render Map
    m_LevelMap->Render();

    // Draw players
    player1->Draw();
    player2->Draw();
    
    // Draw spawned bomb collectables
    for (int i = 0; i < s_bombItemList->size(); i++) {
        s_bombItemList->at(i).Draw();
    }
    // Draw planted bombs
    for (int i = 0; i < s_bombPlantedList->size(); i++) {
        if (s_bombPlantedList->at(i).m_isBombPlanted == true)
            s_bombPlantedList->at(i).Draw();

        // make sure the bomb animation does not loop
        if (!s_bombPlantedList->at(i).m_countDown) {
            s_bombPlantedList->at(i).m_countDown = true;
            // start timer
            clock_t now = clock();
            s_bombPlantedList->at(i).m_start = now;

        }
        //set animations for 1s
        if (s_bombPlantedList->at(i).m_start + 1000 < clock()) {
            s_bombPlantedList->at(i).m_countDown = false;
            s_bombPlantedList->at(i).m_isBombPlanted = false;
        }
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

// Used by Board.cpp to get the s_BombItemList
std::vector<BombCollectable>* Game::GetBombItemList() {
    return s_bombItemList;
}
// Used by Player.cpp to get s_bombPlantedList
std::vector<BombPlanted>* Game::GetBombPlantedList() {
    return s_bombPlantedList;
}

void Game::SpawnItem()
{
    // Only one item exists in the game at this moment (bomb part item)
    // The code below spawns this item.

    // If the number of bomb parts (item) on the map exceeds MAX_BOMBITEM_SPAWNED, stop spawning.
    if (s_bombItemList->size() < MAX_BOMBITEM_SPAWNED) {
        
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

                        auto iter = s_bombItemList->begin(); // 'iter' is an iterator object that points the elements in bombListItem
                        s_bombItemList->insert(iter, BombCollectable(new Properties("bomb", randX * 64, randY * 64, 32, 32)));
                        // update board array to show that a collectable bomb part has spawned there
                        Board::GetInstance()->updateBoardWithItem(randX, randY, 4);
                        std::cout << "Item spawned at " << randX << ", " << randY << std::endl;
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
    Mix_Quit();
    return true;
}

void Game::Quit() {
    m_IsRunning = false;
}
