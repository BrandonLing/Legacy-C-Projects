#include "InputCore.h"

void InputCore::init()
{
    bool success = SDL_Init(SDL_INIT_EVENTS);
    if (success)
        printf("Error in Input Core: Cannot initialize events\n");
}

void InputCore::quit()
{
    SDL_Quit();
}

void InputCore::recv_inputs()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        int keyCode = event.key.keysym.sym;
        int type = event.type;
        int eHandle = Event.handleEvents(keyCode, type);
        //eHandle is 0 if handled.

    }
}
