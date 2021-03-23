#pragma once

#ifndef BOMBPLANTED_H
#define BOMBPLANTED_H


#include "Item.h"
#include "TextureManager.h"
#include "Animation.h"
#include "DrawManager.h"

/* The BombPlanted class represents the planted bomb object
*  placed down by a player. BombPlanted inherits Item.
*  The class file is BombPlanted.cpp.
*/
class BombPlanted : public Item {

public:
	BombPlanted(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

private:
	TextureManager* m_BombItemTextureM;
};

#endif // BOMBPLANTED_H
