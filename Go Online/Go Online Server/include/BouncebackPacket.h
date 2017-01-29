#ifndef BOUNCEBACKPACKET_H
#define BOUNCEBACKPACKET_H

#include <ws2tcpip.h>
#include <string>

class BouncebackPacket
{
    public:
        std::string packet;
        bool ipv6Flag;
        struct sockaddr_in si_other4;
        struct sockaddr_in6 si_other;
        bool returnPacket = false;
        char* payload;

        void createPacket(bool ipv6Flag, std::string msg);
    protected:
    private:
};

#endif // BOUNCEBACKPACKET_H
