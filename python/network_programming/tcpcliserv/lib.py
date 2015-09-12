""" lib
"""
# encoding=utf-8

import errno
import socket
from contextlib import wraps


def entry_retry(func, *args):
    while True:
        try:
            return func(*args)
        except IOError as err:
            if err.args[0] == errno.EINTR:
                continue
            raise


def interrupted(func):
    """ recall func() interrupt by signal """
    @wraps(func)
    def inner(*args, **kwargs):
        while True:
            try:
                func(*args, **kwargs)
            except IOError as err:
                if err.args[0] == errno.EINTR:
                    continue
                raise
    return inner


def tcp_connect(hostname, server):
    addrinfo = socket.getaddrinfo(
        hostname,
        server,
        socket.AF_UNSPEC,
        socket.SOCK_STREAM,
    )

    for family, socktype, proto, canonname, sockaddr in addrinfo:
        print canonname
        sock = socket.socket(family, socktype, proto)
        try:
            sock.connect(sockaddr)
        except socket.error as err:
            print 'Connect error: {0}, {1}'.format(err.args[0], err.args[1])
            sock.close()
            sock = None

        if sock:
            return sock
    return None


