#include "TileLayer.h"
#include "TextureManager.h"

/* TileLayer handles the background layer(s) of our game
*  Help us overlap layers of background if needed
*  Header file is TileLayer.h
*/

#define YOFFSET 60

// Constructor
TileLayer::TileLayer(int tilesize, int colcount, int rowcount, TileMap tilemap, TilesetsList tilesets) :
    m_TileSize(tilesize), m_ColCount(colcount), m_RowCount(rowcount), m_Tilemap(tilemap), m_Tilesets(tilesets) {

    // Run throught tile set list | for each component we Load() the tileset ID, where is the texture + filename
    for (unsigned int i = 0; i < m_Tilesets.size(); i++)
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "res/world/" + m_Tilesets[i].Source);
}

// Render function for TileLayer
void TileLayer::Render() {
    // Loop through row and col
    for (unsigned int i = 0; i < m_RowCount; i++) {
        for (unsigned int j = 0; j < m_ColCount; j++) {
            
            int tileID = m_Tilemap[i][j]; // Get tileID from tileset in .tmx file
            int temp = tileID;

            if (tileID == 0) // if 0 is in tmx file means tile is empty
                continue;

            else {
                int index = 0;
                // Check if we only have 1 tileset if yes then don't need to transform the IDs
                if (m_Tilesets.size() > 1) {
                    // if we have more than 1 tileset, then on the respective tileset in .tmx file, we have to see the firstgid
                    for (unsigned int k = 1; k < m_Tilesets.size(); k++) {

                        // Check if tileID in .tmx file is between <firstgid> and <lastID>
                        if (tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID) {
                            // if between then we recalculate the actual local tileID based on the offset
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            index = k; // set index of our tile
                            break;
                        }
                    }
                }

                // Drawing on screen
                Tileset ts = m_Tilesets[index]; // put respective tile into Tileset list
                int tileRow = tileID / ts.ColCount; // calculate the row of our tile
                int tileCol = tileID - tileRow * ts.ColCount - 1; // calculate col of our tile

                // if this tile is on the last column
                if (tileID % ts.ColCount == 0) {
                    tileRow--; 
                    tileCol = ts.ColCount - 1;
                }

                // Use TextureManager to draw
                TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, j * ts.TileSize, i * ts.TileSize + YOFFSET, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::Update() {

}
