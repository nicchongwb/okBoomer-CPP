#include "Player.h"
#include "TextureManager.h"
#include "Animation.h"
#include "IOHandler.h"
#include "Board.h"
#include <SDL.h>
#include <iostream>

#define YOFFSET 60

/* Player class. Each Player object represents
*  a distinct player in the game.
*  Header file is Player.h
*/

// initialise static playerCount to 0
int Player::s_PlayerCount = 0;
// initialise static alrPressed variables to false;
bool Player::s_AlrPressedP1 = false;
bool Player::s_AlrPressedP2 = false;

int X, Y;
// Constructor for Player
Player::Player(Properties * props): Creature(props) {

	m_Animation = new Animation();
    m_DrawManager = new DrawManager();

    m_pid = s_PlayerCount;
    s_PlayerCount++;

    // Set player m_Health to 10
    m_Health = DEFAULT_HEALTH;
    m_Speed = DEFAULT_SPEED;
    m_bombHeld = DEFAULT_BOMBHELD;
    m_bombCollectable = DEFAULT_BOMBCOLLECTABLE;


	// Set Player 1 animation
	if (props->TextureID == "player1") {
		// Set Properties -> Row, Col, Frame_Count, Animation_Speed, SDL_Flip
		// Row and Col specifies where to chop on the spritesheet
        m_Animation->SetProperties(m_TextureID, 4, 3, 3, 500, SDL_FLIP_NONE);       
	}
	// Set Player 2 animation
	else if (props->TextureID=="player2"){
        m_Animation->SetProperties(m_TextureID, 0, 0, 3, 500, SDL_FLIP_NONE);
	}

}

// Draw player to screen
void Player::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y + YOFFSET, m_Width, m_Height);
}

// Update player animation & position on the screen
void Player::Update(float dt) {

    // Update positions on the screen
    m_DrawManager->Update();
    m_Transform->TranslateX(m_DrawManager->GetPosition().X);
    m_Transform->TranslateY(m_DrawManager->GetPosition().Y);

    m_Animation->Update();

    // Unset force before getting input
    m_DrawManager->UnsetForce();


    GetInput();

}

// Clean screen
void Player::Clean() {
	TextureManager::GetInstance()->Clean();
}

// Get input for player movement
void Player::GetInput() {
    
    X = m_Transform->X;
    Y = m_Transform->Y;

    // temp variables for Board newX and newY
    int nextX = X;
    int nextY = Y;

    if (m_pid == 0) {
        
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_W)) {
            
            if (!s_AlrPressedP1) {
                
                //SDL_Log("Key W pushed.");
                
                nextY -= m_Speed; // set temp value

                if (Board::GetInstance()->canPlayerMove(m_pid, X, Y, nextX, nextY)) 
                {
                    std::cout << "Player 1: "; m_Transform->Log();
                    m_DrawManager->ApplyForceY(-m_Speed);

                    Board::GetInstance()->updateBoardMove(m_pid, X, Y, nextX, nextY);
                    Board::GetInstance()->consoleBoard();
                }
                else {
                    std::cout << "Invalid move." << std::endl;
                }

                s_AlrPressedP1 = true;
            }
        }

        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_S)) {

            if (!s_AlrPressedP1) {
                //SDL_Log("Key S pushed.");

                nextY += m_Speed; // set temp value

                if (Board::GetInstance()->canPlayerMove(m_pid, X, Y, nextX, nextY))
                {
                    std::cout << "Player 1: "; m_Transform->Log();
                    m_DrawManager->ApplyForceY(m_Speed);

                    Board::GetInstance()->updateBoardMove(m_pid, X, Y, nextX, nextY);
                    Board::GetInstance()->consoleBoard();
                }
                else {
                    std::cout << "Invalid move." << std::endl;
                }

                s_AlrPressedP1 = true;
            }

        }

        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_A)) {

            if (!s_AlrPressedP1) {
                //SDL_Log("Key A pushed.");

                nextX -= m_Speed; // set temp value

                if (Board::GetInstance()->canPlayerMove(m_pid, X, Y, nextX, nextY)) 
                {
                    std::cout << "Player 1: "; m_Transform->Log();
                    m_DrawManager->ApplyForceX(-m_Speed);

                    Board::GetInstance()->updateBoardMove(m_pid, X, Y, nextX, nextY);
                    Board::GetInstance()->consoleBoard();
                }
                else {
                    std::cout << "Invalid move." << std::endl;
                }

                s_AlrPressedP1 = true;
            }
            
        }
        
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_D)) {

            if (!s_AlrPressedP1) {
                //SDL_Log("Key D pushed.");

                nextX += m_Speed; // set temp value

                if (Board::GetInstance()->canPlayerMove(m_pid, X, Y, nextX, nextY))
                {
                    std::cout << "Player 1: "; m_Transform->Log();
                    m_DrawManager->ApplyForceX(m_Speed);

                    Board::GetInstance()->updateBoardMove(m_pid, X, Y, nextX, nextY);
                    Board::GetInstance()->consoleBoard();
                }
                else {
                    std::cout << "Invalid move." << std::endl;
                }

                s_AlrPressedP1 = true;
            }

        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_G)) {

            if (!s_AlrPressedP1) 
            {
                //SDL_Log("Key G pushed.");

                if (Board::GetInstance()->canPlayerPlant(m_pid, X, Y))
                {
                    if (this->m_bombHeld > 0) 
                    {
                        // X == nextX, Y == nextY | this tells board that a bomb has been placed
                        Board::GetInstance()->updateBoardPlant(m_pid, X, Y);
                        Board::GetInstance()->consoleBoard();
                    }
                    //else 
                    //{
                    //    std::cout << "Bomb already planted." << std::endl;
                    //}
                }
            }
            s_AlrPressedP1 = true;
        }
        
    }
    else if (m_pid == 1) {

        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_UP)) {
        
            if (!s_AlrPressedP2) {
                //SDL_Log("Key UP pushed.");

                nextY -= m_Speed; // set temp value

                if (Board::GetInstance()->canPlayerMove(m_pid, X, Y, nextX, nextY))
                {
                    std::cout << "Player 2: "; m_Transform->Log();
                    m_DrawManager->ApplyForceY(-m_Speed);

                    Board::GetInstance()->updateBoardMove(m_pid, X, Y, nextX, nextY);
                    Board::GetInstance()->consoleBoard();
                }
                else {
                    std::cout << "Invalid move." << std::endl;
                }

                s_AlrPressedP2 = true;
            }

        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_DOWN)) {
            
            if (!s_AlrPressedP2) {
                //SDL_Log("Key DOWN pushed.");

                nextY += m_Speed; // set temp value

                if (Board::GetInstance()->canPlayerMove(m_pid, X, Y, nextX, nextY))
                {
                    std::cout << "Player 2: "; m_Transform->Log();
                    m_DrawManager->ApplyForceY(m_Speed);

                    Board::GetInstance()->updateBoardMove(m_pid, X, Y, nextX, nextY);
                    Board::GetInstance()->consoleBoard();
                }
                else {
                    std::cout << "Invalid move." << std::endl;
                }

                s_AlrPressedP2 = true;
            }

        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_LEFT)) {

            if (!s_AlrPressedP2) {
                //SDL_Log("Key LEFT pushed.");

                nextX -= m_Speed; // set temp value

                if (Board::GetInstance()->canPlayerMove(m_pid, X, Y, nextX, nextY))
                {
                    std::cout << "Player 2: "; m_Transform->Log();
                    m_DrawManager->ApplyForceX(-m_Speed);

                    Board::GetInstance()->updateBoardMove(m_pid, X, Y, nextX, nextY);
                    Board::GetInstance()->consoleBoard();
                }
                else {
                    std::cout << "Invalid move." << std::endl;
                }
                s_AlrPressedP2 = true;
                
            }
        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_RIGHT)) {

            if (!s_AlrPressedP2) {
                //SDL_Log("Key RIGHT pushed.");

                nextX += m_Speed; // set temp value
                if (Board::GetInstance()->canPlayerMove(m_pid, X, Y, nextX, nextY))
                {
                    std::cout << "Player 2: "; m_Transform->Log();
                    m_DrawManager->ApplyForceX(m_Speed);

                    Board::GetInstance()->updateBoardMove(m_pid, X, Y, nextX, nextY);
                    Board::GetInstance()->consoleBoard();
                }
                else {
                    std::cout << "Invalid move." << std::endl;
                }

                s_AlrPressedP2 = true;
            }

        }
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_COMMA)) {
            if (!s_AlrPressedP2)
            {
                //SDL_Log("Key COMMA pushed.");

                if (Board::GetInstance()->canPlayerPlant(m_pid, X, Y))
                {
                    if (this->m_bombHeld > 0)
                    {
                        // X == nextX, Y == nextY | this tells board that a bomb has been placed
                        Board::GetInstance()->updateBoardPlant(m_pid, X, Y);
                        Board::GetInstance()->consoleBoard();
                    }
                    //else
                    //{
                    //    std::cout << "Bomb already planted." << std::endl;
                    //}
                }
            }
            s_AlrPressedP2 = true;

        }

    }

}

int Player::GetHealth()
{
    return m_Health;
}

int Player::GetBomb()
{
    return m_bombHeld;
}

int Player::GetBombCol()
{
    return m_bombCollectable;
}

void Player::collectBomb()
{
    // +1 to m_bombCollectable when player picks an collectable bomb item
    if (m_bombCollectable < MAX_BOMBCOLLECTABLE) {
        m_bombCollectable += 1;
    }
    // players can only hold a maximum of MAX_BOMBHELD number of bombs in their inventory
    if (m_bombHeld < MAX_BOMBHELD) {
        // for every MAX_BOMBCOLLECTABLE number of collectable bomb items, convert it to 1 bomb inside the player's inventory.
        if (m_bombCollectable >= MAX_BOMBCOLLECTABLE) {
            m_bombCollectable -= MAX_BOMBCOLLECTABLE;
            m_bombHeld += 1;
        }
    }
    std::cout << m_pid+1 << ": BOMB HELD, BOMB PART: " << m_bombHeld << " , " << m_bombCollectable << std::endl;
}

void Player::plantBomb()
{
    if (this->m_bombHeld > 0) {
        this->m_bombHeld -= 1;
        printf("Player %d's bomb left: %d\n", m_pid + 1, this->m_bombHeld);
    }
    else {
        printf("Player %d's bomb left: %d\n", m_pid + 1, this->m_bombHeld);
        printf("No more bombs left!\n");
    }
   
}

void Player::takeDamage()
{
    m_Health -= 1;
    printf("Player %d's m_Health left: %d\n", m_pid + 1, m_Health);
}


