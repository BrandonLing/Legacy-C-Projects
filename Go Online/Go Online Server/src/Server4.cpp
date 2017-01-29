#include "Server4.h"


void Server4::init()
{
    //Init vars
    this->slen = sizeof(si_other);
    //Initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&(this->wsa)) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");

    //Create a socket
    if(((this->s) = socket(AF_INET, SOCK_DGRAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created IPv4.\n");


    memset((char *) &(this->server), 0, sizeof(this->server));
    this->server.sin_addr.S_un.S_addr = inet_addr("174.50.48.212");
    this->server.sin_port = htons(this->port);
    this->server.sin_family = AF_INET;

    //Bind
    if( bind(this->s ,(struct sockaddr *)&(this->server) , sizeof(this->server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Server IPv4 bind successful");

}


void Server4::quit()
{
    closesocket(this->s);
    WSACleanup();
}


int Server4::recvMessage()
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
            //exit(EXIT_FAILURE);
        }

        //print details of the client/peer and the data received
        this->printReceivedData();

        //Bounceback
        this->sendMessage("Hello Client", this->si_other);
    }

    return 0;
}

void Server4::printReceivedData()
{
    //find sender
    char ipstr[INET_ADDRSTRLEN];
    boost::system::error_code err;
    void *sourceIP = &(this->si_other.sin_addr);
    boost::asio::detail::socket_ops::inet_ntop(this->si_other.sin_family, sourceIP, ipstr, sizeof ipstr, 0, err);

    std::cout << "Received Packet from " << ipstr << "\n";
    printf("Data: %s\n" , this->buf);
}

//This Checks the buffer for available data to avoid blocking calls
int Server4::checkBuffer()
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

//ipv6 send
void Server4::sendMessage(char* message, sockaddr_in6 address)
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
    std::cout << "Sent message through IPv6\n";
    printf("Data: %s\n" , message);
}

//ipv4 send
void Server4::sendMessage(char* message, sockaddr_in address)
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
    std::cout << "Sent message through IPv4\n";
    printf("Data: %s\n" , message);
}

