#include "MapParser.h"

/* MapParser handles the parsing of tmx data into a gameMap
*  to be used to render maps based on the tiles
*  Header file is MapParser.h
* 
*  This class relies on 3rd party lib: tinystr.cpp, tinystr.h, 
*  tinyxml.cpp, tinyxml.h, tinyxmlerror.cpp, tinyxmlparser.cpp
*/

MapParser* MapParser::s_Instance = nullptr;

// Absolute file path for world.tmx
bool MapParser::Load() {
    // this function can load multiple maps
    // Parse(arbituary ID, filepath); 
    return Parse("MAP", "res/world/world.tmx");
}

// Method to parse tmx file and add to m_mapDict 
bool MapParser::Parse(std::string id, std::string source) {
    // check if source is valid
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()) {
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    // get root element of .tmx file, in this case it will be <map>
    TiXmlElement* root = xml.RootElement();

    int colcount, rowcount, tilesize = 0;
    root->Attribute("width", &colcount); // get <width> value and set to colcount
    root->Attribute("height", &rowcount); // get <height> value and set to rowcount
    root->Attribute("tilewidth", &tilesize); // get <tilewidth> value and set to tilesize

    // Parse Tile sets <tilesets> as we may have more than 1 tile set used in the .tmx file
    TilesetsList tilesets;
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            tilesets.push_back(ParseTileset(e)); // push to tilesets vector
        }
    }

    // Parse Layers into GameMap obj
    GameMap* gamemap = new GameMap();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            // parse <layer> information into tileLayer obj
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            
            // add scope tileLayer obj into m_MapLayers vector
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    // add the gamemap obj into our dicitionary of maps in m_MapDict
    m_MapDict[id] = gamemap;
    return true;
}

// Method to parse Tileset from tmx file
Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset) {
    Tileset tileset;

    // get attribute values from tmx file and set tileset obj attributes accordingly
    tileset.Name = xmlTileset->Attribute("name"); // set tileset name attribute based on "name" attribute of tmx file
    
    xmlTileset->Attribute("firstgid", &tileset.FirstID); // "firstgid" is from tmx file, we get firstgid's value (int) and parse into tileset.FirstID by reference
    
    xmlTileset->Attribute("tilecount", &tileset.TileCount); // "tilecount" is from tmx file, we get tilecount's value (int) and parse into tileset.TileCount by reference
    
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1; // FirstID is 1 so we subtract 1 to balance out offset

    
    xmlTileset->Attribute("columns", &tileset.ColCount); // "columns" is from tmx file, we get columns's value (int) and parse into tileset.ColCount by reference
    
    tileset.RowCount = tileset.TileCount / tileset.ColCount; // Row = TileCount / ColCount
    
    xmlTileset->Attribute("tilewidth", &tileset.TileSize); // "tilewidth" is from tmx file, we get tilewidth's value (int) and parse into tileset.TileSize by reference

    // Get the image linked to the tmx, in this case it is the "bombermantilesnew_scaled_64x64.png"
    TiXmlElement* image = xmlTileset->FirstChildElement(); // Create tinyXML image object
    
    tileset.Source = image->Attribute("source"); // set tileset.Source attribute to tinyXML image attribute based on "source" attribute in tmx file
    
    return tileset;
}

// Gets the <layer> <data> of .tmx file to be parsed in to generate layer of tiles
TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset> tilesets, int tilesize, int rowcount, int colcount)
{
    TiXmlElement* data = nullptr; // create data object to store <data> of .tmx file

    // xmlLayer is the respective <layer> in .tmx -> FirstChildElement() will target first <> of <layer> in this case it is <data>
    for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        // if name of componenet of .tmx file is == "data" then we write the data in
        if (e->Value() == std::string("data")) { 
            data = e;
            break;
        }
    }

    // Parse Layer tile map
    std::string matrix(data->GetText()); // put <data> value into matrix via GetText()
    std::istringstream iss(matrix); // input stream
    std::string id; // unique ID/KEY for respective Layer

    // Create a tilemap with rowcount and col count and initialise all position of 2D array with 0
    TileMap tilemap(rowcount, std::vector<int>(colcount, 0)); // this object will be added into tileLayer and return out of function later

    // Iterate throught 2D array
    for (int row = 0; row < rowcount; row++) {
        for (int col = 0; col < colcount; col++) {
            // Stream iss matrix object, parsed in each element seperated by ',' as seen in the .tmx <data> section
            getline(iss, id, ','); 
            
            // convert id to stringstream object to be assigned to tilemap[row][col]
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            // Check if we reach the end, if yes then break
            if (!iss.good())
                break;
        }
    }

    // Return created TileLayer obj from function
    return (new TileLayer(tilesize, colcount, rowcount, tilemap, tilesets));
}

// Method to free memory
void MapParser::Clean() {
    std::map<std::string, GameMap*>::iterator it;
    for (it = m_MapDict.begin(); it != m_MapDict.end(); it++)
        it->second = nullptr;

    m_MapDict.clear();
}

