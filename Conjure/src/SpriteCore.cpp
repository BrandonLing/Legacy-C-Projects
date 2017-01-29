#include "SpriteCore.h"

void SpriteCore::init()
{
    //Load Sprite Sheet
    loadSpriteSheetfromFile("knight_spr.png");
        this->setKnightTextureCoords();
    initAnimations();

    loadSpriteSheetfromFile("cursor_spr.png");
    loadSpriteSheetfromFile("buttonBG_spr.png");
        this->setCursorTextureCoords();

    //Load Backgrounds
    loadBackgroundfromFile("background0.png");
    loadBackgroundfromFile("background1.png");

    //LoadTileSets
    loadTileSetfromFile("tileset0.png");
        this->setTileSetCoords();

}

void SpriteCore::initAnimations()
{
    std::vector<int> animationVec;
    animationInfo anim0;
    std::vector<animationInfo> tempAnimationBook;

    //knight
    {
        animationVec = {7, 6, 5, 4, 3, 2, 1, 0};
        anim0.spriteIndexAnim = animationVec;
        tempAnimationBook.push_back(anim0);

        animationVec = {16, 17, 18, 19, 20, 21, 22, 23};
        anim0.spriteIndexAnim = animationVec;
        tempAnimationBook.push_back(anim0);

        animationVec = {31, 30, 29, 28, 27, 26, 25, 24};
        anim0.spriteIndexAnim = animationVec;
        tempAnimationBook.push_back(anim0);

        animationVec = {8, 9, 10, 11, 12, 13, 14, 15};
        anim0.spriteIndexAnim = animationVec;
        tempAnimationBook.push_back(anim0);

        animationVec = {32, 33, 34, 35};
        anim0.spriteIndexAnim = animationVec;
        tempAnimationBook.push_back(anim0);

        animationVec = {40, 41, 42, 43};
        anim0.spriteIndexAnim = animationVec;
        tempAnimationBook.push_back(anim0);

        animationVec = {47, 46, 45, 44};
        anim0.spriteIndexAnim = animationVec;
        tempAnimationBook.push_back(anim0);

        animationVec = {39, 38, 37, 36};
        anim0.spriteIndexAnim = animationVec;
        tempAnimationBook.push_back(anim0);

        this->spriteAnimationBook.push_back(tempAnimationBook);
    }

    //Cursor
    {
        tempAnimationBook.clear();

        animationVec = {0};
        anim0.spriteIndexAnim = animationVec;
        tempAnimationBook.push_back(anim0);

        this->spriteAnimationBook.push_back(tempAnimationBook);
    }

}

void SpriteCore::quit()
{
    for (unsigned int i = 0; i < this->spriteBook.size(); i++)
    {
        glDeleteTextures(1, &this->spriteBook[i]);
    }
}

//Only takes png's atm
void SpriteCore::loadSpriteSheetfromFile(std::string filename)
{
    SDL_Surface *image;
    std::string filepath = "Resources/";
    filepath.append(filename);
    image = IMG_Load(filepath.c_str());

    if(!image) //Handle Error
    {
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";
    }
    else
    {
        this->spriteBook.push_back(0);
        this->spriteBook.push_back(0);
        glGenTextures(1, &(this->spriteBook[loadCount]));
        glBindTexture(GL_TEXTURE_2D, this->spriteBook[loadCount]);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
        this->spriteBookHeights.push_back(image->h);
        this->spriteBookWidths.push_back(image->w);

        glBindTexture(GL_TEXTURE_2D, 0);
        SDL_FreeSurface(image);
        image = NULL;
        this->loadCount = this->loadCount + 1;
    }
}

//Only takes png's atm
void SpriteCore::loadBackgroundfromFile(std::string filename)
{
    SDL_Surface *image;
    std::string filepath = "Resources/";
    filepath.append(filename);
    image = IMG_Load(filepath.c_str());

    if(!image) //Handle Error
    {
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";
    }
    else
    {
        this->bgBook.push_back(0);
        glGenTextures(1, &(this->bgBook[bgCount]));
        glBindTexture(GL_TEXTURE_2D, this->bgBook[bgCount]);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

        glBindTexture(GL_TEXTURE_2D, 0);
        SDL_FreeSurface(image);
        image = NULL;
        this->bgCount++;
    }

}

//Only takes png's atm
void SpriteCore::loadTileSetfromFile(std::string filename)
{
    SDL_Surface *image;
    std::string filepath = "Resources/";
    filepath.append(filename);
    image = IMG_Load(filepath.c_str());

    if(!image) //Handle Error
    {
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";
    }
    else
    {
        this->tileSetBook.push_back(0);
        this->tileSetBook.push_back(0);
        glGenTextures(1, &(this->tileSetBook[tileSetCount]));
        glBindTexture(GL_TEXTURE_2D, this->tileSetBook[tileSetCount]);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
        this->tileSetBookHeights.push_back(image->h);
        this->tileSetBookWidths.push_back(image->w);
        this->tileSizeBook.push_back(128);

        glBindTexture(GL_TEXTURE_2D, 0);
        SDL_FreeSurface(image);
        image = NULL;
        this->tileSetCount = this->tileSetCount + 1;
    }
}

void SpriteCore::setKnightTextureCoords()
{
    //First Row
    spriteTextureCoords knightTex0;
    origin knightOri0;
    std::vector<spriteTextureCoords> tempSpriteTexBook;
    std::vector<origin> tempOriginBook;

    knightTex0.x1 = 0.0; knightTex0.x2 = 128.0; knightTex0.y1 = 0.0; knightTex0.y2 = 128.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 128.0; knightTex0.x2 = 256.0; knightTex0.y1 = 0.0; knightTex0.y2 = 128.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 256.0; knightTex0.x2 = 384.0; knightTex0.y1 = 0.0; knightTex0.y2 = 128.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 384.0; knightTex0.x2 = 512.0; knightTex0.y1 = 0.0; knightTex0.y2 = 128.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 512.0; knightTex0.x2 = 640.0; knightTex0.y1 = 0.0; knightTex0.y2 = 128.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 640.0; knightTex0.x2 = 768.0; knightTex0.y1 = 0.0; knightTex0.y2 = 128.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 768.0; knightTex0.x2 = 896.0; knightTex0.y1 = 0.0; knightTex0.y2 = 128.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 896.0; knightTex0.x2 = 1024.0; knightTex0.y1 = 0.0; knightTex0.y2 = 128.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    //second row
    knightTex0.x1 = 0.0; knightTex0.x2 = 128.0; knightTex0.y1 = 128.0; knightTex0.y2 = 256.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 128.0; knightTex0.x2 = 256.0; knightTex0.y1 = 128.0; knightTex0.y2 = 256.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 256.0; knightTex0.x2 = 384.0; knightTex0.y1 = 128.0; knightTex0.y2 = 256.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 384.0; knightTex0.x2 = 512.0; knightTex0.y1 = 128.0; knightTex0.y2 = 256.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 512.0; knightTex0.x2 = 640.0; knightTex0.y1 = 128.0; knightTex0.y2 = 256.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 640.0; knightTex0.x2 = 768.0; knightTex0.y1 = 128.0; knightTex0.y2 = 256.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 768.0; knightTex0.x2 = 896.0; knightTex0.y1 = 128.0; knightTex0.y2 = 256.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 896.0; knightTex0.x2 = 1024.0; knightTex0.y1 = 128.0; knightTex0.y2 = 256.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    //third row
    knightTex0.x1 = 0.0; knightTex0.x2 = 128.0; knightTex0.y1 = 256.0; knightTex0.y2 = 384.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 128.0; knightTex0.x2 = 256.0; knightTex0.y1 = 256.0; knightTex0.y2 = 384.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 256.0; knightTex0.x2 = 384.0; knightTex0.y1 = 256.0; knightTex0.y2 = 384.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 384.0; knightTex0.x2 = 512.0; knightTex0.y1 = 256.0; knightTex0.y2 = 384.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 512.0; knightTex0.x2 = 640.0; knightTex0.y1 = 256.0; knightTex0.y2 = 384.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 640.0; knightTex0.x2 = 768.0; knightTex0.y1 = 256.0; knightTex0.y2 = 384.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 768.0; knightTex0.x2 = 896.0; knightTex0.y1 = 256.0; knightTex0.y2 = 384.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 896.0; knightTex0.x2 = 1024.0; knightTex0.y1 = 256.0; knightTex0.y2 = 384.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    //fourth row
    knightTex0.x1 = 0.0; knightTex0.x2 = 128.0; knightTex0.y1 = 384.0; knightTex0.y2 = 512.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 128.0; knightTex0.x2 = 256.0; knightTex0.y1 = 384.0; knightTex0.y2 = 512.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 256.0; knightTex0.x2 = 384.0; knightTex0.y1 = 384.0; knightTex0.y2 = 512.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 384.0; knightTex0.x2 = 512.0; knightTex0.y1 = 384.0; knightTex0.y2 = 512.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 512.0; knightTex0.x2 = 640.0; knightTex0.y1 = 384.0; knightTex0.y2 = 512.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 640.0; knightTex0.x2 = 768.0; knightTex0.y1 = 384.0; knightTex0.y2 = 512.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 768.0; knightTex0.x2 = 896.0; knightTex0.y1 = 384.0; knightTex0.y2 = 512.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 896.0; knightTex0.x2 = 1024.0; knightTex0.y1 = 384.0; knightTex0.y2 = 512.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    //attack animations fifth row
    knightTex0.x1 = 0.0; knightTex0.x2 = 128.0; knightTex0.y1 = 512.0; knightTex0.y2 = 640.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 128.0; knightTex0.x2 = 256.0; knightTex0.y1 = 512.0; knightTex0.y2 = 640.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 256.0; knightTex0.x2 = 384.0; knightTex0.y1 = 512.0; knightTex0.y2 = 640.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 384.0; knightTex0.x2 = 512.0; knightTex0.y1 = 512.0; knightTex0.y2 = 640.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 512.0; knightTex0.x2 = 640.0; knightTex0.y1 = 512.0; knightTex0.y2 = 640.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 640.0; knightTex0.x2 = 768.0; knightTex0.y1 = 512.0; knightTex0.y2 = 640.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 768.0; knightTex0.x2 = 896.0; knightTex0.y1 = 512.0; knightTex0.y2 = 640.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 896.0; knightTex0.x2 = 1024.0; knightTex0.y1 = 512.0; knightTex0.y2 = 640.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    //attack animations sixth row
    knightTex0.x1 = 0.0; knightTex0.x2 = 128.0; knightTex0.y1 = 640.0; knightTex0.y2 = 768.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 128.0; knightTex0.x2 = 256.0; knightTex0.y1 = 640.0; knightTex0.y2 = 768.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 256.0; knightTex0.x2 = 384.0; knightTex0.y1 = 640.0; knightTex0.y2 = 768.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 384.0; knightTex0.x2 = 512.0; knightTex0.y1 = 640.0; knightTex0.y2 = 768.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 512.0; knightTex0.x2 = 640.0; knightTex0.y1 = 640.0; knightTex0.y2 = 768.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 640.0; knightTex0.x2 = 768.0; knightTex0.y1 = 640.0; knightTex0.y2 = 768.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 768.0; knightTex0.x2 = 896.0; knightTex0.y1 = 640.0; knightTex0.y2 = 768.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    knightTex0.x1 = 896.0; knightTex0.x2 = 1024.0; knightTex0.y1 = 640.0; knightTex0.y2 = 768.0;
    knightOri0.x = 55/128.0; knightOri0.y = 20/128.0;
    tempSpriteTexBook.push_back(knightTex0);
    tempOriginBook.push_back(knightOri0);

    this->spriteIndexBook.push_back(tempSpriteTexBook);
    this->spriteOriginBook.push_back(tempOriginBook);
}

void SpriteCore::setCursorTextureCoords()
{
    spriteTextureCoords cursorTex;
    origin cursorOri;
    std::vector<spriteTextureCoords> tempSpriteTexBook;
    std::vector<origin> tempOriginBook;

    //cursor
    cursorTex.x1 = 0.0; cursorTex.x2 = 19.0; cursorTex.y1 = 0.0; cursorTex.y2 = 52.0;
    cursorOri.x = 9.5/19.0; cursorOri.y = 26.0/52.0;
    tempSpriteTexBook.push_back(cursorTex);
    tempOriginBook.push_back(cursorOri);

    cursorTex.x1 = 19.0; cursorTex.x2 = 121.0; cursorTex.y1 = 0.0; cursorTex.y2 = 52.0;
    cursorOri.x = 50.5/101.0; cursorOri.y = 26.0/52.0;
    tempSpriteTexBook.push_back(cursorTex);
    tempOriginBook.push_back(cursorOri);

    cursorTex.x1 = 121.0; cursorTex.x2 = 220.0; cursorTex.y1 = 0.0; cursorTex.y2 = 52.0;
    cursorOri.x = 50.5/101.0; cursorOri.y = 26.0/52.0;
    tempSpriteTexBook.push_back(cursorTex);
    tempOriginBook.push_back(cursorOri);

    cursorTex.x1 = 220.0; cursorTex.x2 = 320.0; cursorTex.y1 = 0.0; cursorTex.y2 = 52.0;
    cursorOri.x = 50.5/101.0; cursorOri.y = 26.0/52.0;
    tempSpriteTexBook.push_back(cursorTex);
    tempOriginBook.push_back(cursorOri);

    this->spriteIndexBook.push_back(tempSpriteTexBook);
    this->spriteOriginBook.push_back(tempOriginBook);


    //Clear for next spriteSheet
    tempSpriteTexBook.clear();
    tempOriginBook.clear();

    //button_spr 0
    cursorTex.x1 = 0.0; cursorTex.x2 = 256.0; cursorTex.y1 = 0.0; cursorTex.y2 = 144.0;
    cursorOri.x = 128.0/256.0; cursorOri.y = 77.0/144.0;
    tempSpriteTexBook.push_back(cursorTex);
    tempOriginBook.push_back(cursorOri);

    //button_spr 1
    cursorTex.x1 = 256.0; cursorTex.x2 = 512.0; cursorTex.y1 = 0.0; cursorTex.y2 = 144.0;
    cursorOri.x = 128.0/256.0; cursorOri.y = 77.0/144.0;
    tempSpriteTexBook.push_back(cursorTex);
    tempOriginBook.push_back(cursorOri);

    this->spriteIndexBook.push_back(tempSpriteTexBook);
    this->spriteOriginBook.push_back(tempOriginBook);
}

void SpriteCore::setTileSetCoords()
{
    spriteTextureCoords isoUnitTex0; isoUnitTex0.x1 = 0.0; isoUnitTex0.x2 = 128.0; isoUnitTex0.y1 = 0.0; isoUnitTex0.y2 = 128.0;
    this->tileIndexBook.push_back(isoUnitTex0);

    isoUnitTex0.x1 = 128.0; isoUnitTex0.x2 = 256.0; isoUnitTex0.y1 = 0.0; isoUnitTex0.y2 = 128.0;
    this->tileIndexBook.push_back(isoUnitTex0);
}

