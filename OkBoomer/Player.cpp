#include "Player.h"
#include "TextureManager.h"
#include "Animation.h"
#include "IOHandler.h"
#include <SDL.h>


/* Player class. Each Player object represents
*  a distinct player in the game.
*  Header file is Player.h
*/

// initialise static playerCount to 0
int Player::s_PlayerCount = 0;

int X, Y;
// Constructor for Player
Player::Player(Properties * props): Creature(props) {

	m_Animation = new Animation();

    m_pid = s_PlayerCount;
    s_PlayerCount++;

	// Set Player 1 animation
	if (props->TextureID == "player1") {
		// Set Properties -> Row, Col, Frame_Count, Animation_Speed, SDL_Flip
		// Row and Col specifies where to chop on the spritesheet
		m_Animation->SetProperties(m_TextureID, 0, 0, 3, 500, SDL_FLIP_NONE);
	}
	// Set Player 2 animation
	else if (props->TextureID=="player2"){
		m_Animation->SetProperties(m_TextureID, 4, 3, 3, 500, SDL_FLIP_NONE);
	}

}

// Draw player to screen
void Player::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	//TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
}

// Update player animation on the screen
void Player::Update(float dt) {
	m_Animation->Update();

    GetInput();
    Move();

}

// Clean screen
void Player::Clean() {
	TextureManager::GetInstance()->Clean();
}

// Other methods
void Player::GetInput() {
    // Everytime we call getInput method, we have to reset xMove and yMove
    xMove = 0;
    yMove = 0;

    newY = Y;
    newX = X;

    if (m_pid == 0) {
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_UP)) {
            SDL_Log("Key UP pushed.");
            newY = Y - speed;
            yMove = -speed;
        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_DOWN)) {
            SDL_Log("Key DOWN pushed.");
        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_LEFT)) {
            SDL_Log("Key LEFT pushed.");
        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_RIGHT)) {
            SDL_Log("Key RIGHT pushed.");
        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_COMMA)) {
            SDL_Log("Key COMMA pushed.");
        }
    }
    else if (m_pid == 1) {
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_W)) {
            SDL_Log("Key W pushed.");
        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_A)) {
            SDL_Log("Key A pushed.");
        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_S)) {
            SDL_Log("Key S pushed.");
        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_D)) {
            SDL_Log("Key D pushed.");
        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_G)) {
            SDL_Log("Key G pushed.");
        }
    }

}
