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
void TextureManager::Draw(std::string id, int x, int y, int width, int height, int row, int col, SDL_RendererFlip flip){
    /* x and y will be the location to draw the image.
    *  width and height specifies the width and height of the image to crop. (32 x 32)
    *  row and col specifies WHERE on the image to crop.
    *  Note: SDL_RendererFlip just specifies if we should flip the sprite. Not used, can remove later on.
    */
    SDL_Rect srcRect = { width + (col * width), height * row, width, height };
    SDL_Rect dstRect = {x, y, 64, 64}; // scale sprites to 64 x 64
    SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawIcon(std::string id, int x, int y, int width, int height, int row, int col, SDL_RendererFlip flip)
{
    /* x and y will be the location to draw the image.
    *  width and height specifies the width and height of the image to crop. (32 x 32)
    *  row and col specifies WHERE on the image to crop.
    *  Note: SDL_RendererFlip just specifies if we should flip the sprite. Not used, can remove later on.
    */
    SDL_Rect srcRect = { width + (col * width), height * row, width, height };
    SDL_Rect dstRect = { x, y, 32, 32 }; // scale sprites to 64 x 64
    SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

// Draw Frame for animation.
void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int col, int frame, SDL_RendererFlip flip){
    
    /* x and y will be the location to draw the image. 
    *  width and height specifies the width and height of the image to crop. (32 x 32)
    *  row and col specifies WHERE on the image to crop.
    *  E.g. Animation frames for player are drawn like [][][] <- where each [] represents one frame. 
    */

    SDL_Rect srcRect = {(width*frame)+(col*width), height*row, width, height};
    SDL_Rect dstRect = {x, y, 64, 64}; // scale sprites to 64 x 64
    SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

// Draw Tile for Map Parser
void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip) {
    SDL_Rect srcRect = { tileSize * frame, tileSize * row, tileSize, tileSize };
    SDL_Rect dstRect = { x, y, tileSize, tileSize };
    SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::AddFont(std::string id, std::string path, int fontSize) {
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* TextureManager::GetFont(std::string id) {
    return fonts[id];
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

