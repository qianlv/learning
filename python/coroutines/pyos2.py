# encoding=utf-8
'''
Yield is a trap
Each task runs until it hits the yield,
At the point, the scheduler regains control and switchs to other task.
'''

from Queue import Queue
from pyos1 import Task


class Scheduler(object):
    def __init__(self):
        self.ready = Queue()
        self.taskmap = {}

    def new(self, target):
        newtask = Task(target)
        self.taskmap[newtask.tid] = newtask
        self.schedule(newtask)
        return newtask.tid

    def schedule(self, task):
        self.ready.put(task)

    def mainloop(self):
        while self.taskmap:
            task = self.ready.get()
            task.run()
            self.schedule(task)


def foo():
    while True:
        print "I'm foo"
        yield


def bar():
    while True:
        print "I'm bar"
        yield


def crash_foo():
    for i in range(10):
        print 'I\'ll crash myself'
        yield


if __name__ == '__main__':
    sched = Scheduler()
    sched.new(foo())
    sched.new(bar())
    sched.new(crash_foo())
    sched.mainloop()
