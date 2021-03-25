#include "BombPlanted.h"
#include "Animation.h"

/* The BombPlanted class represents the planted bomb object
*  placed down by a player. BombPlanted inherits Item.
*  The header file is BombPlanted.h.
*/

BombPlanted::BombPlanted(Properties* props) : Item(props) {
    bombID++;
    std::string textureName = "bomb" + std::to_string(bombID);
    props->TextureID = textureName;
    TextureManager::GetInstance()->Load(textureName, "res/sprites/bombs2.bmp");
}
// Draw Bomb Item to screen
void BombPlanted::Draw() {
	TextureManager::GetInstance()->Draw(this->textureName, m_Transform->X, m_Transform->Y, m_Width, m_Height, 0, 0);
}

// Update player animation & position on the screen
void BombPlanted::Update(float dt) {

    //// Check there is a texture
    //if (m_PlantedBombTexture) {
    //    // Set the alpha of the texture
    //    SDL_SetTextureAlphaMod(m_PlantedBombTexture, alpha);
    //}

    //// Update the alpha value
    //if (alpha < SDL_ALPHA_OPAQUE) {
    //    alphaCalc += FADE_SPEED * &dt;
    //    alpha = alphaCalc;
    //}

    //// if alpha is above 255 clamp it
    //if (alpha >= SDL_ALPHA_OPAQUE) {
    //    alpha = SDL_ALPHA_OPAQUE;
    //    alphaCalc = (float)SDL_ALPHA_OPAQUE;
    //}

}

// Clean screen
void BombPlanted::Clean() {
	TextureManager::GetInstance()->Clean();
}