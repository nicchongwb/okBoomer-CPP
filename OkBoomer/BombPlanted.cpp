#include "BombPlanted.h"
#include "Animation.h"
#include <time.h>
#include "Player.h"

#define YOFFSET 60
/* The BombPlanted class represents the planted bomb object
*  placed down by a player. BombPlanted inherits Item.
*  The header file is BombPlanted.h.
*/

int BombPlanted::s_bombID = 0;

BombPlanted::BombPlanted(Properties* props) : Item(props) {

    m_BombAnimation = new Animation();

    s_bombID++;
    std::string textureName = "bomb"; textureName.append(std::to_string(s_bombID));
    props->TextureID = textureName;
    TextureManager::GetInstance()->Load(textureName, "res/sprites/BombFade.png");

    m_BombAnimation->SetProperties(textureName, 0, 0, 50, 50, SDL_FLIP_NONE);
}
// Draw Bomb Item to screen
void BombPlanted::Draw() {
    //if (m_BombAnimation->GetFrameCount() <= 150) {
    m_BombAnimation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
    //}
}

// Update animation & position on the screen
void BombPlanted::Update(float dt) {
    //if (m_putBomb) { // might not need this
        //placeBombCountdown();
        m_BombAnimation->Update();
    //}
}

// Clean screen
void BombPlanted::Clean() {
	TextureManager::GetInstance()->Clean();
}