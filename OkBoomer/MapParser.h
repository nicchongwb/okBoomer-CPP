#pragma once
#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include "GameMap.h"
#include "tinyxml.h"
#include "TileLayer.h"

/* MapParser handles the parsing of tmx data into a gameMap
*  to be used to render maps based on the tiles
*  Class file is MapParser.cpp
*
*  This class relies on 3rd party lib: tinystr.cpp, tinystr.h,
*  tinyxml.cpp, tinyxml.h, tinyxmlerror.cpp, tinyxmlparser.cpp
*/

class MapParser {

public:
    bool Load(); // load map -> if success, return true else return false
    void Clean(); // clean up for memory

    inline GameMap* GetMap(std::string id) { return m_MapDict[id]; } // get GameMap
    inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

private:
    MapParser() {}

    bool Parse(std::string id, std::string source); // parse .tmx file
    Tileset ParseTileset(TiXmlElement* xmlTileset); // parse tileset component from .tmx file

    // parse tileLayer, takes in respective tileset components
    TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset> tilesets, int tilesize, int rowcount, int colcount);

    static MapParser* s_Instance; // singleton class
    std::map<std::string, GameMap*> m_MapDict; // dictionary of Maps (param -> string = id of map, GameMap array)
};

#endif // MAPPARSER_H

