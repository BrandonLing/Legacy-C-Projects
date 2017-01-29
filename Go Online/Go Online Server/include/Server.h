#ifndef SERVER_H
#define SERVER_H

#define _WIN32_WINNT 0x0501

#include <winsock2.h>
#include <ws2tcpip.h>
#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <SocketHandler.h>

class Server
{
    public:
        //Basic socket control functions
        void init();
        void quit();
        void initIPv6Server();
        void initIPv4Server();

        int recvMessage(); //returns handle message code
        void sendMessage(char* message, sockaddr_in address);
        void sendMessage(char* message, sockaddr_in6 address);
        int checkBuffer(SOCKET sockID);
        void printReceivedData();
        void printReceivedData4();

        SocketHandler handler;

    protected:
    private:
        //Basic socket control variables for IPv6 Socket//
        static const int maxBufferLength = 8192;
        static const int port = 7777;
        SOCKET s;
        struct sockaddr_in6 server;
        struct sockaddr_in6 si_other;
        int slen;
        int recv_len;
        char buf[maxBufferLength];
        WSADATA wsa;

        //Basic socket control variables for IPv4 Socket//
        static const int maxBufferLength4 = 8192;
        static const int port4 = 7778;
        SOCKET s4;
        struct sockaddr_in server4;
        struct sockaddr_in si_other4;
        int slen4;
        int recv_len4;
        char buf4[maxBufferLength4];
        WSADATA wsa4;




};

#endif // SERVER_H



