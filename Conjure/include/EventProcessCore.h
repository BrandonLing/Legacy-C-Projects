#ifndef EVENTPROCESSCORE_H
#define EVENTPROCESSCORE_H

//Error Dependencies
#include <iostream>

//Library Dependencies
#include <stdlib.h>
#include <SDL.h>

//Core Dependencies
#include <EventQueueCore.h>
#include <GameDataCore.h>
#include <MonsterCore.h>

extern bool introFlag;
extern bool quitFlag;

extern EventQueueCore EventQueue;
extern GameDataCore GameData;
extern MonsterCore MonsterProcessor;

class EventProcessCore
{
    public:
        void init();
        void quit();

        void processQueue();
    protected:
    private:
};

#endif // EVENTPROCESSCORE_H
