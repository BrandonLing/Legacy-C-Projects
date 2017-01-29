#include "MainCore.h"

//Initialize Singleton Classes
ServerCore Server;
PlayerDataCore PlayerData;

int main(int argc, char* argv[])
{
    init_systems();


    while(!Server.quitFlag)
    {
        //Receive Server Events
        Server.recvMessage();

        //Update Game State

        //Broadcast Server Information (Player Positions)

        //Set FrameRate
        Sleep(34);
    }


    quit_systems();
    return 0;
}


void init_systems()
{
    Server.init();
    PlayerData.init();
}

void quit_systems()
{
    PlayerData.quit();
    Server.quit();
}
