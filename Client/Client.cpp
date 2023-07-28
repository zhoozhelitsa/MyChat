#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <vector>
#include <iostream>

#pragma warning(disable: 4996)

SOCKET Connection;

BOOL CtrlHandler(DWORD fdwCtrlType) {
    const char* msg = "0";
    switch (fdwCtrlType) {
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        std::cout << "App close... " << std::endl;
        send(Connection, msg, sizeof(msg), NULL);
        return FALSE;
    default:
        return FALSE;
    }
}

void ServerHandler() {
    char message[128];
    while (true) {
        recv(Connection, message, sizeof(message), NULL);
        std::cout << "Anonim: ";
        std::cout << message << std::endl;
    }
}

int main()
{
    if (!SetConsoleCtrlHandler(reinterpret_cast<PHANDLER_ROUTINE>(CtrlHandler), TRUE)) {
        std::cerr << "Error Console Handler" << std::endl;
        return 1;
    }

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

    Connection = socket(AF_INET, SOCK_STREAM, NULL);
    
    if (connect(Connection, (SOCKADDR*)&addr, addr_size)) {
        std::cerr << "Error 2\n";
        system("pause");
        return 1;
    }
    std::cout << "Connection succsess!\n";

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ServerHandler, NULL, NULL, NULL);
    char message[128];
    while (true) {
        std::cin.getline(message, sizeof(message));
        send(Connection, message, sizeof(message), NULL);
        if (message == "exit") {
            break;
        }
        Sleep(10);
    }

    system("pause");

    return 0;
}

