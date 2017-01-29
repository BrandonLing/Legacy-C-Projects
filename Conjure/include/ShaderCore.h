#ifndef SHADERCORE_H
#define SHADERCORE_H

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#undef main

#include <string>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GameDataCore.h>
#include <ResourceCore.h>
#include <MapCore.h>

extern GameDataCore GameData;
extern ResourceCore ResourceData;
extern MapCore MapData;

class ShaderCore
{
    public:
        void init();
        void quit();

        bool loadDefaultShaders(std::string shaderFileBaseName);
        bool loadTextShaders(std::string shaderFileBaseName);
        bool loadBackgroundShaders(std::string shaderFileBaseName);
        bool loadTileShaders(std::string shaderFileBaseName);

        void update();

        void useDefaultShader();
        void useTextShader();
        void useGUITextShader();
        void useBGShader();
        void useTileShader();

        GLuint defaultvShader;
        GLuint defaultfShader;
        GLuint defaultProg;

        GLuint textvShader;
        GLuint textfShader;
        GLuint textProg;

        GLuint backgroundvShader;
        GLuint backgroundfShader;
        GLuint backgroundProg;

        GLuint tilevShader;
        GLuint tilefShader;
        GLuint tileProg;

    protected:
    private:
};

#endif // SHADERCORE_H
