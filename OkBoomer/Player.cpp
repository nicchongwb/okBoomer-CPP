#include "Player.h"
#include "TextureManager.h"
#include "Animation.h"
#include <SDL.h>


/* Player class. Each Player object represents
*  a distinct player in the game.
*  Header file is Player.h
*/


// Constructor for Player
Player::Player(Properties * props): Creature(props) {
	m_Animation = new Animation();
	// Set Properties -> Row, Frame_Count, Animation_Speed, SDL_Flip)
	m_Animation->SetProperties(m_TextureID, 0, 3, 500, SDL_FLIP_NONE);

}

// Draw player to screen
void Player::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	//TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
}

// Update player animation on the screen
void Player::Update(float dt) {
	m_Animation->Update();
}

// Clean screen
void Player::Clean() {
	TextureManager::GetInstance()->Clean();
}

