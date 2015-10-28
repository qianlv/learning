# encoding=utf-8

import threading
import time
import pickle
import subprocess
import xml.sax
from Queue import Queue
from coroutine import coroutine
from coroutines_and_event_dispatching import EventHandler
from coroutines_and_event_dispatching import buses_to_dicts
from coroutines_and_event_dispatching import filter_on_field
from coroutines_and_event_dispatching import bus_location


@coroutine
def threaded(target):
    message = Queue()

    def run_target():
        while True:
            item = message.get()
            if item is GeneratorExit:
                target.close()
                return
            else:
                target.send(item)
    threading.Thread(target=run_target).start()
    try:
        while True:
            item = (yield)
            message.put(item)
    except GeneratorExit:
        message.put(GeneratorExit)


@coroutine
def sendto(f):
    try:
        while True:
            item = (yield)
            pickle.dump(item, f)
            f.flush()
    except GeneratorExit:
        f.close()


def recvfrom(f, target):
    try:
        while True:
            item = pickle.load(f)
            target.send(item)
    except EOFError:
        target.close()


def subprocess1(p):
    xml.sax.parse(
        'allroutes.xml',
        EventHandler(buses_to_dicts(sendto(p.stdin))))

if __name__ == '__main__':
    st = time.clock()
    xml.sax.parse(
        'allroutes.xml',
        EventHandler(buses_to_dicts(threaded(
            filter_on_field(
                "route", "22",
                filter_on_field(
                    "direction", "North Bound", bus_location()))))))
    print time.clock() - st

    st = time.clock()
    p = subprocess.Popen(['python', 'coprocess.py'],
                         stdin=subprocess.PIPE)
    subprocess1(p)
    print time.clock() - st
