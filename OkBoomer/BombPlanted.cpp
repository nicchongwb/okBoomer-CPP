#include "BombPlanted.h"
#include "Animation.h"

/* The BombPlanted class represents the planted bomb object
*  placed down by a player. BombPlanted inherits Item.
*  The header file is BombPlanted.h.
*/

BombPlanted::BombPlanted(Properties* props) : Item(props) {

}
// Draw Bomb Item to screen
void BombPlanted::Draw() {
	TextureManager::GetInstance()->Draw("bomb", m_Transform->X, m_Transform->Y, m_Width, m_Height, 0, 0);
}

// Update player animation & position on the screen
void BombPlanted::Update(float dt) {

}

// Clean screen
void BombPlanted::Clean() {
	TextureManager::GetInstance()->Clean();
}