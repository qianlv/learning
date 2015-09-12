# encoding=utf-8

import socket
import sys

from lib import tcp_connect

def daytimecli(hostname, service):
    _, _, iplist = socket.gethostbyname_ex(hostname)
    print iplist
    port = socket.getservbyname(service)
    for ip in iplist:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        try:
            sock.connect((ip, port))
        except socket.error as err:
            print 'connect error: {0}, {1}'.format(err.args[0], err.args[1])
            sock.close()
            sock = None
            continue
        break
    if sock:
        msg = sock.recv(1024)
        print msg

def daytimecli1(hostname, service):
    sock = tcp_connect(hostname, service)
    if sock:
        msg = sock.recv(1024)
        print msg

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print 'usage: python daytimetcpcli1.py <hostname> <service>'
    else:
        # daytimecli(sys.argv[1], sys.argv[2])
        daytimecli1(sys.argv[1], sys.argv[2])
