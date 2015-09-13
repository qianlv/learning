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
    '''tcp connect don't care protocol'''
    hostname = hostname or None
    addrinfo = socket.getaddrinfo(
        hostname,
        server,
        socket.AF_UNSPEC,
        socket.SOCK_STREAM
    )

    sock = None
    for family, socktype, proto, _, sockaddr in addrinfo:
        try:
            sock = socket.socket(family, socktype, proto)
        except socket.error:
            continue

        try:
            sock.connect(sockaddr)
        except socket.error as err:
            print 'Connect error: {0}, {1}'.format(err.args[0], err.args[1])
            sock.close()
            sock = None

        if sock:
            break
    return sock


def tcp_listen(hostname, server, nlisten):
    '''tcp listen don't care protocol'''
    hostname = hostname or None
    addrinfo = socket.getaddrinfo(
        hostname,
        server,
        socket.AF_UNSPEC,
        socket.SOCK_STREAM,
    )

    sock = None
    for family, socktype, proto, _, sockaddr in addrinfo:
        try:
            sock = socket.socket(family, socktype, proto)
            if hasattr(socket, 'AF_INET6') and family == socket.AF_INET6:
                sock.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 0)
        except socket.error:
            continue
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            sock.bind(sockaddr)
        except socket.error as err:
            print 'Bind error: {0}, {1}'.format(err.args[0], err.args[1])
            sock.close()
            sock = None

        if sock:
            break

    if sock:
        sock.listen(nlisten)
    return sock
