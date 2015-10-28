# encoding=utf-8

import select
import types
from Queue import Queue


class Task(object):
    taskid = 0

    def __init__(self, target):
        Task.taskid += 1
        self.tid = Task.taskid
        self.target = target
        self.sendval = None
        self.stack = []

    def run(self):
        while True:
            try:
                result = self.target.send(self.sendval)
                if isinstance(result, SystemCall):
                    return result
                if isinstance(result, types.GeneratorType):
                    self.stack.append(self.target)
                    self.sendval = None
                    self.target = result
                else:
                    if not self.stack:
                        return
                    self.sendval = result
                    self.target = self.stack.pop()
            except StopIteration:
                if not self.stack:
                    raise
                print 'stopiteration:', self.target
                self.sendval = None
                self.target = self.stack.pop()

    def __str__(self):
        return 'Task {} {}'.format(self.tid, str(self.target))

    __repr__ = __str__


class Scheduler(object):
    def __init__(self):
        self.ready = Queue()
        self.taskmap = {}
        self.exit_waiting = {}  # tid: [task0, task1], tid为被等待退出Task的id, 列表为等待的Task
        self.read_waiting = {}
        self.write_waiting = {}

    # I/O wait
    def waitforread(self, task, fd):
        self.read_waiting[fd] = task

    def waitforwrite(self, task, fd):
        self.write_waiting[fd] = task

    def iopoll(self, timeout):
        if self.read_waiting or self.write_waiting:
            rlist, wlist, elist = select.select(self.read_waiting,
                                                self.write_waiting,
                                                [], timeout)
            for fd in rlist:
                self.schedule(self.read_waiting.pop(fd))
            for fd in wlist:
                self.schedule(self.write_waiting.pop(fd))

    def iotask(self):
        while True:
            if self.ready.empty():
                self.iopoll(None)
            else:
                self.iopoll(0)
            yield

    def new(self, target):
        newtask = Task(target)
        self.taskmap[newtask.tid] = newtask
        self.schedule(newtask)
        return newtask.tid

    def schedule(self, task):
        self.ready.put(task)

    def mainloop(self):
        self.new(self.iotask())
        while self.taskmap:
            task = self.ready.get()
            try:
                result = task.run()
                print task, result
                if isinstance(result, SystemCall):
                    result.task = task
                    result.sched = self
                    result.handle()
                    continue
            except StopIteration:
                print 'exit task {}'.format(str(task))
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


class SystemCall(object):
    def handle(self):
        pass


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


class ReadWait(SystemCall):
    def __init__(self, f):
        self.f = f

    def handle(self):
        fd = self.f.fileno()
        self.sched.waitforread(self.task, fd)


class WriteWait(SystemCall):
    def __init__(self, f):
        self.f = f

    def handle(self):
        fd = self.f.fileno()
        self.sched.waitforwrite(self.task, fd)


def Accept(sock):
    yield ReadWait(sock)
    yield sock.accept()


def Send(sock, buffer):
    while buffer:
        yield WriteWait(sock)
        len = sock.send(buffer)
        buffer = buffer[len:]


def Recv(sock, maxbytes):
    yield ReadWait(sock)
    yield sock.recv(maxbytes)
