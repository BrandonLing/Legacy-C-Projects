#ifndef FONTCORE_H
#define FONTCORE_H

#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

class FontCore
{
    public:
        void init();
        void quit();

        //Font Functions
        void loadTexturefromFont(const char* filename, int fontsize);
        int getFontBitmapTotalHeight(TTF_Font* font);
        int getFontBitmapTotalWidth(TTF_Font* font);
        int nextPowerofTwo(int number);
        Uint32 getPixel32(SDL_Surface *surface, int x, int y);
        void putPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);

        //Font Textures
        int fontCount = 0;
        std::vector<GLuint> fontBook; //holds textures
        std::vector<int> fontBookXSize; //holds size of font texture
        std::vector<int> fontBookYSize; //holds size of font texture
        std::vector <std::vector <int> > fontAdvanceBook; //stores advance arrays for each Font loaded. 94 ascii characters per font.
        std::vector <std::vector <int> > fontTexIndexBook; //stores where the x index is in the font bitmap concerning power of 2s
        std::vector <std::vector <int> > fontPowerOfTwoBook; //stores width of each glyph at lowest power of two
        void getTextureDimensions();
        float spaceSize = 8;
        int equippedFont = 0;

    protected:
    private:
};

#endif // FONTCORE_H
