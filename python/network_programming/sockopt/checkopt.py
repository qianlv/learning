""" print socket info by getsockopt """
# encoding=utf-8

import socket

LEVEL_OPTNAME = {
    0: (socket.SOL_SOCKET, socket.SO_BROADCAST),
    1: (socket.SOL_SOCKET, socket.SO_DEBUG),
    2: (socket.SOL_SOCKET, socket.SO_DONTROUTE),
    3: (socket.SOL_SOCKET, socket.SO_ERROR),
    4: (socket.SOL_SOCKET, socket.SO_KEEPALIVE),
    5: (socket.SOL_SOCKET, socket.SO_LINGER),
    6: (socket.SOL_SOCKET, socket.SO_OOBINLINE),
    7: (socket.SOL_SOCKET, socket.SO_RCVBUF),
    8: (socket.SOL_SOCKET, socket.SO_SNDBUF),
    9: (socket.SOL_SOCKET, socket.SO_RCVLOWAT),
    10: (socket.SOL_SOCKET, socket.SO_SNDLOWAT),
    11: (socket.SOL_SOCKET, socket.SO_RCVTIMEO),
    12: (socket.SOL_SOCKET, socket.SO_REUSEADDR),
    13: (socket.SOL_SOCKET, socket.SO_TYPE),
    14: (socket.IPPROTO_IP, socket.IP_TOS),
    15: (socket.IPPROTO_IP, socket.IP_TTL),
    16: (socket.IPPROTO_IPV6, socket.IPV6_UNICAST_HOPS),
    17: (socket.IPPROTO_IPV6, socket.IPV6_V6ONLY),
    18: (socket.IPPROTO_TCP, socket.TCP_MAXSEG),
    19: (socket.IPPROTO_TCP, socket.TCP_NODELAY),
}

for level, optname in LEVEL_OPTNAME.itervalues():
    if level in (socket.SOL_SOCKET, socket.IPPROTO_IP, socket.IPPROTO_TCP):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        print sock.getsockopt(level, optname)
    elif level == socket.IPPROTO_IPV6:
        sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM, 0)
        print sock.getsockopt(level, optname)
