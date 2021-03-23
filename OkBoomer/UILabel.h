#pragma once

#ifndef UILABEL_H
#define UILABEL_H

#include "TextureManager.h"
#include "Game.h"
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

/* UILabe; stores information of labels to be rendered
   this uses SDL_ttf libary */

class UILabel
{
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour);

	void SetLabelText(std::string text, std::string font);

	void draw(){ SDL_RenderCopy(Game::GetInstance()->GetRenderer(), labelTexture, nullptr, &position); }

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};

#endif // UILABEL_H