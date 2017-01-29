#ifndef INPUTCORE_H
#define INPUTCORE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>

//Core Dependencies
#include <EventCore.h>

extern EventCore Event;

class InputCore
{
    public:
        void init();
        void quit();
        void recv_inputs();

    protected:
    private:
};

#endif // INPUTCORE_H
