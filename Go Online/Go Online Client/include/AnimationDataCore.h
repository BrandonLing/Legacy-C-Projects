#ifndef ANIMATIONDATACORE_H
#define ANIMATIONDATACORE_H

#include <GL/glew.h>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream> //file operations
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>

#include <Point.h>
#include <Face.h>
#include <ObjModel.h>
#include <AnimationData.h>

//This class manages animation data
class AnimationDataCore
{
    public:
        void init();
        void quit();
        void loadAllAnimations();

        //file io
        std::vector<std::string> getFileListing(std::string directory);

        int loadModel(std::string filename, AnimationData &keyFrames);
        void parseObjLine(std::string line, ObjModel &obj);
        void parseMtlLine(std::string line, ObjModel &obj);
        void loadTexturefromPNG(std::string filepath, ObjModel &obj);

        std::vector<AnimationData> animationLibrary;
    protected:
    private:
};

#endif // ANIMATIONDATACORE_H
