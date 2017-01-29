#include "MapCore.h"

void MapCore::init()
{
    this->background = 0;
}

void MapCore::quit()
{

}

void MapCore::loadMap(std::string basename)
{
    std::string filename = "Resources/";
    filename.append(basename);
    filename.append(".map");

    std::ifstream mapFile (filename.c_str());
    std::string mapHeader, tileData, heightData;

    if (mapFile.is_open())
    {
        getline(mapFile, mapHeader);
        getline(mapFile, tileData);
        getline(mapFile, heightData);
        mapFile.close();
    }
    else
    {
        std::cout << "File open failure\n";
        mapFile.close();
    }


    //std::cout << mapHeader << "\n" << tileData << "\n";
    //Load Data into Memory
    this->parseMapHeader(mapHeader);
    this->parseTileData(tileData);
    this->parseHeightData(heightData);
}

void MapCore::parseMapHeader(std::string mapHeader)
{
    std::string field;
    std::string letter;
    int delimiterCount = 0;

    //Store map header fields into memory
    for(unsigned int i = 0; i < mapHeader.size(); i++)
    {
        letter = mapHeader[i];
        if (letter.compare(";") == 0)
        {
            switch (delimiterCount)
            {
                case 0: //Map name
                    this->mapName = field;
                    break;
                case 1: //TileCount
                    this->mapSize = atoi(field.c_str());
                    break;
                case 2: //Width
                    this->mapWidth = atoi(field.c_str());
                    break;
                case 3: //Height
                    this->mapHeight = atoi(field.c_str());
                    break;
                case 4: //TileSet
                    this->mapTileSet = atoi(field.c_str());
                    break;
            }
            //std::cout << field << "\n";
            field.clear();
            delimiterCount += 1;
        }
        else
            field.append(letter);
    }
}

//Store map tile data into memory
void MapCore::parseTileData(std::string tileData)
{
    this->mapTileData.clear();
    std::string field;
    std::string letter;
    int delimiterCount = 0;

    //Store map header fields into memory
    for(unsigned int i = 0; i < tileData.size(); i++)
    {
        letter = tileData[i];
        if (letter.compare(",") == 0)
        {
            this->mapTileData.push_back(atoi(field.c_str()));
            field.clear();
            delimiterCount += 1;
        }
        else
            field.append(letter);
    }
}

//Store map tile data into memory
void MapCore::parseHeightData(std::string tileData)
{
    this->mapHeightData.clear();
    std::string field;
    std::string letter;
    int delimiterCount = 0;

    //Store map header fields into memory
    for(unsigned int i = 0; i < tileData.size(); i++)
    {
        letter = tileData[i];
        if (letter.compare(",") == 0)
        {
            this->mapHeightData.push_back(atoi(field.c_str()));
            field.clear();
            delimiterCount += 1;
        }
        else
            field.append(letter);
    }
}




