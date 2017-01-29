#include "EventQueueCore.h"

void EventQueueCore::init()
{

}

void EventQueueCore::quit()
{

}

void EventQueueCore::postInputEvent(int keyCode, int type)
{
    //0 is the origin which is the input core. 1 is a keydown and 0 is a keyup
    int flag;
    if      (type == SDL_KEYDOWN)
        flag = 1;
    else if (type == SDL_KEYUP)
        flag = 0;

    std::list<int>::iterator flagIter = this->eventExists(0, keyCode, flag);

    if (flagIter == this->eQueue.end())
        {
            this->eQueue.push_back(0);
            this->eQueue.push_back(keyCode);
            this->eQueue.push_back(flag);
        }
    else
        *flagIter = flag;

    //std::cout << keyCode << "," << type << "\n";
}

void EventQueueCore::postMouseEvent(int keyCode, int xrel, int yrel)
{
    std::list<int>::iterator qIter;
    bool found = false;
    for (qIter = this->eQueue.begin(); qIter != this->eQueue.end(); qIter++)
    {
        int examinedOrigin = *qIter;
        std::advance(qIter, 1);
        std::advance(qIter, 1);
        if (examinedOrigin == keyCode)
        {
            //keyCode 1 = mouse movement
            //keycode 2 = left mouse click
            //keycode 3 = right mouse click
            std::advance(qIter, -2);
            *qIter = keyCode;
            std::advance(qIter, 1);
            *qIter = xrel;
            std::advance(qIter, 1);
            *qIter = yrel;
            found = true;
            break;
        }
    }
    if (found == false)
    {
        this->eQueue.push_back(keyCode);
        this->eQueue.push_back(xrel);
        this->eQueue.push_back(yrel);
    }
}

void EventQueueCore::postQuitEvent()
{
    eQueue.push_back(-1);
    eQueue.push_back(-1);
    eQueue.push_back(-1);
    //std::cout << keyCode << "," << type << "\n";
}

//Checks if event already exists in the queue and returns -1 if it doesn't. Returns a positive int index if it exists
std::list<int>::iterator EventQueueCore::eventExists(int origin, int identifier, int flag)
{
    std::list<int>::iterator qIter;
    for (qIter = this->eQueue.begin(); qIter != this->eQueue.end(); qIter++)
    {
        //Fill arguments origin, id, and flag
        int examinedOrigin = *qIter;

        std::advance(qIter, 1);
        int examinedID = *qIter;

        std::advance(qIter, 1);

        if ((origin == examinedOrigin) && (identifier == examinedID)) //This event already exists.
        {
            return qIter;
        }
    }
    return qIter; //The event was not found will equal list.end();
}

