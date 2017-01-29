#ifndef EVENTCORE_H
#define EVENTCORE_H

#include <SDL2/SDL.h>
#include <iostream>

#include <GameDataCore.h>

extern GameDataCore GameData;
extern bool quitFlag;

class EventCore
{
    public:
        void init();
        void quit();
        //Events for SDL Inputs from InputCore
        int handleMouseEvents(SDL_Event event);
        int updateKeyboardState(int keyCode, int type);
        int handleKeyboardEvents();

        bool leftFlag, rightFlag, upFlag, downFlag;
    protected:
    private:
};

#endif // EVENTCORE_H
