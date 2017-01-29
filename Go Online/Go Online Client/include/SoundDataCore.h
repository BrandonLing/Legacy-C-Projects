#ifndef SOUNDDATACORE_H
#define SOUNDDATACORE_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <dirent.h>

class SoundDataCore
{
    public:
        void init();
        void quit();

        std::vector<std::string> getFileListing(std::string directory);

        //Music
        void loadAllMusic();
        void loadMusicFromFile(std::string filename);

        std::vector<Mix_Music*> musicBook;


        //Sound Effects
        void loadAllSounds();
        void loadSEFromFile(std::string filename);

        std::vector<Mix_Chunk*> seBook;

    protected:
    private:
};

#endif // SOUNDDATACORE_H
