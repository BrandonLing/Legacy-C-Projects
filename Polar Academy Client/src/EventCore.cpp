#include "EventCore.h"

void EventCore::init()
{

}

void EventCore::quit()
{

}

int EventCore::handleEvents(int keyCode, int type)
{
    switch (type)
    {
        case SDL_KEYDOWN:
            ClientOut.sendMessage("Hello Server\n");
            return 0;
        case SDL_KEYUP:

            return 0;
        case SDL_QUIT:
            quitFlag = true;
            return 0;
    }

    return 1;
}

