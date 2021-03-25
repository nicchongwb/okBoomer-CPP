#pragma once

#ifndef BOMBPLANTED_H
#define BOMBPLANTED_H

#define FADE_SPEED 0.07f;

#include "Item.h"
#include "TextureManager.h"
#include "Animation.h"
#include "DrawManager.h"
#include <vector>

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

	Uint8 alpha = 255;
	float alphaCalc = 0;

	std::string GetBombPlantedTextureName() { return this->textureName; }
	std::vector <BombPlanted>* getListOfPlantedBombs() { return &s_PlantedBombList; };
	

private:
	SDL_Texture * m_PlantedBombTexture = TextureManager::GetInstance()->GetTexture("bomb");
	std::vector <BombPlanted> s_PlantedBombList;
	int bombID = 0;
	std::string textureName = "bomb";
};

#endif // BOMBPLANTED_H
