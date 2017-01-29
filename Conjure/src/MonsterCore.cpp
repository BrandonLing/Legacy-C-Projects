#include "MonsterCore.h"

void MonsterCore::init()
{

}

void MonsterCore::quit()
{

}

void MonsterCore::updateMonstersAI()
{
    if (monsterAIon)
    {
        std::vector<GameObject>::iterator qIter;
        int entityID = 0;
        for (qIter = GameData.EntityVec.begin(); qIter != GameData.EntityVec.end(); qIter++)
        {
            clock_t currentClock = clock();
            clock_t block = (*qIter).aiBlockTimer - currentClock;
            if (block < 0)//do an action
            {
                int type = (*qIter).type;
                bool snapped = (*qIter).snapped;
                if ((type == 1) && snapped)//It's a monster. Do something
                {
                    //check if hostile
                    if ((*qIter).hostile) //Calculate hostile AI path
                    {//ie. move to target, attack, or cast spell
                        this->chooseBasicHostileAction(entityID);
                    }
                    else //calculate non-hostile AI path
                    {//ie. randomly move around or rest
                        this->chooseBasicNonHostileAction(entityID);
                    }

                }
            }
            entityID += 1;
        }
    }
}

void MonsterCore::chooseBasicNonHostileAction(int entityID)
{
    int choice = rand() % 20; //random number 0-19
    switch (choice)
    {
        case 0: //up
            GameData.EntityVec[entityID].yDir = 1;
            break;
        case 1: //right
            GameData.EntityVec[entityID].xDir = 1;
            break;
        case 2: //down
            GameData.EntityVec[entityID].yDir = -1;
            break;
        case 3: //left
            GameData.EntityVec[entityID].xDir = -1;
            break;
    }
    GameData.delayEntity(entityID, 16);
    //std::cout << clock() << "\n";
}

//returns the entity ID of the closest entity and their squared distance apart
std::vector<int> MonsterCore::findClosestTarget(int myID)
{
    int closestID = -1; //holds ID number of the closest entity
    float smallestDist = -1;
    int entityID = 0;
    float myX = GameData.EntityVec[myID].x;
    float myY = GameData.EntityVec[myID].y;

    std::vector<GameObject>::iterator qIter;
    for (qIter = GameData.EntityVec.begin(); qIter != GameData.EntityVec.end(); qIter++)
    {
        if (entityID != myID)
        {
            float yourX = GameData.EntityVec[entityID].x;
            float yourY = GameData.EntityVec[entityID].y;
            float dist = ((yourY - myY) * (yourY - myY)) + ((yourX - myX) * (yourX - myX));
            if ((smallestDist == -1) || (dist < smallestDist))
            {
                smallestDist =  dist;
                closestID = entityID;
            }
        }

        entityID += 1;
    }
    //std::cout << "Closest Target is " << GameData.EntityVec[closestID].name << ". " << smallestDist << "spaces away\n";
    std::vector<int> output;
    output.push_back(closestID);
    output.push_back(smallestDist);
    return output;
}


//returns -1 if no target was found.
//returns 1 if an attack should occur
//returns 0 otherwise
int MonsterCore::chooseBasicHostileAction(int entityID)
{
    std::vector<int> closestTargetInfo = this->findClosestTarget(entityID);
    int targetID = closestTargetInfo[0];
    int distance = closestTargetInfo[1];

    //No target found
    if (targetID == -1)
    {
        GameData.delayEntity(entityID, 16);
        return (-1);
    }

    //Target found in the distance. Walk closer
    int vX = GameData.EntityVec[targetID].x - GameData.EntityVec[entityID].x;
    int vY = GameData.EntityVec[targetID].y - GameData.EntityVec[entityID].y;

    if (vX > 0)
        vX = 1;
    else if (vX < 0)
        vX = -1;
    else if (vX == 0)
        vX = 0;

    if (vY > 0)
        vY = 1;
    else if (vY < 0)
        vY = -1;
    else if (vY == 0)
        vY = 0;

    //if diagonally away, randomly pick a direction
    if ((vX != 0) && (vY != 0))
    {
        int randNo = rand() % 2;
        if (randNo == 1)
            vX = 0;
        else
            vY = 0;
    }
    //std::cout << "Move towards " << vX << "," << vY << "\n";
    GameData.EntityVec[entityID].xDir = vX;
    GameData.EntityVec[entityID].yDir = vY;

    //set facing
    if      (vX == 1)
        GameData.EntityVec[entityID].currentPFacing = 2;
    else if (vX == -1)
        GameData.EntityVec[entityID].currentPFacing = 6;
    else if (vY == 1)
        GameData.EntityVec[entityID].currentPFacing = 0;
    else if (vY == -1)
        GameData.EntityVec[entityID].currentPFacing = 1;

    //target found in attack distance
    if (distance == 1)
    {
        GameData.handleAttack(targetID, entityID);
        GameData.delayEntity(entityID, 16);
        return 1;
    }

    //delay next action
    GameData.delayEntity(entityID, 16);
    return 0;
}

void MonsterCore::moveMonsterUp(int ID)
{
    GameData.EntityVec[ID].yDir = 1;
}

void MonsterCore::moveMonsterRight(int ID)
{
    GameData.EntityVec[ID].xDir = 1;
}

void MonsterCore::moveMonsterDown(int ID)
{
    GameData.EntityVec[ID].yDir = -1;
}

void MonsterCore::moveMonsterLeft(int ID)
{
    GameData.EntityVec[ID].xDir = -1;
}

