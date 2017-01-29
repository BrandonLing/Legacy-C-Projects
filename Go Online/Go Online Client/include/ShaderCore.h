#ifndef SHADERCORE_H
#define SHADERCORE_H

#define GLEW_STATIC
#include <GL/glew.h>
#undef main

#include <string>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <GameDataCore.h>

extern GameDataCore GameData;

class ShaderCore
{
    public:
        void init();
        void quit();

        bool loadDefaultShaders(std::string shaderFileBaseName);
        void useDefaultShader();
        void useObjShader();

        GLuint defaultvShader;
        GLuint defaultfShader;
        GLuint defaultProg;
    protected:
    private:
};

#endif // SHADERCORE_H
