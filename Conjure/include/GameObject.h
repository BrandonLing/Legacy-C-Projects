#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <list>
#include <string>
#include <stdlib.h> //abs
#include <math.h> //fmod
#include <time.h>

#include <iostream>

class pathFinderNode
{
    public:
        int x = 0, y = 0, node = 0;
};

class GameObject
{
    public:
        int ID;
        std::string name, profession;
        std::vector<pathFinderNode> reachableNodes;
        int type;
            //Type 0 is a player character
        float x = 0; float y = 0; float z = 0;
        float xMask = 0; float yMask = 0;
        int xDest = 0, yDest = 0; //destination coordinates for pathing

        int xDir = 0; float yDir = 0; //movement flags

        //sprite info
        float width, height;
        float playerSpeed = 0.125;

        bool visible = false;
        bool collision = false;
        bool animated = false;
        bool snapped = true;
        bool hostile = false;
        bool attacking = false;

        int spriteBook;
        float spriteIndex;
        float imageSpeed;
        float speedOn = 0.55; //image animation speed
        float speedOff = 0.0;

        std::vector<int> spriteTextureIndex;

        //movement
        int prevPFacing = 0; //holds previous button push
        int currentPFacing = 0; //holds current button push
        std::list<int> path;

        //Monster AI vars
        clock_t aiBlockTimer = clock();

        //Flags
        int flag = 0;

        //stats
        int health = 3;
        int damage = 1;
        int moveRange = 3;
        int jumpRange = 1;
    protected:
    private:
};

#endif // GAMEOBJECT_H
