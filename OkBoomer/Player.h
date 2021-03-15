#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Animation.h"


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

private:
	// Initialise variables for animation purposes
	//int m_Row, m_Frame, m_FrameCount, m_AnimSpeed;
	Animation * m_Animation;

};
#endif // PLAYER_H
