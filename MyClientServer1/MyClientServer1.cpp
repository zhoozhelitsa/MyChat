#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <vector>
#include <iostream>
#include "MyClientServer1.h"
#include <thread>
#include <unordered_map>

#pragma warning(disable: 4996)

std::unordered_map<int, SOCKET> ConnectionMAP;

void ClientHandler(int indexClient) {
    char message[128];
    while (true) {
        auto itr = ConnectionMAP.find(indexClient);
        if (itr == ConnectionMAP.end())
            break;
        recv(itr->second, message, sizeof(message), NULL);
        if (message[0] == '0') {
            std::cout << "close connection " << indexClient << "\n";

            closesocket(itr->second);
            ConnectionMAP.erase(itr);
            break;
        }
        
        for (auto element : ConnectionMAP) {
            if (element.first != indexClient)
                send(element.second, message, sizeof(message), NULL);
        }
    }
}

void NewConnectionCreator(const SOCKET& sListen, SOCKADDR_IN& addr, int& addr_size, int indexCL) {
    SOCKET newConnection = accept(sListen, (SOCKADDR*)&addr, &addr_size);
    if (!newConnection) {
        std::cerr << "Error 2\n";
    }
    else {
        std::cout << "Client Connected\n";
        char msg[64] = "Welcome";
        send(newConnection, msg, sizeof(msg), NULL);
        ConnectionMAP.emplace(indexCL, newConnection);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(indexCL), NULL, NULL);

    }
}

int main()
{
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cerr << "Error\n";
        exit(1);
    }

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;
    int addr_size = sizeof(addr);

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    for (int i = 0; i < 100; i++) {
        NewConnectionCreator(sListen, addr, addr_size, i);
    }

    system("pause");
    return 0;
}
