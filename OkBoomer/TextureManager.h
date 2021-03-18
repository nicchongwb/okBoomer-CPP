#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include "SDL.h"
#include <map>

/* Texture Manager handles the drawing of objects
*  and animations to the screen.
*  Class file is TextureManager.cpp
*/

class TextureManager
{
    public:
        static TextureManager* GetInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();}

        bool Load(std::string id, std::string filename);
        void Drop(std::string id);
        void Clean();
        
        // Draw from image to x to y.
        void Draw(std::string id, int x, int y, int width, int height, int row, int col, SDL_RendererFlip flip=SDL_FLIP_NONE);
        /* Draw frame (animation) to x and y, from width to height. 
        *  Row and Col is coordinates on the sprite sheet. 
        *  Frame is frame count.
        */
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int col, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);

        // Similar to DrawFrame(), instead of int width, height we use int tileSize
        void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);


    private:
        TextureManager(){}
        std::map<std::string, SDL_Texture*> m_TextureMap;
        static TextureManager* s_Instance;
};

#endif // TEXTUREMANAGER_H
