
#define WINVER 0x0501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

enum
{
    DEFAULT_PORT = 27015
};

int
main(void)
{
    WSADATA wsaData;                               //contains info about sockets

    int iResult;                                   //variable is needed for testin dem functions

    iResult = WSAStartup(MAKEWORD(2,2), &wsaData); //init freakin' WS2_32.lib
    if (iResult)
    {
        printf("Lib aint started. Error num: %d\n", iResult);
        return 1;
    }

    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    printf("nice\n");
    // Resolve the local address and port to be used by the server
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    WSACleanup();
    return 0;
}

