#pragma once

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "Layer.h"

/* GameMap class will hold information of
* graphics layer of the game background
* No CPP file
*/
class GameMap
{
public:

    GameMap() {}

    void Render() {
        // loop through vector of layers and render
        for (unsigned int i = 0; i < m_MapLayers.size(); i++)
            m_MapLayers[i]->Render();
    }

    void Update() {
        // loop through vector of layers and update
        for (unsigned int i = 0; i < m_MapLayers.size(); i++)
            m_MapLayers[i]->Update();
    }

    std::vector<Layer*> GetLayers() {
        return m_MapLayers;
    }

private:
    friend class MapParser; // GameMap will have private access to MapParser
    std::vector<Layer*> m_MapLayers; // vector of layers of our map
};

#endif // GAMEMAP_H