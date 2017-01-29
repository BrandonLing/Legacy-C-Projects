#include "ServerCore.h"

#include "ServerCore.h"

void ServerCore::init()
{
    //Init vars
    this->quitFlag = false;

    //Initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&(this->wsa)) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");

    //Create a socket
    if(((this->s) = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = "127.0.0.1";
    server.sin_port = htons( port );

    //Bind
    if( bind(this->s ,(struct sockaddr *)&(this->server) , sizeof(this->server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done");
}


void ServerCore::quit()
{
    closesocket(this->s);
    WSACleanup();
}


int ServerCore::recvMessage()
{
    //Check for data
    if (this->checkBuffer() > 0)
    {
        //clear the buffer by filling null, it might have previously received data
        memset(this->buf,'\0', this->maxBufferLength);

        //try to receive some data, this is a blocking call
        if (((this->recv_len) = recvfrom(this->s, this->buf, this->maxBufferLength, 0, (struct sockaddr *) &(this->si_other), &(this->slen))) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(this->si_other.sin_addr), ntohs(this->si_other.sin_port));
        printf("Data: %s\n" , this->buf);
    }

    return 0;
}

//This Checks the buffer for available data to avoid blocking calls
int ServerCore::checkBuffer()
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0; //Making Select return immediately

    fd_set sockCheck;

    FD_ZERO(&sockCheck);
    FD_CLR(0, &sockCheck);
    FD_SET(this->s, &sockCheck);

    int dataExists = select(0+1, &sockCheck, NULL, NULL, &tv);

    //Troubleshooting printouts for select()
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

void ServerCore::sendMessage(char* message, sockaddr_in address)
{
    //clear buffer
    int send_len = strlen(message);

    //send message to client
    if (sendto(this->s, message, send_len, 0, (struct sockaddr*) &(address), this->slen) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    //printf("Sent packet to %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    //printf("Data: %s\n" , message);
}

