#include "Player.h"
#include "TextureManager.h"
#include "Animation.h"
#include "IOHandler.h"
#include "Board.h"
#include "BombPlanted.h"
#include <SDL.h>
#include <iostream>
#include <time.h>

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

// initialise variables for rendering player-facing animations
int Player::s_p1facing = 1;
int Player::s_p2facing = 0;
bool Player::s_countdown = false;
long Player::s_start;
BombPlanted* bombplanted = nullptr;

int X, Y;
// Constructor for Player
Player::Player(Properties * props): Creature(props) {

	m_Animation = new Animation();
    m_DrawManager = new DrawManager();

    m_pid = s_PlayerCount;
    s_PlayerCount++;

    // Player properties variables
    m_Health = DEFAULT_HEALTH;
    m_Speed = DEFAULT_SPEED;
    m_bombHeld = DEFAULT_BOMBHELD;
    m_bombCollectable = DEFAULT_BOMBCOLLECTABLE;

    // Animation variables
    m_getBombed = false;
    m_putBomb = false;
    m_bombPlaced = false;
    m_bombx;
    m_bomby;

	// Set Player 1 animation
	if (props->TextureID == "player1") {
		// Set Properties -> Row, Col, Frame_Count, Animation_Speed, SDL_Flip
		// Row and Col specifies where to chop on the spritesheet
        m_Animation->SetProperties(m_TextureID, 4, 3, 3, 500, SDL_FLIP_NONE);       
	}
	// Set Player 2 animation
	else if (props->TextureID=="player2"){
        m_Animation->SetProperties(m_TextureID, 3, 0, 3, 500, SDL_FLIP_NONE);
	}

}

// Draw player to screen
void Player::Draw() {
    if (m_putBomb && !m_getBombed) {
        Player::placeBombCountdown();
        bombplanted = new BombPlanted(new Properties("bomb", m_bombx, m_bomby + YOFFSET, m_Width, m_Height));
        bombplanted->Draw();

    }
    m_Animation->Draw(m_Transform->X, m_Transform->Y + YOFFSET, m_Width, m_Height);
}

// Update player animation & position on the screen
void Player::Update(float dt) {

    // render animation for different player states
    if (m_getBombed) { // animation for when player is bombed
        Player::bombCountdown();
        Player::getBombedAnimation();
    }
    else { // animation for when player is normal (and the side they are facing)
        Player::getCurrentAnimation();
    }

    // Update positions on the screen
    m_DrawManager->Update();
    m_Transform->TranslateX(m_DrawManager->GetPosition().X);
    m_Transform->TranslateY(m_DrawManager->GetPosition().Y);

    m_Animation->Update();

    // Unset force before getting input
    m_DrawManager->UnsetForce();


    GetInput();

}

// setting player-bombed animations if player steps on planted bomb
void Player::getBombedAnimation() {
    if (m_pid == 0) {
        if (s_p1facing == 0) {
            m_Animation->SetProperties(m_TextureID, 7, 12, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p1facing == 1) {
            m_Animation->SetProperties(m_TextureID, 4, 12, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p1facing == 2) {
            m_Animation->SetProperties(m_TextureID, 5, 12, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p1facing == 3) {
            m_Animation->SetProperties(m_TextureID, 6, 12, 3, 500, SDL_FLIP_NONE);
        }
    }
    else if (m_pid == 1) {

        if (s_p2facing == 0) {
            m_Animation->SetProperties(m_TextureID, 3, 12, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p2facing == 1) {
            m_Animation->SetProperties(m_TextureID, 0, 12, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p2facing == 2) {
            m_Animation->SetProperties(m_TextureID, 1, 12, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p2facing == 3) {
            m_Animation->SetProperties(m_TextureID, 2, 12, 3, 500, SDL_FLIP_NONE);
        }
    }
}

// setting normal player animations
void Player::getCurrentAnimation() {
    if (m_pid == 0) {
        if (s_p1facing == 0) {
            m_Animation->SetProperties(m_TextureID, 7, 3, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p1facing == 1) {
            m_Animation->SetProperties(m_TextureID, 4, 3, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p1facing == 2) {
            m_Animation->SetProperties(m_TextureID, 5, 3, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p1facing == 3) {
            m_Animation->SetProperties(m_TextureID, 6, 3, 3, 500, SDL_FLIP_NONE);
        }
    }
    else if (m_pid == 1) {

        if (s_p2facing == 0) {
            m_Animation->SetProperties(m_TextureID, 3, 0, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p2facing == 1) {
            m_Animation->SetProperties(m_TextureID, 0, 0, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p2facing == 2) {
            m_Animation->SetProperties(m_TextureID, 1, 0, 3, 500, SDL_FLIP_NONE);
        }
        if (s_p2facing == 3) {
            m_Animation->SetProperties(m_TextureID, 2, 0, 3, 500, SDL_FLIP_NONE);
        }
    }
}

// animation for when bomb is planted
void Player::placeBombCountdown() {
    if (m_putBomb && !s_countdown) {
        s_countdown = true;
        clock_t now = clock();
        s_start = now;
    }
    if (s_start + 1000 < clock()) { //set animations for 1s
        m_putBomb = false;
        s_countdown = false;
    }
}

void Player::bombCountdown() {
    if (m_getBombed && !s_countdown) {
        s_countdown = true;
        clock_t now = clock();
        s_start = now;
    }
    if (s_start + 2500 < clock()) { //set animations for 2.5s
        m_getBombed = false;
        s_countdown = false;
    }
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
        
        // P1 - Key W Pushed
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_W)) {
            
            if (!s_AlrPressedP1) {
                
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
                s_p1facing = 0;
            }
        }

        // P1 - Key S Pushed
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_S)) {

            if (!s_AlrPressedP1) {

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
                s_p1facing = 1;
            }

        }

        // P1 - Key A Pushed
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
                s_p1facing = 2;
            }
            
        }
        
        // P1 - Key D Pushed
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
                s_p1facing = 3;
            }

        }

        // P1 - Key G Pushed
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
        
        // P2 - Key UP Pushed
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_UP)) {
        
            if (!s_AlrPressedP2) {

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
                s_p2facing = 0;
            }

        }
        // P2 - Key DOWN Pushed
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_DOWN)) {
            
            if (!s_AlrPressedP2) {

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
                s_p2facing = 1;
            }

        }
        // P2 - Key LEFT Pushed
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_LEFT)) {

            if (!s_AlrPressedP2) {

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
                s_p2facing = 2;
                
            }
        }
        // P2 - Key RIGHT Pushed
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_RIGHT)) {

            if (!s_AlrPressedP2) {

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
                s_p2facing = 3;
            }

        }
        // P2 - Key COMMA Pushed
        if (IOHandler::GetInstance()->KeyPressed(SDL_SCANCODE_COMMA)) {
            if (!s_AlrPressedP2)
            {

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

    m_putBomb = true;
    m_bombx = X;
    m_bomby = Y;
   
}

void Player::takeDamage()
{
    m_Health -= 1;
    m_getBombed = true;
    printf("Player %d's m_Health left: %d\n", m_pid + 1, m_Health);
}


