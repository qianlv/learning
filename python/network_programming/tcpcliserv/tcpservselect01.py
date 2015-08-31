# encoding=utf-8

import socket
import select

from lib import entry_retry

MAX_RECV = 16


def str_echo(client_sock):
    while True:
        data = entry_retry(client_sock.recv, MAX_RECV)
        if data:
            print data
            client_sock.sendall(data)
        else:
            break


def server(address, listen_size):
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.bind(address)
    server_sock.listen(listen_size)

    rset = [server_sock]
    while True:
        rlist, _, _ = entry_retry(
            select.select, rset, [], [],
        )

        for sock in rlist:
            if server_sock == sock:
                client_sock, client_adress = entry_retry(sock.accept)
                print client_sock
                rset.append(client_sock)
            else:
                data = entry_retry(sock.recv, MAX_RECV)
                if not data:
                    sock.close()
                    rset.remove(sock)
                    continue
                sock.sendall(data)


if __name__ == '__main__':
    print "server wait on port 8888..."
    server(('', 8888), 5)
