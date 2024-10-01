#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>

struct Tileset{
    int FirstID = 0, LastID = 0;
    int RowCount = 0, ColCount = 0;
    int TileCount = 0, TileSize = 0;
    std::string Name = "", Source = "";
};

using TilesetList = std::vector<Tileset> ;
using TileMap = std::vector<std::vector<int> > ;

class TileLayer : public Layer
{
    public:
        TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets);
        virtual void Render();
        virtual void Update();
        inline TileMap GetTilemap(){return m_Tilemap;}

    private:
        int m_TileSize = 0, m_RowCount = 0, m_ColCount = 0;

        TileMap m_Tilemap = TileMap(0, std::vector<int>(0, 0));
        TilesetList m_Tilesets;
};

#endif // TILELAYER_H
