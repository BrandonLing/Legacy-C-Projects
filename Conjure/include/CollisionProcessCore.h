#ifndef COLLISIONPROCESSCORE_H
#define COLLISIONPROCESSCORE_H

#include <CollisionCore.h>
#include <GameDataCore.h>

extern CollisionCore CollisionChecker;
extern GameDataCore GameData;

class CollisionProcessCore
{
    public:
        void init();
        void quit();
        void processCollisions();
        float calculateDeltaX(int firstID, int secondID);
        float calculateDeltaY(int firstID, int secondID);
        int getDirectionVector(int firstID, int secondID);
    protected:
    private:
};

#endif // COLLISIONPROCESSCORE_H
