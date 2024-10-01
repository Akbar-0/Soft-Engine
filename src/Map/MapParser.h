#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include <iostream>
#include <memory>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"

class MapParser
{
    public:
        std::string removeNewlines(const std::string& str) {
            std::string result;
            std::remove_copy_if(str.begin(), str.end(), std::back_inserter(result), [](char c) {
                return c == '\n';
            });
            return result;
        }
        /*bool*/GameMap* Load(std::string source);
        void Clean();

        inline GameMap* GetMap(std::string id){return m_MapDict[id];}
        inline static MapParser* GetInstance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new MapParser();}

    private:
        bool Parse(std::string id, std::string source);
        Tileset ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);

    private:
        MapParser(){}
        static MapParser* s_Instance;
        std::map<std::string, GameMap*> m_MapDict;
};

#endif // MAPPARSER_H
