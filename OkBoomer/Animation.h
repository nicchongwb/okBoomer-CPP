#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <string>

/* Animation uses TextureManager to
*  handle the drawing of animations to the screen.
*  Class file is Annimation.cpp
*/

class Animation
{
	// Constructor
public:

	Animation() {

	}

	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight);
	void SetProperties(std::string textureID, int spriteRow, int spriteCol, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	int m_SpriteRow, m_SpriteCol, m_SpriteFrame;
	int m_AnimSpeed, m_FrameCount;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;

};

#endif // !ANIMATION_H
