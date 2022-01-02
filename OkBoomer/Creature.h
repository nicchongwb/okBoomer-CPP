#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#define DEFAULT_SPEED 64
#define DEFAULT_HEALTH 10

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
	}

	virtual void Draw() = 0;
	virtual void Clean() = 0;
	virtual void Update(float dt) = 0;

protected:
	std::string m_Name;

	// Creature characteristics/attributes
	int m_Speed = DEFAULT_SPEED;
	int m_Health = DEFAULT_HEALTH;

};
#endif // CHARACTER_H