#encoding=utf-8
class InterfaceMeta(type):
    def __new__(cls, name, parents, dct):
        if 'class_id' not in dct:
            dct['class_id'] = name.lower()

        if 'file' in dct:
            filename = dct['file']
            dct['file'] = open(filename, 'w')

        return super(InterfaceMeta, cls).__new__(cls, name, parents, dct)

#Interface = InterfaceMeta('Interface', (), dict(file='tmp.txt'))
class Interface(object):
    __metaclass__ = InterfaceMeta
    file = 'tmp.txt'
print(Interface.class_id)
print(Interface.file)
print type(Interface)

class UserInterface(Interface):
    file = 'foo.txt'

print(UserInterface.class_id)
print(UserInterface.file)

class DBInterfaceMeta(type):
    # we user __init__ rather than __new__ here because we want
    # to modify attributes of the class *after* they have been
    # created
    def __init__(cls, name, bases, dct):
        if not hasattr(cls, 'registry'):
            # this is the base class. Create an empty registry
            cls.registry = {}
        else:
            # this is a derived class. Add cls to the registry
            Interface_id = name.lower()
            cls.registry[Interface_id] = cls
        
        super(DBInterfaceMeta, cls).__init__(name, bases, dct)

class DBInterface(object):
    __metaclass__ = DBInterfaceMeta

print(DBInterface.registry)

class FirstInterface(DBInterface):
    pass
class SecondInterface(DBInterface):
    pass
class SecondInterfaceModified(SecondInterface):
    pass
print(DBInterface.registry)
