#include "TextureManager.h"
#include "Game.h"

/* Texture Manager handles the drawing of objects
*  and animations to the screen. 
*  Header file is TextureManager.h
*/
TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename){

    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr){
        SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
    if(texture == nullptr){
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    return true;
}

// Draw from image on screen
void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip){
    // draw from 0 to x and 0 to y.
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

// Draw Frame for animation.
void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip){
    SDL_Rect srcRect = {width*frame, height*row, width, height};
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}


void TextureManager::Drop(std::string id){
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean(){
    std::map<std::string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    m_TextureMap.clear();

    SDL_Log("texture map cleaned!");
}

