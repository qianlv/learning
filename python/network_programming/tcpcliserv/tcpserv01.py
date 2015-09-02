''' tcpser01
'''
# encoding=utf-8

import socket
import os
import signal

from lib import entry_retry

MAX_RECV = 16


def str_echo(client_sock):
    ''' str_echo '''
    print "client {0} start".format(os.getpid())
    while True:
        data = entry_retry(client_sock.recv, MAX_RECV)
        if data:
            print data
            client_sock.sendall(data)
        else:
            break
    print "client {0} stop".format(os.getpid())


def reap_child(sig, stack):
    ''' reap_child '''
    while True:
        try:
            pid, _ = os.waitpid(
                -1,
                os.WNOHANG
            )
        except OSError:
            return

        if pid == 0:
            return
        else:
            print "child {0} terminated\n".format(os.getpid())


def server(address, listen_size):
    ''' server '''
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.bind(address)
    server_sock.listen(listen_size)
    signal.signal(signal.SIGCHLD, reap_child)
    while True:
        client_sock, _ = entry_retry(server_sock.accept)
        pid = os.fork()
        if pid == 0:
            server_sock.close()
            str_echo(client_sock)
            client_sock.close()
            os._exit(0)

        client_sock.close()


if __name__ == '__main__':
    print "server wait on port 8888..."
    server(('', 8888), 5)
