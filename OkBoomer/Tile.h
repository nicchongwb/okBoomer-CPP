#pragma once

#ifndef TILE_H
#define TILE_H

#include <string>
#include "SDL.h"
#include <map>

/* Tile class to store information of our tile */
class Tile
{
public:

private:
	Tile(){}
	std::map<std::string, SDL_Texture*> m_Tile; //our tile array
	static Tile* s_Instance;
};
#endif // TILE_H
