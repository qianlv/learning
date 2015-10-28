# encoding=utf-8


class Task(object):
    taskid = 0

    def __init__(self, target):
        Task.taskid += 1
        self.tid = Task.taskid
        self.target = target
        self.sendval = None

    def run(self):
        return self.target.send(self.sendval)

    def __str__(self):
        return 'Task {} {}'.format(self.tid, str(self.target))

    __repr__ = __str__


def foo():
    print 'Part 1'
    yield           # trap -> the program suspends
    print 'Part 2'
    yield           # trap -> the program suspends

if __name__ == '__main__':
    t1 = Task(foo())
    t1.run()
    t1.run()
