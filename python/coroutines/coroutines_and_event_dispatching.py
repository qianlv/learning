# encoding=utf-8

import time
import xml.sax
import xml.sax.handler
import xml.parsers.expat
from coroutine import coroutine
from functools import partial


class EventHandler(xml.sax.handler.ContentHandler):
    def __init__(self, target):
        self.target = target

    def startElement(self, name, attrs):
        self.target.send(('start', (name, attrs._attrs)))

    def characters(self, text):
        self.target.send(('text', text))

    def endElement(self, name):
        self.target.send(('end', name))


@coroutine
def printer():
    while True:
        event = (yield)
        print event


@coroutine
def buses_to_dicts(target):
    while True:
        event, value = (yield)
        if event == 'start' and value[0] == 'bus':
            busdict = {}
            fragments = []
            while True:
                event, value = (yield)
                if event == 'start':
                    fragments = []
                elif event == 'text':
                    fragments.append(value)
                elif event == 'end':
                    if value != 'bus':
                        busdict[value] = ''.join(fragments)
                    else:
                        target.send(busdict)
                        break


@coroutine
def filter_on_field(fieldname, value, target):
    while True:
        d = (yield)
        if d.get(fieldname) == value:
            target.send(d)


@coroutine
def bus_location():
    while True:
        bus = (yield)
        print '''{route} {id} "{direction}",{latitude},{longitude}'''.format(**bus)


# a C extension module
def expat_parse(f, target):
    parser = xml.parsers.expat.ParserCreate()
    parser.buffer_size = 65536
    parser.buffer_text = True
    parser.returns_unicode = False
    parser.StartElementHandler = lambda name, attrs: target.send(('start', (name, attrs)))
    parser.EndElementHandler = \
        lambda name: target.send(('end', name))
    parser.CharacterDataHandler = \
        lambda data: target.send(('text', data))
    parser.ParseFile(f)

if __name__ == '__main__':
    # xml.sax.parse('allroutes.xml', EventHandler(printer()))

    # xml.sax.parse('allroutes.xml',
    #               EventHandler(buses_to_dicts(printer())))

    filter_func = partial(filter_on_field, target=printer())
    filter_func2 = partial(filter_on_field, target=bus_location())
    # xml.sax.parse('allroutes.xml',
    #                EventHandler(buses_to_dicts(filter_func('route', '22'))))
    # xml.sax.parse('allroutes.xml',
    #                EventHandler(buses_to_dicts(filter_func2('direction', 'North Bound'))))
    st = time.clock()
    xml.sax.parse(
        'allroutes.xml',
        EventHandler(
            buses_to_dicts(
                filter_on_field(
                    "route", "22",
                    filter_on_field(
                        "direction", "North Bound", bus_location())))))
    print time.clock() - st

    st = time.clock()
    expat_parse(
        open('allroutes.xml'),
        buses_to_dicts(
            filter_on_field(
                "route", "22",
                filter_on_field(
                    "direction",
                    "North Bound",
                    bus_location()
                )))
    )
    print time.clock() - st
