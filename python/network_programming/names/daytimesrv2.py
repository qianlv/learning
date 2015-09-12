''' a simple day time server'''
# encoding=utf-8

import time
import sys

from lib import tcp_listen


def daytimesrv(hostname, service):
    sock = tcp_listen(hostname, service, 10)
    while True:
        client_sock, client_address = sock.accept()
        print 'connection from {0}'.format(client_address)
        now = time.ctime()
        client_sock.sendall(now)
        client_sock.close()

if __name__ == '__main__':
    if len(sys.argv) == 2:
        daytimesrv(None, sys.argv[1])
    elif len(sys.argv) == 3:
        daytimesrv(sys.argv[1], sys.argv[2])
    else:
        print 'usage: {0} <service or port> /\
            {1} <hostname> <service or port>'.format(sys.argv[0])
