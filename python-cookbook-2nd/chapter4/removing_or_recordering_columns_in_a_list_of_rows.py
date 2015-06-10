#!/usr/bin/python
#encoding=utf-8

# 重新排列或删除列表中某些列

listOfRows = [[1, 2, 3, 4], [2, 3, 4, 5], [3, 4, 5, 6]]
newList = [ [ row[0], row[2], row[1] ] for row in listOfRows ]
# 用辅助序列
newList = [ [ row[ci] for ci in (0, 2, 1) ] for row in listOfRows ]
print newList

# 修改现有的列表

listOfRows[:] = [ [ row[0], row[2], row[1] ] for row in listOfRows ]
print listOfRows

# 辅助列表方法辅助
def pick_and_recorder_columns(listOfRows, columns_index):
    return [ [ row[ci] for ci in columns_index ] for row in listOfRows ]

columns = 2, 1, 0
newList = pick_and_recorder_columns(listOfRows, columns)
print newList


