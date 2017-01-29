#include "ClientSend.h"

const char ClientSend::serverIP[] = "174.50.48.212";

void ClientSend::init()
{
    //Initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&(this->wsa)) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");

    //create socket
    if ( (s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        printf("socket() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    //setup address structure
    memset((char *) &(this->server), 0, sizeof(this->server));
    this->server.sin_family = AF_INET;
    this->server.sin_port = htons(port);
    this->server.sin_addr.S_un.S_addr = inet_addr(this->serverIP);

}

void ClientSend::quit()
{
    closesocket(this->s);
    WSACleanup();
}

/*To send data to server
ClientSystem.sendMessage("Hello Server");
*/
void ClientSend::sendMessage(const char* message)
{
    //Send the message
    if (sendto(this->s, message, strlen(message) , 0 , (struct sockaddr *) &(this->server), this->slen) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    std::cout << "Sent Packet\n"; //Required to flush the socket and send
}


