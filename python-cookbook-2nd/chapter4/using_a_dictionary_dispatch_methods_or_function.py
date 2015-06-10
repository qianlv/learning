#!/usr/bin/python
#encoding=utf-8

animals = []
number_of_felines = 0
def deal_with_a_cat():
    global number_of_felines
    print 'cat'
    animals.append('cat')
    number_of_felines += 1
def deal_with_a_dog():
    print 'dog'
    animals.append('dog')
def deal_with_a_bear():
    print 'bear'
    animals.append('bear')

tokenDict = {
    "cat" : deal_with_a_cat,
    "dog" : deal_with_a_dog,
    "bear" : deal_with_a_bear,
    }

words = [ "cat", "dog", "cat",  "bear" ]

for word in words:
    tokenDict[word]()

nf = number_of_felines

print 'we met %d felines%s' % (nf, 's'[nf == 1:])
print 'the animals we met were:', ' '.join(animals)
