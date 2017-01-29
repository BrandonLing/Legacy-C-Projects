#ifndef TEXTUREDATACORE_H
#define TEXTUREDATACORE_H

#include <iostream>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class TextureDataCore
{
    public:
        void init();
        void quit();

        void loadTexturefromPNG(std::string filepath);
    protected:
    private:
};

#endif // TEXTUREDATACORE_H
