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
    protected:
    private:
        int windowWidth = 1280;
        int windowHeight = 720;
};

#endif // RENDERCORE_H
