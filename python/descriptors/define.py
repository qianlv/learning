#!/usr/bin/env python
# -*- coding: utf-8 -*-

class SimpleDescriptors:
    
    def __init__(self):
        self._value = 'SimpleDescriptors'

    def __get__(self, instance, onwer):
        print ("Getting: {} {} {}".format(self._value, instance, onwer))
        return self._value

    def __set__(self,instance, value):
        print ("Setting: {} {}".format(value, instance))
        self._value = value

    def __delete__(self, instance):
        print ("Deleting: {} {}".format(self._value, instance))
        del self._name



class StaticMethod:
    """ A pure python staticmethod """

    def __init__(self, f):
        self.f = f

    def __get__(self, obj, objtype=None):
        print ("getting {} {} {}".format(self.f, obj, objtype))
        return self.f


class ClassMethod:
    """ A pure pythone classmethod """

    def __init__(self, f):
        print ("ClassMethod __init__: ", f)
        self.f = f

    def __get__(self, obj, klass=None):
        if klass is None:
            klass = type(obj)
        def newfunc(*args):
            return self.f(klass, *args)
        return newfunc


class Test:
    def f(x):
        print (x)
    f = StaticMethod(f)

if __name__ == '__main__':
    t = Test()
    t.f(1)
    Test.f(2)
