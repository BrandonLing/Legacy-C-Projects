#include "SoundDataCore.h"

void SoundDataCore::init()
{
    //Init SDL Audio
    SDL_Init(SDL_INIT_AUDIO);

    //Init SDL Mixer
    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        std::cout << "Error initializing SDL Mixer\n";

    //Load Files
    this->loadAllMusic();
    this->loadAllSounds();


    //Mix_PlayMusic(this->musicBook[0], 3);
    //Mix_PlayChannel(-1, this->seBook[0], 0);
}

void SoundDataCore::quit()
{
    for (int i = 0; i < this->musicBook.size(); i++)
    {
        Mix_FreeMusic(this->musicBook[i]);
    }

    Mix_CloseAudio();
}

std::vector<std::string> SoundDataCore::getFileListing(std::string directory)
{
    DIR*    dir;
    dirent* pdir;
    std::vector<std::string> files;

    dir = opendir(directory.c_str());
    while (pdir = readdir(dir))
    {
        files.push_back(pdir->d_name);
    }

    //std::cout << files.size() << " files found\n";
    return files;
}

void SoundDataCore::loadAllSounds()
{
    std::string searchDir = "Resources/Sounds/";
    std::vector<std::string> fileListing = this->getFileListing(searchDir);
    for (unsigned int i = 0; i < fileListing.size(); i++)
    {
        //Find filetype
        std::string filetype;
        std::string letter;
        for (unsigned int j = (fileListing[i].size() - 1); j >= 0; j--)
        {
            letter = fileListing[i][j];
            if (letter.compare(".")) //not a period
                filetype.insert(0, letter);
            else //is a period
                break;
        }

        if (!filetype.compare("wav"))
        {
            std::string fileDest = searchDir;
            fileDest.append(fileListing[i]);
            this->loadSEFromFile(fileDest);
        }
    }
}

void SoundDataCore::loadSEFromFile(std::string filename)
{
    this->seBook.push_back(0);
    this->seBook[this->seBook.size() - 1] = Mix_LoadWAV(filename.c_str());

    if (this->seBook[this->seBook.size() - 1] == NULL)
        printf("Error : %s", Mix_GetError());
    /*else
        std::cout << "Loaded sound: " << filename << "\n";*/


}

void SoundDataCore::loadAllMusic()
{
    std::string searchDir = "Resources/Music/";
    std::vector<std::string> fileListing = this->getFileListing(searchDir);
    for (unsigned int i = 0; i < fileListing.size(); i++)
    {
        //Find filetype
        std::string filetype;
        std::string letter;
        for (unsigned int j = (fileListing[i].size() - 1); j >= 0; j--)
        {
            letter = fileListing[i][j];
            if (letter.compare(".")) //not a period
                filetype.insert(0, letter);
            else //is a period
                break;
        }

        if (!filetype.compare("mp3"))
        {
            std::string fileDest = searchDir;
            fileDest.append(fileListing[i]);
            this->loadMusicFromFile(fileDest);
        }
    }
}


void SoundDataCore::loadMusicFromFile(std::string filename)
{
    this->musicBook.push_back(0);
    this->musicBook[this->musicBook.size() - 1] = Mix_LoadMUS(filename.c_str());

    if (this->musicBook[this->musicBook.size() - 1] == NULL)
        printf("Error : %s", Mix_GetError());
    /*else
        std::cout << "Loaded music: " << filename << "\n";*/

}


