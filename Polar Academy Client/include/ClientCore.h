#ifndef CLIENTCORE_H
#define CLIENTCORE_H

#include <winsock2.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>


/*
#define SERVER "50.130.87.57"//"192.168.2.8"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 7777   //The port on which to listen for incoming data
*/

class ClientCore
{
    public:
        //Basic socket functions
        void init();
        void quit();
        void sendMessage(const char message[]);
        int recvMessage();
        int checkBuffer();

        //Basic socket connection variables
        static const char serverIP[];
        static const int maxBufferLength = 8192;
        static const int port = 7777;
        int bppDataSize = 4;
    protected:
    private:
        //Basic socket variables initiablized
        struct sockaddr_in server;
        unsigned int s;
        int slen = sizeof(server);
        char buf [maxBufferLength];
        char message [maxBufferLength];
        WSADATA wsa;



};

#endif // CLIENTCORE_H
