# encoding=utf-8


def coroutine(func):
    def start(*args, **kwargs):
        cr = func(*args, **kwargs)
        cr.send(None)
        return cr
    return start
