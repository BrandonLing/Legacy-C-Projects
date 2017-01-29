#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <ws2tcpip.h>

class ClientInfo
{
    public:
        int ID;
        int ipVersion;

        struct sockaddr_in6 si_other;
        struct sockaddr_in si_other4;
    protected:
    private:
};

#endif // CLIENTINFO_H
