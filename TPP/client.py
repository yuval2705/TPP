import socket
import typing
from enum import Enum
import argparse

DEFAULT_SERVER_IP = "127.0.0.1"
DEFAULT_SERVER_PORT = 33333
MESSAGE_LEN_SIZE = 4


class ClientCommand(str, Enum):
    EXIT = "exit"
    PING = "ping"


def init_socket(server_ip: str, server_port: int) -> socket.socket:
    """
    Creates a TCP socket to communicate with a server with the given ip and port.
    
    @param server_ip, The IPv4 address of the server.
    @param server_port, The port the server is listening on.
    @return A TCP socket connected to the server.
    """
    client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    client_sock.connect((server_ip, server_port))
    return client_sock


def send_message_to_server(sock: socket.socket, msg: str) -> None:
    """
    Sends a message to the server.

    @param sock, The socket used to communicate with the server.
    @param msg, The message to send to the server.
    """
    sock.send(len(msg).to_bytes(MESSAGE_LEN_SIZE, byteorder='little', signed=False))
    sock.send(msg.encode())


def receive_from_server(sock: socket.socket) -> bytes:
    """
    Called when a reponse/message is to be received from the server.

    @param sock, The socket used to communicate with the server.
    @return The bytes received from the server.
    """
    msg_len:bytes = sock.recv(MESSAGE_LEN_SIZE)
    msg_len = int.from_bytes(msg_len, byteorder='little', signed=False)
    return sock.recv(msg_len)


def handle_ping(sock: socket.socket) -> None:
    """
    Handles the action associated with ping.
    (sends the message `ping` to the server)

    @param sock, The socket used to communicate with the server.
    """
    send_message_to_server(sock, "ping")


def start_client(server_addr: str, server_port: int) -> None:
    """
    Starts the client side. Handles the communication with the server.

    @param server_addr, The IPv4 address of the server.
    @param server_port, The port the server is listening on.
    """
    client_sock = init_socket(server_addr, server_port)

    command = input("The command to execute: ")
    while command != ClientCommand.EXIT:
        if command == ClientCommand.PING:
            handle_ping(client_sock)
            server_response = receive_from_server(client_sock).decode()
            print(f"Server sent: {server_response}")

        command = input("The command to execute: ")


def init_argparser() -> argparse.ArgumentParser:
    """
    Inits the argparser used in the Management client app.
    """
    argparser = argparse.ArgumentParser("Management Client")
    argparser.add_argument("--address", type=str, default=DEFAULT_SERVER_IP,
                           help=f"The IPv4 address of the server (default is {DEFAULT_SERVER_IP}.")
    argparser.add_argument("--port", type=int, default=DEFAULT_SERVER_PORT,
                           help=f"The port of the server (default is {DEFAULT_SERVER_PORT}.")
    return argparser


def main():
    args = init_argparser().parse_args()
    start_client(args.address, args.port)


if __name__ == "__main__":
    main()
