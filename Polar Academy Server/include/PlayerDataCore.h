#ifndef PLAYERDATACORE_H
#define PLAYERDATACORE_H

#include <winsock2.h>
#include <string>

class PlayerDataCore
{
    public:
        void init();
        void quit();
    protected:
    private:
};


class Player
{
    public:
        std::string name = "";
        float x = 0; float y = 0; float z = 0;
        struct sockaddr_in address;
    protected:
    private:
};

#endif // PLAYERDATACORE_H
