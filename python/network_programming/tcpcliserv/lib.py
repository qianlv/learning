""" lib
"""
# encoding=utf-8

import errno
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
