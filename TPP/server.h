#pragma once
#include <string>
#include <winsock.h>


#define DEFAULT_MANAGER_SERVER_PORT (33333)
class ManagementServer
{
  private:
    SOCKET m_listening_socket;
    fd_set* m_openSockets;

    static SOCKET init_listening_socket(std::string ip, int port);
    void acceptConnection();
    void handleRequest(SOCKET clientSock);
  public:
    ManagementServer(std::string ip, int port);
    ~ManagementServer();
    void start();
    SOCKET getListeningSocket();
    fd_set* getOpenSockets();
};