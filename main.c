#define WINVER 0x0501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_PORT "60000"

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

    struct addrinfo *result = NULL, *ptr = NULL, hints; // addrinfo contains info about address family, IP addr, port

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result); // result contains of info which is used for socket
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    SOCKET listening_socket = INVALID_SOCKET;                  //initializing our god damn socket, only for waiting for clients

    listening_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (listening_socket == INVALID_SOCKET) {
        printf("Error at socket(): %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    //binding socket with a internet adress within da system

    iResult = bind(listening_socket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(listening_socket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result); // dat info is useless binding

    //now socket is bound to an IP address and port on the system
    //listen func waits on socket for incoming connection requests
    //SOMAXCONN contains number of pending connections

    if (listen(listening_socket, SOMAXCONN ) == SOCKET_ERROR ) {
        printf( "Listen failed with error: %d\n", WSAGetLastError() );
        closesocket(listening_socket);
        WSACleanup();
        return 1;
    }

    printf("nice\n");

    SOCKET ClientSocket = INVALID_SOCKET; // socket for connecting with client

    // Accept a client socket
    ClientSocket = accept(listening_socket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accepting connection failed: %d\n", WSAGetLastError());
        closesocket(listening_socket);
        WSACleanup();
        return 1;
    }



    WSACleanup();
    return 0;
}

