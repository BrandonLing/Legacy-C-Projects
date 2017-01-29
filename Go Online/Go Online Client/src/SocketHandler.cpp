#include "SocketHandler.h"

void SocketHandler::handleMessage(std::string packet)
{
    //Check error for empty packet
    if (packet.size() == 0)
    {
        std::cout << "Error: Received an empty packet\n";
    }

    //Check for IPv4 ping return
    else if (!packet.compare("IPv6"))
    {
        this->IPv6Flag = true;
    }
    else if (!packet.compare("IPv4"))
    {
        this->IPv4Flag = true;
    }

}


