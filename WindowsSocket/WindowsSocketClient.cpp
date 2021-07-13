/**********************************************************************
**File name:WindowsSocketClient.cpp
**Author:hexiao<hexiao.hrbeu.edu.cn>    Version:1.0    Date:2020.12.24
**Description:Windows socket class 
**GPL-3.0 License Usage
**********************************************************************/
#include "WindowsSocketClient.h"

#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>


#pragma comment(lib,"ws2_32.lib")

WindowsSocketClient::WindowsSocketClient()
{
	socketClient = 0;
	port = 11411;
	addr = (char *)"127.0.0.1";
}
WindowsSocketClient::~WindowsSocketClient()
{
	closesocket(socketClient);
}

int WindowsSocketClient::init()
{
	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(socketVersion, &wsaData) != 0)
	{
		return 1;
	}
	socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketClient == INVALID_SOCKET)
	{
		return 2;
	}
	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);
	inet_pton(AF_INET, addr, &serAddr.sin_addr.S_un.S_addr);
	if (connect(    socketClient, 
                        (struct sockaddr*) & serAddr, 
                        sizeof(serAddr)) == SOCKET_ERROR)
	{
		closesocket(socketClient);
		return 3;
	}
        char value = 1;
	// close nagle 
        setsockopt (    socketClient, 
                        IPPROTO_TCP, 
                        TCP_NODELAY, 
                        &value, 
                        sizeof (value));
        // disable blocking
        u_long iMode = 1;
        ioctlsocket (socketClient, FIONBIO, &iMode);
	return 0;
}

int WindowsSocketClient::read()
{
	char data;
	int result = recv(socketClient, &data, 1, 0);
	if (result < 0)
	{
		if (WSAEWOULDBLOCK != WSAGetLastError())
		{
			//
		}
		return -1;
	}
	else if (result == 0)
	{
		return -2;
	}

	return (unsigned char)data;
}

void WindowsSocketClient::write(const unsigned char * data, int length)
{
	send(socketClient, (const char*)data, length, 0);
}

int WindowsSocketClient::configure(char* addr, uint32_t port)
{
	this->addr = addr;
	this->port = port;
	return 0;
}

unsigned long WindowsSocketClient::time()
{
	SYSTEMTIME st_now;
	GetSystemTime(&st_now);
	unsigned long millis =  st_now.wHour * 3600000 +
                                st_now.wMinute * 60000 +
                                st_now.wSecond * 1000 +
                                st_now.wMilliseconds;
	return millis;
}