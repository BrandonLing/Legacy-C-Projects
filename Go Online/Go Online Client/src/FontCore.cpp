#include "FontCore.h"

void FontCore::init()
{
    TTF_Init();

    //load fonts into textures
    this->loadTexturefromFont("Resources/OpenSans-Semibold.ttf", 40);


}

void FontCore::quit()
{

}

void FontCore::loadTexturefromFont(const char* filename, int fontsize)
{
    int x_offset = 0;
    int totalWidth = 0;
    int totalHeight = 0;
    std::vector <int> advance;
    std::vector <int> charIndex;
        charIndex.push_back(x_offset);
    std::vector <int> powerOfTwoOffset;

    TTF_Font *font;
    if(!(font = TTF_OpenFont(filename, fontsize)))
    {
          std::cout << TTF_GetError() << "\n";
    }

    //Get total size of texture required
    totalWidth = this->getFontBitmapTotalWidth(font);
    totalHeight = this->getFontBitmapTotalHeight(font);
    this->fontBookXSize.push_back(totalWidth);
    this->fontBookYSize.push_back(totalHeight);

    this->fontBook.push_back(0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenTextures( 1, &(this->fontBook[this->fontCount]));
    glBindTexture( GL_TEXTURE_2D, this->fontBook[this->fontCount] );
    glTexImage2D( GL_TEXTURE_2D, 0, 4, totalWidth, totalHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );

    //Go through each ascii letter
    SDL_Color color = {255, 255, 255};
    for (int ascii = 32; ascii <= 126; ascii++)
    {
        SDL_Surface *loadSurface, *finalSurface, *convertedSurface;

        char letter = ascii;
        std::string renderLetter = &letter;
        renderLetter.resize(1);

        loadSurface = TTF_RenderText_Solid(font, renderLetter.c_str(), color);
        //ascii = 127; quick cancel for loop for troublshooting
        //std::cout << letter;
        advance.push_back(loadSurface->w);


        if ( loadSurface )
        {
        finalSurface = SDL_CreateRGBSurface(0, loadSurface->w, loadSurface->h, 32, 0, 0, 0, 0);
        SDL_FillRect( finalSurface, NULL, SDL_MapRGBA( finalSurface->format, 0, 0, 0, 0) );
        convertedSurface = SDL_ConvertSurface(loadSurface, finalSurface->format, 0);
        //std::cout << "Surface dimensions: " << finalSurface->w << ", " << finalSurface->h << "\n";

        SDL_LockSurface(convertedSurface);
        SDL_LockSurface(finalSurface);
        //Pull pixels into a properly casted surface
        for (int ix = 0; ix < (convertedSurface-> w) - 1; ix++) //for each column
        {
            for (int iy = 0; iy < (convertedSurface->h) - 1; iy++) //for each row
            {
                Uint32 pixel = this->getPixel32(convertedSurface, ix, iy);
                //std::cout << pixel << ",";
                if (pixel != 0)
                {
                    this->putPixel32(finalSurface, ix, iy, pixel);
                }
            }
        }
        SDL_UnlockSurface(convertedSurface);
        SDL_UnlockSurface(finalSurface);


        //Generate openGL texture
        glTexSubImage2D(GL_TEXTURE_2D, 0, x_offset, 0, finalSurface->w, finalSurface->h, GL_RGBA, GL_UNSIGNED_BYTE, finalSurface->pixels);

        int newOffset = this->nextPowerofTwo(finalSurface->w);
        x_offset = x_offset + newOffset;
        charIndex.push_back(x_offset);
        powerOfTwoOffset.push_back(newOffset);

        //Free Memory
        SDL_FreeSurface(loadSurface);
        SDL_FreeSurface(finalSurface);
        SDL_FreeSurface(convertedSurface);

        loadSurface = NULL;
        finalSurface = NULL;
        convertedSurface = NULL;
        }
        else
        {
            std::cout << "Error in ResourceCore: Line 95\n";
        }
    }

    glBindTexture( GL_TEXTURE_2D, 0);

    TTF_CloseFont(font);
    font = NULL;

    //std::cout << "Total width of font texture" << totalWidth << "\n";
    this->fontCount++;
    this->fontAdvanceBook.push_back(advance);
    this->fontTexIndexBook.push_back(charIndex);
    this->fontPowerOfTwoBook.push_back(powerOfTwoOffset);


    /*std::cout << "\nCharadvance\n";
    for(int i = 0; i < advance.size(); i++)
    {
        std::cout << advance[109-33] << ",";
        std::cout << advance[109-32] << ",";
        std::cout << advance[109-31] << ",";
        exit(0);
    }
    */

    //std::cout << "Font loaded\n";
}

//This function returns the number of texels required to fit a font bitmap
int FontCore::getFontBitmapTotalWidth(TTF_Font* font)
{
    SDL_Color color = {0, 0, 0};
    int totalWidth = 0;
    for (int ascii = 32; ascii <= 126; ascii++)
    {
        char letter = ascii;
        std::string renderLetter = &letter;
        renderLetter.resize(1);
        SDL_Surface *loadSurface = TTF_RenderText_Solid(font, renderLetter.c_str(), color);
        totalWidth = totalWidth + this->nextPowerofTwo(loadSurface->w);
    }
    return totalWidth;
}

Uint32 FontCore::getPixel32(SDL_Surface *surface, int x, int y)
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

void FontCore::putPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}

//This function returns the number of texels required to fit a font bitmap
int FontCore::getFontBitmapTotalHeight(TTF_Font* font)
{
    SDL_Color color = {0, 0, 0};
    SDL_Surface *loadSurface = TTF_RenderText_Solid(font, "!", color);
    int totalHeight = loadSurface->h;
    return this->nextPowerofTwo(totalHeight);
}

//returns the next highest number that is a power of two for mipmapping
int FontCore::nextPowerofTwo(int number)
{
    int output = 1;
    while (output < number)
    {
        output = output * 2;
    }
    return output;
}

void FontCore::getTextureDimensions()
{
    int W,H;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &W);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &H);
    std::cout << "GL Texture Size: " << W << ", " << H << "\n";
}

