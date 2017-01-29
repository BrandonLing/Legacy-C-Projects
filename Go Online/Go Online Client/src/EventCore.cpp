#include "EventCore.h"

void EventCore::init()
{
    this->upFlag = false;
    this->downFlag = false;
    this->leftFlag = false;
    this->rightFlag = false;
}

void EventCore::quit()
{

}

int EventCore::handleMouseEvents(SDL_Event event)
{
    int deltaXMouse = event.motion.xrel;
    int deltaYMouse = event.motion.yrel;

    if (deltaXMouse > 0)
    {
        GameData.player1.changeYaw(GameData.player1.turnSpd);
    }
    else if (deltaXMouse < 0)
    {
        GameData.player1.changeYaw(-GameData.player1.turnSpd);
    }

    if (GameData.cameraList[0].yFlag)
    {
        if (deltaYMouse > 0)
        {
            GameData.player1.changePitch(-GameData.player1.lookSpd);
        }
        else if (deltaYMouse < 0)
        {
            GameData.player1.changePitch(+GameData.player1.lookSpd);
        }
    }
    return 1;
}

int EventCore::handleKeyboardEvents()
{
    if (GameData.cameraList[0].strafeFlag)
    {
        if (this->leftFlag == true)
        {
            float leftAngle = GameData.player1.yaw - 90;
            float degreesToRadian = 180/3.14;
            GameData.player1.x += cos(leftAngle / degreesToRadian)* GameData.player1.strafeSpdFactor;
            GameData.player1.z += sin(leftAngle / degreesToRadian)* GameData.player1.strafeSpdFactor;
        }

        if (this->rightFlag == true)
        {
            float rightAngle = GameData.player1.yaw + 90;
            float degreesToRadian = 180/3.14;
            GameData.player1.x += cos(rightAngle / degreesToRadian)* GameData.player1.strafeSpdFactor;
            GameData.player1.z += sin(rightAngle / degreesToRadian)* GameData.player1.strafeSpdFactor;
        }
    }

    if (this->upFlag == true)
    {
        float degreesToRadian = 180/3.14;
        GameData.player1.x += cos(GameData.player1.yaw / degreesToRadian) * GameData.player1.moveSpdFactor;
        GameData.player1.z += sin(GameData.player1.yaw / degreesToRadian) * GameData.player1.moveSpdFactor;
    }

    if (this->downFlag == true)
    {
        float degreesToRadian = 180/3.14;
        GameData.player1.x -= cos(GameData.player1.yaw / degreesToRadian) * GameData.player1.moveSpdFactor;
        GameData.player1.z -= sin(GameData.player1.yaw / degreesToRadian) * GameData.player1.moveSpdFactor;
    }
    return 0;
}

int EventCore::updateKeyboardState(int keyCode, int type)
{
    switch (type)
    {
        case SDL_KEYDOWN:
            //strafe left
            if ((keyCode == SDLK_LEFT) || (keyCode == SDLK_a))
            {
                this->leftFlag = true;
            }
            //strafe right
            else if ((keyCode == SDLK_RIGHT) || (keyCode == SDLK_d))
            {
                this->rightFlag = true;
            }
            //walk forward
            else if ((keyCode == SDLK_UP) || (keyCode == SDLK_w))
            {
                this->upFlag = true;
            }
            //walk backwards
            else if ((keyCode == SDLK_DOWN) || (keyCode == SDLK_s))
            {
                this->downFlag = true;
            }

            return 0;
        case SDL_KEYUP:
            if ((keyCode == SDLK_LEFT) || (keyCode == SDLK_a))
            {
                this->leftFlag = false;
            }
            //strafe right
            else if ((keyCode == SDLK_RIGHT) || (keyCode == SDLK_d))
            {
                this->rightFlag = false;
            }
            //walk forward
            else if ((keyCode == SDLK_UP) || (keyCode == SDLK_w))
            {
                this->upFlag = false;
            }
            //walk backwards
            else if ((keyCode == SDLK_DOWN) || (keyCode == SDLK_s))
            {
                this->downFlag = false;
            }
            return 0;
    }

    return 1;
}

