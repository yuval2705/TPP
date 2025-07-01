#include "server.h"
#include <iostream>


#define DEFAULT_BUFFER_LEN (512)

SOCKET ManagementServer::getListeningSocket()
{
    return this->m_listening_socket;
}

fd_set* ManagementServer::getOpenSockets()
{
    return this->m_openSockets;
}

SOCKET ManagementServer::init_listening_socket(std::string ip, int port)
{

    // Resolve the local address and port to be used by the server

    SOCKET listenSocket = INVALID_SOCKET;
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return NULL;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddr.sin_port = htons((u_short)port);

    int bindingRes = bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (bindingRes == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return NULL;
    }

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


ManagementServer::ManagementServer(std::string ip, int port)
    : m_listening_socket(ManagementServer::init_listening_socket(ip, port)), m_openSockets(new fd_set())
{
    if (this->getListeningSocket() != NULL)
    {
        FD_SET(this->getListeningSocket(), this->getOpenSockets());
    }
}

ManagementServer::~ManagementServer()
{
    closesocket(this->m_listening_socket);
    delete this->m_openSockets;
    WSACleanup();
}


void ManagementServer::handleRequest(SOCKET clientSock)
{
    char recvBuf[DEFAULT_BUFFER_LEN];
    int bytesReceived = recv(clientSock, recvBuf, sizeof(recvBuf), 0);
    if (bytesReceived <= 0)
    {
        // need to handle this one!
        return;
    }
    std::cout << recvBuf << std::endl;
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
        
    while (TRUE)
    {
        fd_set readables = *this->getOpenSockets();
        int count = select(0, &readables, NULL, NULL, NULL);

        for (unsigned i = 0; i < readables.fd_count; i++)
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