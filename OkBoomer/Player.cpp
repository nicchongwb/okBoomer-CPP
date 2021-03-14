#include "Player.h"
#include "TextureManager.h"
#include <SDL.h>


/* Player class. Each Player object represents
*  a distinct player in the game.
*  Header file is Player.h
*/


// Constructor for Player
Player::Player(Properties * props): Creature(props) {
	m_Row = 0;
	m_FrameCount = 3;
	m_AnimSpeed = 500;
}

// Draw player to screen
void Player::Draw() {
	TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
}

// Update player animation on the screen
void Player::Update(float dt) {
	m_Frame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

// Clean screen
void Player::Clean() {
	TextureManager::GetInstance()->Clean();
}

