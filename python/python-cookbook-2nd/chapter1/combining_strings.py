#/usr/bin/python
#encoding=utf-8

pieces = ['one', 'two', 'three', 'four']

# join 性能好于 +, += 建议使用join
largeString1 = ''.join(pieces)

small1 = 'one'
small2 = 'two'
small3 = 'three'

largeString2 = '%s%s something %s yet more' % (small1, small2, small3)

largeString3 = small1 + small2 + ' something ' + small3 + ' yet more'

largeString4 = ''
for piece in pieces:
    largeString4 += piece

import operator
largeString5 = reduce(operator.add, pieces, '')

print largeString1
print largeString2
print largeString3
print largeString4
print largeString5

print '%.2lf is float' % 45.3454



