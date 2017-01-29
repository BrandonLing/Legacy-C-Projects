#ifndef SERVER4_H
#define SERVER4_H

#define _WIN32_WINNT 0x0501

#include <winsock2.h>
#include <ws2tcpip.h>
#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

class Server4
{
    public:
        //Basic socket control functions
        void init();
        void quit();
        int recvMessage(); //returns handle message code
        void sendMessage(char* message, sockaddr_in address);
        void sendMessage(char* message, sockaddr_in6 address);
        int checkBuffer();
        void printReceivedData();

    protected:
    private:
        //Basic socket control variables//
        static const int maxBufferLength = 8192;
        static const int port = 7777;
        SOCKET s;
        struct sockaddr_in server;
        struct sockaddr_in si_other;
        int slen;
        int recv_len;
        char buf[maxBufferLength];
        WSADATA wsa;





};


#endif // SERVER4_H
