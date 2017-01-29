#ifndef GAMEDATACORE_H
#define GAMEDATACORE_H

#include <vector>
#include <iostream>

#include <Camera.h>
#include <GameObject.h>


class GameDataCore
{
    public:
        void init();
        void quit();

        //Camera controls
        GameObject player1;
        void updateCamera();
        void updateGameState();

        std::vector<GameObject> entityList;
        std::vector<Camera> cameraList;
    protected:
    private:
};

#endif // GAMEDATACORE_H
