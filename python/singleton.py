# encoding=utf-8


class Singleton(object):
    @staticmethod
    def instance():
        if not hasattr(Singleton, '_instance'):
            Singleton._instance = Singleton()
        return Singleton._instance

    def input(self, a):
        print a

if __name__ == '__main__':
    t = Singleton.instance()
    tt = Singleton.instance()
    ttt = Singleton.instance()
    t.input('abv')
