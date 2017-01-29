#ifndef COLLISIONCORE_H
#define COLLISIONCORE_H

#include <iostream>

#include <vector>
#include <list>
#include <GameObject.h>
#include <CollideEvent.h>

//Core Dependencies
#include <GameDataCore.h>

extern GameDataCore GameData;

class CollisionCore
{
    public:
        void init();
        void quit();

        void checkCollisions();
        std::vector<CollideEvent> collideQueue;
    protected:
    private:
};

#endif // COLLISIONCORE_H
