#!/usr/bin/env python
# -*- coding: utf-8 -*-

import functools 
import inspect
from define import ClassMethod

#  def function_wrapper(wrapped):
    #  print ("function_wrapper: ", wrapped)
    #  @functools.wraps(wrapped)
    #  def _wrapper(*args, **kwargs):
        #  return wrapped(*args, **kwargs)
    #  return _wrapper



class object_proxy:

    def __init__(self, wrapped):
        self.wrapped = wrapped
        try:
            self.__name__ = wrapped.__name__
        except AttributeError:
            pass

    @property
    def __class__(self):
        return self.wrapped.__class__

    def __getattr__(self, name):
        return getattr(self.wrapped, name)

class bound_function_wrapper(object_proxy):
    def __init__(self, wrapped):
        super(bound_function_wrapper, self).__init__(wrapped)

    def __call__(self, *args, **kwargs):
        return self.wrapped(*args, **kwargs)


class function_wrapper(object_proxy):
    def __init__(self, wrapped):
        super(function_wrapper, self).__init__(wrapped)

    def __get__(self, instance, owner):
        wrapped = self.wrapped.__get__(instance, owner)
        return bound_function_wrapper(wrapped)

    def __call__(self, *args, **kwargs):
        return self.wrapped(*args, **kwargs)

class Class:
    @function_wrapper
    @ClassMethod
    def cmethod(cls):
        print ("---", cls)
    #  cmethod = function_wrapper(ClassMethod(cmethod)) # 等价方式


@function_wrapper
def function(arg1, arg2): pass


if __name__ == '__main__':
    Class.cmethod()
    print (inspect.getargspec(function))
    print (inspect.getsource(function))
    print ("---------------------------")
    print (inspect.getsource(Class.cmethod))
