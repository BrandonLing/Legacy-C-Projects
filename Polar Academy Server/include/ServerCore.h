#ifndef SERVERCORE_H
#define SERVERCORE_H

#include <winsock2.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

class ServerCore
{
    public:
        //Basic socket control functions
        void init();
        void quit();
        int recvMessage(); //returns handle message code
        void sendMessage(char* message, sockaddr_in address);
        int checkBuffer();

        bool quitFlag;
    protected:
    private:
        //Basic socket control variables//
        static const int maxBufferLength = 8192;
        static const int port = 7777;
        SOCKET s;
        struct sockaddr_in server, si_other;
        int slen = sizeof(si_other);
        int recv_len;
        char buf[maxBufferLength];
        WSADATA wsa;





};


#endif // SERVERCORE_H
