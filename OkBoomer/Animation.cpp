#include "Animation.h"
#include "TextureManager.h"
#include <SDL.h>

/* Animation uses TextureManager to 
*  handle the drawing of animations to the screen.
*  Header file is Animation.h
*/
void Animation::Update() {
	m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;

}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight) {
	TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteCol, m_SpriteFrame, m_Flip);
}

// Called by other classes to set the variables for animation. (e.g. called in Player.cpp)
void Animation::SetProperties(std::string textureID, int spriteRow, int spriteCol, int frameCount, int animSpeed, SDL_RendererFlip flip) {
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_SpriteCol = spriteCol;
	m_FrameCount = frameCount;
	m_AnimSpeed = animSpeed;
	m_Flip = flip;
}


