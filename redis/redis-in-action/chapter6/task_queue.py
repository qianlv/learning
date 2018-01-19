#!/usr/bin/env python
# -*- coding: utf-8 -*-
import time
import json
import uuid
from lock import (
    acquire_lock,
    release_lock,
)

QUIT = False


def send_sold_email_via_queue(conn, seller, item, price, buyer):
    data = {
        'seller_id': seller,
        'item_id': item,
        'price': price,
        'buyer_id': buyer,
        'time': time.time()
    }

    conn.rpush('queue:email', json.dumps(data))


def fetch_data_and_send_sold_email(to_send):
    pass


def process_sold_email_queue(conn):
    while not QUIT:
        packed = conn.blpop(['queue:email'], 30)
        if not packed:
            continue

        to_send = json.loads(packed[1])
        try:
            fetch_data_and_send_sold_email(to_send)
        except Exception as err:
            print("Failed to send sold email", err, to_send)
        else:
            print("Send sold email", to_send)


def worker_watch_queue(conn, queue, callbacks):
    while not QUIT:
        packed = conn.blpop([queue], 30)
        if not packed:
            continue
        name, args = json.loads(packed[1])
        if name not in callbacks:
            print("Unknow callback %s" % name)
            continue
        callbacks[name](*args)


def worker_watch_queue_with_priority(conn, queues, callbacks):
    while not QUIT:
        packed = conn.blpop(queues, 30)
        if not packed:
            continue
        name, args = json.loads(packed[1])
        if name not in callbacks:
            print("Unknow callback %s" % name)
            continue
        callbacks[name](*args)


def execute_later(conn, queue, name, args, delay=0):
    identifier = str(uuid.uuid4())
    item = json.dumps([identifier, queue, name, args])
    if delay > 0:
        conn.zadd('delayed:', item, time.time() + delay)
    else:
        conn.rpush('queue:' + queue, item)

    return identifier


def poll_queue(conn):
    while not QUIT:
        item = conn.zrange('delayed:', 0, 0, withscores=True)
        if not item or item[0][1] > time.time():
            time.sleep(0.01)
            continue

        item = item[0][0]
        identifier, queue, function, args = json.loads(item)

        locked = acquire_lock(conn, identifier)
        if not locked:
            continue

        if conn.zrem('delayed:', item):
            conn.rpush('queue:' + queue, item)
        release_lock(conn, identifier, locked)
