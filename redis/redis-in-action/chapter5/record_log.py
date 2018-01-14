#!/usr/bin/env python
# -*- coding: utf-8 -*-

import logging
import time
from datetime import datetime
import redis

SEVERITY = {
    logging.DEBUG: 'debug',
    logging.INFO: 'info',
    logging.WARNING: 'warning',
    logging.ERROR: 'error',
    logging.CRITICAL: 'critical',
}

SEVERITY.update((name, name) for name in SEVERITY.values())
print(SEVERITY)


def log_recent(conn, name, message, serverity=logging.INFO, pipe=None):
    serverity = str(SEVERITY.get(serverity, serverity)).lower()
    destination = 'recent:{0}:{1}'.format(name, serverity)
    message = time.asctime() + ' ' + message
    pipe = pipe or conn.pipeline()
    pipe.lpush(destination, message)
    pipe.ltrim(destination, 0, 99)
    pipe.execute()


def log_common(conn, name, message, serverity=logging.INFO, timeout=5):
    serverity = str(SEVERITY.get(serverity, serverity)).lower()
    destination = 'common:{0}:{1}'.format(name, serverity)
    start_key = destination + ':start'
    pipe = conn.pipeline()
    end = time.time() + timeout
    while time.time() < end:
        try:
            pipe.watch(start_key)
            now = datetime.utcnow().timetuple()
            hour_start = datetime(*now[:4]).isoformat()

            existing = pipe.get(start_key)
            pipe.multi()
            if existing and existing < hour_start:
                pipe.rename(destination, destination + ':last')
                pipe.rename(start_key, destination + ':pstart')
                pipe.set(start_key, hour_start)

            pipe.zincrby(destination, message)
            log_recent(pipe, name, message, serverity, pipe)
            return
        except redis.exceptions.WatchError:
            continue
