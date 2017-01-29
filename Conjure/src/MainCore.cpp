#include "MainCore.h"

//Init Global Vars
bool quitFlag = false;
bool introFlag = false;

//Init Singleton Classes
InputCore Input;
RenderCore Render;
GameDataCore GameData;
ShaderCore Shaders;
EventQueueCore EventQueue;
EventProcessCore EventProcessor;
ResourceCore ResourceData;
MapCore MapData;
MonsterCore MonsterProcessor;
SoundQueueCore SoundQueue;
SoundProcessCore SoundProcessor;

int main(int argc, char* argv[])
{
    //Init Game Systems
    init_systems();

    GameData.initIntro();

    //Play Intro
    while (!introFlag)
    {
        //get clocktime
        clock_t starttime = clock();

        //Get User Inputs
        Input.recv_inputs();

        //Process Event Queue
        EventProcessor.processQueue(); //For Inputs

        //Update Camera Position
        GameData.updateCamera();
        Shaders.update();

        //Render Data
        Render.render();

        //Play Sounds
        SoundProcessor.playSounds();

        //get clock duration of time step
        clock_t endtime = clock();
        int diffTime = (endtime - starttime)/CLOCKS_PER_SEC;
        float sleepDuration = ((1000.0/frameRate) - diffTime) + 1.0;

        //Sleep for remainder of duration of framestep
        if (sleepDuration >= 0)
            Sleep(sleepDuration);

        //introFlag = true;
    }

    GameData.resetGame();
    GameData.init_Game();
    //Enter Game
    while(!quitFlag)
    {
        //get clocktime
        clock_t starttime = clock();

        //Get User Inputs
        Input.recv_inputs();

        //Process Event Queue
        EventProcessor.processQueue(); //For Inputs

        //Run AI - unneccessary for new game mechanic
        //MonsterProcessor.updateMonstersAI();
        //Update Game Step
        GameData.updateGameState();

        //Update Camera Position
        GameData.updateCamera();
        Shaders.update();

        //Render Data
        Render.render();

        //Play Sounds
        SoundProcessor.playSounds();

        //get clock duration of time step
        clock_t endtime = clock();
        int diffTime = (endtime - starttime)/CLOCKS_PER_SEC;
        float sleepDuration = ((1000.0/frameRate) - diffTime) + 1.0;

        //Sleep for remainder of duration of framestep
        //if (sleepDuration >= 0)
            Sleep(sleepDuration);

    }

    quit_systems();
    return 0;
}

void init_systems()
{
    Input.init();
    Render.init();
    ResourceData.init();
    GameData.init();
    Shaders.init();
    EventQueue.init();
    EventProcessor.init();
    MapData.init();
    MonsterProcessor.init();
    SoundQueue.init();
    SoundProcessor.init();
}

void quit_systems()
{
    SoundProcessor.quit();
    SoundQueue.quit();
    MonsterProcessor.quit();
    MapData.quit();
    EventProcessor.quit();
    ResourceData.quit();
    EventQueue.quit();
    Shaders.quit();
    GameData.quit();
    Render.quit();
    Input.quit();

}
