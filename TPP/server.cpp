#include "server.h"
#include <WSPiApi.h>
#include <iostream>

SOCKET ManagementServer::init_listening_socket(std::string ip, int port)
{
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    int iResult = getaddrinfo(NULL, DEFAULT_MANAGER_SERVER_PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return NULL;
    }

    SOCKET listenSocket = INVALID_SOCKET;
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return NULL;
    }


    iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return NULL;
    }
    freeaddrinfo(result);

    return listenSocket;
}


void ManagementServer::acceptConnection()
{
    SOCKET clientSocket = accept(this->getListeningSocket(), NULL, NULL);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Failed accept with error " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }

    FD_SET(clientSocket, this->getOpenSockets());
}


void ManagementServer::start()
{
    if (listen(this->m_listening_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cout << "Failed listening with error " << WSAGetLastError() << std::endl;
        closesocket(this->m_listening_socket);
        WSACleanup();
        return;
    }
        
    SOCKET client_socket = INVALID_SOCKET;
    while (TRUE)
    {
        fd_set readables = *this->getOpenSockets();
        int count = select(0, &readables, NULL, NULL, NULL);

        for (int i = 0; i < readables.fd_count; i++)
        {
            if (readables.fd_array[i] == this->m_listening_socket)
            {
                this->acceptConnection();
            }
            else
            {
                this->handleRequest(readables.fd_array[i]);
            }
        }
    }


}