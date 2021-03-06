""" a simple asynchronous tcp client """
# encoding=utf-8

import socket
# import time
import signal
import sys
import select
from lib import entry_retry

MAX_RECV = 1024


def readn(client_sock, size):
    data = entry_retry(client_sock.recv, size)
    return data


def str_cli(client_sock):
    stdineof = False
    inputlist = [sys.stdin, client_sock]
    while True:
        rlist, _, _ = entry_retry(
            select.select, inputlist, [], []
        )

        print rlist
        if sys.stdin in rlist:
            msg = sys.stdin.readline()
            if not msg:
                stdineof = True
                client_sock.shutdown(socket.SHUT_WR)
                inputlist.remove(sys.stdin)
                continue
            client_sock.sendall(msg)

        if client_sock in rlist:
            res_msg = readn(client_sock, MAX_RECV)
            if not res_msg:
                if stdineof:
                    return
                sys.exit("str_cli: server terminated prematurely")
            print res_msg


def handle_sigpip(sig, stack):
    print "recived a sigpipe signal"
    return


def client(address):
    client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    signal.signal(signal.SIGPIPE, handle_sigpip)
    client_sock.connect(address)
    str_cli(client_sock)


if __name__ == '__main__':
    client((sys.argv[1], int(sys.argv[2])))
