#pragma once

#ifndef Menu_H
#define Menu_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "BombCollectable.h"
#include "BombPlanted.h"

/* Menu.H AND Menu.CPP CONTAINS Menu LOOP METHODS */

// Define screen dimensions
#define SCREEN_WIDTH 640
#define SCREN_HEIGHT 760


class Menu {

public:
    static Menu* GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Menu();
    }

    // static variables for checking if key is already held down
    static bool s_AlrPressedSpace;

    // Menu loop methods
    bool Init();
    bool Clean();
    void Quit();

    void Render();
    void Events();




    inline bool IsRunning() { return m_IsRunning; }
    // To render SDL window
    inline SDL_Renderer* GetRenderer() { return m_Renderer; }

private:
    Menu() {}
    bool m_IsRunning;


    // To render SDL Window
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static Menu* s_Instance;
};

#endif // Menu_H
