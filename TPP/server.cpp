#include "server.h"

#include <iostream>
#include <ws2tcpip.h>
#include <map>
#include <functional>
#include <memory>


SOCKET ManagementServer::getListeningSocket() {
    return this->m_listeningSocket;
}

fd_set* ManagementServer::getOpenSockets() {
    return this->m_openSockets;
}

SOCKET ManagementServer::initListeningSocket(const std::string& ip, int port) {
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    // Resolve the local address and port to be used by the server


    SOCKET listenSocket = INVALID_SOCKET;
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return NULL;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddr.sin_port = htons(static_cast<u_short>(port));

    int bindingRes = bind(listenSocket, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr));
    if (bindingRes == SOCKET_ERROR) {
        std::cerr << "bind failed with error: " << WSAGetLastError() << std::endl;
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

/*
std::string** ManagementServer::initActionToStringMapping() {
    std::string** stringMappings = new std::string* [NUM_OF_ACTIONS] {NULL};
    stringMappings[static_cast<unsigned int>(ManagementServer::Action::PING)] = new std::string("ping");
    stringMappings[static_cast<unsigned int>(ManagementServer::Action::RUN)] = new std::string("run");
    stringMappings[static_cast<unsigned int>(ManagementServer::Action::UNSUPPORTED_ACTION)] = new std::string("NULL");

    return stringMappings;
}
*/


std::map<std::string, std::function<void(ManagementServer*, SOCKET, std::string&)>> ManagementServer::
    initActionToStringMapping()
{
    using namespace std::placeholders;
    std::map<std::string, std::function<void(ManagementServer*, SOCKET, std::string&)>> mappings;

    mappings.insert({"ping", std::bind(&ManagementServer::handlePing, _1, _2, _3)});
    mappings.insert({"run", std::bind(&ManagementServer::handlePing, _1, _2, _3)});
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
        return "";
    }
    if (bytesReceived < 0) {
        this->closeConnection(clientSock);
        return "";
    }

    char* recvBuf = new char[requestSize+1]{0};
    bytesReceived = recv(clientSock, recvBuf, requestSize, 0);

    // Connection closing
    if (bytesReceived == 0) {
        this->closeConnection(clientSock);
        return "";
    }
    if (bytesReceived < 0) {
        this->closeConnection(clientSock);
        return "";
    }

    std::string retString = std::string(recvBuf);
    delete[] recvBuf;
    return retString;
}

ManagementServer::Action ManagementServer::mapRequestToAction(std::string& request) {
    for (const auto& [action, handler] : this->m_actionStringMappings) {

        if (request.length() < action.length())
        {
            continue;
        }

        if (request.compare(0, action.length(), action.c_str()) == 0)
        {
            request.erase(0, action.length());
            return static_cast<ManagementServer::Action>(i);
        }
    }
    return ManagementServer::Action::UNSUPPORTED_ACTION;
}

void ManagementServer::handlePing(SOCKET clientSock) {
    this->handleSend(clientSock, "PONG");
}

void ManagementServer::handleRun(SOCKET clientSock, const std::string& request_body) {
    std::string response;

    HINSTANCE result = ShellExecuteA(NULL, NULL, request_body.c_str(), NULL, NULL, SW_SHOWDEFAULT);

    /*
        If the function succeeds, it returns a value greater than 32. If the function fails,
        it returns an error value that indicates the cause of the failure.
        The return value is cast as an HINSTANCE for backward compatibility with 16-bit Windows applications.
        It is not a true HINSTANCE, however.
        It can be cast only to an INT_PTR and compared to either 32 or the following error codes below.

        https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shellexecutea
     */
    if (reinterpret_cast<int>(result) > 32) {
        response = "File executed succesfuly!";
    } else {
        switch (reinterpret_cast<int>(result))
        {
        case ERROR_FILE_NOT_FOUND:
            response = "File not found!";
            break;
        case ERROR_PATH_NOT_FOUND:
            response = "Path not found!";
            break;
        default:
            std::cerr << GetLastError() << std::endl;
            break;
        }
    }
    this->handleSend(clientSock, response);
}

void ManagementServer::handleRequest(SOCKET clientSock, std::string& request) {
    for (const auto& [action, handler] : this->m_actionStringMappings)
    {

        if (request.length() < action.length())
        {
            continue;
        }

        if (request.compare(0, action.length(), action.c_str()) == 0)
        {
            request.erase(0, action.length());
            handler(*this, clientSock, request.substr(action.length() + 1));
        }
    }
    return ManagementServer::Action::UNSUPPORTED_ACTION;
}

void ManagementServer::handleSend(SOCKET clientSock, const std::string& response) {
    int responseLen = response.length();
    int sendResult = send(clientSock, reinterpret_cast<char*>(&responseLen), sizeof(responseLen), 0);
    if (sendResult == SOCKET_ERROR) {
        //handle closing socket!
        std::cerr << "got error: " << WSAGetLastError() << std::endl; 
        this->closeConnection(clientSock);
        return;
    }

    sendResult = send(clientSock, response.c_str(), responseLen, 0);
    if (sendResult == SOCKET_ERROR) {
        // handle closing socket!
        this->closeConnection(clientSock);
        std::cerr << "got error: " << WSAGetLastError() << std::endl; 
        return;
    }
}

void ManagementServer::start() {
    std::cout << "starting the sever" << std::endl;
    if (listen(this->m_listeningSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Failed listening with error " << WSAGetLastError() << std::endl;
        this->closeConnection(this->m_listeningSocket);
        WSACleanup();
        return;
    }
        
    while (true) {
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