#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "IOObject.h"
#include "Transform.h"
#include "SDL.h"

/* Entity encompasses all objects in the game.
*  Entity implements IOObject.h, and has a struct to define 
*  the common properties of each object.
*  The pure virtual functions are defined here.
*  There is no class file for Entity.
*/

// Properties struct defines the common features of each object
struct Properties {

public:
    Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        X = x;
        Y = y;
        PrevX = x;
        PrevY = y;
        Flip = flip;
        Width = width;
        Height = height;
        TextureID = textureID;
    }

public:
    std::string TextureID;
    int Width, Height;
    int X, Y, PrevX, PrevY;
    SDL_RendererFlip Flip;
};

class Entity : public IOObject {
public:

    explicit Entity(Properties* props): m_TextureID(props->TextureID),
        m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip) {
        m_Transform = new Transform(props->X, props->Y);
    }

    virtual void Draw() = 0;
    virtual void Clean() = 0;
    virtual void Update(float dt) = 0;

protected:

    Transform* m_Transform;
    int m_Width, m_Height;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};

#endif // ENTITY_H

