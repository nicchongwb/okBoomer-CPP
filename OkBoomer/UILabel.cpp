#include "UILabel.h"


UILabel::UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) :
	labelText(text), labelFont(font), textColour(colour)
{
	position.x = xpos;
	position.y = ypos;
	SetLabelText(labelText, labelFont);
}

void UILabel::SetLabelText(std::string text, std::string font)
{
	SDL_Surface* surf = TTF_RenderText_Blended(TextureManager::GetInstance()->GetFont(font), text.c_str(), textColour);
	labelTexture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surf);
	SDL_FreeSurface(surf);

	SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);

}