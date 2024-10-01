#include "MapParser.h"

#include "Engine.h"

MapParser* MapParser::s_Instance = nullptr;

/*bool*/GameMap* MapParser::Load(std::string source)
{
    if(!Parse("level1", source)){
        /*return false;*/
        std::cerr << "\n|=|=|=|=|=|--Failed to Load Map--|=|=|=|=|=|\n" << std::endl;
    }

    /*return true;*/
    return m_MapDict["level1"];
}

bool MapParser::Parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    int rowcount = 0, colcount = 0, tilesize = 0;

    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    // Parse Tilesets
    TilesetList tilesets;
    for(TiXmlElement* e= root->FirstChildElement(); e != nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("tileset")){
            //std::cerr << "\nProcessing element: " << e->Value() << std::endl;///////////////
            tilesets.push_back(ParseTileset(e));
        }
    }

    // Parse Layers
    GameMap* gamemap = new GameMap();
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
        if(e->Value() == std::string("layer")){
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    m_MapDict[id] = gamemap;
    return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    //std::cerr << "Parsing tileset name: " << tileset.Name << std::endl;//////////////////////////////
    xmlTileset->Attribute("firstgid", &tileset.FirstID);

    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount/tileset.ColCount;

    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    if ( xmlTileset -> FirstChildElement() -> Value() == std::string("image") )
		tileset.Source = xmlTileset -> FirstChildElement("image") -> Attribute("source");
	else
		tileset.Source = xmlTileset -> Attribute("source") ;

    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
    TiXmlElement* data = nullptr;
    for(TiXmlElement* p = xmlLayer->FirstChildElement(); p!= nullptr; p=p->NextSiblingElement()){
        if(p->Value() == std::string("data")){
            data = p;
            break;
        }
    }

    //Parse layer Tilemap
    if (data != nullptr) {
        //std::cerr << "\n -------------Layer Data loaded--------------- \n" << std::endl;///////////////////////
        std::string matrix(data->GetText());
        // Removing Whitespace and Newline characters
        std::string result = "";
        std::remove_copy_if(matrix.begin(), matrix.end(), std::back_inserter(result), ::isspace);
        std::istringstream iss(result);
        std::string id;

    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));

    for(int row = 0; row < ROW_COUNT; row++){
        for(int col = 0; col < COL_COUNT; col++){
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if(!iss.good())
                break;
        }
    }

    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
        // ...
    } else {
        std::cerr << "\n -------------Layer Data not loaded--------------- \n" << std::endl;
    }
}

void MapParser::Clean()
{
    std::map<std::string, GameMap*>::iterator it;
    for(it = m_MapDict.begin(); it != m_MapDict.end(); it++)
        it->second = nullptr;

    m_MapDict.clear();

    std::cerr << "|=|=|=|=|=|--Map Data Cleaned!--|=|=|=|=|=|" << std::endl;
}

