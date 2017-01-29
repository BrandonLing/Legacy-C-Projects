#ifndef CLIENT_H
#define CLIENT_H

#define _WIN32_WINNT 0x0501

#include <winsock2.h>
#include <ws2tcpip.h>
#include <boost/asio.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <time.h>
#include <stdlib.h>     /* srand, rand */
#include <SocketHandler.h>

class Client
{
    public:
        //Basic socket init functions
        void init();
        void quit();
        void initIPv6Client();
        void initIPv4Client();
        void ipVersionDetection();

        //Socket functions
        void sendMessage(const char message[]);
        void testMessage(const char message[]);
        void testMessage4(const char message[]);
        int recvMessage();
        int checkBuffer(unsigned int socket);

        SocketHandler handler;

    protected:
    private:
        //Basic IPv6 socket variables initiablized
        static const int maxBufferLength = 8192;
        static const int port = 7777;
        struct sockaddr_in6 server;
        unsigned int s;
        int slen;
        char buf [maxBufferLength];
        char message [maxBufferLength];
        WSADATA wsa;

        //Basic IPv4 socket variables initiablized
        static const int maxBufferLength4 = 8192;
        static const int port4 = 7778;
        struct sockaddr_in server4;
        unsigned int s4;
        int slen4;
        char buf4 [maxBufferLength4];
        char message4 [maxBufferLength4];
        WSADATA wsa4;
};

#endif // CLIENT_H
