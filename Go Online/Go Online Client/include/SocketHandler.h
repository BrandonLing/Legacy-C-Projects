#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <iostream>
#include <string>

class SocketHandler
{
    public:
        void handleMessage(std::string packet);

        //ipv4/6 check
        bool IPv6Flag;
        bool IPv4Flag;

    protected:
    private:
};

#endif // SOCKETHANDLER_H
