#pragma once
#ifndef TILELAYER_H
#define TILELAYER_H

#include <string>
#include <vector>
#include "Layer.h"
#include "Vector2D.h"

/* Tileset help us to manage our tiles in mulitple set(s)
*  It will utitlise textureManager to help us render via DrawTile();
*/

// Properties of Tileset
struct Tileset {
    int FirstID, LastID; // see .tmx file, FirstID starts with 1
    int RowCount, ColCount; // Row and Col for our Tileset, see .tmx file
    int TileCount, TileSize;
    std::string Name, Source; // Name and Source to correspond with .tmx file
};

using TilesetsList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int> >; // space between > > is important

/* TileLayer handles the background layer(s) of our game
*  Help us overlap layers of background if needed
*  Class file is TileLayer.cpp
* 
*  TileLayer inherits from Layer 
*  TileLayer uses Tileset to help us draw tiles
*/

class TileLayer : public Layer {

public:
    TileLayer(int tilesize, int width, int height, TileMap tilemap, TilesetsList tilesets);

    virtual void Render(); // implement Layer virtual Render
    virtual void Update(); // implement Layer virtual Update

    // Get TileMap matrix/array seq
    inline TileMap GetTileMap() { return m_Tilemap; }

private:
    int m_TileSize;
    int m_ColCount, m_RowCount;

    TileMap m_Tilemap; // to store array seq from tmx file
    TilesetsList m_Tilesets; // list of tilesets, depends on tmx file
};

#endif // TILELAYER_H

