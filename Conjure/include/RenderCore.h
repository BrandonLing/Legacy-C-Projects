#ifndef RENDERCORE_H
#define RENDERCORE_H

#define GLEW_STATIC
#include <GL/glew.h>

//Error Dependencies
#include <iostream>
#include <stdio.h>

//Library Dependencies
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <list>
#include <vector>
#include <IsoConversion.h>
#include <math.h> //fmod

//Core Dependencies
#include <GameDataCore.h>
#include <GameObject.h>
#include <ShaderCore.h>
#include <ResourceCore.h>
#include <MapCore.h>

extern GameDataCore GameData;
extern ResourceCore ResourceData;
extern ShaderCore Shaders;
extern MapCore MapData;

extern bool introFlag;
extern bool quitFlag;

//Front face is counter clockwise
class RenderCore
{
    public:
        void init();
        void quit();
        void glRefreshViewport();
        void render();

        //Utility
        void printGLInfo();

        std::string windowTitle;
        SDL_Window *sdlWindow;
        SDL_GLContext glContext;

        //Drawing functions
        void drawText(float x, float y, std::string message);
        void drawGUIText(float x, float y, std::string message);
        void drawEntities(int entityType);

        void drawMap();
        void drawBackground();
    protected:
    private:
        int windowWidth = 1280;
        int windowHeight = 720;

        GLuint dynamicEntityBuffer;
        GLuint dynamicTextureBuffer;
        GLuint dynamicVAO;
};

#endif // RENDERCORE_H
