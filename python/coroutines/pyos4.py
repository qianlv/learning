# encoding=utf-8

from Queue import Queue
from pyos1 import Task


class SystemCall(object):
    def handle(self):
        pass


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
                result = task.run()
                if isinstance(result, SystemCall):
                    result.task = task
                    result.sched = self
                    result.handle()
                    continue
            except StopIteration:
                self.exit(task)
                continue
            self.schedule(task)

    def exit(self, task):
        print "Task {} terminated".format(task.tid)
        del self.taskmap[task.tid]


class GetTid(SystemCall):
    def handle(self):
        self.task.sendval = self.task.tid
        self.sched.schedule(self.task)


def foo():
    mytid = yield GetTid()
    for i in range(10):
        print "I'm foo", mytid
        yield


def bar():
    mytid = yield GetTid()
    for i in range(5):
        print "I'm bar", mytid
        yield

if __name__ == '__main__':
    sched = Scheduler()
    sched.new(foo())
    sched.new(bar())
    sched.mainloop()
