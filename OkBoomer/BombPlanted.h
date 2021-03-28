#pragma once

#ifndef BOMBPLANTED_H
#define BOMBPLANTED_H

#define FADE_SPEED 0.07f;

#include "Item.h"
#include "TextureManager.h"
#include "Animation.h"
#include "DrawManager.h"
#include <vector>
#include <thread>

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

	std::string GetBombPlantedTextureName() { return this->textureName; }
	std::vector <BombPlanted>* getListOfPlantedBombs() { return &s_PlantedBombList; };

	static int s_bombID;
	bool m_isBombPlanted; // boolean var for animating bomb if it is freshly planted. (bomb anim will run for 1 second)
	bool m_countDown; // boolean var for animating bomb (checks if 1 second countdown timer has started)
	long m_start; // used to check if the 1 second is up

private:
	SDL_Texture * m_PlantedBombTexture;
	std::vector <BombPlanted> s_PlantedBombList;
	std::string textureName;
	Animation* m_BombAnimation;
	
};

#endif // BOMBPLANTED_H
