#pragma once
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS (1)
#include <WinSock2.h>


#define DEFAULT_MANAGER_SERVER_PORT (33333)
class ManagementServer
{
  private:
    SOCKET m_listeningSocket;
    fd_set* m_openSockets;
    std::string** m_actionStringMappings;

    static SOCKET initListeningSocket(std::string ip, int port);
    static std::string** initActionToStringMapping();
    void acceptConnection();
    void handleRequest(SOCKET clientSock, std::string& request);
    std::string handleReceive(SOCKET clientSock);
    void handleSend(SOCKET clientSock, const std::string& response);
    void handlePing(SOCKET clientSock);
    void closeConnection(SOCKET sock);
  public:
    static const int NUM_OF_ACTIONS = 2;
    enum class Action : unsigned int
    {
        UNSUPPORTED_ACTION = 0,
        PING = 1
    };
    Action mapRequestToAction(const std::string& request);
    ManagementServer(std::string ip, int port);
    ~ManagementServer();
    void start();
    SOCKET getListeningSocket();
    fd_set* getOpenSockets();
};