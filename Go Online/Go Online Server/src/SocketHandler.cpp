#include "SocketHandler.h"

BouncebackPacket SocketHandler::handleMessage(std::string packet, int ipVersion, struct sockaddr_in6 loc6, struct sockaddr_in loc4)
{
    //print packet
    //std::cout << "Packet Received: " << packet << "\n";

    //re-init variables from previous use
    BouncebackPacket output;
    this->message = "";

    //Empty packet
    if (packet.size() == 0)
    {
        std::cout << "Error: Received an empty packet\n";
    }

    //Client requests ipv6 ID
    else if(!packet.compare("PingIPv6"))
    {
        //bounce back message
        output.createPacket(true, "IPv6");
        return output;
    }
    //Client requests ipv4 ID
    else if(!packet.compare("PingIPv4"))
    {
        //bounce back message
        output.createPacket(true, "IPv4");
        return output;
    }

    //Login client ipv6
    else if(!packet.compare("LoginIPv6"))
    {
        //log client in
        ClientInfo account;
        account.ID = clientList.generateID();
        account.ipVersion = 6;
        account.si_other = loc6;
        this->clientList.loginClient(account);

        //bounce back message "Login\ClientID"
        this->message = "Login";
        this->message.push_back(this->fileSeparator);
        char id[10];
        itoa(account.ID, id, 10);
        this->message.append(id);
        output.createPacket(true, message);
        //std::cout << "IPv6 Login Detected\n";
        return output;
    }
    //Login client ipv4
    else if(!packet.compare("LoginIPv4"))
    {
        //log client in
        ClientInfo account;
        account.ID = clientList.generateID();
        account.ipVersion = 4;
        account.si_other4 = loc4;
        this->clientList.loginClient(account);

        //bounce back message "Login\ClientID"
        this->message = "Login";
        this->message.push_back(this->fileSeparator);
        char id[10];
        itoa(account.ID, id, 10);
        this->message.append(id);
        output.createPacket(true, message);
        return output;
    }


    return output;
}
