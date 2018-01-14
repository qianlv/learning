#!/usr/bin/env python
# -*- coding: utf-8 -*-
import json
import time
import functools
import redis

LAST_CHECKED = None
IS_UNER_MAINTENANCE = False


def is_under_maintenance(conn):
    global LAST_CHECKED, IS_UNER_MAINTENANCE

    if LAST_CHECKED is None or LAST_CHECKED < time.time() - 1:
        LAST_CHECKED = time.time()
        IS_UNER_MAINTENANCE = bool(
            conn.get('is-under-maintenance'))

    return IS_UNER_MAINTENANCE


def set_config(conn, type, component, config):
    conn.set(
        'config:%s:%s' % (type, component),
        json.dumps(config))


CONFIGS = {}
CHECKED = {}


def get_config(conn, type, component, wait=1):
    key = 'config:%s:%s' % (type, component)

    if CHECKED.get(key) < time.time() - wait:
        CHECKED[key] = time.time()
        config = json.loads(conn.get(key) or '{}')
        old_config = CONFIGS.get(key)

        if config != old_config:
            CONFIGS[key] = config

    return CONFIGS.get(key)


REDIS_CONNECTIONS = {}
config_connection = redis.Redis()


def redis_connection(component, wait=1):
    key = 'config:redis:' + component

    def wrapper(function):
        @functools.wraps(function)
        def call(*args, **kwargs):
            old_config = CONFIGS.get(key, object())
            _config = get_config(
                config_connection, 'redis', component, wait)

            config = {}
            for k, v in _config.iteritems():
                config[k.encode('utf-8')] = v

            if config != old_config:
                REDIS_CONNECTIONS[key] = redis.Redis(**config)

            return function(
                REDIS_CONNECTIONS.get(key), *args, **kwargs)
        return call
    return wrapper

