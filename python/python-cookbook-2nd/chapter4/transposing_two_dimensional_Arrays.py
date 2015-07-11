#!/usr/bin/pytnon
#encoding=utf-8

# 旋转二维矩阵, 行变为列， 列变为行
twoDimensional = [[1,2,3,4], [5, 6,7,8], [9, 10, 11, 12]]
newDimensional = [ [row[col] for row in twoDimensional] for col in range(len(twoDimensional[0])) ] 
print newDimensional

import itertools
print map(list, itertools.izip(*twoDimensional))

newDimensional = itertools.izip(*twoDimensional)
for row in newDimensional:
    for col in row:
        print col,
    print 
