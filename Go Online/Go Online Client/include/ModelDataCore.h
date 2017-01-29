#ifndef MODELDATACORE_H
#define MODELDATACORE_H

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

//This class holds static mesh data
class ModelDataCore
{
    public:
        void init();
        void quit();
        void loadAllObjects();

        //file io
        std::vector<std::string> getFileListing(std::string directory);

        int loadModel(std::string filename);
        void parseObjLine(std::string line, ObjModel &obj);
        void parseMtlLine(std::string line, ObjModel &obj);
        void loadTexturefromPNG(std::string filepath, ObjModel &obj);

        std::vector<ObjModel> meshLibrary;
    protected:
    private:
};

#endif // MODELDATACORE_H
