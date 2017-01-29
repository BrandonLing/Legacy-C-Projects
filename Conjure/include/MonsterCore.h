#ifndef MONSTERCORE_H
#define MONSTERCORE_H

#include <iostream>

#include <stdlib.h> //rand

#include <GameObject.h>
#include <GameDataCore.h>

extern GameDataCore GameData;

class MonsterCore
{
    public:
        void init();
        void quit();

        void updateMonstersAI();
        int chooseBasicHostileAction(int ID);
        void chooseBasicNonHostileAction(int ID);
        std::vector<int> findClosestTarget(int entityID);

        void delayEntity(int entityID, int delay);

        void moveMonsterUp(int ID);
        void moveMonsterRight(int ID);
        void moveMonsterDown(int ID);
        void moveMonsterLeft(int ID);

        bool monsterAIon = true;
    protected:
    private:
};

#endif // MONSTERCORE_H
