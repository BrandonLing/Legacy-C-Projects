#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <BouncebackPacket.h>
#include <ClientList.h>

//This class handles all packets that are received
class SocketHandler
{
    public:
        //Packet Handler
        BouncebackPacket handleMessage(std::string packet, int ipVersion, struct sockaddr_in6 loc6, struct sockaddr_in loc4);

        char fileSeparator = 28;
        std::string message;

        //ClientList
        ClientList clientList;
    protected:
    private:
};

#endif // SOCKETHANDLER_H
