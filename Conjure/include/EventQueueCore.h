#ifndef EVENTQUEUECORE_H
#define EVENTQUEUECORE_H

//Error Dependencies
#include <iostream>

//Library Dependencies
#include <list>
#include <SDL.h>

class EventQueueCore
{
    public:
        void init();
        void quit();

        //Events for SDL Inputs from InputCore
        void postInputEvent(int keyCode, int type);
        void postMouseEvent(int keyCode, int xrel, int yrel);
        void postQuitEvent();
        std::list<int>::iterator eventExists(int origin, int identifier, int flag);

        //eQueue is the raw data of the event queue. Format is as follows:
            //For Keyboard Input Events from the Input Core (ID = 0): {0, keyCode, type};
                                           ////Monster Core (ID = 1) : {1, movementDirection, unused}
        std::list<int> eQueue;
    protected:
    private:



};

#endif // EVENTQUEUECORE_H
