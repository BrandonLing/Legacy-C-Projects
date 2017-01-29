#include <main.h>

Client Network;
RenderCore Render;
InputCore Input;
EventCore Event;
GameDataCore GameData;
ShaderCore Shader;
ModelDataCore ModelData;
SoundDataCore SoundData;
AnimationDataCore AnimationLibrary;

bool quitFlag = false;

int main(int argc, char* argv[])
{
    init();

    while(!quitFlag)
    {
        //Gather Player Input Data
        Input.recv_inputs();

        //Gather Packet data
        Network.recvMessage();

        //Update GameState
        GameData.updateCamera();
        GameData.updateGameState();

        //Render
        //Shader.update();
        Render.render();

        //Delay
        Sleep(17);
        //std::cout << __FUNCTION__ << "\n";
    }

    quit();
    return 0;
}

void init()
{
    Network.init();
    Render.init();
    GameData.init();
    Input.init();
    Event.init();
    Shader.init();
    ModelData.init();
    SoundData.init();
    AnimationLibrary.init();
}

void quit()
{
    AnimationLibrary.quit();
    SoundData.quit();
    ModelData.quit();
    Shader.quit();
    Event.quit();
    GameData.quit();
    Input.quit();
    Render.quit();
    Network.quit();
}
