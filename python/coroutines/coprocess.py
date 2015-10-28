# encoding=utf-8

import sys
from coroutines_and_event_dispatching import filter_on_field
from coroutines_and_event_dispatching import bus_location
from from_data_processing_to_concurrent_programming import recvfrom

if __name__ == '__main__':
    recvfrom(
        sys.stdin,
        filter_on_field('route', '22', filter_on_field(
            'direction', 'North Bound', bus_location())))
