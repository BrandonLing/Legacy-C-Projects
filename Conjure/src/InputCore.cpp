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
        switch (type)
        {
            case SDL_KEYDOWN: //fallthrough
            case SDL_KEYUP:
                EventQueue.postInputEvent(keyCode, type);
                break;
            case SDL_MOUSEMOTION:
                EventQueue.postMouseEvent(1, event.motion.xrel, event.motion.yrel);
                //std::cout << event.motion.xrel << "," << event.motion.yrel << "\n";
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    EventQueue.postMouseEvent(2, event.button.x, event.button.y);
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    EventQueue.postMouseEvent(3, event.button.x, event.button.y);
                //std::cout << "Mouse at " << event.button.x << "," << event.button.y << "\n";
                break;
            case SDL_QUIT:
                EventQueue.postQuitEvent();
                break;
        }


    }
}
