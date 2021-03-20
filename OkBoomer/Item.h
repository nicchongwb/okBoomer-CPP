#pragma once

#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include <string.h>

/* Item encompasses the item in the game.
*  The pure virtual functions are defined here.
*  Item has a class file - Item.cpp
*/

// Item extends Entity

class Item : public Entity {

public:
	// Initialise the information from Entity into Item
	Item(Properties* props) : Entity(props) {
	}

	virtual void Draw() = 0;
	virtual void Clean() = 0;
	virtual void Update(float dt) = 0;
	virtual int getItemX() { return m_Transform->X; }
	virtual int getItemY() { return m_Transform->Y; };
};
#endif // ITEM_H

