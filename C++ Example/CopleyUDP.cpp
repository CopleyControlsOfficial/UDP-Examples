// CopleyUDP.cpp : This file contains definitions for the functions declared in UDPExample.h

#include "CopleyUDP.h"

void UDPSocket::SendTo(const std::string& address, unsigned short port, const char* buffer, int len, int flags)
{
    sockaddr_in add;
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr(address.c_str());
    //add.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", address.c_str());
    add.sin_port = htons(port);
    int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
    //std::cout << ret;
    if (ret < 0)
        throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
}

int UDPSocket::RecvFrom(char* buffer, int len, int flags)
{
    sockaddr_in from;
    int size = sizeof(from);
    int ret = recvfrom(sock, buffer, len, flags, reinterpret_cast<SOCKADDR*>(&from), &size);
    if (ret < 0)
        throw std::system_error(WSAGetLastError(), std::system_category(), "recvfrom failed");
    // make the buffer zero terminated
    buffer[ret] = 0;
    return ret;
}

void UDPSocket::Bind(unsigned short port)
{
    sockaddr_in add;
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = htonl(INADDR_ANY);
    add.sin_port = htons(port);

    int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
    if (ret < 0)
        throw std::system_error(WSAGetLastError(), std::system_category(), "Bind failed");
}
