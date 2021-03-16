#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#define DEFAULT_SPEED 64

#include "Entity.h"
#include <string.h>

/* Creature encompasses the characters in the game. 
*  The pure virtual functions are defined here.
*  Creature has a class file - Creature.cpp
*/

// Creature extends Entity
class Creature : public Entity {

public:

	// initialise the information from Entity into Creature
	Creature(Properties * props): Entity(props){
		
		xMove = 0;
		yMove = 0;
	}

	virtual void Draw() = 0;
	virtual void Clean() = 0;
	virtual void Update(float dt) = 0;

	void Move();

protected:
	std::string m_Name;

	// Creature characteristics/attributes
	int xMove, yMove;
	int speed;
	int health;

};
#endif // CHARACTER_H