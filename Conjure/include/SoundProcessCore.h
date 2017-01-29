#ifndef SOUNDPROCESSCORE_H
#define SOUNDPROCESSCORE_H

#include <stdio.h>
#include <iostream>

#include <vector>
#include <SDL.h>
#include <SDL2/SDL_mixer.h>

#include <SoundQueueCore.h>

extern SoundQueueCore SoundQueue;

class SoundProcessCore
{
    public:
        void init(); //loads all sound files
        void quit();
        void loadAllMusic();
        void loadAllSounds();
        void loadSEFromFile(std::string filename);
        void loadMusicFromFile(std::string filename);

        //Library of music
        int musicCount = 0;
        std::vector<Mix_Music*> musicBook;

        //Libary of Sounds
        int seCount = 0;
        std::vector<Mix_Chunk*> seBook;

        void playSounds();
    protected:
    private:
};

#endif // SOUNDPROCESSCORE_H
