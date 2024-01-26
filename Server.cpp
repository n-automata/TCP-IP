/*
Ryan Tu 
Fall 2023 
TCP/IP Lab 
Server File 
*/

#define BUFFER_SIZE 128 // used to define buffer size, can be changed 

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    // create server socket 
    int ServerSocket;
    ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ServerSocket == -1)
    {
        std::cout << "ERROR: Failed to create ServerSocket" << std::endl;
        return 0;
    }

    // bind socket
    sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_addr.s_addr = INADDR_ANY;
    SvrAddr.sin_port = htons(27000);

    if (bind(ServerSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr)) == -1)
    {
        close(ServerSocket);
        std::cout << "ERROR: Failed to bind ServerSocket" << std::endl;
        return 0;
    }

    // listen for incoming connection
    if (listen(ServerSocket, 1) == -1)
    {
        close(ServerSocket);
        std::cout << "ERROR: listen failed to configure ServerSocket" << std::endl;
        return 0;
    }

    // accept the SYN request 
    int ConnectionSocket;
    ConnectionSocket = -1;
    if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == -1)
    {
        close(ServerSocket);
        return 0;
    }

    std::cout << "Listening" << std::endl;

    // create char array to store receive string, then perform receive function
    char received_string[BUFFER_SIZE];
    recv(ConnectionSocket, received_string, sizeof(received_string), 0);

    if (sizeof(received_string) == -1)
    {
        std::cerr << "ERROR: Failed to receive data" << std::endl;
    }
    else
    {
        std::cout << "Received: " << received_string << std::endl;
    }

    // close sockets when done 
    close(ConnectionSocket);
    close(ServerSocket);

    return 0;
}