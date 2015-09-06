# encoding=utf-8

class Account(object):
    """ The Account class,
    The amount is in dollars.
    """
    def __init__(self, rate):
        self.__amt = 0
        self.rate = rate

    @property
    def amount(self):
        return self.__amt

    @property
    def inr(self):
        return self.__amt * self.rate

    @amount.setter
    def amount(self, value):
        if value < 0:
            print "Sorry, no negative amount in the account."
            return 
        self.__amt = value

if __name__ == '__main__':
    acc = Account(rate=61)
    acc.amount = 20
    print acc.amount
    print acc.inr
    acc.amount = -100
    print acc.amount

