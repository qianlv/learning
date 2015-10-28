# encoding=utf-8


# A subroutine
def add(x, y):
    yield x + y


# A function that calls a subroutines.
def main():
    r = yield add(2, 2)
    print r
    yield


def run():
    m = main()
    # An example of a 'trampoline'
    sub = m.send(None)
    result = sub.send(None)
    m.send(result)

if __name__ == '__main__':
    run()
