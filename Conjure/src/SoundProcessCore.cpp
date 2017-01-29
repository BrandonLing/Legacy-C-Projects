#include "SoundProcessCore.h"

void SoundProcessCore::init()
{
    //Init SDL Audio
    SDL_Init(SDL_INIT_AUDIO);

    //Init SDL Mixer
    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        std::cout << "Error initializing SDL Mixer\n";

    //Load Files
    this->loadAllMusic();
    //Mix_PlayMusic(this->musicBook[0], 3);

    this->loadAllSounds();
}

void SoundProcessCore::quit()
{
    for (int i = 0; i < this->musicCount; i++)
    {
        Mix_FreeMusic(this->musicBook[i]);
    }

    Mix_CloseAudio();
}

void SoundProcessCore::loadAllMusic()
{
    this->loadMusicFromFile("Resources/classical.mp3");
}

void SoundProcessCore::loadMusicFromFile(std::string filename)
{
    this->musicBook.push_back(0);
    this->musicBook[this->musicCount] = Mix_LoadMUS(filename.c_str());


    if (this->musicBook[this->musicCount] == NULL)
        printf("Error : %s", Mix_GetError());

    this->musicCount += 1;
}

void SoundProcessCore::loadAllSounds()
{
    this->loadSEFromFile("Resources/assail.wav");
}

void SoundProcessCore::loadSEFromFile(std::string filename)
{
    this->seBook.push_back(0);
    this->seBook[this->seCount] = Mix_LoadWAV(filename.c_str());


    if (this->seBook[this->seCount] == NULL)
        printf("Error : %s", Mix_GetError());

    this->seCount += 1;
}

//playSounds goes through the SoundQueue and plays the sound effect index. It then removes it from the queue
void SoundProcessCore::playSounds()
{
    int soundQueueSize = SoundQueue.seQueue.size();
    for(int i = 0; i < soundQueueSize; i++)
    {
        int seIndex = SoundQueue.seQueue[i];
        Mix_PlayChannel(-1, this->seBook[seIndex], 0);
    }

    SoundQueue.seQueue.clear();
}

