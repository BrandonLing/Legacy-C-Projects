#include "CollisionCore.h"

void CollisionCore::init()
{

}

void CollisionCore::quit()
{

}

void CollisionCore::checkCollisions()
{
    //get player xMask,yMask data.
    float pXLeft, pXRight, pYBottom, pYTop;
    int pIndex = GameData.getEntityID(GameData.playerCharacter, 0);
    GameObject player = GameData.EntityVec[pIndex];
    pXLeft = player.x;
    pXRight = pXLeft + player.widthMask;
    pYBottom = player.y;
    pYTop = pYBottom + player.heightMask;

    //go through each entity
    std::vector<GameObject>::iterator objectIter;
    for (objectIter = GameData.EntityVec.begin(); objectIter != GameData.EntityVec.end(); objectIter++)
    {
        //check if it applies collision
        if ((*objectIter).collision)
        {
            //Check x and y axis
            float objxMaskLeft = (*objectIter).x;
            float objxMaskRight = objxMaskLeft + (*objectIter).widthMask;
            if ((objxMaskLeft >= pXRight) || (objxMaskRight <= pXLeft))
            {//Object is not colliding with player
                //std::cout << "xCheck\n";

                continue;
            }
            else //check y axis
            {
                float objyMaskBot = (*objectIter).y;
                float objyMaskTop = objyMaskBot + (*objectIter).heightMask;
                if ((objyMaskBot >= pYTop) || (objyMaskTop <= pYBottom))
                {//Object is not colliding with player
                    //std::cout << "yCheck\n";
                    continue;
                }
                else
                {//Object is colliding with player
                    //check if it is player colliding with itself
                    if ((*objectIter).ID != player.ID)
                    {
                        CollideEvent collision;
                        collision.collidedObjects.push_back(player.ID);
                        collision.collidedObjects.push_back((*objectIter).ID);
                        this->collideQueue.push_back(collision);
                        //std::cout << "Collision detected with " << (*objectIter).name << "\n";
                        //std::cout << (*objectIter).name << "\n";
                        //std::cout << objxMaskLeft << "," << objxMaskRight << "\n";
                    }
                }
            }
        }


    }

    //check lists for x overlap

    //send potential collisions with x overlap for further checking


}

