#include "ClientList.h"

int ClientList::loginClient(ClientInfo client)
{
    this->connectedClients.push_back(client);
    this->totalClients++;

    //std::cout << "Total Clients: " << this->totalClients << "\n";
    return (this->totalClients);
}

int ClientList::generateID()
{
    this->randNo ++;
    return (this->randNo);
}

int ClientList::logoutClient(int ID)
{
    int clientIndex = this->findClientIndex(ID);
    std::cout << clientIndex << "\n";

    return 0;
}

int ClientList::findClientIndex(int cID)
{
    for (int i = 0; i < this->totalClients; i++)
    {
        ClientInfo clientData = this->connectedClients[i];
        if (clientData.ID == cID)
        {
            return i;
        }
    }
}

