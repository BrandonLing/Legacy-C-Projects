#ifndef MAPCORE_H
#define MAPCORE_H

#include <iostream>

#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

class MapCore
{
    public:
        void init();
        void quit();

        void loadMap(std::string filename);
        void parseMapHeader(std::string headerLine);
        void parseTileData(std::string tileData);
        void parseHeightData(std::string tileData);

        int mapWidth, mapHeight, mapSize;
        float tileSizeX = 6; //Describes the size of the tiles on the screen
        std::string mapName;
        std::vector<int> mapTileData; //Stores an indexed map of tiles. Must use in coordination with mapWidth or height to draw
        std::vector<int> mapHeightData; //stores heightMap of the entire map. Used in conjunction with mapTileData
        int mapTileSet; //stores index of texture to use

        int background; //stores index for which background to use

        int displaceFactor = 5;
    protected:
    private:
};

#endif // MAPCORE_H
