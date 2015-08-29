# encoding=utf-8

import errno
from contextlib import wraps


def entry_retry(func, *args):
    while True:
        try:
            return func(*args)
        except IOError as e:
            code, msg = e.args
            if code == errno.EINTR:
                continue
            raise


def interrupted(func):
    @wraps(func)
    def inner(*args, **kwargs):
        while True:
            try:
                func(*args, **kwargs)
            except IOError as e:
                code, msg = e.args
                if code == errno.EINTR:
                    continue
                raise
    return inner
