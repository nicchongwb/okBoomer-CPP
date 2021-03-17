#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

// Absolute file path for world.tmx
bool MapParser::Load() {
    // this function can load multiple maps
    // Parse(arbituary ID, filepath); 
    return Parse("MAP", "res/world/world.tmx");
}

bool MapParser::Parse(std::string id, std::string source) {

    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()) {
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();

    int colcount, rowcount, tilesize = 0;
    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    // Parse Tile sets
    TilesetsList tilesets;
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            tilesets.push_back(ParseTileset(e));
        }
    }

    // Parse Layers
    GameMap* gamemap = new GameMap();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    m_MapDict[id] = gamemap;
    return true;
}

// 
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

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset> tilesets, int tilesize, int rowcount, int colcount)
{
    TiXmlElement* data = nullptr;
    for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            data = e;
            break;
        }
    }

    // Parse Layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
    for (int row = 0; row < rowcount; row++) {
        for (int col = 0; col < colcount; col++) {
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if (!iss.good())
                break;
        }
    }

    return (new TileLayer(tilesize, colcount, rowcount, tilemap, tilesets));
}

void MapParser::Clean() {
    std::map<std::string, GameMap*>::iterator it;
    for (it = m_MapDict.begin(); it != m_MapDict.end(); it++)
        it->second = nullptr;

    m_MapDict.clear();
}

