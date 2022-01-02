#pragma once

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GameMap.h"
#include "BombCollectable.h"
#include "BombPlanted.h"

/* GAME.H AND GAME.CPP CONTAINS GAME LOOP METHODS */

// Define screen dimensions
#define SCREEN_WIDTH 640
#define SCREN_HEIGHT 760


class Game {

public:
    static Game * GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Game();
    }

    // Game loop methods
    bool Init();
    bool Clean();
    void Quit();

    void Update();
    void Render();
    void Events();

    // Game logic methods
    void BombPlayer(int m_pid);
    void CollectBomb(int m_pid);
    void PlantBomb(int m_pid);
    void SpawnItem();

    // To get GameMap
    inline GameMap* GetMap() { return m_LevelMap; }

    // Maintain one instance of the number of bomb items spawned on the map.
    std::vector<BombCollectable>* GetBombItemList();
    // Maintain one instance of the planted bombs on the map
    std::vector<BombPlanted>* GetBombPlantedList();

    inline bool IsRunning() { return m_IsRunning; }
    // To render SDL window
    inline SDL_Renderer* GetRenderer() { return m_Renderer; }

private:
    Game() {}
    bool m_IsRunning;

    // Create GameMap
    GameMap* m_LevelMap;

    // To render SDL Window
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static Game * s_Instance;
};

#endif // GAME_H
