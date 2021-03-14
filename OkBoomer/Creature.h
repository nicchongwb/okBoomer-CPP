#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include <string.h>

/* Creature encompasses the characters in the game. 
*  The pure virtual functions are defined here.
*  There is no class file for Creature.
*/

// Creature extends Entity
class Creature : public Entity {

public:
	Creature(Properties * props): Entity(props){}

	virtual void Draw() = 0;
	virtual void Clean() = 0;
	virtual void Update(float dt) = 0;

protected:
	std::string m_Name;
};
#endif // CHARACTER_H