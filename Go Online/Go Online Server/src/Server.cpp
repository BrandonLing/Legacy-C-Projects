#include "Server.h"

void Server::init()
{
    //Initialise winsock
    //printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&(this->wsa)) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    //printf("Initialised.\n");

    this->initIPv6Server();
    this->initIPv4Server();

}

void Server::initIPv4Server()
{
    //init vars
    this->slen4 = sizeof(si_other4) ;

    //Create a socket
    if((s4 = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    //printf("Created IPv4 socket.\n");

    //Prepare the sockaddr_in structure
    std::cout << "Detecting IPv4 Location automatically\n";
    server4.sin_family = AF_INET;
    server4.sin_addr.s_addr = INADDR_ANY;
    server4.sin_port = htons( this->port4 );

    //Bind
    if( bind(s4 ,(struct sockaddr *)&server4 , sizeof(server4)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    //puts("Bind done");
    std::cout << "Server IPv4 bind successful\n";
}

void Server::initIPv6Server()
{
    //Init vars
    this->slen = sizeof(si_other);

    //Prepare the sockaddr_in6 structure
    struct addrinfo hints, *serveraddr, *p;
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    //Find endpoints
    //std::cout << "Locating IPv6 Endpoint\n";
    int addrResult = getaddrinfo("2601:3c3:c000:afbd:4068:602e:879a:cbc0", "7777", &hints, &serveraddr); // can put a website link here
    if (addrResult != 0)
        std::cout << "Error: addrResult = " << addrResult << "\n";

    for(p = serveraddr;p != NULL; p = p->ai_next)
    {
        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET)
        { // IPv4
            std::cout << "Error: Found IPv4 endpoint during IPv6 lookup\n";
        }
        else
        { // IPv6
            //Create a socket
            if(((this->s) = socket(AF_INET6, SOCK_DGRAM , 0 )) == INVALID_SOCKET)
            {
                printf("Could not create socket : %d" , WSAGetLastError());
            }
            //printf("Created IPv6 socket.\n");

            //print IP
            char ipstr[INET6_ADDRSTRLEN];
            void *addr;
            boost::system::error_code err;

            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)serveraddr->ai_addr;
            addr = &(ipv6->sin6_addr);
            boost::asio::detail::socket_ops::inet_ntop(serveraddr->ai_family, addr, ipstr, sizeof ipstr, 0, err);
            std::cout << "Server IP location set to: " << ipstr << "\n";

            //set server
            this->server = *ipv6;
            int no = 0;
            setsockopt(this->s, IPPROTO_IPV6, IPV6_V6ONLY, (const char *)&no, sizeof(no));

            //Bind
            if( bind(this->s ,(struct sockaddr *)&(this->server) , sizeof(this->server)) == SOCKET_ERROR)
            {
                printf("Bind failed with error code : %d" , WSAGetLastError());
                exit(EXIT_FAILURE);
            }
            puts("Server IPv6 bind successful");
        }
    }
}

void Server::quit()
{
    closesocket(this->s);
    closesocket(this->s4);
    WSACleanup();
}


int Server::recvMessage()
{
    //Check for data IPv6
    if (this->checkBuffer(this->s) > 0)
    {
        //std::cout << "IPv6 message detected\n";
        //clear the buffer by filling null, it might have previously received data
        memset(this->buf,'\0', this->maxBufferLength);

        //try to receive some data, this is a blocking call
        if (((this->recv_len) = recvfrom(this->s, this->buf, this->maxBufferLength, 0, (struct sockaddr *) &(this->si_other), &(this->slen))) == SOCKET_ERROR)
        {
            //printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            //exit(EXIT_FAILURE);
        }

        //print details of the client/peer and the data received
        if (this->buf[0] != '\0')
        {
            //Handle buffer
            BouncebackPacket packetinfo = this->handler.handleMessage(this->buf, 6, this->si_other, this->si_other4);
            if (packetinfo.returnPacket)
            {
                packetinfo.si_other = this->si_other;
                this->sendMessage(packetinfo.payload, packetinfo.si_other);
            }
            //this->printReceivedData();
        }

        else
        {
            //Clear Buffer
            memset(this->buf,'\0', this->maxBufferLength);
        }

    }


    //Check for data IPv4
    if (this->checkBuffer(this->s4) > 0)
    {
        //std::cout << "IPv4 message detected\n";
        //clear the buffer by filling null, it might have previously received data
        memset(this->buf4,'\0', this->maxBufferLength4);

        //try to receive some data, this is a blocking call
        if (((this->recv_len4) = recvfrom(this->s4, this->buf4, this->maxBufferLength4, 0, (struct sockaddr *) &(this->si_other4), &(this->slen4))) == SOCKET_ERROR)
        {
            //printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            //exit(EXIT_FAILURE);
        }

        //print details of the client/peer and the data received
        if (this->buf4[0] != '\0')
        {
            //Handle buffer
            BouncebackPacket packetinfo = this->handler.handleMessage(this->buf4, 4, this->si_other, this->si_other4);
            if (packetinfo.returnPacket)
            {
                packetinfo.si_other4 = this->si_other4;
                this->sendMessage(packetinfo.payload, packetinfo.si_other4);
            }
            //this->printReceivedData4();
        }
        else
        {

            //Clear Buffer
            memset(this->buf4,'\0', this->maxBufferLength4);
        }


    }

    return 0;
}

void Server::printReceivedData4()
{
    //find sender
    char ipstr[INET_ADDRSTRLEN];
    boost::system::error_code err;
    void *sourceIP = &(this->si_other4.sin_addr);
    boost::asio::detail::socket_ops::inet_ntop(this->si_other4.sin_family, sourceIP, ipstr, sizeof ipstr, 0, err);

    std::cout << "Received Packet from " << ipstr << ":" << ntohs(this->si_other4.sin_port) << "\n";
    printf("Data: %s\n" , this->buf4);

    //Bounceback
    //this->sendMessage("Hello Client. I got it!", this->si_other4);
}

void Server::printReceivedData()
{
    //find sender
    char ipstr[INET6_ADDRSTRLEN];
    boost::system::error_code err;
    void *sourceIP = &(this->si_other.sin6_addr);
    boost::asio::detail::socket_ops::inet_ntop(this->si_other.sin6_family, sourceIP, ipstr, sizeof ipstr, 0, err);

    std::cout << "Received Packet from " << ipstr << "\n";
    printf("Data: %s\n" , this->buf);

    //Bounceback
    //this->sendMessage("Hello Client. I got it!", this->si_other);
}

//This Checks the buffer for available data to avoid blocking calls
int Server::checkBuffer(SOCKET sockID)
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0; //Making Select return immediately

    fd_set sockCheck;

    FD_ZERO(&sockCheck);
    FD_CLR(0, &sockCheck);
    FD_SET(sockID, &sockCheck);

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
void Server::sendMessage(char* message, sockaddr_in6 address)
{
    //clear buffer
    int send_len = strlen(message);

    //send message to client
    if (sendto(this->s, message, send_len, 0, (struct sockaddr*) &(address), this->slen) == SOCKET_ERROR)
    {
        //printf("sendto() failed with error code : %d" , WSAGetLastError());
        //exit(EXIT_FAILURE);
    }
    //printf("Sent packet to %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    std::cout << "Sent message: ";
    printf("Data: %s\n" , message);
}

//ipv4 send
void Server::sendMessage(char* message, sockaddr_in address)
{
    //clear buffer
    int send_len = strlen(message);

    //send message to client
    if (sendto(this->s4, message, send_len, 0, (struct sockaddr*) &(address), this->slen4) == SOCKET_ERROR)
    {
        //printf("sendto() failed with error code : %d" , WSAGetLastError());
        //exit(EXIT_FAILURE);
    }
    //printf("Sent packet to %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    std::cout << "Sent message through IPv4\n";
    printf("Data: %s\n" , message);
}



