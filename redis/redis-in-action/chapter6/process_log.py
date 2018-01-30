#!/usr/bin/env python
# -*- coding: utf-8 -*-
from collections import (
    defaultdict,
    deque,
)
import zlib
import os
import time
from .message_system import (
    send_message,
    create_chat,
    fetch_pending_mssages,
)


def find_city_by_ip_local(ip):
    pass


# log: ip date time msg
aggregates = defaultdict(lambda: defaultdict(int))


def daily_country_aggregate(conn, line):
    if line:
        line = line.split()
        ip = line[0]
        day = line[1]
        country = find_city_by_ip_local(ip)[2]
        aggregates[day][country] += 1
        return
    for day, aggregate in aggregates.items():
        conn.zadd('daily:country:' + day, **aggregate)
        del aggregates[day]


def _clean(conn, channel, waiting, count):
    if not waiting:
        return 0
    w0 = waiting[0][0]
    if conn.get(channel + w0 + ':done') == count:
        conn.delete(channel + w0, channel + w0 + ':done')
        return waiting.popleft()[1]
    return 0


def copy_logs_to_redis(conn, path, channel, count=10,
                       limit=2**30, quit_when_done=True):
    bytes_in_redis = 0
    waiting = deque()
    create_chat(conn, 'source', map(str, range(count)), '', channel)
    count = str(count)
    for logfile in sorted(os.listdir(path)):
        full_path = os.path.join(path, logfile)

        fsize = os.stat(full_path).st_size
        while bytes_in_redis + fsize > limit:
            cleaned = _clean(conn, channel, waiting, count)
            if cleaned:
                bytes_in_redis -= cleaned
            else:
                time.sleep(.25)
        with open(full_path, 'rb') as inp:
            block = ' '
            while block:
                block = inp.read(2**17)
                conn.append(channel + logfile, block)

        send_message(conn, channel, 'source', logfile)
        bytes_in_redis += fsize
        waiting.append((logfile, fsize))

    if quit_when_done:
        send_message(conn, channel, 'source', ':done')

    while waiting:
        cleaned = _clean(conn, channel, waiting, count)
        if cleaned:
            bytes_in_redis -= cleaned
        else:
            time.sleep(.25)


def readlines(conn, key, rblocks):
    out = ''
    for block in rblocks(conn, key):
        out += block
        posn = out.rfind('\n')
        if posn >= 0:
            for line in out[:posn].split('\n'):
                yield line + '\n'
            out = out[posn + 1:]

        if not block:
            yield out
            break


def readblocks(conn, key, blocksize=2**17):
    lb = blocksize
    pos = 0
    while lb == blocksize:
        block = conn.substr(key, pos, pos + blocksize - 1)
        yield block
        lb = len(block)
        pos += lb
    yield ''


def readblocks_gz(conn, key):
    inp = ''
    decoder = None
    for block in readblocks(conn, key):
        if not decoder:
            inp += block
            try:
                if inp[:3] != "\x1f\x8b\x08":
                    raise IOError("invalid gizp data")
                i = 10
                flag = ord(inp[3])
                if flag & 4:
                    i += 2 + ord(inp[i]) + 256 * ord(inp[i + 1])
                if flag & 8:
                    i = inp.index('\0', i) + 1
                if flag & 16:
                    i = inp.index('\0', i) + 1
                if flag & 2:
                    i += 2
                if i > len(inp):
                    raise IndexError("not enough data")
            except (IndexError, ValueError):
                continue
            else:
                block = inp[i:]
                inp = None
                decoder = zlib.decompressobj(-zlib.MAX_WBITS)
                if not block:
                    continue
        if not block:
            yield decoder.flush()
            break
        yield decoder.decompress(block)


def process_logs_from_redis(conn, id, callback):
    while True:
        fdata = fetch_pending_mssages(conn, id)

        for ch, mdata in fdata:
            for message in mdata:
                logfile = message['message']

                if logfile == ':done':
                    return
                elif not logfile:
                    continue

                block_reader = readblocks
                if logfile.endswith('.gz'):
                    block_reader = readblocks_gz

                for line in readlines(conn, ch + logfile, block_reader):
                    callback(conn, line)

                callback(conn, None)

                conn.incr(ch + logfile + ':done')

        if not fdata:
            time.sleep(.1)
