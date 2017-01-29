#include "RenderCore.h"

void RenderCore::init()
{
    //Init vars
    this->windowTitle = "Williston - 3D World";
    //this->windowWidth = 1280;
    //this->windowHeight = 720;

    //init SDL2
    bool success1 = SDL_Init(SDL_INIT_VIDEO);
    this->sdlWindow = SDL_CreateWindow(this->windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->windowWidth, this->windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALLOW_HIGHDPI);
    this->glContext = SDL_GL_CreateContext(this->sdlWindow);
    SDL_GetWindowSize(this->sdlWindow, &(this->windowWidth), &(this->windowHeight));
    //Check for success of window/openGL creation
    if (success1 != 0) //returns 0 on success
        std::cout << "Error in Render Core: Cannot Init";

    //init openGL
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	glClearColor( 1.f, 0.5f, 0.f, 1.f );
    this->glRefreshViewport();

    //init glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        //Problem: glewInit failed, something is seriously wrong.
        std::cout << "GLEW Init failed\n";
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    //Init Generation of Buffers
    glGenBuffers(1, &this->dynamicEntityBuffer);
    glGenBuffers(1, &this->dynamicTextureBuffer);
    glGenVertexArrays(1, &this->dynamicVAO);
}

void RenderCore::quit()
{
    SDL_GL_DeleteContext(this->glContext);
    SDL_Quit();
    this->sdlWindow = NULL;

    //DestroyBuffers
    glDeleteVertexArrays(1, &this->dynamicVAO);
    glDeleteBuffers(1, &this->dynamicTextureBuffer);
    glDeleteBuffers(1, &this->dynamicEntityBuffer);
}

void RenderCore::glRefreshViewport()
{
    SDL_GetWindowSize(this->sdlWindow, &(this->windowWidth), &(this->windowHeight));
    glViewport(-(this->windowWidth), -(this->windowHeight), (this->windowWidth) * 2, (this->windowHeight) * 2);
    std::cout << "Refresh viewport: " << (this->windowWidth) << "x" << (this->windowHeight) << "\n";
}

void RenderCore::printGLInfo()
{
    //print openGL version data
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion =
    glGetString( GL_SHADING_LANGUAGE_VERSION );
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    printf("GL Vendor : %s\n", vendor);
    printf("GL Renderer : %s\n", renderer);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);
}

void RenderCore::drawText(float x, float y, std::string message)
{
    Shaders.useTextShader();


    //Convert string to ascii ints
    int mLength = message.size();
    std::vector<int> asciiMessage; //stores the message in ascii form

    asciiMessage.resize(mLength);
    char letter; int asciiLetter;

    std::vector<int> charAdvance; //stores the advance of each character in message
    charAdvance.resize(mLength);

    std::vector<int> charWidth; //stores width in power of 2
    charWidth.resize(mLength);

    std::vector<int> charXIndex;
    charXIndex.resize(mLength);

    for (int i = 0; i < mLength; i++)
    {
        //Convert to ascii
        letter = message[i];
        asciiLetter = letter;
        asciiMessage[i] = asciiLetter;
        //std::cout << asciiLetter << "\n";

        //Error check out of range ascii
        if ((asciiLetter < 32) || (asciiLetter > 126))
        {
            std::cout << "Error: Invalid Message in RenderCore Line 175\n";
            exit(0);
        }
        else
        {
            //Pull actual width (for mipmapping)
            //Pulladvance of each char (for rendering) in message into a vector
            //Pull actual x position indices in texture
            charXIndex[i] = ResourceData.FontSystem.fontTexIndexBook[ResourceData.FontSystem.equippedFont][asciiLetter - 32];
            charAdvance[i] = ResourceData.FontSystem.fontAdvanceBook[ResourceData.FontSystem.equippedFont][asciiLetter - 32];
            charWidth[i] = ResourceData.FontSystem.fontPowerOfTwoBook[ResourceData.FontSystem.equippedFont][asciiLetter - 32];
        }
    }

    //Pull texture dimensions
    float xTotal, yTotal;
    xTotal = ResourceData.FontSystem.fontBookXSize[ResourceData.FontSystem.equippedFont];
    yTotal = ResourceData.FontSystem.fontBookYSize[ResourceData.FontSystem.equippedFont];

    //Build vertex map of text
    std::vector<float> textVertData;
    std::vector<float> textureCoordData;
    int numVerts = mLength * 6;
    textVertData.resize(numVerts * 3);
    textureCoordData.resize((numVerts * 2) + 1);

    //For first letter
    float x1 = x, x2 = x1 + charWidth[0];
    float y1 = y, y2 = y + yTotal;

    //For remaining letters
    for (int i = 0; i < mLength; i++)
    {
        if (i != 0)
        {
            x1 = textVertData[(i * 18) - 18] + charAdvance[i - 1];
            x2 = x1 + charWidth[i];
        }

        textVertData[i * 18] = x1;        textVertData[(i * 18) + 1] = y1;   textVertData[(i * 18) + 2] = y1;
        textVertData[(i * 18) + 3] = x2;  textVertData[(i * 18) + 4] = y1;   textVertData[(i * 18) + 5] = y1;
        textVertData[(i * 18) + 6] = x2;  textVertData[(i * 18) + 7] = y2;   textVertData[(i * 18) + 8] = y2;
        textVertData[(i * 18) + 9] = x2;  textVertData[(i * 18) + 10] = y2;  textVertData[(i * 18) + 11] = y2;
        textVertData[(i * 18) + 12] = x1; textVertData[(i * 18) + 13] = y2;  textVertData[(i * 18) + 14] = y2;
        textVertData[(i * 18) + 15] = x1; textVertData[(i * 18) + 16] = y1;  textVertData[(i * 18) + 17] = y1;
        textureCoordData[(i * 12)]     = charXIndex[i] / xTotal;                   textureCoordData[(i * 12) + 1] = 1.0;
        textureCoordData[(i * 12) + 2] = (charXIndex[i] + charWidth[i]) / xTotal;  textureCoordData[(i * 12) + 3] = 1.0;
        textureCoordData[(i * 12) + 4] = (charXIndex[i] + charWidth[i]) / xTotal;  textureCoordData[(i * 12) + 5] = 0.0;
        textureCoordData[(i * 12) + 6] = (charXIndex[i] + charWidth[i]) / xTotal;  textureCoordData[(i * 12) + 7] = 0.0;
        textureCoordData[(i * 12) + 8] = charXIndex[i] / xTotal;                   textureCoordData[(i * 12) + 9] = 0.0;
        textureCoordData[(i * 12) + 10]= charXIndex[i] / xTotal;                   textureCoordData[(i * 12) + 11] = 1.0;
    }

    //translation to origin
    //add scale since default is way too big
    //re-add translation
    float xTranslate = x, yTranslate = y;
    float scale = 0.10;
    for(unsigned int i = 0; i < textVertData.size(); i+=3)
    {
        textVertData[i] = ((textVertData[i] - xTranslate) * scale) + xTranslate;
        textVertData[i+1] = ((textVertData[i+1] - yTranslate) * scale) + yTranslate;
        textVertData[i+2] = ((textVertData[i+2] - yTranslate) * scale) + yTranslate;

    }





    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (textVertData.size()), &textVertData[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (textureCoordData.size()), &textureCoordData[0], GL_STREAM_DRAW);

    glBindVertexArray (this->dynamicVAO);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);


    glDrawArrays(GL_TRIANGLES, 0, textVertData.size() / 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void RenderCore::drawGUIText(float x, float y, std::string message)
{
    Shaders.useGUITextShader();

    //Convert string to ascii ints
    int mLength = message.size();
    std::vector<int> asciiMessage; //stores the message in ascii form

    asciiMessage.resize(mLength);
    char letter; int asciiLetter;

    std::vector<int> charAdvance; //stores the advance of each character in message
    charAdvance.resize(mLength);

    std::vector<int> charWidth; //stores width in power of 2
    charWidth.resize(mLength);

    std::vector<int> charXIndex;
    charXIndex.resize(mLength);

    for (int i = 0; i < mLength; i++)
    {
        //Convert to ascii
        letter = message[i];
        asciiLetter = letter;
        asciiMessage[i] = asciiLetter;
        //std::cout << asciiLetter << "\n";

        //Error check out of range ascii
        if ((asciiLetter < 32) || (asciiLetter > 126))
        {
            std::cout << "Error: Invalid Message in RenderCore Line 175\n";
            exit(0);
        }
        else
        {
            //Pull actual width (for mipmapping)
            //Pulladvance of each char (for rendering) in message into a vector
            //Pull actual x position indices in texture
            charXIndex[i] = ResourceData.FontSystem.fontTexIndexBook[ResourceData.FontSystem.equippedFont][asciiLetter - 32];
            charAdvance[i] = ResourceData.FontSystem.fontAdvanceBook[ResourceData.FontSystem.equippedFont][asciiLetter - 32];
            charWidth[i] = ResourceData.FontSystem.fontPowerOfTwoBook[ResourceData.FontSystem.equippedFont][asciiLetter - 32];
        }
    }

    //Pull texture dimensions
    float xTotal, yTotal;
    xTotal = ResourceData.FontSystem.fontBookXSize[ResourceData.FontSystem.equippedFont];
    yTotal = ResourceData.FontSystem.fontBookYSize[ResourceData.FontSystem.equippedFont];

    //Build vertex map of text
    std::vector<float> textVertData;
    std::vector<float> textureCoordData;
    int numVerts = mLength * 6;
    textVertData.resize(numVerts * 3);
    textureCoordData.resize((numVerts * 2) + 1);

    //For first letter
    float x1 = x, x2 = x1 + charWidth[0];
    float y1 = y, y2 = y1 + yTotal;

    //For remaining letters
    for (int i = 0; i < mLength; i++)
    {
        if (i != 0)
        {
            x1 = textVertData[(i * 18) - 18] + charAdvance[i - 1];
            x2 = x1 + charWidth[i];
        }

        textVertData[i * 18] = x1;        textVertData[(i * 18) + 1] = y1;   textVertData[(i * 18) + 2] = y1;
        textVertData[(i * 18) + 3] = x2;  textVertData[(i * 18) + 4] = y1;   textVertData[(i * 18) + 5] = y1;
        textVertData[(i * 18) + 6] = x2;  textVertData[(i * 18) + 7] = y2;   textVertData[(i * 18) + 8] = y2;
        textVertData[(i * 18) + 9] = x2;  textVertData[(i * 18) + 10] = y2;  textVertData[(i * 18) + 11] = y2;
        textVertData[(i * 18) + 12] = x1; textVertData[(i * 18) + 13] = y2;  textVertData[(i * 18) + 14] = y2;
        textVertData[(i * 18) + 15] = x1; textVertData[(i * 18) + 16] = y1;  textVertData[(i * 18) + 17] = y1;
        textureCoordData[(i * 12)]     = charXIndex[i] / xTotal;                   textureCoordData[(i * 12) + 1] = 1.0;
        textureCoordData[(i * 12) + 2] = (charXIndex[i] + charWidth[i]) / xTotal;  textureCoordData[(i * 12) + 3] = 1.0;
        textureCoordData[(i * 12) + 4] = (charXIndex[i] + charWidth[i]) / xTotal;  textureCoordData[(i * 12) + 5] = 0.0;
        textureCoordData[(i * 12) + 6] = (charXIndex[i] + charWidth[i]) / xTotal;  textureCoordData[(i * 12) + 7] = 0.0;
        textureCoordData[(i * 12) + 8] = charXIndex[i] / xTotal;                   textureCoordData[(i * 12) + 9] = 0.0;
        textureCoordData[(i * 12) + 10]= charXIndex[i] / xTotal;                   textureCoordData[(i * 12) + 11] = 1.0;
    }

    //translation to origin
    float xTranslate = x, yTranslate = y;

    //add scale since default is way too big
    float scale = 0.10;
    int playerID = GameData.getEntityID(GameData.playerCharacter, 0);
    float pX, pY;
    float Xc = GameData.getPlayerX(playerID);
    float Yc = GameData.getPlayerY(playerID); //float gridX = MapData.tileSizeX; float Xcmax = MapData.mapWidth;
    if (!introFlag) //title screen
    {
        pX = Xc;
        pY = Yc;
    }
    else //in game
    {
        pX = GameData.xLocSave;
        pY = GameData.yLocSave;
    }

    int vertCount = textVertData.size();

    //calculate values to center text
    float minX = textVertData[0]; //lower bound x
    float minY = textVertData[1];  //lower bound y
    float maxX = textVertData[vertCount - 18] + charAdvance[charAdvance.size() - 1]; //the last x coordinate
    float maxY = textVertData[vertCount - 5]; //the last y coordinate
    //std::cout << minY << "," << maxY << "\n";

    xTranslate += ((maxX - minX) / 2);
    yTranslate += ((maxY - minY) / 2);

    //re-add translation to player position
    //translate again depending on x and y. -1 is left and bottom of screen. 1 is top and bottom.
    for(int i = 0; i < vertCount; i+=3)
    {
        textVertData[i] = ((textVertData[i] - xTranslate) * scale) + pX + (GameData.getPlayerWidth(playerID) / 2) + (GameData.playerCam.viewWidth * x / 4);
        textVertData[i+1] = ((textVertData[i+1] - yTranslate) * scale) + pY + (GameData.playerCam.viewHeight * y / 4);
        textVertData[i+2] = ((textVertData[i+2] - yTranslate) * scale) + pY + (GameData.playerCam.viewHeight * y / 4);
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (textVertData.size()), &textVertData[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (textureCoordData.size()), &textureCoordData[0], GL_STREAM_DRAW);

    glBindVertexArray (this->dynamicVAO);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);


    glDrawArrays(GL_TRIANGLES, 0, textVertData.size() / 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

//Renders map that is loaded in map core
void RenderCore::drawMap()
{
    //Use Program
    Shaders.useTileShader();
    GLint texLoc = glGetUniformLocation(Shaders.tileProg, "tileTexture");
    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE0);

    //Set MipMap settings and texture
    int tileBookIndex = MapData.mapTileSet;
    glBindTexture(GL_TEXTURE_2D, ResourceData.SpriteData.tileSetBook[tileBookIndex]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //pull mapWidth and tile Widths
    int mapWidth = MapData.mapWidth;
    int tileWidth = MapData.tileSizeX; //Stores width size of map tiles actually on screen

    std::vector<float> vertexArray, textureArray;
    std::list<float> zOrder;

    //go through each element of map Tile Data
    for (int i = 0; i < MapData.mapSize; i++)
    {
        //pull relevant isometric variables
        int Xcmax = MapData.mapWidth; //Max x in cartesian
        int gridX = MapData.tileSizeX;
        int Xc = i % mapWidth;
        int Yc = i / mapWidth;

        float Xi = (calcXi(Xc, Yc, gridX, Xcmax));
        float Yi = (calcYi(Xc, Yc, gridX, Xcmax));
        //std::cout << Xi << "," << Yi << "\n";

        //Pull value of tile in tileSet
        int tileIndex = MapData.mapTileData[i];

        //Pull Tile Height for displacement
        int tileHeight = MapData.mapHeightData[i];
        int yDisp = tileHeight * MapData.displaceFactor;

        if (tileIndex == -1)
        {
            continue;
        }

        //get actual tile dimensions
        int tileTextureWidth = ResourceData.SpriteData.tileSetBookWidths[tileBookIndex];
        int tileTextureHeight = ResourceData.SpriteData.tileSetBookHeights[tileBookIndex];
        float yxRatio = (ResourceData.SpriteData.tileIndexBook[tileIndex].y2 - ResourceData.SpriteData.tileIndexBook[tileIndex].y1)
            / (ResourceData.SpriteData.tileIndexBook[tileIndex].x2 - ResourceData.SpriteData.tileIndexBook[tileIndex].x1);

        //get coordinates for vertex array
        float x1, y1, x2, y2;
        x1 = Xi - (tileWidth);
        x2 = Xi + (tileWidth);
        y1 = Yi - (tileWidth * yxRatio) - (tileWidth/2); //shift down a fourth of the width to fix coordinate space
        y2 = Yi + (tileWidth * yxRatio) - (tileWidth/2); //shift down a fourth of the width to fix coordinate space
        //std::cout << x1 << "," << y1 << "  " << x2 << "," << y2 << "\n";

        //Find position in zOrder List
        std::list<float>::iterator zOrderIndex;
        int sortedIndex = 0;
        bool inserted = false;

        for (zOrderIndex = zOrder.begin(); zOrderIndex != zOrder.end(); zOrderIndex++)
        {
            inserted = false;
            float examinedZ = (*zOrderIndex);
            if (Yi >= examinedZ)
            {
                zOrder.insert(zOrderIndex, Yi);

                sortedIndex = distance(zOrder.begin(), zOrderIndex);
                inserted = true;
                for (int heightCount = 1; heightCount <= tileHeight; heightCount++)
                {
                    zOrder.insert(zOrderIndex, Yi);
                }

                break;
            }
            sortedIndex = distance(zOrder.begin(), zOrder.end());
        }

        //Add to end of list
        if (!inserted)
        {
            for (int heightCount = 0; heightCount <= tileHeight; heightCount++)
            {
                zOrder.push_back(Yi);
            }
        }
        if (zOrder.size() == 0)
        {
            for (int heightCount = 0; heightCount <= tileHeight; heightCount++)
            {
                zOrder.push_back(Yi);
            }
        }

        //form vertexArray
        if ((sortedIndex > 0) && (Yc != 0))
            sortedIndex -= 1;


        //get coordinates for textureArray
        float tx1 = ResourceData.SpriteData.tileIndexBook[tileIndex].x1 / tileTextureWidth;
        float tx2 = ResourceData.SpriteData.tileIndexBook[tileIndex].x2 / tileTextureWidth;
        float ty1 = ResourceData.SpriteData.tileIndexBook[tileIndex].y1 / tileTextureHeight;
        float ty2 = ResourceData.SpriteData.tileIndexBook[tileIndex].y2 / tileTextureHeight;

        //draw wall and column underneath the tile (this is in case the tile is so high that you can see the bottom of the cube)
        for (int heightCount = 0; heightCount <= tileHeight; heightCount++)
        {
            //displace tile due to elevation
            float y1New = y1 + yDisp - (MapData.displaceFactor * (tileHeight - heightCount));
            float y2New = y2 + yDisp - (MapData.displaceFactor * (tileHeight - heightCount));
            float depth = y2;

            std::vector<float>::iterator vertInputIndex = vertexArray.begin() + (sortedIndex * 18);
            vertexArray.insert(vertInputIndex, {x1, y1New, -depth, x2, y1New, -depth, x2, y2New, -depth, x2, y2New, -depth, x1, y2New, -depth, x1, y1New, -depth});

            //form texture Array in zOrder
            std::vector<float>::iterator textureInputIndex = textureArray.begin() + (sortedIndex * 12);
            textureArray.insert(textureInputIndex, {tx1, ty2, tx2, ty2, tx2, ty1, tx2, ty1, tx1, ty1, tx1, ty2});

        }
    }


    //Draw map
    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexArray.size(), &vertexArray[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textureArray.size(), &textureArray[0], GL_STREAM_DRAW);

    glBindVertexArray (this->dynamicVAO);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    glDrawArrays(GL_TRIANGLES, 0, vertexArray.size() / 3);
    //std::cout << vertexArray.size() << "\n";

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray (0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderCore::drawBackground()
{
    Shaders.useBGShader();

    std::vector<float> bgVecData; std::vector<float> bgTexCoord;
    float x1, x2, y1, y2, tx1, tx2, ty1, ty2;

    x1 = 0.0; x2 = 1.0; y1 = 0.0; y2 = 1.0;
    bgVecData.insert(bgVecData.end(), {x1, y1, y1, x2, y1, y1, x2, y2, y2, x2, y2, y2, x1, y2, y1, x1, y1, y1});

    tx1 = 0.0, ty1 = 0.0; tx2 = 1.0; ty2 = 1.0;
    bgTexCoord.insert(bgTexCoord.end(), {tx1, ty2, tx2, ty2, tx2, ty1, tx2, ty1, tx1, ty1, tx1, ty2});

    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (bgVecData.size()), &bgVecData[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (bgTexCoord.size()), &bgTexCoord[0], GL_STREAM_DRAW);

    glBindVertexArray (this->dynamicVAO);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    glDrawArrays(GL_TRIANGLES, 0, bgVecData.size() / 3);
}

void RenderCore::drawEntities(int entityType)
{
    Shaders.useDefaultShader();
    GLint texLoc = glGetUniformLocation(Shaders.defaultProg, "spriteTexture");
    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE0);

    //Draw Sprite Data
    //Build vector of draw data
    std::vector<float> gpuBuffer;
    std::vector<float> textureBuffer;
    std::vector<float> zOrder; //zOrder holding Yi data
    std::vector<std::string> guiTextBuffer;
    std::vector<float> guiTextCoordBuffer;

    gpuBuffer.push_back(0.0); //padding bug fix. Refer to Bug Report 001;
    std::vector<GameObject>::iterator gObjIter;
    for (gObjIter = GameData.EntityVec.begin(); gObjIter != GameData.EntityVec.end(); gObjIter++)
    {
        //Check visibility flag
        if ((*gObjIter).visible)
        {
            //identify type of object
            int type = (*gObjIter).type;
            if (type != entityType)
            {
                continue;
            }

            //pull isometric conversion constants
            float Xc = (*gObjIter).x;
            float Yc = (*gObjIter).y;
            float Gx = MapData.tileSizeX;
            float Xcmax = MapData.mapWidth;
            float x1, x2, y1, y2;


            x1 = calcXi(Xc, Yc, Gx, Xcmax); //Xisometric
            x2 = x1 + (*gObjIter).width;
            y1 = calcYi(Xc, Yc, Gx, Xcmax); //Yisometric
            y2 = y1 + (*gObjIter).height;

            //sort by zOrder
            int sortedIndex = 0;
            bool inserted = false;
            if (zOrder.size() != 0)
            {
                std::vector<float>::iterator zOrderIndex;
                for (zOrderIndex = zOrder.begin(); zOrderIndex != zOrder.end(); zOrderIndex++)
                {
                    float depth = *zOrderIndex;
                    if (y1 > depth)
                    {
                        zOrder.insert(zOrderIndex, y1);
                        inserted = true;
                        break;
                    }
                    sortedIndex += 1;
                }

            }
            else
            {//if empty
                zOrder.push_back(y1);
                inserted = true;
            }
            if (!inserted)
            {
                sortedIndex = distance(zOrder.begin(), zOrder.end());
                zOrder.push_back(y1);
            }

            /*for (int i = 0; i < zOrder.size(); i++)
            {
                std::cout << zOrder[i]<<",";
            }
            std::cout << "\n";
            std::cout <<sortedIndex << "Index\n";*/


            //get sprite data to draw
            int spriteBookIndex = (*gObjIter).spriteBook;
            glBindTexture(GL_TEXTURE_2D, ResourceData.SpriteData.spriteBook[spriteBookIndex]);

            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            float spriteIndexf = (*gObjIter).spriteIndex;
            int spriteIndex = spriteIndexf;
            float spriteIndexMax = ResourceData.SpriteData.totalAnimationFrames;
            int pFacing = (*gObjIter).currentPFacing;

            float remainder = fmod(spriteIndexf, spriteIndexMax);
            float imgSpeed = (*gObjIter).imageSpeed;

            //Loop Sprite index
            if ((remainder < imgSpeed) && (spriteIndex > 0))
            {
                (*gObjIter).spriteIndex -= spriteIndexMax;
                spriteIndex -= spriteIndexMax;
            }

            int textureIndex = (*gObjIter).spriteIndex;
            if ((((*gObjIter).attacking == false) && (type == 1)) || (type == 4))
            {
                textureIndex = ResourceData.SpriteData.spriteAnimationBook[spriteBookIndex][pFacing/2].spriteIndexAnim[spriteIndex];
            }
            else if ((((*gObjIter).attacking == true) && (type == 1)) || (type == 4))
            {
                textureIndex = ResourceData.SpriteData.spriteAnimationBook[spriteBookIndex][(pFacing/2) + 4].spriteIndexAnim[spriteIndex];
            }
            else if (type == 2)
            {
                textureIndex = (*gObjIter).spriteIndex;
            }

            float tx1, tx2, ty1, ty2;
            if ((type == 1) || (type == 2))
            {
                //get origin and translate sprite
                float xOri, yOri;
                xOri = ResourceData.SpriteData.spriteOriginBook[spriteBookIndex][textureIndex].x * (x2 - x1);
                yOri = ResourceData.SpriteData.spriteOriginBook[spriteBookIndex][textureIndex].y * (y2 - y1);
                x1 -= xOri; x2 -= xOri; y1 -= yOri; y2 -= yOri;
            }

            //get texture coords
            tx1 = ResourceData.SpriteData.spriteIndexBook[spriteBookIndex][textureIndex].x1 / ResourceData.SpriteData.spriteBookWidths[spriteBookIndex];
            tx2 = ResourceData.SpriteData.spriteIndexBook[spriteBookIndex][textureIndex].x2 / ResourceData.SpriteData.spriteBookWidths[spriteBookIndex];
            ty1 = ResourceData.SpriteData.spriteIndexBook[spriteBookIndex][textureIndex].y1 / ResourceData.SpriteData.spriteBookHeights[spriteBookIndex];
            ty2 = ResourceData.SpriteData.spriteIndexBook[spriteBookIndex][textureIndex].y2 / ResourceData.SpriteData.spriteBookHeights[spriteBookIndex];

            //std::cout << (*gObjIter).name << "\n";// print every entity's name
            switch (type)
            {
                case 0: //draw all player characters
                {
                    x1 = Xc;
                    x2 = x1 + (*gObjIter).width;
                    y1 = Yc;
                    y2 = y1 + (*gObjIter).height;

                    //get origin and translate sprite
                    float xOri, yOri;
                    xOri = ResourceData.SpriteData.spriteOriginBook[spriteBookIndex][textureIndex].x * (x2 - x1);
                    yOri = ResourceData.SpriteData.spriteOriginBook[spriteBookIndex][textureIndex].y * (y2 - y1);
                    x1 -= xOri; x2 -= xOri; y1 -= yOri; y2 -= yOri;

                    //gpuBuffer.insert(gpuBuffer.end(), {x1, y1, y1, x2, y1, y1, x2, y2, y2, x2, y2, y2, x1, y2, y1, x1, y1, y1});
                    std::vector<float>::iterator vertInputIndex = gpuBuffer.begin() + (sortedIndex * 18) + 1;
                    gpuBuffer.insert(vertInputIndex, {x1, y1, y1, x2, y1, y1, x2, y2, y2, x2, y2, y2, x1, y2, y2, x1, y1, y1});

                    std::vector<float>::iterator textInputIndex = textureBuffer.begin() + (sortedIndex * 12);
                    textureBuffer.insert(textInputIndex, {tx1, ty2, tx2, ty2, tx2, ty1, tx2, ty1, tx1, ty1, tx1, ty2});
                    break;
                }
                case 1: //draw all monsters
                {
                    //Displace due to map tile elevation
                    /*int tileIndex = (*gObjIter).xMask + ((*gObjIter).yMask * MapData.mapWidth);
                    int height = MapData.mapHeightData[tileIndex];
                    float disp = MapData.displaceFactor * height;*/


                    float disp = (*gObjIter).z * MapData.displaceFactor;

                    float depth = y2 - 8;
                    y1 += disp;
                    y2 += disp;

                    std::vector<float>::iterator vertInputIndex = gpuBuffer.begin() + (sortedIndex * 18) + 1;
                    gpuBuffer.insert(vertInputIndex, {x1, y1, -depth, x2, y1, -depth, x2, y2, -depth, x2, y2, -depth, x1, y2, -depth, x1, y1, -depth});

                    std::vector<float>::iterator textInputIndex = textureBuffer.begin() + (sortedIndex * 12);
                    textureBuffer.insert(textInputIndex, {tx1, ty2, tx2, ty2, tx2, ty1, tx2, ty1, tx1, ty1, tx1, ty2});
                    break;
                }
                case 2: //draw cursor target location
                {
                    //Displace due to map tile elevation
                    int tileIndex = (*gObjIter).x + ((*gObjIter).y * MapData.mapWidth);
                    int height = MapData.mapHeightData[tileIndex];
                    float disp = MapData.displaceFactor * height;

                    float depth = y2;
                    y1 += disp;
                    y2 += disp;

                    std::vector<float>::iterator vertInputIndex = gpuBuffer.begin() + (sortedIndex * 18) + 1;
                    gpuBuffer.insert(vertInputIndex, {x1, y1, -depth, x2, y1, -depth, x2, y2, -depth, x2, y2, -depth, x1, y2, -depth, x1, y1, -depth});

                    std::vector<float>::iterator textInputIndex = textureBuffer.begin() + (sortedIndex * 12);
                    textureBuffer.insert(textInputIndex, {tx1, ty2, tx2, ty2, tx2, ty1, tx2, ty1, tx1, ty1, tx1, ty2});
                    break;
                }
                case 3: //draw button background. Text will be drawn after due to texture changing to the True type font texture
                {
                    float winHeight = (*gObjIter).height * GameData.playerCam.viewHeight / 4;
                    float winWidth = (*gObjIter).width * GameData.playerCam.viewWidth / 4;
                    //set position of button
                    float camX = GameData.playerCam.cameraPos[0];
                    float camY = GameData.playerCam.cameraPos[1];

                    x1 = camX + ((*gObjIter).x * GameData.playerCam.viewWidth / 4);
                    y1 = camY + ((*gObjIter).y * GameData.playerCam.viewHeight / 4);

                    //normalize to screen. 1.0 in height is whole screen
                    x2 = x1 + winWidth;
                    x1 = x1 - winWidth;
                    y2 = y1 + winHeight;
                    y1 = y1 - winHeight;

                    std::vector<float>::iterator vertInputIndex = gpuBuffer.begin() + (sortedIndex * 18) + 1;
                    gpuBuffer.insert(vertInputIndex, {x1, y1, y1, x2, y1, y1, x2, y2, y2, x2, y2, y2, x1, y2, y2, x1, y1, y1});

                    std::vector<float>::iterator textInputIndex = textureBuffer.begin() + (sortedIndex * 12);
                    textureBuffer.insert(textInputIndex, {tx1, ty2, tx2, ty2, tx2, ty1, tx2, ty1, tx1, ty1, tx1, ty2});

                    //std::cout << (*gObjIter).x << "," << (*gObjIter).y << "\n";
                    guiTextCoordBuffer.push_back((*gObjIter).x);
                    guiTextCoordBuffer.push_back((*gObjIter).y);
                    guiTextBuffer.push_back((*gObjIter).name);
                    break;
                }
                case 4: //draw GUI mouse
                {
                    x1 = Xc;
                    x2 = x1 + (*gObjIter).width;
                    y1 = Yc;
                    y2 = y1 + (*gObjIter).height;

                    std::vector<float>::iterator vertInputIndex = gpuBuffer.begin() + (sortedIndex * 18) + 1;
                    gpuBuffer.insert(vertInputIndex, {x1, y1, y1, x2, y1, y1, x2, y2, y2, x2, y2, y2, x1, y2, y2, x1, y1, y1});

                    std::vector<float>::iterator textInputIndex = textureBuffer.begin() + (sortedIndex * 12);
                    textureBuffer.insert(textInputIndex, {tx1, ty2, tx2, ty2, tx2, ty1, tx2, ty1, tx1, ty1, tx1, ty2});
                    break;
                }
                case 6: //in game gui button
                //draw button background. Text will be drawn after due to texture changing to the True type font texture
                {
                    float winHeight = (*gObjIter).height * GameData.playerCam.viewHeight / 4;
                    float winWidth = (*gObjIter).width * GameData.playerCam.viewWidth / 4;
                    //set position of button
                    float camX = GameData.playerCam.cameraPos[0];
                    float camY = GameData.playerCam.cameraPos[1];

                    x1 = camX + ((*gObjIter).x * GameData.playerCam.viewWidth / 4);
                    y1 = camY + ((*gObjIter).y * GameData.playerCam.viewHeight / 4);

                    //normalize to screen. 1.0 in height is whole screen
                    x2 = x1 + winWidth;
                    x1 = x1 - winWidth;
                    y2 = y1 + winHeight;
                    y1 = y1 - winHeight;

                    std::vector<float>::iterator vertInputIndex = gpuBuffer.begin() + (sortedIndex * 18) + 1;
                    gpuBuffer.insert(vertInputIndex, {x1, y1, y1, x2, y1, y1, x2, y2, y2, x2, y2, y2, x1, y2, y1, x1, y1, y1});

                    std::vector<float>::iterator textInputIndex = textureBuffer.begin() + (sortedIndex * 12);
                    textureBuffer.insert(textInputIndex, {tx1, ty2, tx2, ty2, tx2, ty1, tx2, ty1, tx1, ty1, tx1, ty2});

                    //std::cout << (*gObjIter).x << "," << (*gObjIter).y << "\n";
                    guiTextCoordBuffer.push_back((*gObjIter).x);
                    guiTextCoordBuffer.push_back((*gObjIter).y);
                    guiTextBuffer.push_back((*gObjIter).name);
                    break;
                }
                case 7: //draw range indicator
                {
                    int entityFlag = (*gObjIter).flag;
                    std::vector<pathFinderNode> nodeList;
                    //std::cout << entityFlag << "\n";
                    if (entityFlag >= 0)
                    {
                        nodeList = GameData.EntityVec[entityFlag].reachableNodes;
                        int totalNodes = nodeList.size();

                        for(int i = 0; i < totalNodes; i++)
                        {
                            //std::cout << "iteration " << i << "\n";
                            pathFinderNode node = nodeList[i];

                            //pull isometric conversion constants
                            Xc = node.x;
                            Yc = node.y;

                            x1 = calcXi(Xc, Yc, Gx, Xcmax); //Xisometric
                            x2 = x1 + (*gObjIter).width;
                            y1 = calcYi(Xc, Yc, Gx, Xcmax); //Yisometric
                            y2 = y1 + (*gObjIter).height;

                            //get origin and translate sprite
                            float xOri = ResourceData.SpriteData.spriteOriginBook[spriteBookIndex][textureIndex].x * (x2 - x1);
                            float yOri = ResourceData.SpriteData.spriteOriginBook[spriteBookIndex][textureIndex].y * (y2 - y1);
                            x1 -= xOri; x2 -= xOri; y1 -= yOri; y2 -= yOri;

                            //Displace due to map tile elevation
                            int tileIndex = Xc + (Yc * MapData.mapWidth);
                            int height = MapData.mapHeightData[tileIndex];
                            float disp = MapData.displaceFactor * height;

                            float depth = y2 + 0.01;
                            y1 += disp;
                            y2 += disp;

                            std::vector<float>::iterator vertInputIndex = gpuBuffer.begin() + (sortedIndex * 18) + 1;
                            gpuBuffer.insert(vertInputIndex, {x1, y1, -depth, x2, y1, -depth, x2, y2, -depth, x2, y2, -depth, x1, y2, -depth, x1, y1, -depth});

                            std::vector<float>::iterator textInputIndex = textureBuffer.begin() + (sortedIndex * 12);
                            textureBuffer.insert(textInputIndex, {tx1, ty2, tx2, ty2, tx2, ty1, tx2, ty1, tx1, ty1, tx1, ty2});

                        }
                    }
                    break;
                }//end case 7

            }
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (gpuBuffer.size() - 1), &gpuBuffer[1], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (textureBuffer.size()), &textureBuffer[0], GL_STREAM_DRAW);

    glBindVertexArray (this->dynamicVAO);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicEntityBuffer);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER, this->dynamicTextureBuffer);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    glDrawArrays(GL_TRIANGLES, 0, (gpuBuffer.size() - 1) / 3);
    //std::cout << (gpuBuffer.size() - 1) / 3 << "\n";

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray (0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
        //Print gpuBuffer
        /*for (int i = 1; i < gpuBuffer.size(); i++)
                {
                    std::cout << gpuBuffer[i];
                    std::cout << ",";
                    if ((i % 3) == 0 )
                        std::cout << "\n";
                }
        std::cout << "\n\n";*/
    gpuBuffer.clear();

    //Draw Text Buttons if type == 3
    int textBufferSize = guiTextBuffer.size();
    if (entityType == 3)
    {
        if (textBufferSize > 0)
        {
            glBindTexture(GL_TEXTURE_2D, ResourceData.FontSystem.fontBook[0]);
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            for (int i = 0; i < textBufferSize; i++)
            {
                this->drawGUIText(guiTextCoordBuffer[i * 2], guiTextCoordBuffer[(i * 2) + 1], guiTextBuffer[i]);
            }
        }
    }
    else if (entityType == 6)
    {
        if (textBufferSize > 0)
        {
            glBindTexture(GL_TEXTURE_2D, ResourceData.FontSystem.fontBook[0]);
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            for (int i = 0; i < textBufferSize; i++)
            {
                this->drawGUIText(guiTextCoordBuffer[i * 2], guiTextCoordBuffer[(i * 2) + 1], guiTextBuffer[i]);
            }
        }
    }
}

void RenderCore::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //this->printGLInfo(); //Sleep(2000); exit(0);

    this->drawBackground();

    glEnable(GL_DEPTH_TEST);
    this->drawMap();

    this->drawEntities(7); //draw range indicator

    if (GameData.GameState == 0)
    {
        this->drawEntities(2); //draw all cursor boxes
    }

    this->drawEntities(1); //draw all monsters
    glDisable(GL_DEPTH_TEST);

    this->drawEntities(3); //draw all buttons
    this->drawEntities(4); //draw title screen cursor
    if ((GameData.GameState == 1) || (GameData.GameState == 2)) //in menu mode
    {
        this->drawEntities(0); //draw camera position
    }
    if (GameData.GameState == 1)
    {
        this->drawEntities(6); //draw in game buttons
    }


    //draw text data
    glBindTexture(GL_TEXTURE_2D, ResourceData.FontSystem.fontBook[0]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //this->drawText(7, 12, "Koi Koi bites Kei Kei for 13 damage!");
    //this->drawGUIText(0.0, 0.0, "Centered Text");

    //Flip Windows
    SDL_GL_SwapWindow(sdlWindow);

    //exit(0);

}





