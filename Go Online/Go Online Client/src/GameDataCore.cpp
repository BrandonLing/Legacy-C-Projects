#include "GameDataCore.h"

void GameDataCore::init()
{
    //Init player camera
    Camera playerCam;
    playerCam.init();
    this->cameraList.push_back(playerCam);

    //Init player
    this->player1.x = -5.0; this->player1.y = 0.0; this->player1.z = 0.0;

    //init some game objects
    GameObject box0(0.0, -0.93, 0.0, 100.0, 1.0, 100.0);
    box0.meshID = 0;
    this->entityList.push_back(box0);

    GameObject box1(25.0, 5.0, 10.0, 1.0, 1.0, 1.0);
    box1.meshID = 0;
    this->entityList.push_back(box1);

    GameObject box2(10.0, 0.0, 0.0, 1.0, 2.0, 1.0);
    box2.meshID = 0;
    this->entityList.push_back(box2);

    GameObject human(5.0, 0.0, 0.0);
    human.xscale = 0.25;human.yscale = 0.25;human.zscale = 0.25;
    human.meshID = 1;
    this->entityList.push_back(human);
}

void GameDataCore::quit()
{

}

void GameDataCore::updateCamera()
{
    //get player facing
    float zOffsetFactor = 20.0;
    float backAngle = this->player1.yaw - 180;
    float degreesToRadian = 180/3.14;
    float camdX = cos(backAngle / degreesToRadian) * zOffsetFactor;
    float camdZ = sin(backAngle / degreesToRadian) * zOffsetFactor;
    float camdY = 3.0;

    //get player position
    float camX = this->player1.x + camdX;
    float camY = this->player1.y + camdY;
    float camZ = this->player1.z + camdZ;

    float playerPitch = this->player1.pitch + this->cameraList[0].pitchCorrAngle; //rotation about the z axis
    float playerYaw = this->player1.yaw - this->cameraList[0].yawCorrAngle; //rotation about the y axis

    //acquire camera target
    float xTarget = camX + cos(playerYaw / degreesToRadian);
    float yTarget = camY + sin(playerPitch / degreesToRadian) - 0.2;
    float zTarget = camZ + sin(playerYaw / degreesToRadian);
    /*
    float xTarget = camX + cos(playerYaw / degreesToRadian);
    float yTarget = camY + sin(playerPitch / degreesToRadian);
    float zTarget = camZ + sin(playerYaw / degreesToRadian);*/

    //Update Camera Position
    this->cameraList[0].updateCamPos(camX, camY, camZ);
    this->cameraList[0].updateCamTarget(xTarget, yTarget, zTarget);
    this->cameraList[0].updateMVPMatrix();

}

void GameDataCore::updateGameState()
{
    this->entityList[3].x = this->player1.x;
    this->entityList[3].y = this->player1.y;
    this->entityList[3].z = this->player1.z;
    this->entityList[3].pitch = this->player1.yaw;
}






