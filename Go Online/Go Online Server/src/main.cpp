#include <main.h>

Server server;

int main(int argc, char* argv[])
{
    server.init();

    while (1)
    {
        server.recvMessage();
        //std::cout << "Players online: " << server.handler.clientList.connectedClients.size() << "\n";

    }

    server.quit();
    return 0;
}

