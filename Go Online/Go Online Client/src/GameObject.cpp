#include "GameObject.h"

GameObject::GameObject()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;

    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;

    this->xscale = 1.0;
    this->yscale = 1.0;
    this->zscale = 1.0;

    this->moveSpdFactor = 0.5;
    this->strafeSpdFactor = 0.25;
    this->turnSpd = 0.2;
    this->lookSpd = 0.1;

    this->meshID = 0;
    this->animated = false;
}

GameObject::GameObject(float xpos, float ypos, float zpos)
{
    this->x = xpos;
    this->y = ypos;
    this->z = zpos;

    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;

    this->xscale = 1.0;
    this->yscale = 1.0;
    this->zscale = 1.0;

    this->moveSpdFactor = 0.5;
    this->strafeSpdFactor = 0.25;
    this->turnSpd = 0.2;
    this->lookSpd = 0.1;

    this->meshID = 0;
    this->animated = false;
}

GameObject::GameObject(float xpos, float ypos, float zpos, float xscale, float yscale, float zscale)
{
    this->x = xpos;
    this->y = ypos;
    this->z = zpos;

    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;

    this->xscale = xscale;
    this->yscale = yscale;
    this->zscale = zscale;

    this->moveSpdFactor = 0.5;
    this->strafeSpdFactor = 0.25;
    this->turnSpd = 0.2;
    this->lookSpd = 0.1;

    this->meshID = 0;
    this->animated = false;
}

float GameObject::changeYaw(float deltaYaw)
{
    this->yaw += deltaYaw;
    if (this->yaw > 360)
    {
        this->yaw -= 360;
    }
    else if (this->yaw < 0)
    {
        this->yaw += 360;
    }
    //std::cout << this->yaw << " yaw\n";

    return (this->yaw);
}

float GameObject::changePitch(float deltaPitch)
{
    this->pitch += deltaPitch;
    if (this->pitch > 90)
    {
        this->pitch = 90;
    }
    else if (this->pitch < -90)
    {
        this->pitch = -90;
    }
    return (this->pitch);
}
