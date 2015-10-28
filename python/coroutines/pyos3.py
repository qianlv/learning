# encoding=utf-8

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
            try:
                task.run()
            except StopIteration:
                self.exit(task)
                continue
            self.schedule(task)

    def exit(self, task):
        print "Task {} terminated".format(task.tid)
        del self.taskmap[task.tid]


def foo():
    for i in range(10):
        print "I'm foo"
        yield


def bar():
    for i in range(5):
        print "I'm bar"
        yield


if __name__ == '__main__':
    sched = Scheduler()
    sched.new(foo())
    sched.new(bar())
    sched.mainloop()
