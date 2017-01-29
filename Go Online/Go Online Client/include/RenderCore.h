#ifndef RENDERCORE_H
#define RENDERCORE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

#include <ShaderCore.h>
#include <ModelDataCore.h>
#include <GameDataCore.h>
#include <GameObject.h>
#include <Face.h>

extern ShaderCore Shader;
extern ModelDataCore ModelData;
extern GameDataCore GameData;

class RenderCore
{
    public:
        void init();
        void quit();
        void glRefreshViewport();
        void render();

        void renderGameObject(GameObject obj);
        void renderAllEntities();

        //Utility
        void printGLInfo();

        std::string windowTitle;
        SDL_Window *sdlWindow;
        SDL_GLContext glContext;
    protected:
    private:
        int windowWidth;
        int windowHeight;

        GLuint dynamicEntityBuffer;
        GLuint dynamicTextureBuffer;
        GLuint dynamicVAO;
};

#endif // RENDERCORE_H
