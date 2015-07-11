#!/usr/bin/python
#encoding=utf-8

# 使每行空格相同
def reindent(s, numSpace):
    leading_space = numSpace * ' '
    lines = [ leading_space + line.strip() for line in s.splitlines() ]
    return "\n".join(lines)

# 保持每行相等空格，然后整体添加空格
def addSpace(s, numAdd):
    white = numAdd * ' '
    # s.join(list) list之间添加s连接
    # 所以需要开头需要添加一个white
    # splitlines() 当传入 True 参数时它保留每行末尾的换行
    print s.splitlines(True)
    return  white + white.join(s.splitlines(True))

def numSpace(s):
    return [ len(line) - len(line.strip()) for line in s.splitlines() ]

# 保持每行相等空格，然后整体删除空格
def delSpace(s, numDel):
    if numDel > min(numSpace(s)):
        raise ValueError, "removing more spaces than there are"
    return '\n'.join([ line[numDel:] for line in s.splitlines() ])

# 保持每行相等空格，然后整体删除能够删除的空格
def unIndentBlock(s):
    return delSpace(s, min(numSpace(s)))
if __name__ == '__main__':
    lines = """  one
        two
          three"""
    print lines
    print reindent(lines, 4)
    print addSpace(lines, 4)
    print delSpace(reindent(lines, 2), 2)
    print unIndentBlock(lines)
