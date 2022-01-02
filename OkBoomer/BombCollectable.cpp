#include "BombCollectable.h"

BombCollectable::BombCollectable(Properties* props) : Item(props) {
	
}
// Draw Bomb Item to screen
void BombCollectable::Draw() {
	TextureManager::GetInstance()->Draw("bomb", m_Transform->X, m_Transform->Y + YOFFSET, m_Width, m_Height, 0, 0);
}

// Update player animation & position on the screen
void BombCollectable::Update(float dt) {

}

// Clean screen
void BombCollectable::Clean() {
    TextureManager::GetInstance()->Clean();
}