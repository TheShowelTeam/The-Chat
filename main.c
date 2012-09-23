#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <windows.h>
#include "libws2_32.a"

#pragma comment(lib, "libws2_32.a") //говорим компилятору что нужна библиотека Ws2_32.lib

int
main(void)
{
    WSADATA wsaData; //инициализмруем библиотеку Ws2_32.lib
    int res = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (res)
    {
        printf("Unable to initiate lib, tard\n");
        return 0;
    }

    return 0;
}
