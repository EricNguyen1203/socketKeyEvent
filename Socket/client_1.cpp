#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define _WIN32_WINNT 0x0600
#define MAX_CONNECTIONS 1
#pragma warning(disable : 4996)
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include "WinUser.h"
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

int main() {
    int iResult;
    WSADATA wsaData;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
    else
    {
        printf("Winsock DLL found!\n");
        printf("status: %s\n", wsaData.szSystemStatus);
    }

    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        printf("Cannot create a socket!\n");
        WSACleanup();
        return 1;
    }
    else
    {
        printf("socket() is OK!\n");
    }


    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_port = htons(8001); // little endian -> big endian
    PCWSTR serverPszAddrString = L"127.0.0.1";
    int result = InetPtonW(AF_INET, serverPszAddrString, &service.sin_addr.s_addr);
    if (connect(clientSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        printf("connection failed, Error: %s\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
    }
    else
    {
        printf("Connect success!\nCan send message here:......\n");
        printf("Press 'esc' if you want to escape:\n");
        char* message = new char[1001];
        /*while(true){
            printf("Input your message: ");
            char s = _getch();
            if (s == 27)
                break;
            else
                message[0] = s;
        cin.getline(message, 1001);
        
        int BytesCount = send(clientSocket, message, 1001, 0);
        if (BytesCount == SOCKET_ERROR)
        {
            printf("Something wrong!\nError: %s", WSAGetLastError());
        }
        else {*/
           /* printf("Send success, send %ld bytes to server\n", BytesCount);*/
        char thanh;
        while (true) {
            if (GetAsyncKeyState(VK_ESCAPE) & 1) {
                break;
            }
                int BytesCount = recv(clientSocket, message, 1001, 0);
                message[strlen(message)] = '\0';
                puts(message);
                int a = atoi(message);
                if (BytesCount == SOCKET_ERROR)
                {
                    printf("Something wrong!\nError: %s\n", WSAGetLastError());
                }
                else {
                    printf("Capture key event: %c, number:%d\n", a, a);
                }
        }
        //}
        //}
        delete message;

    }


    fflush(stdout);
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}