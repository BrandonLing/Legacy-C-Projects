#ifndef INPUTCORE_H
#define INPUTCORE_H

//Error Dependencies
#include <iostream>
#include <stdio.h>

//Library Dependencies
#include <SDL.h>

//Core Dependencies
#include <EventQueueCore.h>

extern EventQueueCore EventQueue;

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
