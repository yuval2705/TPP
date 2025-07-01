import socket
import typing
from enum import Enum

DEFAULT_SERVER_IP = "127.0.0.1"
DEFAULT_SERVER_PORT = 33333
MESSAGE_LEN_SIZE = 4


class Client_Command(Enum):
    EXIT = "exit"
    PING = "ping"

def init_socket(server_ip:str, server_port:int):
    client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    client_sock.connect((server_ip, server_port))
    return client_sock

def send_message_to_server(sock:socket.socket, msg:str):
    sock.send(len(msg).to_bytes(4, byteorder='little', signed=False))
    sock.send(msg.encode())

def get_server_response(sock:socket.socket):
    msg_len = sock.recv(MESSAGE_LEN_SIZE)
    msg_len = int(msg_len)
    return sock.recv(msg_len)

def start_client():
    client_sock = init_socket(DEFAULT_SERVER_IP, DEFAULT_SERVER_PORT)

    command = input("The command to execute: ")
    while command != Client_Command.EXIT:
        send_message_to_server(client_sock, "sending ping")

        # server_response = get_server_response(client_sock)
        #print(f"Server sent: {server_response}")
        command = input("The command to execute: ")

def main():
    start_client()

if __name__ == "__main__":
    main()
