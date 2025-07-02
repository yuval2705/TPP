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

    /*
    * @brief Creates the main listening socket of the server.
    * 
    * @param ip [IN] The IPv4 address of the server.
    * @param port [IN] The port that the server should listen on.
    * 
    * @return A new TCP `SOCKET` listening on the given ip and port.
    */
    static SOCKET initListeningSocket(std::string ip, int port);

    /*
    * @brief Creates an array that the indexs are the Actions and the values are their string represention.
    * 
    * @return An Array of pointers to strings represeting the Actions.
    */
    static std::string** initActionToStringMapping();

    /*
    * @brief Accepts new connection from the main listening socket.
    * It adds them to the open sockets set.
    */
    void acceptConnection();

    /*
    * @brief Handle the different requests sent by the client.
    * 
    * @param clientSock [IN] The socket representing the connection.
    * @param request [IN] The request itself sent from the given socket.
    */
    void handleRequest(SOCKET clientSock, std::string& request);

    /*
    * @brief Receives a message from the given socket.
    * 
    * @param clientSock [IN] The socket to receive from.
    * @return A `std::string` object with the data of the request.
    */
    std::string handleReceive(SOCKET clientSock);

    /*
    * @brief Sends a message to the given socket.
    * It first sends the size of the data and then the data itself.
    * 
    * @param clientSock [IN] The socket to send through.
    * @param response [IN] The response to send back.
    */
    void handleSend(SOCKET clientSock, const std::string& response);

    /*
    * @brief Handles the `PING` request, sends `pong` to the client.
    * 
    * @param clientSock [IN] The socket to reponse to.
    */
    void handlePing(SOCKET clientSock);

    /*
    * @brief Called everytime a connection (socket) needs to be closed.
    * Closes the socket, remove it from the server and cleansup after.
    * 
    * @param sock [IN] The socket representing the connection to close.
    */
    void closeConnection(SOCKET sock);
  public:
    static const int NUM_OF_ACTIONS = 2;
    enum class Action : unsigned int
    {
        UNSUPPORTED_ACTION = 0,
        PING = 1
    };

    /*
    * @brief Returns the `Action` from the given request.
    * 
    * @param request [IN] The request itself to get what Action it is.
    * @return `Action` to perform from the given request.
    */
    Action mapRequestToAction(const std::string& request);

    /*
    * @brief CTOR for the server.
    * 
    * @param ip [IN] The IPv4 address of the server.
    * @param port [IN] The port that the server should listen on.
    */
    ManagementServer(std::string ip, int port);

    /*
    * @brief DTOR for the server.
    * Cleans up the server when deleted.
    */
    ~ManagementServer();

    /*
    * @brief Starts the server listening loop and for shorts just starts the server.
    */
    void start();

    /*
    * @brief Returns the main listening socket of the server.
    * 
    * @return The main listening socket of the server.
    */
    SOCKET getListeningSocket();

    /*
    * @brief Return the `fd_set*` of the server that contains all the open sockets that the server has.
    * 
    * @return `fd_set*` that has all the open sockets of the server.
    */
    fd_set* getOpenSockets();
};