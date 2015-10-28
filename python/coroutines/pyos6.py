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
        self.exit_waiting = {}  # tid: [task0, task1], tid为被等待退出Task的id, 列表为等待的Task

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
        for task in self.exit_waiting.pop(task.tid, []):
            self.schedule(task)

    def waitforexit(self, task, waittid):
        if waittid in self.taskmap:
            self.exit_waiting.setdefault(waittid, []).append(task)
            return True
        else:
            return False


class GetTid(SystemCall):
    def handle(self):
        self.task.sendval = self.task.tid
        self.sched.schedule(self.task)


class NewTask(SystemCall):
    def __init__(self, target):
        self.target = target

    def handle(self):
        tid = self.sched.new(self.target)
        # print 'New Task', tid, self.task
        self.task.sendval = tid
        self.sched.schedule(self.task)


class KillTask(SystemCall):
    def __init__(self, tid):
        self.tid = tid

    def handle(self):
        task = self.sched.taskmap.get(self.tid, None)
        if task:
            task.target.close()
            self.task.sendall = True
        else:
            self.task.sendall = False
        self.sched.schedule(self.task)


class WaitTask(SystemCall):
    def __init__(self, tid):
        self.tid = tid

    def handle(self):
        result = self.sched.waitforexit(self.task, self.tid)
        self.task.sendval = result
        # if waiting for non-existent task.
        # return immediately without waiting.
        if not result:
            self.sched.schedule(self.task)


def foo():
    mytid = yield GetTid()
    while True:
        print "I'm foo", mytid
        yield


def main():
    child = yield NewTask(foo())
    print 'Wait for child'
    yield WaitTask(child)
    print 'child done'

if __name__ == '__main__':
    sched = Scheduler()
    sched.new(main())
    sched.mainloop()
