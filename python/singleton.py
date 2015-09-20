# encoding=utf-8

import threading


class Singleton(object):
    @staticmethod
    def instance():
        if not hasattr(Singleton, '_instance'):
            Singleton._instance = Singleton()
        return Singleton._instance

    def input(self, a):
        print a


# use metaclass
class MSingleton(type):
    _instances = {}

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = \
                super(MSingleton, cls).__call__(*args, **kwargs)
        else:
            cls._instances[cls].__init__(*args, **kwargs)
        return cls._instances[cls]


class Logger(object):
    __metaclass__ = MSingleton

    def __init__(self, name, version):
        print '__init__'
        self.name = name
        self.version = version

    def log(self, value):
        print self.name, self.version, value


# use Modules
# 模块只会被import一次
class Modules(object):
    def __init__(self, name, version):
        self.name = name
        self.version = version


some_global_variable = Modules('name', 'version')


# threading safe
class SingletonMixin(object):
    __singleton_lock = threading.Lock()
    __singleton_instance = None

    @classmethod
    def instance(cls):
        if not cls.__singleton_instance:
            with cls.__singleton_lock:
                # 下面这个判断目的是: 在多个线程通过上面的第一个测试时,
                # 其中一个实例化后, 不会有其他线程实例化
                if not cls.__singleton_instance:
                    cls.__singleton_instance = cls()
        return cls.__singleton_instance


class TestA(SingletonMixin):
    pass


class TestB(SingletonMixin):
    pass

if __name__ == '__main__':
    t = Logger('test_logger', 'v0.1')
    tt = Logger('logger', 'v0.2')
    t.log('Hello')
    tt.log('World')

    a, a2 = TestA.instance(), TestA.instance()
    b, b2 = TestB.instance(), TestB.instance()
    assert a is a2
    assert b is b2
    assert a is not b
    print 'a: %s\na2: %s' % (a, a2)
    print 'b: %s\nb2: %s' % (b, b2)
