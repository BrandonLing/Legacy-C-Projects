#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include <iostream>
#include <vector>
#include <ClientInfo.h>

//This class organizes a list of clients connected to the server
class ClientList
{
    public:
        std::vector<ClientInfo> connectedClients;

        int loginClient(ClientInfo client);
        int logoutClient(int ID);
        int findClientIndex(int ID);
        int generateID();

        int totalClients = 0;
        int randNo = 0;
    protected:
    private:
};

#endif // CLIENTLIST_H
