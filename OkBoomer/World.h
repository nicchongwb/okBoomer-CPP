#pragma once

#ifndef WORLD_H
#define WORLD_H

#include "TextureManager.h"
#include <SDL.h>
#include <iostream>
#include <map>

/* World handles the loading and drawing of tiles to the screen.
*  Similar to TextureManager class.
*  Class file is World.cpp
*/

// World extends Texture Manager
class World {
public:
	static World* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new World(); }

	bool Load(std::string id, std::string filename);
	void Drop(std::string id);
	void Clean();

	// Draw from image to x to y.
	void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	/* Draw frame (animation) to x and y, from width to height.
	*  Row and Col is coordinates on the sprite sheet.
	*  Frame is frame count.
	*/
	void DrawFrame(std::string id, int x, int y, int width, int height, int row, int col, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

	bool LoadWorld(std::string filename);

private:
	World(){}
	std::map<std::string, SDL_Texture*> m_WorldMap;
	static World* s_Instance;



};
#endif
