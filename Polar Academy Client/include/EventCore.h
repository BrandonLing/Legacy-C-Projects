#ifndef EVENTCORE_H
#define EVENTCORE_H

#include <SDL2/SDL.h>
#include <iostream>

//Core Dependencies
#include <ClientSend.h>

extern ClientSend ClientOut;

extern bool quitFlag;

class EventCore
{
    public:
        void init();
        void quit();
        //Events for SDL Inputs from InputCore
        int handleEvents(int keyCode, int type);
    protected:
    private:
};

#endif // EVENTCORE_H
