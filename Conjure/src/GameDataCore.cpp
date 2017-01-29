#include "GameDataCore.h"

void GameDataCore::init()
{
    //Init Constant vars
    this->playerBaseSpeed = 0.5;

    //Temp Stuff
        GameObject player;
        player.x = 0.0; player.y = 0.0;
        player.name = "Marona";
        player.type = 0;//player
        player.width = 8;
        player.height = 8;
        player.visible = true;
        player.collision = true;
        player.widthMask = player.width / 2;
        player.heightMask = player.height;
        player.spriteBook = 0.0;
        player.spriteIndex = 0;
        this->addGameObject(player);


        GameObject player2;
        player2.x = 5.0; player2.y = 4.4;
        player2.name = "Ashe";
        player2.type = 0;
        player2.width = 8;
        player2.height = 8;
        player2.visible = true;
        player2.collision = true;
        player2.widthMask = player2.width / 2;
        player2.heightMask = player2.height;
        player2.spriteBook = 0;
        player2.spriteIndex = 1;
        this->addGameObject(player2);

        GameObject player3;
        player3.x = 1.0; player3.y = 10.4;
        player3.name = "Walnut";
        player3.type = 0;
        player3.width = 8;
        player3.height = 8;
        player3.visible = true;
        player3.collision = true;
        player3.widthMask = player3.width / 2;
        player3.heightMask = player3.height;
        player3.spriteBook = 0;
        player3.spriteIndex = 2;
        this->addGameObject(player3);

    //Temp Stuff

    //Init Camera
    playerCam.init();
}

void GameDataCore::quit()
{

}

void GameDataCore::addGameObject(GameObject newObject)
{
    newObject.ID = this->ID;
    this->EntityVec.push_back(newObject);
    this->ID += 1;
}

bool GameDataCore::deleteGameObject(int deleteID)
{
    std::vector<GameObject>::iterator objectIter;
    for (objectIter = this->EntityVec.begin(); objectIter != this->EntityVec.end(); objectIter++)
    {
        if ( ( (*objectIter).ID ) == deleteID )
        {
            this->EntityVec.erase(objectIter);
            return false;
        }
    }
    return true; //error
}

int GameDataCore::getObjectCount()
{
    return (this->EntityVec.size());
}

void GameDataCore::setPlayerX(int ID, float newX)
{
    if (ID >= 0)
        this->EntityVec[ID].x = newX;
}

void GameDataCore::setPlayerY(int ID, float newY)
{
    if (ID >= 0)
        this->EntityVec[ID].y = newY;
}

void GameDataCore::setPlayerZ(int ID, float newZ)
{
    if (ID >= 0)
        this->EntityVec[ID].z = newZ;
}

float GameDataCore::getPlayerX(int ID)
{
    if (ID >= 0)
        return this->EntityVec[ID].x;
    else
        return 0;
}

float GameDataCore::getPlayerY(int ID)
{
    if (ID >= 0)
        return this->EntityVec[ID].y;
    else
        return 0;
}

float GameDataCore::getPlayerZ(int ID)
{
    if (ID >= 0)
        return this->EntityVec[ID].z;
    else
        return 0;
}

int GameDataCore::getEntityID(std::string objectName, int objectType)
{
    std::vector<GameObject>::const_iterator qIter;
    for (qIter = this->EntityVec.begin(); qIter != this->EntityVec.end(); qIter++)
    {
        GameObject examinedObject = *qIter;
        if (examinedObject.type == objectType)
        {
            if (!examinedObject.name.compare(objectName)) //Object was found;
            {
                return examinedObject.ID;
            }
        }
    }
    //Object was not found
    std::cout << "Error: GameCore cannot find entityID\n";
    return -1;
}

int GameDataCore::getPlayerWidth(int ID)
{
    if (ID >= 0)
        return this->EntityVec[ID].width;
    else
        return 0;
}

int GameDataCore::getPlayerHeight(int ID)
{
    if (ID >= 0)
        return this->EntityVec[ID].height;
    else
        return 0;
}

void GameDataCore::updateCamera()
{
    //Update Camera Position
    int ID = this->getEntityID(this->playerCharacter, 0);
    float camX = (this->getPlayerX(ID) + this->getPlayerWidth(ID) / 2);
    float camY = (this->getPlayerY(ID) + this->getPlayerHeight(ID) / 2);
    this->playerCam.model = glm::translate(glm::mat4(1.0f), glm::vec3(this->playerCam.xRight/2, this->playerCam.yHigh/2, 0.0f));
    this->playerCam.updateCamPos(camX, camY, 0);
    //std::cout << camX << "," << camY << "," << 0 << "\n";
    this->playerCam.updateCamTarget(camX, camY, -1.0f);
    this->playerCam.updateCamUpVec(0.0, 1.0, 0.0);
}

void GameDataCore::updateGameState()
{
    //find playerID
    int playerID = this->getEntityID(this->playerCharacter, 0);

    //get old position
    float oldX = this->getPlayerX(playerID);
    float oldY = this->getPlayerY(playerID);

    //Get Direction, Direction is 8 way. 0 at 12 o clock and going clockwise 0-7;
    //move player as well
    //Normalize Speed for diagonal directions
    this->playerSpeed = this->playerBaseSpeed;
    if ((this->playerXDir == 0) && (this->playerYDir > 0))
    {
        this->setPlayerY(playerID, oldY + this->playerSpeed);
        this->playerFacing = 0;
    }
    else if ((this->playerXDir > 0) && (this->playerYDir > 0))
    {
        this->playerSpeed = this->playerBaseSpeed * 0.70711; //1/sqrt(2)
        this->setPlayerX(playerID, oldX + this->playerSpeed);
        this->setPlayerY(playerID, oldY + this->playerSpeed);
        this->playerFacing = 1;
    }
    else if ((this->playerXDir > 0) && (this->playerYDir == 0))
    {
        this->setPlayerX(playerID, oldX + this->playerSpeed);
        this->playerFacing = 2;
    }
    else if ((this->playerXDir > 0) && (this->playerYDir < 0))
    {
        this->playerSpeed = this->playerBaseSpeed * 0.70711;//1/sqrt(2)
        this->setPlayerX(playerID, oldX + this->playerSpeed);
        this->setPlayerY(playerID, oldY - this->playerSpeed);
        this->playerFacing = 3;
    }
    else if ((this->playerXDir == 0) && (this->playerYDir < 0))
    {
        this->setPlayerY(playerID, oldY - this->playerSpeed);
        this->playerFacing = 4;
    }
    else if ((this->playerXDir < 0) && (this->playerYDir < 0))
    {
        this->playerSpeed = this->playerBaseSpeed * 0.70711;//1/sqrt(2)
        this->setPlayerX(playerID, oldX - this->playerSpeed);
        this->setPlayerY(playerID, oldY - this->playerSpeed);
        this->playerFacing = 5;
    }
    else if ((this->playerXDir < 0) && (this->playerYDir == 0))
    {
        this->setPlayerX(playerID, oldX - this->playerSpeed);
        this->playerFacing = 6;
    }
    else if ((this->playerXDir < 0) && (this->playerYDir > 0))
    {
        this->playerSpeed = this->playerBaseSpeed * 0.70711;//1/sqrt(2)
        this->setPlayerX(playerID, oldX - this->playerSpeed);
        this->setPlayerY(playerID, oldY + this->playerSpeed);
        this->playerFacing = 7;
    }
    //Print player facing
    //std::cout << "Player Facing: " << this->playerFacing << "\n";
}

void GameDataCore::talkToNPC()
{
    //getplayerID
    int playerID = this->getEntityID(this->playerCharacter, 0);

    //get coordinates of search point
    float nextX, nextY;
    float playerXLeft, playerXRight, playerYBot, playerYTop;
    playerXLeft = this->getPlayerX(playerID);
    playerYBot = this->getPlayerY(playerID);
    playerXRight = playerXLeft + this->getPlayerWidth(playerID);
    playerYTop = playerYBot + this->getPlayerHeight(playerID);

    switch(this->playerFacing)
    {
        case 0:
            nextX = (playerXLeft + playerXRight) / 2;
            nextY = playerYTop + this->npcSearchRange;
            break;
        case 1:
            nextX = playerXRight + this->npcSearchRange;
            nextY = playerYTop + this->npcSearchRange;
            break;
        case 2:
            nextX = playerXRight + this->npcSearchRange;
            nextY = (playerYBot + playerYTop) / 2;
            break;
        case 3:
            nextX = playerXRight + this->npcSearchRange;
            nextY = playerYBot - this->npcSearchRange;
            break;
        case 4:
            nextX = (playerXLeft + playerXRight) / 2;
            nextY = playerYBot - this->npcSearchRange;
            break;
        case 5:
            nextX = playerXLeft - this->npcSearchRange;
            nextY = playerYBot - this->npcSearchRange;
            break;
        case 6:
            nextX = playerXLeft - this->npcSearchRange;
            nextY = (playerYBot + playerYTop) / 2;
            break;
        case 7:
            nextX = playerXLeft - this->npcSearchRange;
            nextY = playerYTop + this->npcSearchRange;
            break;
    }

    //search for npc in direction
    int npcID = this->findNPCatLocation(nextX, nextY);

    //pull NPC dialogue
    if (npcID != -1)
    {//npc was found. initiate dialogue
        //TO DO: Initiate dialogue
        std::cout << npcID << "\n";
    }


 }

//This function returns the entity ID of a character with type 0 at a certain location.
int GameDataCore::findNPCatLocation(float xSearch, float ySearch)
{
    std::vector<GameObject>::const_iterator objIter;
    for (objIter = this->EntityVec.begin(); objIter != this->EntityVec.end(); objIter++)
    {
        float objXleft = (*objIter).x;
        float objXright = objXleft + (*objIter).widthMask;
        float objYbot = (*objIter).y;
        float objYtop = objYbot + (*objIter).heightMask;

        if ((xSearch >= objXleft) && (xSearch <= objXright))
        {
            if ((ySearch >= objYbot) && (ySearch <= objYtop))
            {
                std::cout << ((*objIter).name) << "\n";
                return ((*objIter).ID);
            }
        }
    }
    return -1;
}
