#pragma once

#ifndef BOMBPLANTED_H
#define BOMBPLANTED_H


#include "Item.h"
#include "TextureManager.h"


class BombPlanted : public Item {

public:
	BombPlanted(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

private:

	//TextureManager* m_BombItemTextureM;
};

#endif // BOMBPLANTED_H


