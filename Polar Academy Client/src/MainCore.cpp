#include "MainCore.h"

//Initialize singletons
InputCore Input;
ClientSend ClientOut;
ClientRecv ClientIn;
RenderCore Render;
EventCore Event;

bool quitFlag = false;

int main(int argc, char* argv[])
{
    init_systems();

    while(!quitFlag)
    {
        //Get User Inputs
        Input.recv_inputs();

        //Receive New Data if Available
        ClientIn.recvMessage();

        //Update GameState

        //Render Data
        Render.render();

        //Sleep for duration of framestep
            //TODO: Make this consider calculation times with time.h
        Sleep(17);
        //return 0; //For one pass testing
    }

    quit_systems();
    return 0;
}

void init_systems()
{
    Input.init();
    ClientIn.init();
    ClientOut.init();
    Render.init();
    Event.init();
}

void quit_systems()
{
    Event.quit();
    Render.quit();
    ClientOut.quit();
    ClientIn.quit();
    Input.quit();
}
