#ifndef SOUNDQUEUECORE_H
#define SOUNDQUEUECORE_H

#include <vector>
#include <SDL2/SDL_mixer.h>

class SoundQueueCore
{
    public:
        void init();
        void quit();

        std::vector<int> seQueue;
    protected:
    private:
};

#endif // SOUNDQUEUECORE_H
