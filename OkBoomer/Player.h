#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Animation.h"
#include "DrawManager.h"

#define DEFAULT_BOMBHELD 1
#define DEFAULT_BOMBCOLLECTABLE 0
#define MAX_BOMBCOLLECTABLE 3 // 3 bomb collectable parts = 1 bomb held

/* Player header file. Each Player object represents
*  a distinct player in the game.
*  Class file is Player.cpp
*/

// Player extends Creature
class Player : public Creature {

public:
	Player(Properties * props);
	
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);
	void GetInput();

	static int s_PlayerCount; // playerCount initialised to 0 inside class file
	static bool s_AlrPressedP1; // static variables for checking if key is already held down
	static bool s_AlrPressedP2;

	// Player bomb interaction
	void collectBomb();
	
	void plantBomb();

	void takeDamage();

private:
	// Initialise variables for animation purposes
	//int m_Row, m_Frame, m_FrameCount, m_AnimSpeed;
	Animation* m_Animation;
	DrawManager* m_DrawManager;
	int m_pid; // player id

	int newX, newY; // Temporary variables to hold next player coordinates

	int m_bombHeld; // Amount of bombs held
	int m_bombCollectable; // Amount of bomb collectables; Note: 2 bombCollectables = 1 bomb part
	int m_Health, m_Speed;

};
#endif // PLAYER_H
