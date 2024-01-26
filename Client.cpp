/*
Ryan Tu 
Fall 2023 
TCP/IP Lab 
Client File 
*/

#include <windows.networking.sockets.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#pragma comment (lib, "Ws2_32.lib")

int main()
{
	// create WSADATA object
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "ERROR: Failed to start WSA" << std::endl;
		return 0;
	}

	// create client socket 
	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		std::cout << "ERROR: Failed to create ServerSocket" << std::endl;
		return 0;
	}

	// create connection
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_port = htons(27500);
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) 
	{
		closesocket(ClientSocket);
		WSACleanup();
		std::cout << "ERROR: Connection attempted failed" << std::endl;
		return 0;
	}

	Sleep(2000); // wait for 2s after establishing a connection

	// create data string and send it 
	char data_string [] = "Hello World";
	send(ClientSocket, data_string, strlen((data_string)-1), 0); 

	std::cout << "completed send\n" << std::endl;

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();
	
	return 0; 
}