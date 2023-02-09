// CopleyUDP.h
// 
// This file contains class definitions used for socket programming
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#pragma comment (lib, "ws2_32")

#include <iostream>
#include <string>
#include <system_error>
#include <Windows.h>


class WSASession
{
public:
    WSASession()
    {
        int ret = WSAStartup(MAKEWORD(2, 2), &data);
        if (ret != 0)
            throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");
    }
    ~WSASession()
    {
        WSACleanup();
    }

private:
    WSAData data;
};

class UDPSocket
{
public:
    UDPSocket()
    {
        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock == INVALID_SOCKET)
            throw std::system_error(WSAGetLastError(), std::system_category(), "Error opening socket");
        setsockopt(sock, IPPROTO_UDP, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
    }
    ~UDPSocket()
    {
        closesocket(sock);
    }

    void SendTo(const std::string& address, unsigned short port, const char* buffer, int len, int flags = 0);
    int RecvFrom(char* buffer, int len, int flags = 0);
    void Bind(unsigned short port);

private:
    SOCKET sock;
    time_t timeout = 1;
};