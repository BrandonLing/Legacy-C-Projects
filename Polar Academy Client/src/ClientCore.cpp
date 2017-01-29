#include "ClientCore.h"
const char ClientCore::serverIP[] = "50.130.87.57";

void ClientCore::init()
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

void ClientCore::quit()
{
    closesocket(this->s);
    WSACleanup();
}

/*To send data to server
ClientSystem.sendMessage("Hello Server");
*/
void ClientCore::sendMessage(const char* message)
{
    //Send the message
    if (sendto(this->s, message, strlen(message) , 0 , (struct sockaddr *) &(this->server), this->slen) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    //std::cout << "Sent Packet\n"; //Required to flush the socket and send
}


/*To call this data from recvMessage
    char* msg = ClientSystem.recvMessage();
    std::cout << "Received: "; puts(msg); std::cout << "\n";
*/
int ClientCore::recvMessage()
{
    //Check for data
    //std::cout << "CheckBuffer: " << this->checkBuffer() << "\n";
    if ((this->checkBuffer()) > 0)
    {
        //clear the buffer by filling null, it might have previously received data
        memset(this->buf,'\0', this->maxBufferLength);

        //try to receive some data, this is a blocking call
        if (recvfrom(this->s, this->buf, this->maxBufferLength, 0, (struct sockaddr *) &(this->server), &(this->slen)) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        //print reply to console
        puts(this->buf);
    }

    return 0;
}

//This Checks the buffer for available data to avoid blocking calls
int ClientCore::checkBuffer()
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0; //Making Select return immediately

    fd_set sockCheck;

    FD_ZERO(&sockCheck);
    FD_CLR(0, &sockCheck);
    FD_SET(this->s, &sockCheck);

    int dataExists = select(0+1, &sockCheck, NULL, NULL, &tv);
    /*if (dataExists == -1)
        printf("Error in select()\n");
    else if (dataExists == 0)
        printf("No Data received\n");
    else
        printf("Select() works finally!\n");
    */
    //std::cout << "Data exists flag = " << dataExists << "\n";
    return dataExists;
}

