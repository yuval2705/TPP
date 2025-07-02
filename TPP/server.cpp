#include "server.h"
#include <iostream>
#include <ws2tcpip.h>

SOCKET ManagementServer::getListeningSocket() {
    return this->m_listeningSocket;
}

fd_set* ManagementServer::getOpenSockets() {
    return this->m_openSockets;
}

SOCKET ManagementServer::initListeningSocket(std::string ip, int port) {
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    // Resolve the local address and port to be used by the server


    SOCKET listenSocket = INVALID_SOCKET;
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return NULL;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddr.sin_port = htons((u_short)port);

    int bindingRes = bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (bindingRes == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return NULL;
    }

    return listenSocket;
}

void ManagementServer::acceptConnection() {
    SOCKET clientSocket = accept(this->getListeningSocket(), NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Failed accept with error " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }
    FD_SET(clientSocket, this->m_openSockets);
}

ManagementServer::ManagementServer(std::string ip, int port)
    : m_listeningSocket(ManagementServer::initListeningSocket(ip, port)), m_openSockets(new fd_set()) {
    FD_ZERO(this->m_openSockets);

    if (this->getListeningSocket() != NULL) {
        FD_SET(this->getListeningSocket(), this->getOpenSockets());
    }

    this->m_actionStringMappings = ManagementServer::initActionToStringMapping();
}

ManagementServer::~ManagementServer() {
    closesocket(this->m_listeningSocket);
    delete this->m_openSockets;
    for (int i = 0; i < NUM_OF_ACTIONS; i++) {
        delete this->m_actionStringMappings[i];
    }
    delete[] this->m_actionStringMappings;
    WSACleanup();
}


std::string** ManagementServer::initActionToStringMapping() {
    std::string** stringMappings = new std::string*[NUM_OF_ACTIONS];
    stringMappings[static_cast<unsigned int>(ManagementServer::Action::PING)] = new std::string("ping");
    stringMappings[static_cast<unsigned int>(ManagementServer::Action::UNSUPPORTED_ACTION)] = new std::string("NULL");

    return stringMappings;
}

void ManagementServer::closeConnection(SOCKET sock) {
    if (FD_ISSET(sock, this->m_openSockets)) {
        FD_CLR(sock, this->m_openSockets);
    }
    closesocket(sock);
}

std::string ManagementServer::handleReceive(SOCKET clientSock) {
    int requestSize = 0;
    int bytesReceived = recv(clientSock, reinterpret_cast<char*>(&requestSize), sizeof(requestSize), 0);

    // Connection closing
    if (bytesReceived == 0) {
        this->closeConnection(clientSock);
        return std::string("");
    }
    if (bytesReceived < 0) {
        this->closeConnection(clientSock);
        return std::string("");
    }

    char* recvBuf = new char[requestSize+1]{0};
    bytesReceived = recv(clientSock, recvBuf, requestSize, 0);

    // Connection closing
    if (bytesReceived == 0) {
        this->closeConnection(clientSock);
        return std::string("");
    }
    if (bytesReceived < 0) {
        this->closeConnection(clientSock);
        return std::string("");
    }

    std::string retString = std::string(recvBuf);
    delete[] recvBuf;
    return retString;
}

ManagementServer::Action ManagementServer::mapRequestToAction(const std::string& request) {
    for (int i = 1; i < ManagementServer::NUM_OF_ACTIONS; i++) {
        std::string* currAction =  this->m_actionStringMappings[i];
        if (currAction == NULL) {
            return ManagementServer::Action::UNSUPPORTED_ACTION;
        }
        
        if (request.length() < currAction->length()) {
            continue;
        }

        if (request.compare(0, currAction->length(), currAction->c_str()) == 0) {
            return static_cast<ManagementServer::Action>(i);
        }
    }
    return ManagementServer::Action::UNSUPPORTED_ACTION;
}

void ManagementServer::handlePing(SOCKET clientSock) {
    this->handleSend(clientSock, "PONG");
}

void ManagementServer::handleRequest(SOCKET clientSock, std::string& request) {
    ManagementServer::Action action = this->mapRequestToAction(request);
    switch (action) {
        case ManagementServer::Action::PING:
            this->handlePing(clientSock);
            break;
        default:
            break;
    }
}

void ManagementServer::handleSend(SOCKET clientSock, const std::string& response) {
    int responseLen = response.length();
    int sendResult = send(clientSock, reinterpret_cast<char*>(&responseLen), sizeof(responseLen), 0);
    if (sendResult == SOCKET_ERROR) {
        //handle closing socket!
        std::cout << "got error: " << WSAGetLastError() << std::endl; 
        this->closeConnection(clientSock);
        return;
    }

    sendResult = send(clientSock, response.c_str(), responseLen, 0);
    if (sendResult == SOCKET_ERROR) {
        // handle closing socket!
        this->closeConnection(clientSock);
        std::cout << "got error: " << WSAGetLastError() << std::endl; 
        return;
    }
}

void ManagementServer::start() {
    std::cout << "starting the sever" << std::endl;
    if (listen(this->m_listeningSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "Failed listening with error " << WSAGetLastError() << std::endl;
        this->closeConnection(this->m_listeningSocket);
        WSACleanup();
        return;
    }
        
    while (TRUE) {
        fd_set readables = *this->getOpenSockets();
        int count = select(0, &readables, NULL, NULL, NULL);
        for (unsigned i = 0; i < readables.fd_count; i++) {
            if (readables.fd_array[i] == this->m_listeningSocket) {
                this->acceptConnection();
            } else {
                std::string request = this->handleReceive(readables.fd_array[i]);
                if (request != "")
                {
                    this->handleRequest(readables.fd_array[i], request);
                }
            }
        }
    }

    this->closeConnection(this->m_listeningSocket);
    WSACleanup();
}