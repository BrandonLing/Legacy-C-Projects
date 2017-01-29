#include "CollisionProcessCore.h"

void CollisionProcessCore::init()
{

}

void CollisionProcessCore::quit()
{

}

void CollisionProcessCore::processCollisions()
{
    //std::cout << CollisionChecker.collideQueue.size() << " Collisions Detected\n";
    std::vector<CollideEvent>::iterator collisionIter;
    for (collisionIter = CollisionChecker.collideQueue.begin(); collisionIter != CollisionChecker.collideQueue.end(); collisionIter++)
    {
        //get playerID
        int playerID = GameData.getEntityID(GameData.playerCharacter, 0);

        //examine objects
        std::vector<int> collisionObj = (*collisionIter).collidedObjects;
        int firstObjID, secondObjID;

        //firstObjID is set to playerID
        firstObjID = collisionObj[0];
        if (firstObjID == playerID)
            secondObjID = collisionObj[1];
        else
        {
            firstObjID = collisionObj[1];
            secondObjID = collisionObj[0];
        }
        //Print ID first trouble shooting
        //std::cout << collisionObj[0] << "," << collisionObj[1] << "\n";

        //find delta x
        float deltaX = this->calculateDeltaX(firstObjID, secondObjID);

        //find delta y
        float deltaY = this->calculateDeltaY(firstObjID, secondObjID);

        //get direction vector
        int direction = this->getDirectionVector(firstObjID, secondObjID);
        //std::cout << "Direction: " << direction << "\n";

        //correct collision by moving player by comparing deltaX and deltaY
        if (deltaX < deltaY) //correct collision in X direction
        {
            float playerX = GameData.getPlayerX(firstObjID);
            switch(direction)
            {
                case 0:
                    GameData.setPlayerX(firstObjID, playerX - deltaX);
                    break;
                case 1:
                    GameData.setPlayerX(firstObjID, playerX - deltaX);
                    break;
                case 2:
                    GameData.setPlayerX(firstObjID, playerX - deltaX);
                    break;
                case 3:
                    GameData.setPlayerX(firstObjID, playerX - deltaX);
                    break;
                case 4:
                    GameData.setPlayerX(firstObjID, playerX + deltaX);
                    break;
                case 5:
                    GameData.setPlayerX(firstObjID, playerX + deltaX);
                    break;
                case 6:
                    GameData.setPlayerX(firstObjID, playerX + deltaX);
                    break;
                case 7:
                    GameData.setPlayerX(firstObjID, playerX + deltaX);
                    break;
            }
        }
        else //correct collision in Y direction
        {
            float playerY = GameData.getPlayerY(firstObjID);
            switch(direction)
            {
                case 7:
                    GameData.setPlayerY(firstObjID, playerY - deltaY);
                    break;
                case 0:
                    GameData.setPlayerY(firstObjID, playerY - deltaY);
                    break;
                case 1:
                    GameData.setPlayerY(firstObjID, playerY - deltaY);
                    break;
                case 2:
                    GameData.setPlayerY(firstObjID, playerY - deltaY);
                    break;
                case 3:
                    GameData.setPlayerY(firstObjID, playerY + deltaY);
                    break;
                case 4:
                    GameData.setPlayerY(firstObjID, playerY + deltaY);
                    break;
                case 5:
                    GameData.setPlayerY(firstObjID, playerY + deltaY);
                    break;
                case 6:
                    GameData.setPlayerY(firstObjID, playerY + deltaY);
                    break;
            }
        }


    }

    CollisionChecker.collideQueue.clear();
}

float CollisionProcessCore::calculateDeltaX(int firstID, int secondID)
{
    float leftX1, rightX1, leftX2, rightX2;
    leftX1 = GameData.EntityVec[firstID].x;
    leftX2 = GameData.EntityVec[secondID].x;
    rightX1 = leftX1 + GameData.EntityVec[firstID].widthMask;
    rightX2  = leftX2 + GameData.EntityVec[secondID].widthMask;

    //Get left and right coordinate for both collided objects
    float leftX, rightX;
    if (leftX1 < leftX2)
        leftX = leftX1;
    else
        leftX = leftX2;

    if (rightX1 < rightX2)
        rightX = rightX2;
    else
        rightX = rightX1;

    //Get collided width
    float collidedWidth = rightX - leftX;

    //Get actual widths
    float width1, width2;
    width1 = GameData.EntityVec[firstID].widthMask;
    width2 = GameData.EntityVec[secondID].widthMask;
    float actualWidth = width1 + width2;

    //return overlap in widths due to collision
    return (actualWidth - collidedWidth);
}

float CollisionProcessCore::calculateDeltaY(int firstID, int secondID)
{
    float bottomY1, topY1, bottomY2, topY2;
    bottomY1 = GameData.EntityVec[firstID].y;
    bottomY2 = GameData.EntityVec[secondID].y;
    topY1 = bottomY1 + GameData.EntityVec[firstID].heightMask;
    topY2  = bottomY2 + GameData.EntityVec[secondID].heightMask;

    //Get left and right coordinate for both collided objects
    float bottomY, topY;
    if (bottomY1 < bottomY2)
        bottomY = bottomY1;
    else
        bottomY = bottomY2;

    if (topY1 < topY2)
        topY = topY2;
    else
        topY = topY1;

    //Get collided width
    float collidedHeight = topY - bottomY;

    //Get actual widths
    float height1, height2;
    height1 = GameData.EntityVec[firstID].heightMask;
    height2 = GameData.EntityVec[secondID].heightMask;
    float actualHeight = height1 + height2;

    //return overlap in widths due to collision
    return (actualHeight - collidedHeight);
}

int CollisionProcessCore::getDirectionVector(int firstID, int secondID)
{
    float obj1x, obj1y, obj2x, obj2y;
    obj1x = GameData.getPlayerX(firstID);
    obj1y = GameData.getPlayerY(firstID);
    obj2x = GameData.getPlayerX(secondID);
    obj2y = GameData.getPlayerY(secondID);

    float diffX = obj2x - obj1x;
    float diffY = obj2y - obj1y;

    if ((diffX == 0) && (diffY > 0))
    {
        return 0;
    }
    else if ((diffX > 0) && (diffY > 0))
    {
        return 1;
    }
    else if ((diffX > 0) && (diffY == 0))
    {
        return 2;
    }
    else if ((diffX > 0) && (diffY < 0))
    {
        return 3;
    }
    else if ((diffX == 0) && (diffY < 0))
    {
        return 4;
    }
    else if ((diffX < 0) && (diffY < 0))
    {
        return 5;
    }
    else if ((diffX < 0) && (diffY == 0))
    {
        return 6;
    }
    else if ((diffX < 0) && (diffY > 0))
    {
        return 7;
    }
    else
    {
        return (-1);
    }
}
