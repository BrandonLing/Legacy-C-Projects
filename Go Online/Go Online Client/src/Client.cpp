#include "Client.h"

void Client::init()
{
    //Initialise winsock
    //printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    //printf("Initialised.\n");

    //create sockets
    this->initIPv6Client();
    this->initIPv4Client();

    //test for ipv6, if not use ipv4 socket
    this->ipVersionDetection();

    //Detect whether client will use ipv6 or ipv4 by pinging server

}

void Client::initIPv4Client()
{
    this->slen4 = sizeof(server4);

    //create socket
    if ( (s4 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
    {
        printf("socket() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    //std::cout << "Created IPv4 socket.\n";

    //setup address structure
    memset((char *) &server4, 0, sizeof(server4));
    std::string serverIP = "50.130.87.251";
    //std::string serverIP = "10.0.0.90";
    this->server4.sin_family = AF_INET;
    this->server4.sin_port = htons(this->port4);
    this->server4.sin_addr.S_un.S_addr = inet_addr(serverIP.c_str());
    std::cout << "Server IP location: " << serverIP << "\n";
}

void Client::initIPv6Client()
{
    //init vars
    this->slen = sizeof(server);

    //Prepare the sockaddr_in6 structure
    struct addrinfo hints, *serveraddr;// *p, *selfaddr;
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    //Find endpoints
    /*int selfFlag = getaddrinfo(NULL , "7777", &hints, &selfaddr); // can put a website link here
    if (selfFlag != 0)
        std::cout << "Error: addrResult = " << selfFlag << "\n";

    std::cout << "Detecting local nodes\n";
    for(p = selfaddr;p != NULL; p = p->ai_next)
    {
        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET)
        { // IPv4
            if (this->IPv6Flag != true)
                this->IPv6Flag = false;
            std::cout << "Local IPv4 endpoint detected\n";
        }
        else
        { // IPv6
            this->IPv6Flag = true;
            std::cout << "Local IPv6 endpoint detected\n";
        }
    }*/

    //std::cout << "Created IPv6 socket\n";
    if ( (s = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        printf("socket() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    //Find endpoints
    int addrResult = getaddrinfo("2601:3c3:c000:afbd:4068:602e:879a:cbc0" , "7777", &hints, &serveraddr); // can put a website link here
    //int addrResult = getaddrinfo("::1" , "7777", &hints, &serveraddr); // can put a website link here
    if (addrResult != 0)
        std::cout << "Error: addrResult = " << addrResult << "\n";

    /*std::cout << "Detecting server nodes\n";

    for(p = serveraddr;p != NULL; p = p->ai_next)
    {
        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) { // IPv4
            std::cout << "Found an IPv4 endpoint\n";
        } else { // IPv6
            std::cout << "Found an IPv6 endpoint\n";
        }
    }*/

    /*//Print ipv4 or ipv6 detection
    if (serveraddr->ai_family == AF_INET)
        std::cout << "IPv4 server detected\n";
    else
        std::cout << "IPv6 server detected\n";*/

    //print IP
    char ipstr[INET6_ADDRSTRLEN];
    void *addr;
    boost::system::error_code err;

    struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)serveraddr->ai_addr;
    addr = &(ipv6->sin6_addr);
    boost::asio::detail::socket_ops::inet_ntop(serveraddr->ai_family, addr, ipstr, sizeof ipstr, 0, err);
    std::cout << "Server IP location: " << ipstr << "\n";

    //set server
    this->server = *ipv6;
}

void Client::ipVersionDetection()
{
    //ipv6
    this->testMessage("PingIPv6");
    Sleep(500);
    this->recvMessage();

    this->testMessage4("PingIPv4");
    Sleep(500);
    this->recvMessage();

    //Check for IPv6 response
    if (this->handler.IPv6Flag)
    {
        std::cout << "Using IPv6\n";
        this->testMessage("LoginIPv6");
    }
    else if (this->handler.IPv4Flag)
    {
        std::cout << "Using IPv4\n";
        this->testMessage4("LoginIPv4");
    }
    else
    {
        std::cout << "Server is down. Please try again later\n";
    }
}

void Client::quit()
{
    closesocket(this->s);
    closesocket(this->s4);
    WSACleanup();
}

/*To send data to server
ClientSystem.sendMessage("Hello Server");
*/
void Client::sendMessage(const char* message)
{
    if (handler.IPv6Flag)
    {
        //Send the message
        if (sendto(this->s, message, strlen(message) , 0,(struct sockaddr *) &(this->server), this->slen) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }
        //std::cout << "Sent Packet: " << message << "\n"; //Required to flush the socket and send
    }
    else if (handler.IPv4Flag)
    {
        //Send the message
        if (sendto(this->s4, message, strlen(message) , 0,(struct sockaddr *) &(this->server4), this->slen4) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }
        //std::cout << "Sent Packet: " << message << "\n"; //Required to flush the socket and send
    }
    else
    {
        std::cout << "Error: Client is not set to use IPv4 or IPv6\n";
    }
}

void Client::testMessage(const char* message)
{
    //Send the message
    if (sendto(this->s, message, strlen(message) , 0,(struct sockaddr *) &(this->server), this->slen) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    //std::cout << "Sent Packet: " << message << "\n"; //Required to flush the socket and send
}

void Client::testMessage4(const char* message)
{
    //Send the message
    if (sendto(this->s4, message, strlen(message) , 0,(struct sockaddr *) &(this->server4), this->slen4) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    //std::cout << "Sent Packet: " << message << "\n"; //Required to flush the socket and send
}

int Client::recvMessage()
{
    //Check for data ipv6
    if ((this->checkBuffer(this->s)) > 0)
    {
        //clear the buffer by filling null, it might have previously received data
        memset(this->buf,'\0', this->maxBufferLength);

        //try to receive some data, this is a blocking call
        if (recvfrom(this->s, this->buf, this->maxBufferLength, 0, (struct sockaddr *) &(this->server), &(this->slen)) == SOCKET_ERROR)
        {
            //printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            //exit(EXIT_FAILURE);
        }

        //print reply to console
        if (this->buf[0] != '\0')
        {
            handler.handleMessage(this->buf);
            //std::cout << "Received Message: ";
            //puts(this->buf);
        }
    }

    //Check for data ipv4
    if ((this->checkBuffer(this->s4)) > 0)
    {
        //clear the buffer by filling null, it might have previously received data
        memset(this->buf4,'\0', this->maxBufferLength4);

        //try to receive some data, this is a blocking call
        if (recvfrom(this->s4, this->buf4, this->maxBufferLength4, 0, (struct sockaddr *) &(this->server4), &(this->slen4)) == SOCKET_ERROR)
        {
            //printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            //exit(EXIT_FAILURE);
        }

        //print reply to console
        if (this->buf4[0] != '\0')
        {
            handler.handleMessage(this->buf4);
            //std::cout << "Received Message: ";
            //puts(this->buf4);
        }
    }

    return 0;
}

//This Checks the buffer for available data to avoid blocking calls
int Client::checkBuffer(unsigned int socket)
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0; //Making Select return immediately

    fd_set sockCheck;

    FD_ZERO(&sockCheck);
    FD_CLR(0, &sockCheck);
    FD_SET(socket, &sockCheck);

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


