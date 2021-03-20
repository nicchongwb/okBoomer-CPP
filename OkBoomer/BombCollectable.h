#pragma once

#ifndef BOMBCOLLECTABLE_H
#define BOMBCOLLECTABLE_H

#define MAX_BOMBITEM_SPAWNED 3 // max number of collectable bomb item on the map at one go is 3

#include "Item.h"
#include "TextureManager.h"
#include <vector>

class BombCollectable : public Item{

public:
	BombCollectable(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);
	inline std::vector <BombCollectable> * getListOfSpawnedBombs() { return &m_BombsSpawnedList; };

private:

	TextureManager* m_BombItemTextureM;
	std::vector <BombCollectable> m_BombsSpawnedList;
	int m_NumBombsSpawned = 0; // count current number of collectable bomb items on the map.
	int m_ItemBombID = 0; 
};

#endif // BOMBCOLLECTABLE_H


