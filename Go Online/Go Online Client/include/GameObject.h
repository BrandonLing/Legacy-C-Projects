#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <iostream>

class GameObject
{
    public:
        GameObject();
        GameObject(float xpos, float ypos, float zpos);
        GameObject(float xpos, float ypos, float zpos, float xscale, float yscale, float zscale);

        std::string name;
        float x, y, z; //position
        float roll, yaw, pitch; //rotation
        float xscale, yscale, zscale; //scale
        int meshID;

        float changePitch(float deltaPitch);
        float changeYaw(float deltaYaw);

        float moveSpdFactor;
        float strafeSpdFactor;
        float turnSpd;
        float lookSpd;

        bool animated;
    protected:
    private:
};

#endif // GAMEOBJECT_H
