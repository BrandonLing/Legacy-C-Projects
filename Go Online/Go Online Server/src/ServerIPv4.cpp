#include "ServerIPv4.h"

void ServerIPv4::init()
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
    printf("Socket created.\n");

    //Prepare the sockaddr_in6 structure
    struct addrinfo hints, *serveraddr;
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    int addrResult = getaddrinfo(NULL , "7778", &hints, &serveraddr); // can put a website link here
    if (addrResult != 0)
        std::cout << "Error: addrResult = " << addrResult << "\n";

    //Print ipv4 or ipv6 detection
    if (serveraddr->ai_family == AF_INET)
        std::cout << "IPv4 server detected\n";
    else
        std::cout << "IPv6 server detected\n";

    //print IP
    char ipstr[INET6_ADDRSTRLEN];
    void *addr;
    boost::system::error_code err;

    struct sockaddr_in *ipv6 = (struct sockaddr_in *)serveraddr->ai_addr;
    addr = &(ipv6->sin_addr);
    boost::asio::detail::socket_ops::inet_ntop(serveraddr->ai_family, addr, ipstr, sizeof ipstr, 0, err);
    std::cout << "Server IP location: " << ipstr << "\n";

    //set server
    this->server = *ipv6;

    //Bind
    if( bind(this->s ,(struct sockaddr *)&(this->server) , sizeof(this->server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Server bind successful");
}


void ServerIPv4::quit()
{
    closesocket(this->s);
    WSACleanup();
}


int ServerIPv4::recvMessage()
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
        //printf("Received packet from %s:%d\n", inet_ntoa(this->si_other.sin6_addr), ntohs(this->si_other.sin6_port));
        printf("Data: %s\n" , this->buf);
        this->sendMessage("Hello Client", this->si_other);
    }

    return 0;
}

//This Checks the buffer for available data to avoid blocking calls
int ServerIPv4::checkBuffer()
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
void ServerIPv4::sendMessage(char* message, sockaddr_in6 address)
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
void ServerIPv4::sendMessage(char* message, sockaddr_in address)
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


