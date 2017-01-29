//The SpriteCore holds texture data on backgrounds, tilesets, and spriteSheets

#ifndef SPRITECORE_H
#define SPRITECORE_H

#include <iostream>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <spriteTextureCoords.h>

class origin
{
    public:
        float x, y;
};

class animationInfo
{
    public:
        std::vector <int> spriteIndexAnim;

};

class SpriteCore
{
    public:
        void init();
        void initAnimations();
        void quit();
        void loadSpriteSheetfromFile(std::string filename);
        void loadBackgroundfromFile(std::string filename);
        void loadTileSetfromFile(std::string filename);

        //Game Textures
            //Sprites
            int loadCount = 0;
            std::vector<GLuint> spriteBook; //Holds Texture Data
            std::vector<int> spriteBookWidths;
            std::vector<int> spriteBookHeights;
            std::vector <std::vector<spriteTextureCoords> > spriteIndexBook; //Holds texture positions
            std::vector <std::vector<origin> > spriteOriginBook; //holds sprite Origins
            std::vector <std::vector<animationInfo> > spriteAnimationBook; //holds vectors of sprite indices for animations
            int totalAnimationFrames = 8;

            //Backgrounds
            int bgCount = 0;
            std::vector<GLuint> bgBook; //Holds Texture Data

            //Tilesets
            int tileSetCount = 0;
            std::vector<GLuint> tileSetBook; //Holds Texture Data
            std::vector<int> tileSetBookWidths;
            std::vector<int> tileSetBookHeights;
            std::vector<int> tileSizeBook;
            std::vector<spriteTextureCoords> tileIndexBook; //Holds texture positions

        //Specific texture data
        void setKnightTextureCoords();
        void setCursorTextureCoords();

        void setTileSetCoords();
    protected:
    private:
};



#endif // SPRITECORE_H
